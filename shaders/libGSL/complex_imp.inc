#ifndef _GSL_COMPLEX_IMP_INC_
#define _GSL_COMPLEX_IMP_INC_


#include "../libUSL/USL.inc"
#include "complex.inc"
#include "standard_buffers.inc"



// Macros and settings
#define SETTINGS_FUNC() (SETTINGS_BUFFER[0].x)
#define NUM_ELEMENTS() (SETTINGS_BUFFER[0].y)
#define COMPLEX_TYPE_STRIDE 2

#define PARAM_POOL_TYPE(p) (CONTROL_BUFFER[p].x)
#define PARAM_STATIC_POOL_ID(p) (CONTROL_BUFFER[p].y)
#define PARAM_STATIC_POOL_OFFSET(p) (CONTROL_BUFFER[p].z)


// Buffer read/write accessors

#ifndef read
#define read(buf, index) \
	get_buffer_scalar(buf, index)
#endif

#ifndef write
#define write(buf, index, val_expr) \
	set_buffer_scalar(buf, index, val_expr)
#endif

#ifndef write_complex
#define write_complex(buf, idx, val_expr) \
do{                                     \
    STRUCT gsl_complex v = val_expr;    \
	write(buf, idx * COMPLEX_TYPE_STRIDE + 0, GSL_REAL(v)); \
	write(buf, idx * COMPLEX_TYPE_STRIDE + 1, GSL_IMAG(v)); \
} while (false);
#endif

#ifndef write_complex_offset
#define write_complex_offset(buf, offset, idx, val_expr) \
do{                                     \
    STRUCT gsl_complex v = val_expr;    \
	write(buf, (offset) + (idx) * COMPLEX_TYPE_STRIDE + 0, GSL_REAL(v)); \
	write(buf, (offset) + (idx) * COMPLEX_TYPE_STRIDE + 1, GSL_IMAG(v)); \
} while (false);
#endif

/*#ifndef write_res_complex
#define write_res_complex(idx, val) write_complex(RES_BUFFER, idx, val)
#endif*/
void write_res_complex_dynamic(uint idx, STRUCT gsl_complex val){
    write_complex(RES_BUFFER, idx, val);
}
void write_res_complex_static(uint idx, STRUCT gsl_complex val){
    switch(PARAM_STATIC_POOL_ID(0)){
        case 0:
            write_complex_offset(POOL_BUFFER_1, PARAM_STATIC_POOL_OFFSET(0), idx, val);
            break;
        case 1:
            write_complex_offset(POOL_BUFFER_2, PARAM_STATIC_POOL_OFFSET(0),  idx, val);
            break; 
    }
    
}
void write_res_complex(uint idx, STRUCT gsl_complex val){
    switch(PARAM_POOL_TYPE(0)){
        case POOL_TYPE_DYNAMIC:
            write_res_complex_dynamic(idx, val);
            break;
        case POOL_TYPE_STATIC:
            write_res_complex_static(idx, val);
            break;
        default:
            STRUCT gsl_complex t_res;
            GSL_SET_COMPLEX(t_res, 255, 255);
            write_res_complex_dynamic(idx, t_res);
            break;
    }


}


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

#ifndef read_complex
#define read_complex(buf, idx, out_cpx) \
    GSL_SET_COMPLEX(out_cpx, read(buf, (idx) * COMPLEX_TYPE_STRIDE + 0), read(buf, (idx) * COMPLEX_TYPE_STRIDE + 1))
#endif

#ifndef read_complex_offset
#define read_complex_offset(buf, offset, idx, out_cpx) \
    GSL_SET_COMPLEX(out_cpx, read(buf, (offset) + (idx) * COMPLEX_TYPE_STRIDE + 0), read(buf, (offset) + (idx) * COMPLEX_TYPE_STRIDE + 1))
#endif

#define read_float(buf, idx) read(buf, idx);

STRUCT gsl_complex Get_Complex_dynamic(uint p, uint idx){
    STRUCT gsl_complex res;
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
STRUCT gsl_complex Get_Complex_static(uint p, uint idx){
    STRUCT gsl_complex res;
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
STRUCT gsl_complex Get_Complex(uint p, uint idx){
    STRUCT gsl_complex res;
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

/*
STRUCT gsl_complex Get_Complex_p1(uint idx){
    STRUCT gsl_complex res;
    read_complex(PARAM_1_BUFFER, idx, res);
    return res;
}

STRUCT gsl_complex Get_Complex_p2(uint idx){
    STRUCT gsl_complex res;
    read_complex(PARAM_2_BUFFER, idx, res);
    return res;
}

STRUCT gsl_complex Get_Complex_p3(uint idx){
    STRUCT gsl_complex res;
    read_complex(PARAM_3_BUFFER, idx, res);
    return res;
}

STRUCT gsl_complex Get_Complex_p4(uint idx){
    STRUCT gsl_complex res;
    read_complex(PARAM_4_BUFFER, idx, res);
    return res;
}*/


gsl_type Get_Float_dynamic(uint p, uint idx){
    gsl_type res;
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
gsl_type Get_Float_static(uint p, uint idx){
    gsl_type res;
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
gsl_type Get_Float(uint p, uint idx){
    gsl_type res;
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

/*
gsl_type Get_Float_p1(uint idx){
    return read_float(PARAM_1_BUFFER, idx);
}

gsl_type Get_Float_p2(uint idx){
    return read_float(PARAM_2_BUFFER, idx);
}

gsl_type Get_Float_p3(uint idx){
    return read_float(PARAM_3_BUFFER, idx);
}

gsl_type Get_Float_p4(uint idx){
    return read_float(PARAM_4_BUFFER, idx);
}*/

// Functions IDs

#define FUNC_ID_COMPLEX_ADD 1
#define FUNC_ID_COMPLEX_SUB 2
#define FUNC_ID_COMPLEX_MUL 3
#define FUNC_ID_COMPLEX_DIV 4

// Combinations of result buffers, and parameter type presets

#define CPX_EXECUTE_CPX1(func, idx)\
	write_res_complex(idx,      \
        func(                   \
            Get_Complex(1, idx) \
            )                   \
        );

#define CPX_EXECUTE_CPX2(func, idx)\
	write_res_complex(idx,      \
        func(                   \
            Get_Complex(1, idx), \
            Get_Complex(2, idx) \
            )                   \
        );

#define CPX_EXECUTE_CPX_FLT(func, idx)\
	write_res_complex(idx,      \
        func(                   \
            Get_Complex(1, idx), \
            Get_Float(2, idx)   \
            )                   \
        );

#define CPX_EXECUTE_FLT1(func, idx)\
	write_res_complex(idx,      \
        func(                   \
            Get_Float(1, idx)   \
            )                   \
        );

#define CPX_EXECUTE_FLT2(func, idx)\
	write_res_complex(idx,      \
        func(                   \
            Get_Float(1, idx),   \
            Get_Float(2, idx)   \
            )                   \
        );

#define FLT_EXECUTE_CPX1(func, idx)\
    write_res_float(idx,        \
        func(                   \
            Get_Complex(1, idx) \
            )                   \
        );

#define FLT_EXECUTE_CPX2(func, idx)\
    write_res_float(idx,        \
        func(                   \
            Get_Complex(1, idx), \
            Get_Complex(2, idx) \
            )                   \
        );

#define FLT_EXECUTE_CPX_FLT(func, idx)\
    write_res_float(idx,        \
        func(                   \
            Get_Complex(1, idx), \
            Get_Float(2, idx)   \
            )                   \
        );

// Function entry point preset
#ifndef IMPLEMENT
#define IMPLEMENT(_exec_, _func_) \
void _func_##_main(uint idx) \
{                           \
	_exec_(_func_, idx)     \
}
#endif

void nothing_func(uint idx){
    write(RES_BUFFER, idx * COMPLEX_TYPE_STRIDE + 0, 256);
	write(RES_BUFFER, idx * COMPLEX_TYPE_STRIDE + 1, 257);
}

// Function implementations
IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_add)
IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_sub)
IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_mul)
IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_div)

// Main entry point
void Execute(uint x){
    //return;

	uint func_id = SETTINGS_FUNC();
	switch(func_id){
		case FUNC_ID_COMPLEX_ADD:
			gsl_complex_add_main(x);
			break;
		case FUNC_ID_COMPLEX_SUB:
			gsl_complex_sub_main(x);
			break;
		case FUNC_ID_COMPLEX_MUL:
			gsl_complex_mul_main(x);
			break;
		case FUNC_ID_COMPLEX_DIV:
			gsl_complex_div_main(x);
			break;

        default:
            nothing_func(x);
            break;
	}
}




#endif


