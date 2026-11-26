#pragma once

#include "slcompute.h"
#include <string>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include "bimap.h"
#include "SLC_func_ids.h"
#include "Compute/ForwardDeclarations.h"
#include "Compute/dynamic_compute.h"
#include "SLC_Structures.h"
#include "glm_inc.h"

using namespace DynamicCompute::Compute;

namespace SLCompute {

	typedef std::shared_ptr<ComputePool_private> PoolInstance;

	class SLCOMPUTE_EXPORT ProgramController {
		friend class ComputePool_private;
	public:
		enum class Programs {
			UTILITIES = PROGRAM_ID_UTILITIES,
			COMPLEX = PROGRAM_ID_COMPLEX,
		};

		struct ProgramSettings {
			uint32_t Device_ID = UINT32_MAX; // UINT32_MAX = auto-select highest-class device

			void Set_Device(const SL_Device_Info& d){ Device_ID = d.id; }
		};

		struct PoolSettings {
			int x_size;
			int y_size;
			int z_size;
			PoolType type;
		};

		typedef size_t ProgramInstance;

		ProgramController(ProgramInstance id, ProgramSettings);

		static std::vector<SL_Device_Info> Get_Devices();

		static void Enable(Programs p);
		static ProgramInstance Create(ProgramSettings settings);
		static PoolInstance CreatePool(ProgramInstance p, PoolSettings settings);
		static void Start(ProgramInstance p);
		static IComputeBuffer* CreateBuffer(ProgramInstance p, size_t elements, size_t stride);

		static void Execute(ProgramInstance p, program_id p_id, func_id f_id, SL_Strided_Buffer res, const std::vector<SL_Strided_Buffer>& params);

		static void DisposePool(PoolInstance pool_inst);

		static void DisposeProgram(ProgramInstance p);

	protected:


		IComputeController* Get_Controller() { return m_controller; }

		void AddBuffer(int bind, IComputeBuffer* buffer);

		void AddBuffer(std::string program_name, int bind, IComputeBuffer* buffer);

		void Finalize();

		void Execute(program_id p_id, func_id f_id, SL_Strided_Buffer res, const std::vector<SL_Strided_Buffer>& params);

		void Execute(std::string p_name, int size_x, int size_y, int size_z);

		void Execute(program_id p_id, int size_x, int size_y, int size_z);

		static ProgramController& Get_ProgramController(ProgramInstance p);

		void Dispose_Pool(PoolInstance pool_inst);

		void Dispose();
	private:

		constexpr static int MAX_FUNCTION_PARAMS = 4;

		constexpr static int PARAM_BIND_START = 3;
		constexpr static int NUM_PARAM_BIND_BUFFERS = 4;
		constexpr static int POOL_BUFF_BIND_START = 7;
		constexpr static int NUM_POOL_BIND_BUFFERS = 2;

		void Initialize();

		void CreateProgram(std::string name, std::vector<uint8_t> data);

		IComputeBuffer* create_buffer(size_t elements, size_t stride);

		static constexpr int MAX_PARAMS = 4;
		bool finalized = false;
		bool initialized = false;
		inline static unsigned int pool_num = 0;
		ProgramSettings m_settings;
		ProgramInstance m_prog_inst;
		size_t m_static_bind_idx {0};

		std::string kernel_name = "main";

		IComputeController* m_controller = nullptr;
		ComputeInterface::ControllerInfo m_controllerInfo{};

		std::unordered_map<std::string, IComputeProgram*> m_programs;
		std::vector<IComputeProgram*> m_programs_list;

		IComputeBuffer* src_float_stage_buffer;
		IComputeBuffer* src_complex_stage_buffer;

		IComputeBuffer* m_result_buffer;
		std::vector<IComputeBuffer*> m_param_buffers;

		IComputeBuffer* buffer_complex_previous;
		IComputeBuffer* buffer_in_float_previous;

		IComputeBuffer* buffer_complex;
		IComputeBuffer* buffer_float;

		IComputeBuffer* settings_buffer;
		IComputeBuffer* control_in;

		void initialize_buffers();

		virtual void configure_workgroup_sizes();

		void SetProgramWorkGroupSize(std::string program_name, glm::uvec3 size);

		PoolInstance create_pool(PoolSettings settings);
		void start();

		void Set_Settings(func_id function_id, int elements);

		const glm::uvec4 get_settings(uint32_t func, uint32_t elements)
		{
			return glm::uvec4(func, elements, 0, 0);
		}

		void Set_Control(std::vector<glm::uvec4>& settings);

		inline static std::unordered_map<ProgramInstance, std::unique_ptr<ProgramController>> m_program_instances;
		std::unordered_map<unsigned int, std::shared_ptr<ComputePool_private>> m_pools;
		std::vector<std::shared_ptr<ComputePool_private>> m_static_pools;
		IComputeBuffer* m_dummy_static_buffer;

		inline static std::unordered_set<Programs> m_activate_programs;
		inline static const BiMap<Programs, std::string> m_program_name_map
		{
			{Programs::UTILITIES, "utilities"},
			{ Programs::COMPLEX, "complex" }
		};
		//inline static std::map<Programs>

		inline static const std::string LOG_LOC{ "ProgramController" };
	};
}