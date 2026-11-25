
#ifndef SETTINGS_BUFFER
#define SETTINGS_BUFFER settings_in
#endif

#ifndef SETTINGS_BUFFER_BIND
#define SETTINGS_BUFFER_BIND 0
#endif

#ifndef CONTROL_BUFFER
#define CONTROL_BUFFER control_in
#endif

#ifndef CONTROL_BUFFER_BIND
#define CONTROL_BUFFER_BIND 1
#endif


// Result buffer
#ifndef RES_BUFFER
#define RES_BUFFER res_out
#endif
#ifndef RES_BUFFER_BIND
#define RES_BUFFER_BIND 2
#endif

#define MAX_FUNCTION_PARAMS 4

// param copy buffer names and bindings
#define PARAM_BIND_START 3
#define NUM_PARAM_BIND_BUFFERS 4

#ifndef PARAM_1_BUFFER
#define PARAM_1_BUFFER param_1_in
#endif
#ifndef PARAM_1_BUFFER_BIND
#define PARAM_1_BUFFER_BIND (PARAM_BIND_START + 0)
#endif

#ifndef PARAM_2_BUFFER
#define PARAM_2_BUFFER param_2_in
#endif
#ifndef PARAM_2_BUFFER_BIND
#define PARAM_2_BUFFER_BIND (PARAM_BIND_START + 1)
#endif

#ifndef PARAM_3_BUFFER
#define PARAM_3_BUFFER param_3_in
#endif
#ifndef PARAM_3_BUFFER_BIND
#define PARAM_3_BUFFER_BIND (PARAM_BIND_START + 3)
#endif

#ifndef PARAM_4_BUFFER
#define PARAM_4_BUFFER param_4_in
#endif
#ifndef PARAM_4_BUFFER_BIND
#define PARAM_4_BUFFER_BIND (PARAM_BIND_START + 4)
#endif

// pool buffer names and bindings
#define POOL_BUFF_BIND_START 7
#define NUM_POOL_BIND_BUFFERS 2

#ifndef POOL_BUFFER_1
#define POOL_BUFFER_1 bind_buff_1
#endif
#ifndef POOL_BUFFER_1_BIND
#define POOL_BUFFER_1_BIND (POOL_BUFF_BIND_START + 0)
#endif

#ifndef POOL_BUFFER_2
#define POOL_BUFFER_2 bind_buff_2
#endif
#ifndef POOL_BUFFER_2_BIND
#define POOL_BUFFER_2_BIND (POOL_BUFF_BIND_START + 1)
#endif





// Misc control buffers
read_buffer(uvec4, SETTINGS_BUFFER_BIND, SETTINGS_BUFFER)
read_buffer(uvec4, CONTROL_BUFFER_BIND, CONTROL_BUFFER)

// Result buffer
readwrite_buffer_float(RES_BUFFER_BIND, RES_BUFFER)

// Parameter buffers (dynamic pools)
readwrite_buffer_float(PARAM_1_BUFFER_BIND, PARAM_1_BUFFER)
readwrite_buffer_float(PARAM_2_BUFFER_BIND, PARAM_2_BUFFER)
readwrite_buffer_float(PARAM_3_BUFFER_BIND, PARAM_3_BUFFER)
readwrite_buffer_float(PARAM_4_BUFFER_BIND, PARAM_4_BUFFER)

// bound buffer pools (static pools)
readwrite_buffer_float(POOL_BUFFER_1_BIND, POOL_BUFFER_1)
readwrite_buffer_float(POOL_BUFFER_2_BIND, POOL_BUFFER_2)

