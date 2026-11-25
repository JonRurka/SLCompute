#pragma once

#include "SLC_Program.h"
#include "Compute/dynamic_compute.h"
#include "SLC_Structures.h"
#include "glm_inc.h"

namespace SLCompute {



	class ComputePool_private {
		friend class ProgramController;
	public:
		ComputePool_private(size_t progInst, unsigned int pool_num, PoolType type, size_t sx,  size_t sy,  size_t sz);

		size_t ProgramInstance() { return m_prog_inst; }

		unsigned int PoolID() { return m_pool_id; }

		PoolType Pool_Type() { return m_type; }

		size_t Element_Size() {return m_elements;}

		SL_Float Get_Float();

		SL_Float Get_Float(std::vector<float> data);

		SL_Complex Get_Complex();

		SL_Complex Get_Complex(std::vector<Complex> data);

		const size_t Num_Elements() const { return m_elements; }

		size_t SetStaticPoolID() {
			return m_static_pool_id;
		}

		void Rebuild();

		//void Execute_Func(program_id p_id, func_id f_id);

		glm::uvec4 Get_Control_Vec(BufferInstance b);

		void Set_Control(uint32_t slot_1, uint32_t slot_2, uint32_t slot_3, uint32_t slot_4, bool set_all = false);

		void Set_Control(glm::uvec4 control, bool set_all = false);

		void Set_Settings(func_id function_id);

		std::vector<float> Extract_Float(BufferInstance src);

		std::vector<Complex> Extract_Complex(BufferInstance src);

		std::vector<float> Extract_Float(SL_Float src);

		std::vector<Complex> Extract_Complex(SL_Complex src);

		IComputeBuffer* GetComputeBuffer(BufferInstance src);
		IComputeBuffer* GetComputeBuffer(SL_Strided_Buffer src);

		IComputeBuffer* GetStaticComputeBuffer();

		void Destroy_Buffer(BufferInstance buffer);

		void Destroy_Buffer(SL_Strided_Buffer buffer);

		void Test_Buffer_Engine(size_t offset, size_t elem);

		void Dispose();

	private:

		constexpr static unsigned int POOL_ID_NULL = 0xFFFFFFFF;

		size_t m_elements {0};
		size_t m_float_elem_size;
		size_t m_complex_elem_size;
		size_t m_prog_inst {0};
		unsigned int m_pool_id {POOL_ID_NULL};
		PoolType m_type;
		size_t m_static_buffer_idx{0};
		size_t m_static_pool_id{POOL_ID_NULL};

		//IComputeBuffer* src_float_stage_buffer;
		//IComputeBuffer* src_complex_stage_buffer;

		IComputeBuffer* src_stage_buffer;

		struct sl_buffer {
			IComputeBuffer* comp_buffer;
			SL_Strided_Buffer info_buffer;

			sl_buffer() : comp_buffer(nullptr), info_buffer(0){}
		};

		//IComputeBuffer* buffer_complex_previous;
		//IComputeBuffer* buffer_in_float_previous;

		//IComputeBuffer* buffer_complex;
		//IComputeBuffer* buffer_float;

		IComputeBuffer* settings_buffer;
		IComputeBuffer* control_in;

		//std::vector<SL_Float> m_float_list;
		//std::vector<SL_Complex> m_complex_list;

		std::unordered_map<BufferInstance, sl_buffer> m_pool_buffers;
		IComputeBuffer* m_static_buffer {nullptr};


		void SetStaticPoolID(size_t pool_id) {
			m_static_pool_id = pool_id;
		}

		glm::fvec4 get_settings(uint32_t func);

		void Init();

		void map_float_variables();

		void map_complex_variables();

		void initialize_buffers();

		void load_source_data();
		
		void Flush_Float(SL_Float val);

		void Flush_Complex(SL_Complex val);

		void run_utilities_function(func_id id, glm::fvec4 control);

		void run_utilities_function(func_id id, glm::fvec4 control, int num);

		inline static const std::string LOG_LOC{ "ComputePool" };
	};
}