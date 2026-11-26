#ifndef _SLC_STANDARD_BUFFERS_INC_
#define _SLC_STANDARD_BUFFERS_INC_


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
#define PARAM_3_BUFFER_BIND (PARAM_BIND_START + 2)
#endif

#ifndef PARAM_4_BUFFER
#define PARAM_4_BUFFER param_4_in
#endif
#ifndef PARAM_4_BUFFER_BIND
#define PARAM_4_BUFFER_BIND (PARAM_BIND_START + 3)
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

#define POOL_TYPE_DYNAMIC 1
#define POOL_TYPE_STATIC 2

// Macros and settings
#define SETTINGS_FUNC() (SETTINGS_BUFFER[0].x)
#define NUM_ELEMENTS() (SETTINGS_BUFFER[0].y)

#define PARAM_POOL_TYPE(p) (CONTROL_BUFFER[p].x)
#define PARAM_STATIC_POOL_ID(p) (CONTROL_BUFFER[p].y)
#define PARAM_STATIC_POOL_OFFSET(p) (CONTROL_BUFFER[p].z)


// Buffer read/write accessors
#ifndef read
#define read(buf, index) get_buffer_scalar(buf, index)
#endif

#ifndef write
#define write(buf, index, val_expr) \
	set_buffer_scalar(buf, index, val_expr)
#endif



// #### Standard Float Accessors ####
#ifndef write_float
#define write_float(buf, idx, val) write(buf, idx, val)
#endif

/*
#ifndef write_res_float
#define write_res_float(idx, val) write_float(RES_BUFFER, idx, val);
#endif*/
void write_res_float_dynamic(uint idx, float val){
    write_float(RES_BUFFER, idx, val);
}
void write_res_float_static(uint idx, float val){
    switch(PARAM_STATIC_POOL_ID(0)){
        case 0:
            write_float(POOL_BUFFER_1, PARAM_STATIC_POOL_OFFSET(0) + idx, val);
            break;
        case 1:
            write_float(POOL_BUFFER_2, PARAM_STATIC_POOL_OFFSET(0) + idx, val);
            break; 
    }
    
}
void write_res_float(uint idx, float val){
    switch(PARAM_POOL_TYPE(0)){
        case POOL_TYPE_DYNAMIC:
            write_res_float_dynamic(idx, val);
            break;
        case POOL_TYPE_STATIC:
            write_res_float_static(idx, val);
            break;
        default:
            write_res_float_dynamic(idx, 255);
            break;
    }
}

#ifndef read_float
#define read_float(buf, idx) read(buf, idx)
#endif

slc_type Get_Float_dynamic(uint p, uint idx){
    slc_type res;
    switch(p){
        case 1:
            res = read_float(PARAM_1_BUFFER, idx);
            break;
        case 2:
            res = read_float(PARAM_2_BUFFER, idx);
            break;
        case 3:
            res = read_float(PARAM_3_BUFFER, idx);
            break;
        case 4:
            res = read_float(PARAM_4_BUFFER, idx);
            break;
    }
    return res;
}
slc_type Get_Float_static(uint p, uint idx){
    slc_type res;
    switch(PARAM_STATIC_POOL_ID(p)){
        case 0:
            res = read_float(POOL_BUFFER_1, PARAM_STATIC_POOL_OFFSET(p) + idx);
            break;
        case 1:
            res = read_float(POOL_BUFFER_2, PARAM_STATIC_POOL_OFFSET(p) + idx);
            break;
    }
    return res;
}
slc_type Get_Float(uint p, uint idx){
    slc_type res;
    switch(PARAM_POOL_TYPE(p)){
        case POOL_TYPE_DYNAMIC:
            res = Get_Float_dynamic(p, idx);
            break;
        case POOL_TYPE_STATIC:
            res = Get_Float_static(p, idx);
            break;
    }
    return res;
}
// #### END Standard Float Accessors ####



// #### Complex Accessors ####
#ifndef INCLUDE_COMPLEX_ACCESSORS
#define INCLUDE_COMPLEX_ACCESSORS 0
#endif

#if INCLUDE_COMPLEX_ACCESSORS

#ifndef write_complex
#define write_complex(buf, idx, val_expr) \
do{                                     \
    STRUCT slc_complex v = val_expr;    \
	write(buf, (idx) * COMPLEX_TYPE_STRIDE + 0, SLC_REAL(v)); \
	write(buf, (idx) * COMPLEX_TYPE_STRIDE + 1, SLC_IMAG(v)); \
} while (false);
#endif

#ifndef write_complex_offset
#define write_complex_offset(buf, offset, idx, val_expr) \
do{                                     \
    STRUCT slc_complex v = val_expr;    \
	write(buf, (offset) + (idx) * COMPLEX_TYPE_STRIDE + 0, SLC_REAL(v)); \
	write(buf, (offset) + (idx) * COMPLEX_TYPE_STRIDE + 1, SLC_IMAG(v)); \
} while (false);
#endif

/*#ifndef write_res_complex
#define write_res_complex(idx, val) write_complex(RES_BUFFER, idx, val)
#endif*/
void write_res_complex_dynamic(uint idx, STRUCT slc_complex val){
    write_complex(RES_BUFFER, idx, val);
}
void write_res_complex_static(uint idx, STRUCT slc_complex val){
    switch(PARAM_STATIC_POOL_ID(0)){
        case 0:
            write_complex_offset(POOL_BUFFER_1, PARAM_STATIC_POOL_OFFSET(0), idx, val);
            break;
        case 1:
            write_complex_offset(POOL_BUFFER_2, PARAM_STATIC_POOL_OFFSET(0),  idx, val);
            break; 
    }
    
}
void write_res_complex(uint idx, STRUCT slc_complex val){
    switch(PARAM_POOL_TYPE(0)){
        case POOL_TYPE_DYNAMIC:
            write_res_complex_dynamic(idx, val);
            break;
        case POOL_TYPE_STATIC:
            write_res_complex_static(idx, val);
            break;
        default:
            STRUCT slc_complex t_res;
            SLC_SET_COMPLEX(t_res, 255, 255);
            write_res_complex_dynamic(idx, t_res);
            break;
    }


}


#ifndef read_complex
#define read_complex(buf, idx, out_cpx) \
    SLC_SET_COMPLEX(out_cpx, read(buf, (idx) * COMPLEX_TYPE_STRIDE + 0), read(buf, (idx) * COMPLEX_TYPE_STRIDE + 1))
#endif

#ifndef read_complex_offset
#define read_complex_offset(buf, offset, idx, out_cpx) \
    SLC_SET_COMPLEX(out_cpx, read(buf, (offset) + (idx) * COMPLEX_TYPE_STRIDE + 0), read(buf, (offset) + (idx) * COMPLEX_TYPE_STRIDE + 1))
#endif

STRUCT slc_complex Get_Complex_dynamic(uint p, uint idx){
    STRUCT slc_complex res;
    switch(p){
        case 1:
            read_complex(PARAM_1_BUFFER, idx, res);
            break;
        case 2:
            read_complex(PARAM_2_BUFFER, idx, res);
            break;
        case 3:
            read_complex(PARAM_3_BUFFER, idx, res);
            break;
        case 4:
            read_complex(PARAM_4_BUFFER, idx, res);
            break;
    }
    return res;
}
STRUCT slc_complex Get_Complex_static(uint p, uint idx){
    STRUCT slc_complex res;
    switch(PARAM_STATIC_POOL_ID(p)){
        case 0:
            read_complex_offset(POOL_BUFFER_1, PARAM_STATIC_POOL_OFFSET(p), idx, res);
            break;
        case 1:
            read_complex_offset(POOL_BUFFER_2, PARAM_STATIC_POOL_OFFSET(p), idx, res);
            break;
    }
    return res;
}
STRUCT slc_complex Get_Complex(uint p, uint idx){
    STRUCT slc_complex res;
    switch(PARAM_POOL_TYPE(p)){
        case POOL_TYPE_DYNAMIC:
            res = Get_Complex_dynamic(p, idx);
            break;
        case POOL_TYPE_STATIC:
            res = Get_Complex_static(p, idx);
            break;
    }
    return res;
}
#endif // INCLUDE_COMPLEX_ACCESSORS

// #### END Complex Accessors ####


#endif // _SLC_STANDARD_BUFFERS_INC_