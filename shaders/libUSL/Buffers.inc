#ifndef _BUFFERS_INC_
#define _BUFFERS_INC_

#include "Types.inc"


// ############### VULKAN ###############
#if USL_VULKAN == 1

// buffers for vector types
#define read_buffer(__type__, __binding_num__, __name__) \
layout(std140, binding = __binding_num__) buffer readonly SSBO_##__name__{ \
	__type__ __name__[ ]; \
};

#define readwrite_buffer(__type__, __binding_num__, __name__) \
layout(std140, binding = __binding_num__) buffer SSBO_##__name__{ \
	__type__ __name__[ ]; \
};

// buffers for primitive scalar types
#define read_buffer_float(__binding_num__, __name__) \
read_buffer(fvec4, __binding_num__, __name__)

#define readwrite_buffer_float(__binding_num__, __name__) \
readwrite_buffer(fvec4, __binding_num__, __name__)

#define read_buffer_int(__binding_num__, __name__) \
read_buffer(ivec4, __binding_num__, __name__)

#define readwrite_buffer_int(__binding_num__, __name__) \
readwrite_buffer(ivec4, __binding_num__, __name__)

#define read_buffer_uint(__binding_num__, __name__) \
read_buffer(uvec4, __binding_num__, __name__)

#define readwrite_buffer_uint(__binding_num__, __name__) \
readwrite_buffer(uvec4, __binding_num__, __name__)

// buffers for user defined structs
#define read_buffer_struct(__type__, __binding_num__, __name__) read_buffer(__type__, __binding_num__, __name__)

#define readwrite_buffer_struct(__type__, __binding_num__, __name__) readwrite_buffer(__type__, __binding_num__, __name__)

// textures
#define read_texture_2D()

#define readwrite_texture_2D()

#define read_texture_3D()

#define readwrite_texture_3D()

// accessors
#define set_buffer_scalar(__buffer_name__, __index__, __value__) \
__buffer_name__[(__index__) / 4][(__index__) % 4] = (__value__)

#define get_buffer_scalar(__buffer_name__, __index__) \
__buffer_name__[(__index__) / 4][(__index__) % 4]


#define set_buffer_vector(__buffer_name__, __index__, __value__) \
__buffer_name__[__index__] = __value__

#define get_buffer_vector(__buffer_name__, __index__) \
__buffer_name__[__index__]



#define set_buffer_named_element(__buffer_name__, __index__, __element_name__, __element_ind__, __value__) \
__buffer_name__[__index__][__element_ind__] = __value__

#define get_buffer_named_element(__buffer_name__, __index__, __element_name__, __element_ind__) \
__buffer_name__[__index__][__element_ind__]

#define set_buffer_object(__buffer_name__, __index__, __value__) \
__buffer_name__[__index__] = __value__

#define get_buffer_object(__buffer_name__, __index__) \
__buffer_name__[__index__]


//  ############### OPEN CL ###############
#elif USL_OPENCL == 1

// buffers for vector types
#define read_buffer(__type__, __binding_num__, __name__) \
__global __type__* __name__;

#define readwrite_buffer(__type__, __binding_num__, __name__)\
__global __type__* __name__;


// buffers for primitive scalar types
#define read_buffer_float(__binding_num__, __name__) \
read_buffer(float, __binding_num__, __name__)

#define readwrite_buffer_float(__binding_num__, __name__) \
readwrite_buffer(float, __binding_num__, __name__)

#define read_buffer_int(__binding_num__, __name__) \
read_buffer(int, __binding_num__, __name__)

#define readwrite_buffer_int(__binding_num__, __name__) \
readwrite_buffer(int, __binding_num__, __name__)

#define read_buffer_uint(__binding_num__, __name__) \
read_buffer(uint, __binding_num__, __name__)

#define readwrite_buffer_uint(__binding_num__, __name__) \
readwrite_buffer(uint, __binding_num__, __name__)


// buffers for user defined structs
#define read_buffer_struct(__type__, __binding_num__, __name__) \
__global struct __type__* __name__;

#define readwrite_buffer_struct(__type__, __binding_num__, __name__)\
__global struct __type__* __name__;

// textures
#define read_texture_2D()

#define readwrite_texture_2D()

#define read_texture_3D()

#define readwrite_texture_3D()

// accessors

// INTERNAL USE ONLY
#define set_buffer_value(__buffer_name__, __index__, __value__) \
__buffer_name__[__index__] = __value__

// INTERNAL USE ONLY
#define get_buffer_value(__buffer_name__, __index__) \
__buffer_name__[__index__]


#define set_buffer_scalar(__buffer_name__, __index__, __value__) \
set_buffer_value(__buffer_name__, __index__, __value__)

#define get_buffer_scalar(__buffer_name__, __index__) \
get_buffer_value(__buffer_name__, __index__)


#define set_buffer_vector(__buffer_name__, __index__, __value__) \
set_buffer_value(__buffer_name__, __index__, __value__)

#define get_buffer_vector(__buffer_name__, __index__) \
get_buffer_value(__buffer_name__, __index__)


#define set_buffer_named_element(__buffer_name__, __index__, __element_name__, __element_ind__, __value__) \
__buffer_name__[__index__].__element_name__ = __value__

#define get_buffer_named_element(__buffer_name__, __index__, __element_name__, __element_ind__) \
__buffer_name__[__index__].__element_name__

#define set_buffer_object(__buffer_name__, __index__, __value__) \
__buffer_name__[__index__] = __value__

#define get_buffer_object(__buffer_name__, __index__) \
__buffer_name__[__index__]

//  ############### DirectX Unity3D  ###############
#elif USL_DIRECTX_UNITY3D == 1

// buffers for vector types
#define read_buffer(__type__, __binding_num__, __name__) \
StructuredBuffer<__type__> __name__;

#define readwrite_buffer(__type__, __binding_num__, __name__) \
RWStructuredBuffer<__type__> __name__;

// buffers for primitive scalar types
#define read_buffer_float(__binding_num__, __name__) \
read_buffer(float, __binding_num__, __name__)

#define readwrite_buffer_float(__binding_num__, __name__) \
readwrite_buffer(float, __binding_num__, __name__)

#define read_buffer_int(__binding_num__, __name__) \
read_buffer(int, __binding_num__, __name__)

#define readwrite_buffer_int(__binding_num__, __name__) \
readwrite_buffer(int, __binding_num__, __name__)

#define read_buffer_uint(__binding_num__, __name__) \
read_buffer(uint, __binding_num__, __name__)

#define readwrite_buffer_uint(__binding_num__, __name__) \
readwrite_buffer(uint, __binding_num__, __name__)

// buffers for user defined structs
#define read_buffer_struct(__type__, __binding_num__, __name__) read_buffer(__type__, __binding_num__, __name__)

#define readwrite_buffer_struct(__type__, __binding_num__, __name__) readwrite_buffer(__type__, __binding_num__, __name__)


// textures
#define read_texture_2D()

#define readwrite_texture_2D()

#define read_texture_3D()

#define readwrite_texture_3D()


// accessors

// INTERNAL USE ONLY
#define set_buffer_value(__buffer_name__, __index__, __value__) \
__buffer_name__[__index__] = __value__

// INTERNAL USE ONLY
#define get_buffer_value(__buffer_name__, __index__) \
__buffer_name__[__index__]


#define set_buffer_scalar(__buffer_name__, __index__, __value__) \
set_buffer_value(__buffer_name__, __index__, __value__)

#define get_buffer_scalar(__buffer_name__, __index__) \
get_buffer_value(__buffer_name__, __index__)


#define set_buffer_vector(__buffer_name__, __index__, __value__) \
set_buffer_value(__buffer_name__, __index__, __value__)

#define get_buffer_vector(__buffer_name__, __index__) \
get_buffer_value(__buffer_name__, __index__)



#define set_buffer_named_element(__buffer_name__, __index__, __element_name__, __element_ind__, __value__) \
__buffer_name__[__index__].__element_name__ = __value__

#define get_buffer_named_element(__buffer_name__, __index__, __element_name__, __element_ind__) \
__buffer_name__[__index__].__element_name__

#define set_buffer_object(__buffer_name__, __index__, __value__) \
__buffer_name__[__index__] = __value__

#define get_buffer_object(__buffer_name__, __index__) \
__buffer_name__[__index__]

#endif




#endif // _BUFFERS_INC_


