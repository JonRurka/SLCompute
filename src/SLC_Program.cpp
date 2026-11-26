#include "SLC_Program.h"
#include "Compute/dynamic_compute.h"
#include "Compute/InterfaceIncludes_private.h"
#include "Resources/binary_resources.hpp"
#include "SLC_func_ids.h"
#include "SLC_Structures.h"
#include "SLC_ComputePool_private.h"

//#include "src/resources/shader_bin.hpp"

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>

#include "SLC_ComputePool_private.h"
#include "Logger.h"

#define VEC4_SIZE (sizeof(float) * 4)

using namespace SLCompute;
using namespace DynamicCompute::Compute;
using namespace SLCompute::Resources;

std::vector<SL_Device_Info> ProgramController::Get_Devices() {
	std::vector<SL_Device_Info> res;
	std::vector<Vulkan_Device_Info> devices = ComputeInterface::GetSupportedDevices_Vulkan();
	res.reserve(devices.size());

	for (auto& dvc : devices) {
		Logger::LogDebug(LOG_LOC, "\tFound: %s (%s)", dvc.Name, dvc.GetTypeName().c_str());
		SL_Device_Info d{};

		d.id = dvc.Device_ID;
		d.device_class = static_cast<SL_Device_Class>(dvc.Type);
		strcpy(d.name, dvc.Name);

		res.push_back(d);
	}

	std::sort(res.begin(), res.end(), [](const SL_Device_Info& a, const SL_Device_Info& b) {
		return static_cast<uint32_t>(a.device_class) > static_cast<uint32_t>(b.device_class);
	});

	return res;
}

ProgramController::ProgramInstance ProgramController::Create(ProgramSettings settings) {
	static std::mt19937_64 rng(std::random_device{}());

	ProgramInstance id;
	do {
		id = rng();
	} while (m_program_instances.count(id));

	Logger::LogDebug(LOG_LOC, "Create Program Instance %d", id);
	m_program_instances[id] = std::make_unique<ProgramController>(id, settings);
	return id;
}

PoolInstance ProgramController::CreatePool(ProgramInstance p, PoolSettings settings) {
	SL_ASSERT(m_program_instances.count(p) > 0, "Program not found; Unable to create pool.");
	return m_program_instances[p]->create_pool(settings);
}

PoolInstance ProgramController::create_pool(PoolSettings settings) {
	unsigned int pool_id = pool_num++;
	PoolInstance inst = std::make_shared<ComputePool_private>(m_prog_inst, pool_id, settings.type, settings.x_size, settings.y_size, settings.z_size);
	m_pools[pool_id] = inst;
	if (inst->Pool_Type() == PoolType::Dynamic) {
		Logger::LogDebug(LOG_LOC, "Create a dynamic pool.");
	}
	else if (inst->Pool_Type() == PoolType::Static) {
		Logger::LogDebug(LOG_LOC, "Create a static pool.");
		SL_ASSERT(m_static_bind_idx < NUM_POOL_BIND_BUFFERS, "Exceeded maximum static pool count.");
		inst->SetStaticPoolID(m_static_bind_idx++);
		m_static_pools.push_back(inst);
	}
	return inst;
}

void ProgramController::Start(ProgramInstance p) {
	SL_ASSERT(m_program_instances.count(p) > 0, "Program not found; Unable to start program.");
	return m_program_instances[p]->start();
}

void ProgramController::start() {
	Logger::LogDebug(LOG_LOC, "Program %d: Starting program controller.", m_prog_inst);

	initialize_buffers();
	configure_workgroup_sizes();
	Finalize();
}

IComputeBuffer* ProgramController::CreateBuffer(ProgramInstance p, size_t elements, size_t stride) {
	SL_ASSERT(m_program_instances.count(p) > 0, "Program not found; Unable to create buffer.");
	return m_program_instances[p]->create_buffer(elements, stride);
}

IComputeBuffer* ProgramController::create_buffer(size_t elements, size_t stride) {
	SL_ASSERT(elements > 0 && stride > 0, "Invalid Create Buffer Request.");
	return Get_Controller()->NewReadWriteBuffer(elements, stride);
}

ProgramController& ProgramController::Get_ProgramController(ProgramInstance p) {
	SL_ASSERT(m_program_instances.count(p) > 0, "Program not found.");
	return *m_program_instances[p];
}

void ProgramController::Execute(ProgramInstance p, program_id p_id, func_id f_id, SL_Strided_Buffer res, const std::vector<SL_Strided_Buffer>& params)
{
	SL_ASSERT(m_program_instances.count(p) > 0, "Program not found.");
	m_program_instances[p]->Execute(p_id, f_id, res, params);
}

void ProgramController::DisposePool(PoolInstance pool_inst) {
	SL_ASSERT(pool_inst != nullptr, "Pool is null.");
	ProgramInstance p_inst = pool_inst->ProgramInstance();
	SL_ASSERT(m_program_instances.count(p_inst) > 0, "Program not found.");
	m_program_instances[p_inst]->Dispose_Pool(pool_inst);
}

void ProgramController::Dispose_Pool(PoolInstance pool_inst) {
	SL_ASSERT(pool_inst != nullptr, "Pool is null.");
	SL_ASSERT(pool_inst->Pool_Type() == PoolType::Dynamic, "Non-dynamic pool types must be disposed by the program controller.");
	unsigned int id = pool_inst->PoolID();
	pool_inst->Dispose();
	m_pools.erase(id);
}

void ProgramController::DisposeProgram(ProgramInstance p) {
	SL_ASSERT(m_program_instances.count(p) > 0, "Program not found.");
	m_program_instances[p]->Dispose();
}

void ProgramController::Dispose() {
	for (auto& [key, val] : m_programs) {
		Logger::LogDebug(LOG_LOC, "\tDispose: %s.", key.c_str());
		SL_ASSERT(val != nullptr, "Compute program null.");
		val->Dispose();
		delete val;
	}

	m_programs_list.clear();
	m_programs.clear();

	for (auto& [key, val] : m_pools) {
		val->Dispose();
	}
	m_pools.clear();

	control_in->Dispose();
	delete control_in;

	settings_buffer->Dispose();
	delete settings_buffer;

	m_result_buffer->Dispose();
	delete m_result_buffer;

	for (auto& pb : m_param_buffers) {
		pb->Dispose();
		delete pb;
	}
	m_param_buffers.clear();

	m_static_pools.clear();

	m_dummy_static_buffer->Dispose();
	delete m_dummy_static_buffer;
}

ProgramController::ProgramController(ProgramInstance id, ProgramSettings settings) : m_prog_inst(id), m_settings(settings)
{
	Initialize();
}

void ProgramController::AddBuffer(int bind, IComputeBuffer* buffer)
{
	SL_ASSERT(initialized, "Program not initialized.");
	SL_ASSERT(!finalized, "Program already finalized.");

	IComputeProgram::BindIndex ind{};
	ind.GlobalIndex = bind;

	for (const auto& pair : m_programs)
		pair.second->KernelSetBuffer(kernel_name, buffer, ind);
}

void ProgramController::AddBuffer(std::string program_name, int bind, IComputeBuffer* buffer)
{
	SL_ASSERT(initialized, "Program not initialized.");
	SL_ASSERT(!finalized, "Program already finalized.");
	SL_ASSERT(m_programs.count(program_name) > 0, "Compute Program not found.");
	SL_ASSERT(m_programs[program_name] != nullptr, "Compute Program null");

	Logger::LogDebug(LOG_LOC, "ProgramInstance %d: Bind compute buffer to %d on program %s.",
		m_prog_inst, bind, program_name.c_str());

	IComputeProgram::BindIndex ind{};
	ind.GlobalIndex = bind;

	m_programs[program_name]->KernelSetBuffer(kernel_name, buffer, ind);
}

void ProgramController::configure_workgroup_sizes()
{
	for (auto& [name, prog] : m_programs) {
		prog->KernelSetWorkGroupSize(kernel_name, glm::uvec3(64, 1, 1));
	}
}

void ProgramController::SetProgramWorkGroupSize(std::string program_name, glm::uvec3 size)
{
	SL_ASSERT(m_programs.count(program_name) > 0, "Program not found.");
	m_programs[program_name]->KernelSetWorkGroupSize(kernel_name, size);
}

void ProgramController::Finalize()
{
	Logger::LogDebug(LOG_LOC, "Program %d: Finalizing programs.", m_prog_inst);

	SL_ASSERT(initialized, "Program not initialized.");
	SL_ASSERT(!finalized, "Program already finalized.");

	for (auto& [key, val] : m_programs) {
		Logger::LogDebug(LOG_LOC, "\tFinalize: %s.", key.c_str());
		SL_ASSERT(val != nullptr, "Program null.");
		val->FinishBuild();
	}

	finalized = true;
	Logger::LogDebug(LOG_LOC, "Program %d: Finalized program.", m_prog_inst);
}

void ProgramController::Execute(program_id p_id, func_id f_id, SL_Strided_Buffer res, const std::vector<SL_Strided_Buffer>& params)
{
	SL_ASSERT(initialized, "Program not initialized.");
	SL_ASSERT(finalized, "Program not finalized.");

	SL_ASSERT(res != nullptr, "Result ref null.");


	ComputePool_private* res_comp_pool = static_cast<ComputePool_private*>(res->Pool());
	SL_ASSERT(res_comp_pool != nullptr, "Result ComputePool null.");
	const size_t num_elements = res_comp_pool->Element_Size();

	Logger::LogDebug(LOG_LOC, "Executing program %i on pool %i for %i elements.",
		m_prog_inst, res_comp_pool->PoolID(), num_elements);

	std::vector<glm::uvec4> param_control;
	param_control.reserve(params.size() + 1);


	param_control.push_back(res_comp_pool->Get_Control_Vec(res->Handle()));

	int pi = 0;
	for (auto& p : params) {
		SL_ASSERT(p != nullptr, "parameter null.");

		ComputePool_private* p_comp_pool = static_cast<ComputePool_private*>(p->Pool());

		SL_ASSERT(p_comp_pool != nullptr, "Parameter ComputePool null.");
		SL_ASSERT(p_comp_pool->ProgramInstance() == m_prog_inst, "All buffer pools must belong to the same program.");
		SL_ASSERT(p_comp_pool->Element_Size() == num_elements, "All buffer pools must be the same size.");

		param_control.push_back(p_comp_pool->Get_Control_Vec(p->Handle()));

		if (p_comp_pool->Pool_Type() == PoolType::Dynamic) {
			IComputeBuffer* p_buffer = p_comp_pool->GetComputeBuffer(p);
			p_buffer->CopyTo(m_param_buffers[pi]);
		}

		pi++;
	}


	Set_Settings(f_id, num_elements);
	Set_Control(param_control);

	Execute(p_id, num_elements, 1, 1);

	if (res_comp_pool->Pool_Type() == PoolType::Dynamic) {
		Logger::LogDebug(LOG_LOC, "Sync to res-buffer");
		IComputeBuffer* res_buffer = res_comp_pool->GetComputeBuffer(res);
		m_result_buffer->CopyTo(res_buffer, num_elements * res->Stride() * sizeof(float));
	}
}

void ProgramController::Execute(std::string p_name, int size_x, int size_y, int size_z)
{
	SL_ASSERT(initialized, "Program not initialized.");
	SL_ASSERT(finalized, "Program not finalized.");

	SL_ASSERT(m_programs.count(p_name) > 0, "Program does not exist.");

	m_programs[p_name]->RunKernel(kernel_name, size_x, size_y, size_z);
}

void ProgramController::Execute(program_id p_id, int size_x, int size_y, int size_z)
{
	SL_ASSERT(initialized, "Program not initialized.");
	SL_ASSERT(finalized, "Program not finalized.");

	SL_ASSERT(m_programs_list.size() > p_id, "Program id invalid.");
	SL_ASSERT(m_programs_list[p_id], "Program does not exist.");

	m_programs_list[p_id]->RunKernel(kernel_name, size_x, size_y, size_z);
}

void ProgramController::Enable(Programs p) {
	m_activate_programs.insert(p);
}

void ProgramController::Initialize()
{
	SL_ASSERT(!initialized, "Program not initialized.");

	Logger::LogInfo(LOG_LOC, "Program %d: Initialize", m_prog_inst);

	SL_Float_Type::Enable();
	Logger::LogDebug(LOG_LOC, "Program %d: Float datatype enabled.", m_prog_inst);

	Logger::LogDebug(LOG_LOC, "Program %d: Utilities compute program enabled.", m_prog_inst);
	Enable(Programs::UTILITIES);

	m_static_pools.reserve(NUM_POOL_BIND_BUFFERS);

	std::vector<SL_Device_Info> sl_devices = Get_Devices(); // sorted highest-class first
	SL_ASSERT(!sl_devices.empty(), "No compute devices found.");

	uint32_t target_id = m_settings.Device_ID;
	if (target_id == UINT32_MAX)
		target_id = sl_devices[0].id;

	std::vector<Vulkan_Device_Info> vk_devices = ComputeInterface::GetSupportedDevices_Vulkan();
	Logger::LogDebug(LOG_LOC, "Program %d: Get Compute Devices: %d", m_prog_inst, vk_devices.size());
	for (const auto& dvc : vk_devices)
		Logger::LogDebug(LOG_LOC, "\tFound: %s", dvc.Name);

	auto it = std::find_if(vk_devices.begin(), vk_devices.end(),
		[&](const Vulkan_Device_Info& d){ return d.Device_ID == target_id; });
	SL_ASSERT(it != vk_devices.end(), "Selected device not found.");
	Vulkan_Device_Info selected_device = *it;
	Logger::LogDebug(LOG_LOC, "Program %d: Selected compute device: %s", m_prog_inst, selected_device.Name);
	m_controllerInfo.device = &selected_device;

	m_controller = ComputeInterface::GetComputeController(ComputeInterface::VULKAN, m_controllerInfo);
	Logger::LogDebug(LOG_LOC, "Program %d: Create Program Controller.", m_prog_inst);

	//SLC::Resources::complex().size();

	std::vector<uint8_t> data;

	Shader_Binaries::Init();

	std::vector<std::string> spv_programs_names = Shader_Binaries::Get_SPV_Programs();
	Logger::LogDebug(LOG_LOC, "Program %d: Get SL Program list: %d.", m_prog_inst, spv_programs_names.size());
	SL_ASSERT(!spv_programs_names.empty(), "Program list is empty.");

	m_programs_list.resize(spv_programs_names.size());

	for (const std::string& name : spv_programs_names) {
		CreateProgram(name, Shader_Binaries::Get_SPV_Binary(name));
	}

	m_programs_list[PROGRAM_ID_UTILITIES] = m_programs[PROGRAM_NAME_UTILITIES];
	SL_ASSERT(!m_programs.empty(), "No programs created.");

	initialized = true;
}

void ProgramController::CreateProgram(std::string name, std::vector<uint8_t> data)
{
	if (!m_program_name_map.contains_value(name)) {
		Logger::LogDebug(LOG_LOC, "Program %d: Program not found: %s.", m_prog_inst, name.c_str());
		return;
	}
	Programs program = m_program_name_map.get_key(name);
	int p_id = static_cast<int>(program);

	if (!m_activate_programs.count(program)) {
		Logger::LogDebug(LOG_LOC, "Program %d: Program not Included: %s.", m_prog_inst, name.c_str());
		return;
	}

	Logger::LogDebug(LOG_LOC, "Program %d: Program included: %s.", m_prog_inst, name.c_str());

	Logger::LogDebug(LOG_LOC, "\tGet Program Info.");
	IComputeProgram::ProgramInfo program_info = IComputeProgram::ProgramInfo(name, IComputeProgram::FileType::Binary_Data);
	program_info.AddKernel(kernel_name);
	program_info.SetData(data);

	Logger::LogDebug(LOG_LOC, "\tCreate CL Program.");
	IComputeProgram* m_program = m_controller->AddProgram(program_info);
	m_program->Build();
	Logger::LogDebug(LOG_LOC, "\tBuild CL Program.");

	m_programs[name] = m_program;
	m_programs_list[p_id] = m_program;
}

void ProgramController::initialize_buffers()
{
	Logger::LogDebug(LOG_LOC, "Program %d: Initializing buffers.", m_prog_inst);

	size_t elements = 0;
	const size_t max_stride = SL_Strided_Buffer_Type::Max_Stride();
	int float_elem_size = 1;
	int complex_elem_size = 1;

	for(const auto& [id, pool] : m_pools) {
		elements = glm::max(elements, pool->Element_Size());
	}

	Logger::LogDebug(LOG_LOC, "Program %d: Create control buffers", m_prog_inst);
	control_in = Get_Controller()->NewReadBuffer(MAX_FUNCTION_PARAMS + 1,  sizeof(float) * 4);
	settings_buffer = Get_Controller()->NewReadBuffer(1, sizeof(float) * 4);

	Logger::LogDebug(LOG_LOC, "Program %d: Create result and param buffers", m_prog_inst);
	m_result_buffer = Get_Controller()->NewReadWriteBuffer(elements * max_stride, sizeof(float));
	m_param_buffers.reserve(MAX_PARAMS);
	for (int i = 0; i < MAX_PARAMS; i++) {
		m_param_buffers.push_back(Get_Controller()->NewReadWriteBuffer(elements * max_stride, sizeof(float)));
	}

	/*Logger::LogDebug(LOG_LOC, "Program %d: Bind utility program buffers.", m_prog_inst);
	AddBuffer(PROGRAM_NAME_UTILITIES, 0, control_in);
	AddBuffer(PROGRAM_NAME_UTILITIES, 1, settings_buffer);
	AddBuffer(PROGRAM_NAME_UTILITIES, 2, m_result_buffer);
	for (int i = 0; i < MAX_PARAMS; i++) {
		AddBuffer(PROGRAM_NAME_UTILITIES, i + 3, m_param_buffers[i]);
	}*/

	m_dummy_static_buffer = Get_Controller()->NewReadWriteBuffer(1, sizeof(float));


	Logger::LogDebug(LOG_LOC, "Program %d: Rebuild %d static pools", m_prog_inst, m_static_bind_idx);
	for (int i = 0; i < m_static_bind_idx; i++) {
		SL_ASSERT(m_static_pools[i] != nullptr, "Static pool null!");
		Logger::LogDebug(LOG_LOC, "\tRebuild static pool %d", i);
		m_static_pools[i]->Rebuild();
	}


	for (auto& [name, prog] : m_programs) {
		Logger::LogDebug(LOG_LOC, "Program %d: Bind %s program buffers.", m_prog_inst, name.c_str());
		AddBuffer(name, 0, settings_buffer);
		AddBuffer(name, 1, control_in);
		AddBuffer(name, 2, m_result_buffer);

		Logger::LogDebug(LOG_LOC, "Program %d: Bind %s dynamic buffers.", m_prog_inst, name.c_str());
		for (int i = 0; i < MAX_PARAMS; i++) {
			AddBuffer(name, i + PARAM_BIND_START, m_param_buffers[i]);
		}

		Logger::LogDebug(LOG_LOC, "Program %d: Bind %s static pool buffers.", m_prog_inst, name.c_str());
		for (int i = 0; i < NUM_POOL_BIND_BUFFERS; i++) {
			if (i < m_static_bind_idx) {
				SL_ASSERT(m_static_pools[i] != nullptr, "Static pool null!");
				SL_ASSERT(m_static_pools[i]->GetStaticComputeBuffer() != nullptr, "Static pool buffer null!");
				AddBuffer(name, i + POOL_BUFF_BIND_START, m_static_pools[i]->GetStaticComputeBuffer());
			}
			else {
				AddBuffer(name, i + POOL_BUFF_BIND_START, m_dummy_static_buffer);
			}
		}
	}


	//src_float_stage_buffer = Get_Controller()->NewReadBuffer(elements, sizeof(float));
	//src_complex_stage_buffer = Get_Controller()->NewReadBuffer(elements * 2, sizeof(float));

	//buffer_float = Get_Controller()->NewReadWriteBuffer(elements * float_elem_size, sizeof(float));
	//buffer_complex = Get_Controller()->NewReadWriteBuffer(elements * complex_elem_size * 2, sizeof(float));




	/*AddBuffer(PROGRAM_NAME_UTILITIES, 0, control_in);
	AddBuffer(PROGRAM_NAME_UTILITIES, 1, settings_buffer);
	AddBuffer(PROGRAM_NAME_UTILITIES, 2, src_complex_stage_buffer);
	AddBuffer(PROGRAM_NAME_UTILITIES, 3, src_float_stage_buffer);
	AddBuffer(PROGRAM_NAME_UTILITIES, 4, buffer_complex);
	AddBuffer(PROGRAM_NAME_UTILITIES, 5, buffer_float);

	AddBuffer(PROGRAM_NAME_COMPLEX, 0, settings_buffer);
	AddBuffer(PROGRAM_NAME_COMPLEX, 1, control_in);
	AddBuffer(PROGRAM_NAME_COMPLEX, 2, buffer_complex);
	AddBuffer(PROGRAM_NAME_COMPLEX, 3, buffer_float);
	AddBuffer(PROGRAM_NAME_COMPLEX, 4, buffer_complex);
	AddBuffer(PROGRAM_NAME_COMPLEX, 5, buffer_float);*/

}

void ProgramController::Set_Settings(func_id function_id, int elements)
{
	glm::uvec4 settings = get_settings(function_id, elements);
	settings_buffer->SetData(&settings, 1 * VEC4_SIZE);
}

void ProgramController::Set_Control(std::vector<glm::uvec4>& settings)
{
	SL_ASSERT(settings.size() <= (MAX_FUNCTION_PARAMS + 1), "Control buffer size exceeds MAX_FUNCTION_PARAMS and result buffer.");
	control_in->SetData(static_cast<glm::uvec4*>(settings.data()), settings.size() * VEC4_SIZE);
}