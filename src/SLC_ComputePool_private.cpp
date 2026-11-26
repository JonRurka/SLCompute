#include "SLC_ComputePool_private.h"
#include "Compute/stdafx.h"
#include "SLC_func_ids.h"
#include "Logger.h"

#define VEC4_SIZE (sizeof(float) * 4)

using namespace SLCompute;

ComputePool_private::ComputePool_private(size_t progInst, unsigned int pool_num, PoolType type, size_t sx,  size_t sy,  size_t sz)
{
	Logger::LogDebug(LOG_LOC, "Create Compute Pool %d for program %d", pool_num, progInst);
	m_prog_inst = progInst;
	m_pool_id = pool_num;
	m_elements = sx;// * sy * sz;
	m_type = type;
	Init();
}

void ComputePool_private::Init()
{
	if (m_type == PoolType::Dynamic) {

	}
	else if (m_type == PoolType::Static) {

	}
}

SL_Float ComputePool_private::Get_Float()
{
	Logger::LogDebug(LOG_LOC, "Create Float Buffer");
	SL_Float res = new SL_Float_struct();
	sl_buffer b{};

	res->pool = this;
	res->source = nullptr;

	if (m_type == PoolType::Dynamic) {

		res->id = 0;

		Logger::LogDebug(LOG_LOC, "\tCreate Float Buffer Compute Buffer");
		b.comp_buffer = ProgramController::CreateBuffer(m_prog_inst, m_elements * res->Stride(), sizeof(float));
		//b.comp_buffer->SetData(res->source);
	}
	else if (m_type == PoolType::Static) {
		res->id = m_static_buffer_idx;
		m_static_buffer_idx += m_elements * res->Stride();
	}

	b.info_buffer = res;
	m_pool_buffers[res->Handle()] = b;

	return res;
}

SL_Float ComputePool_private::Get_Float(std::vector<float> data)
{
	Logger::LogDebug(LOG_LOC, "Create Float Buffer");
	float* src_data = new float[data.size()];
	memcpy(src_data, data.data(), data.size() * sizeof(float));

	SL_Float res = new SL_Float_struct();
	sl_buffer b{};

	res->pool = this;
	res->source = src_data;

	if (m_type == PoolType::Dynamic) {

		res->id = 0;

		Logger::LogDebug(LOG_LOC, "\tCreate Float Buffer Compute Buffer");
		b.comp_buffer = ProgramController::CreateBuffer(m_prog_inst, m_elements * res->Stride(), sizeof(float));
		b.comp_buffer->SetData(res->source);
	}
	else if (m_type == PoolType::Static) {
		res->id = m_static_buffer_idx;
		m_static_buffer_idx += m_elements * res->Stride();
	}


	b.info_buffer = res;
	m_pool_buffers[res->Handle()] = b;
	return res;
}

SL_Complex ComputePool_private::Get_Complex()
{
	Logger::LogDebug(LOG_LOC, "\tCreate Complex Buffer");
	SL_Complex res = new SL_Complex_struct();
	sl_buffer b{};

	res->pool = this;
	res->source = nullptr;

	if (m_type == PoolType::Dynamic) {
		res->id = 0;

		Logger::LogDebug(LOG_LOC, "\tCreate Complex Buffer Compute Buffer");
		b.comp_buffer = ProgramController::CreateBuffer(m_prog_inst, m_elements * res->Stride(), sizeof(float));
		//b.comp_buffer->SetData(res->source);
	}
	else if (m_type == PoolType::Static) {
		res->id = m_static_buffer_idx;
		m_static_buffer_idx += m_elements * res->Stride();
	}

	b.info_buffer = res;
	m_pool_buffers[res->Handle()] = b;
	return res;
}

SL_Complex ComputePool_private::Get_Complex(std::vector<Complex> data)
{

	Complex* src_data = new Complex[data.size()];
	memcpy(src_data, data.data(), data.size() * sizeof(Complex));
	SL_Complex res = new SL_Complex_struct();
	sl_buffer b{};

	res->pool = this;
	res->source = src_data;

	if (m_type == PoolType::Dynamic) {
		res->id = 0;

		Logger::LogDebug(LOG_LOC, "\tCreate Complex Buffer - Pool: %d, Elements: %d, Stride: %d",
			m_pool_id, m_elements, res->Stride());
		Logger::LogDebug(LOG_LOC, "\tCreate Complex Buffer Compute Buffer");
		b.comp_buffer = ProgramController::CreateBuffer(m_prog_inst, m_elements * res->Stride(), sizeof(float));
		Logger::LogDebug(LOG_LOC, "\tCreate Complex Buffer Set Data");
		b.comp_buffer->SetData(res->source);
	}
	else if (m_type == PoolType::Static) {
		res->id = m_static_buffer_idx;
		m_static_buffer_idx += m_elements * res->Stride();
	}

	b.info_buffer = res;
	m_pool_buffers[res->Handle()] = b;

	Logger::LogDebug(LOG_LOC, "\tCreate Complex Buffer Finish");

	return res;
}

IComputeBuffer* ComputePool_private::GetComputeBuffer(BufferInstance src) {
	SL_ASSERT(m_type == PoolType::Dynamic, "GetComputeBuffer(BufferInstance) only supported on Dynamic Pools.");
	return m_pool_buffers[src].comp_buffer;
}

IComputeBuffer* ComputePool_private::GetComputeBuffer(SL_Strided_Buffer src) {
	return GetComputeBuffer(src->Handle());
}

IComputeBuffer* ComputePool_private::GetStaticComputeBuffer() {
	SL_ASSERT(m_type == PoolType::Static, "GetStaticComputeBuffer() only supported on Static Pools.");
	SL_ASSERT(m_static_buffer != nullptr, "m_static_buffer is null!");
	return m_static_buffer;
}

void ComputePool_private::Destroy_Buffer(SL_Strided_Buffer buffer) {
	Destroy_Buffer(buffer->Handle());
}

void ComputePool_private::Destroy_Buffer(BufferInstance buffer) {
	m_pool_buffers[buffer].comp_buffer->Dispose();

	if (m_type == PoolType::Dynamic) {
		delete m_pool_buffers[buffer].comp_buffer;
	}
	else if (m_type == PoolType::Static) {
		// todo: what happens if static buffer delete is attempted?
	}

	delete m_pool_buffers[buffer].info_buffer;
	m_pool_buffers.erase(buffer);
}

void ComputePool_private::Test_Buffer_Engine(size_t offset, size_t elem) {

	/*SL_ASSERT(elem > 0, "Test element size is 0.");

	std::vector<float> test_float_buf;
	test_float_buf.reserve(elem);
	for (int i = 0; i < elem; i++) {
		test_float_buf.push_back(i + 1);
	}
	Logger::LogDebug(LOG_LOC, "Creating test compute buffer.");
	IComputeBuffer* test_buf = ProgramController::CreateBuffer(m_prog_inst, elem, sizeof(float));

	Logger::LogDebug(LOG_LOC, "Setting test data.");
	test_buf->SetData(test_float_buf.data());

	//std::vector<float> test_float_buf_res;
	//test_float_buf.resize(elem);
	float* test_float_buf_res = new float[elem];

	Logger::LogDebug(LOG_LOC, "Loading test data.");
	test_buf->GetData(test_float_buf_res);

	Logger::LogDebug(LOG_LOC, "Printing results:");
	for (int i = 0; i < elem; i++) {
		printf("Val %d: %f\n", i, test_float_buf_res[i]);
	}

	Logger::LogDebug(LOG_LOC, "Disposing test buffer.");
	test_buf->Dispose();
	delete[] test_float_buf_res;
	delete test_buf;*/

	std::vector<float> test_float_buf;
	test_float_buf.reserve(elem);
	for (int i = 0; i < elem; i++) {
		test_float_buf.push_back(offset + i + 1);
	}

	IComputeBuffer* test_buf_src = ProgramController::CreateBuffer(m_prog_inst, elem, sizeof(float));
	IComputeBuffer* test_buf_dst = ProgramController::CreateBuffer(m_prog_inst, elem, sizeof(float));

	test_buf_src->SetData(test_float_buf.data());

	test_buf_src->CopyTo(test_buf_dst);

	float* test_float_buf_res = new float[elem];
	test_buf_dst->GetData(test_float_buf_res);

	Logger::LogDebug(LOG_LOC, "Got results:");
	for (int i = 0; i < elem; i++) {
		//printf("Val %d: %f\n", i, test_float_buf_res[i]);
	}

	test_buf_src->Dispose();
	test_buf_dst->Dispose();
	delete[] test_float_buf_res;
	delete test_buf_src;
	delete test_buf_dst;
}


void ComputePool_private::Rebuild()
{
	// initialize and map variables
	//map_float_variables();
	//map_complex_variables();

	// Create compute buffers
	initialize_buffers();

	// Finalize compute shader programs
	//Finalize();

	// flush variable initial data.
	load_source_data();


}

/*void ComputePool_private::Execute_Func(program_id p_id, func_id f_id)
{
	Set_Settings(f_id);
	Execute(PROGRAM_ID_UTILITIES, m_elements, 1, 1);
}*/

void ComputePool_private::Set_Control(uint32_t slot_1, uint32_t slot_2, uint32_t slot_3, uint32_t slot_4, bool set_all)
{
	Set_Control(glm::uvec4(slot_1, slot_2, slot_3, slot_4), set_all);
}

void ComputePool_private::Set_Control(glm::uvec4 control, bool set_all) 
{
	if (set_all) {
		control_in->SetData(&control);
	}
	else {
		control_in->SetData(&control, 1 * VEC4_SIZE);
		// TODO: run utility program to duplicate accross all elements
	}
}

glm::uvec4 ComputePool_private::Get_Control_Vec(BufferInstance b) {
	SL_ASSERT(m_pool_buffers.count(b) > 0, "Buffer instance not found.");
	SL_ASSERT(m_pool_buffers[b].info_buffer != nullptr, "Buffer instance not found.");
	SL_ASSERT(m_pool_buffers[b].info_buffer->pool == this, "Buffer does not belong to pool.");

	glm::uvec4 res(m_type, 0, 0, 0);
	if (m_type == PoolType::Dynamic) {

	}
	else if (m_type == PoolType::Static) {
		res.y = m_static_pool_id;
		res.z = m_pool_buffers[b].info_buffer->ID();
	}
	return res;
}

void ComputePool_private::Set_Settings(func_id function_id)
{
	glm::fvec4 settings = get_settings(function_id);
	settings_buffer->SetData(&settings, 1 * VEC4_SIZE);
}

std::vector<float> ComputePool_private::Extract_Float(SL_Float src)
{
	return Extract_Float(src->Handle());
}

std::vector<Complex> ComputePool_private::Extract_Complex(SL_Complex src)
{
	return Extract_Complex(src->Handle());
}

std::vector<float> ComputePool_private::Extract_Float(BufferInstance src) {
	std::vector<float> res;
	res.resize(m_elements);

	if (m_type == PoolType::Dynamic) {
		SL_ASSERT(m_pool_buffers.count(src) > 0, "Pool buffer not found.");

		IComputeBuffer* buf = m_pool_buffers[src].comp_buffer;
		buf->GetData(&res[0], m_elements * sizeof(float));

	}
	else if (m_type == PoolType::Static) {
		SL_ASSERT(m_static_buffer != nullptr, "StaticBuffer is null!");

		m_static_buffer->GetData(
			&res[0],
			m_pool_buffers[src].info_buffer->ID() * m_pool_buffers[src].info_buffer->Stride() * sizeof(float),
			m_elements * m_pool_buffers[src].info_buffer->Stride() * sizeof(float));
	}

	return res;
}

std::vector<Complex> ComputePool_private::Extract_Complex(BufferInstance src) {
	std::vector<Complex> res;
	res.resize(m_elements);

	if (m_type == PoolType::Dynamic) {
		SL_ASSERT(m_pool_buffers.count(src) > 0, "Pool buffer not found.");

		IComputeBuffer* buf = m_pool_buffers[src].comp_buffer;
		buf->GetData(&res[0], m_elements * sizeof(Complex));
	}
	else if (m_type == PoolType::Static) {
		SL_ASSERT(m_static_buffer != nullptr, "StaticBuffer is null!");

		m_static_buffer->GetData(
			&res[0],
			m_pool_buffers[src].info_buffer->ID() * sizeof(float),
			m_elements * m_pool_buffers[src].info_buffer->Stride() * sizeof(float));
	}

	return res;
}

void ComputePool_private::Dispose() {
	for (auto& [key, val] : m_pool_buffers) {

		if (m_type == PoolType::Dynamic) {
			val.comp_buffer->Dispose();
			delete val.comp_buffer;
		}

		delete val.info_buffer;
	}
	m_pool_buffers.clear();

	if (m_type == PoolType::Static) {
		m_static_buffer->Dispose();
		delete m_static_buffer;
	}

}

glm::fvec4 ComputePool_private::get_settings(uint32_t func)
{
	return glm::fvec4(func, m_elements, 0, 0);
	//if (m_type == PoolType::Dynamic) {
	//}
}



void ComputePool_private::map_float_variables()
{
	/*int index = 0;
	for (const SL_Float& gp_float : m_float_list) {
		gp_float->index = index++;
	}
	m_float_elem_size = index;*/
}

void ComputePool_private::map_complex_variables()
{
	/*int index = 0;
	for (const SL_Complex& gp_float : m_complex_list) {
		gp_float->index = index;
		index += 2;
	}
	m_complex_elem_size = index;*/
}

void ComputePool_private::initialize_buffers()
{
	m_static_buffer = ProgramController::CreateBuffer(m_prog_inst, std::max(m_static_buffer_idx, (size_t)1), sizeof(float));


	/*control_in = Get_Controller()->NewReadBuffer(m_elements, sizeof(float) * 4);
	settings_buffer = Get_Controller()->NewReadBuffer(1, sizeof(float) * 4);
	

	src_float_stage_buffer = Get_Controller()->NewReadBuffer(m_elements, sizeof(float));
	src_complex_stage_buffer = Get_Controller()->NewReadBuffer(m_elements * 2, sizeof(float));

	buffer_float = Get_Controller()->NewReadWriteBuffer(m_elements * m_float_elem_size, sizeof(float));
	buffer_complex = Get_Controller()->NewReadWriteBuffer(m_elements * m_complex_elem_size * 2, sizeof(float));


	AddBuffer(PROGRAM_NAME_UTILITIES, 0, control_in);
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

void ComputePool_private::load_source_data()
{
	/*for (const SL_Float& gp_float : m_float_list) {
		Flush_Float(gp_float);
	}

	for (const SL_Complex& gp_float : m_complex_list) {
		Flush_Complex(gp_float);
	}*/

	for (auto& [key, val] : m_pool_buffers) {
		SL_ASSERT(val.info_buffer->source != nullptr, "Buffer source null!");
		m_static_buffer->SetData(val.info_buffer->source, val.info_buffer->ID() * sizeof(float), m_elements * val.info_buffer->Stride() * sizeof(float));
	}
}

void ComputePool_private::Flush_Float(SL_Float val) {
	/*if (val->source != nullptr) {
		glm::fvec4 control(val->index, 0, 0, 0);
		src_float_stage_buffer->SetData(val->source, 0, m_elements * sizeof(float));
		run_utilities_function(FUNCTION_UTILITIES_LOAD_SOURCE_FLOAT, control);
	}*/
}

void ComputePool_private::Flush_Complex(SL_Complex val) {
	/*if (val->source != nullptr) {
		glm::fvec4 control(val->index, 0, 0, 0);
		src_complex_stage_buffer->SetData(val->source, 0, m_elements * sizeof(float));
		run_utilities_function(FUNCTION_UTILITIES_LOAD_SOURCE_COMPLEX, control);
	}*/
}

void ComputePool_private::run_utilities_function(func_id id, glm::fvec4 control)
{
	run_utilities_function(id, control, m_elements);
}

void ComputePool_private::run_utilities_function(func_id id, glm::fvec4 control, int num)
{
	Set_Control(control);
	Set_Settings(id);
	//Execute(PROGRAM_ID_UTILITIES, num, 1, 1);
}
