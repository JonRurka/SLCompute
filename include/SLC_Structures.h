#pragma once

#include "slcompute.h"
#include "Compute/std_includes.h"
#include <cstdint>
#include <unordered_map>

namespace SLCompute {

	class ComputePool_private;

	// POOL_TYPE_DYNAMIC and POOL_TYPE_STATIC in shaders/libSLC/standard_buffers.inc
	// must stay in sync with these values — Get_Control_Vec packs m_type directly
	// into the control vec and the shader switch dispatches on the same integer.
	enum class PoolType : uint32_t {
		Dynamic = 1,
		Static = 2,
	};
	static_assert(static_cast<uint32_t>(PoolType::Dynamic) == 1, "PoolType::Dynamic must match POOL_TYPE_DYNAMIC 1 in standard_buffers.inc");
	static_assert(static_cast<uint32_t>(PoolType::Static)  == 2, "PoolType::Static must match POOL_TYPE_STATIC 2 in standard_buffers.inc");

	enum class SL_Device_Class : uint32_t {
		CPU = 0,
		INTEGRATED_GPU = 1,
		DISCRETE_GPU = 2,
		VIRTUAL_GPU = 3,
		ACCELERATOR = 4,
		OTHER = 5,
	};
	struct SL_Device_Info {
		uint32_t id;
		SL_Device_Class device_class;
		char name[256];
	};

	typedef uint32_t func_id;
	typedef uint32_t program_id;

	typedef void* pool_ref;
	typedef void* src_ptr;

	typedef uint32_t BufferInstance;

	class SLCOMPUTE_EXPORT SL_Strided_Buffer_struct {
		friend class ComputePool_private;
	public:
		static size_t Max_Stride() { return max_stride; }

		uint32_t ID() { return id; }
		BufferInstance Handle() { return handle;}
		pool_ref Pool() { return pool; }
		uint32_t Stride() {return stride;}

		SL_Strided_Buffer_struct(const size_t element_stride) : stride(element_stride) {
			next_id++;
			handle = next_id;
			insert();
		}

		static SL_Strided_Buffer_struct* Get(BufferInstance h) {
			assert(s_buffer_instances.count(h) > 0);
			return s_buffer_instances[h];
		}

		virtual ~SL_Strided_Buffer_struct() {
			remove();
		}

	protected:
		void insert() {
			s_buffer_instances[handle] = this;
		}

		void remove() {
			s_buffer_instances.erase(handle);
		}

	private:
		uint32_t id;
		BufferInstance handle;
		size_t stride;
		pool_ref pool;
		src_ptr source;

		static inline std::unordered_map<BufferInstance, SL_Strided_Buffer_struct*> s_buffer_instances;
		static inline uint32_t next_id = 0;
	protected:
		static inline size_t max_stride = 0;
	};
	typedef SL_Strided_Buffer_struct SL_Strided_Buffer_Type;
	typedef SL_Strided_Buffer_struct* SL_Strided_Buffer;
	typedef BufferInstance StridedInstance;

	class SLCOMPUTE_EXPORT SL_Float_struct : public SL_Strided_Buffer_struct {
		friend class ComputePool_private;
	public:
		static constexpr size_t STRIDE = 1;
		SL_Float_struct() : SL_Strided_Buffer_struct(STRIDE){}
		static void Enable() {
			Enabled = true;
			max_stride = std::max(STRIDE, max_stride);
		}
	private:
		inline static bool Enabled = false;
	};
	typedef SL_Float_struct SL_Float_Type;
	typedef SL_Float_struct* SL_Float;
	typedef StridedInstance FloatInstance;

	class SLCOMPUTE_EXPORT SL_Complex_struct : public SL_Strided_Buffer_struct{
		friend class ComputePool_private;
		static constexpr size_t STRIDE = 2;
	public:
		SL_Complex_struct() : SL_Strided_Buffer_struct(STRIDE){}
		static void Enable() {
			Enabled = true;
			max_stride = std::max(STRIDE, max_stride);
		}
	private:
		inline static bool Enabled = false;
	};
	typedef SL_Complex_struct* SL_Complex;
	typedef StridedInstance ComplexInstance;

	struct SLCOMPUTE_EXPORT Complex {
		float real;
		float imaginary;
	};

}