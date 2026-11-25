#ifndef _SLC_COMPLEX_IMP_INC_
#define _SLC_COMPLEX_IMP_INC_

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


#include "../libUSL/USL.inc"
#include "complex.inc"

//#define IN_BUFFER buffer_in
//#define OUT_BUFFER buffer_out
//#include "complex.inc"

read_buffer(uvec4, SETTINGS_BUFFER_BIND, SETTINGS_BUFFER)
read_buffer(uvec4, CONTROL_BUFFER_BIND, CONTROL_BUFFER)

read_buffer_float(2, buffer_in_complex)
read_buffer_float(3, buffer_in_float)

readwrite_buffer_float(4, buffer_out_complex)
readwrite_buffer_float(5, buffer_out_float)


#define SETTINGS_FUNC()(SETTINGS_BUFFER[0].x)


#ifndef read
#define read(buf, index) \
	get_buffer_scalar(buf, index)
#endif

#ifndef write
#define write(buf, index, val) \
	set_buffer_scalar(buf, index, val)
#endif

/*slc_type read(uint index)
{
	return get_buffer_scalar(IN_BUFFER, index);
}

void write(uint index, slc_type val)
{
	set_buffer_scalar(OUT_BUFFER, index, val);
}*/

#define FUNC_ID_COMPLEX_ADD 1
#define FUNC_ID_COMPLEX_SUB 2
#define FUNC_ID_COMPLEX_MUL 3
#define FUNC_ID_COMPLEX_DIV 4

/*
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_

#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_

#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_

#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_

#define FUNC_COMPLEX_
#define FUNC_COMPLEX_

#define FUNC_COMPLEX_
#define FUNC_COMPLEX_

#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_

#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_
#define FUNC_COMPLEX_*/

/*

slc_type slc_complex_arg 	(STRUCT slc_complex z);
slc_type slc_complex_abs 	(STRUCT slc_complex z);
slc_type slc_complex_abs2 	(STRUCT slc_complex z);
slc_type slc_complex_logabs (STRUCT slc_complex z);

STRUCT slc_complex slc_complex_add (STRUCT slc_complex a, STRUCT slc_complex b);
STRUCT slc_complex slc_complex_sub (STRUCT slc_complex a, STRUCT slc_complex b);
STRUCT slc_complex slc_complex_mul (STRUCT slc_complex a, STRUCT slc_complex b);
STRUCT slc_complex slc_complex_div (STRUCT slc_complex a, STRUCT slc_complex b);
                                                           
STRUCT slc_complex slc_complex_add_real (STRUCT slc_complex a, slc_type x);
STRUCT slc_complex slc_complex_sub_real (STRUCT slc_complex a, slc_type x);
STRUCT slc_complex slc_complex_mul_real (STRUCT slc_complex a, slc_type x);
STRUCT slc_complex slc_complex_div_real (STRUCT slc_complex a, slc_type x);

STRUCT slc_complex slc_complex_add_imag (STRUCT slc_complex a, slc_type y);
STRUCT slc_complex slc_complex_sub_imag (STRUCT slc_complex a, slc_type y);
STRUCT slc_complex slc_complex_mul_imag (STRUCT slc_complex a, slc_type y);
STRUCT slc_complex slc_complex_div_imag (STRUCT slc_complex a, slc_type y);

STRUCT slc_complex slc_complex_conjugate (STRUCT slc_complex z);
STRUCT slc_complex slc_complex_inverse  (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_negative (STRUCT slc_complex a);


STRUCT slc_complex slc_complex_sqrt 	(STRUCT slc_complex z);
STRUCT slc_complex slc_complex_sqrt_real (slc_type x);

STRUCT slc_complex slc_complex_pow 		(STRUCT slc_complex a, STRUCT slc_complex b);
STRUCT slc_complex slc_complex_pow_real (STRUCT slc_complex a, slc_type b);

STRUCT slc_complex slc_complex_exp   (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_log   (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_log10 (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_log_b (STRUCT slc_complex a, STRUCT slc_complex b);



STRUCT slc_complex slc_complex_sin (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_cos (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_sec (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_csc (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_tan (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_cot (STRUCT slc_complex a);



STRUCT slc_complex slc_complex_arcsin (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arcsin_real (slc_type a);
STRUCT slc_complex slc_complex_arccos (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arccos_real (slc_type a);
STRUCT slc_complex slc_complex_arcsec (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arcsec_real (slc_type a);
STRUCT slc_complex slc_complex_arccsc (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arccsc_real (slc_type a);
STRUCT slc_complex slc_complex_arctan (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arccot (STRUCT slc_complex a);


STRUCT slc_complex slc_complex_sinh (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_cosh (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_sech (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_csch (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_tanh (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_coth (STRUCT slc_complex a);


STRUCT slc_complex slc_complex_arcsinh (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arccosh (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arccosh_real (slc_type a);
STRUCT slc_complex slc_complex_arcsech (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arccsch (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arctanh (STRUCT slc_complex a);
STRUCT slc_complex slc_complex_arctanh_real (slc_type a);
STRUCT slc_complex slc_complex_arccoth (STRUCT slc_complex a);

*/

#define CPX_EXECUTE_CPX(func, idx)\
	write_complex(Res_Index(idx), func(Get_Complex(idx, 0)));

#define CPX_EXECUTE_CPX1(func, idx)\
	write_complex(Res_Index(idx), func(Get_Complex(idx, 1)));

#define CPX_EXECUTE_CPX2(func, idx)\
	write_complex(Res_Index(idx), func(Get_Complex(idx, 1), Get_Complex(idx, 2)));
	
#define CPX_EXECUTE_CPX_FLT(func, idx)\
	write_complex(Res_Index(idx), func(Get_Complex(idx, 1), Get_Float(idx, 2)));


#define CPX_EXECUTE_FLT1(func, idx)\
	write_complex(Res_Index(idx), func(Get_Float(idx, 1)));
	
#define CPX_EXECUTE_FLT2(func, idx)\
	write_complex(Res_Index(idx), func(Get_Float(idx, 1), Get_Float(idx, 2)));
	

#define FLT_EXECUTE_CPX(func, idx)\
	write_float(Res_Index(idx), func(Get_Complex(idx, 0)));

#define FLT_EXECUTE_CPX1(func, idx)\
	write_float(Res_Index(idx), func(Get_Complex(idx, 1)));

#define FLT_EXECUTE_CPX2(func, idx)\
	write_float(Res_Index(idx), func(Get_Complex(idx, 1), Get_Complex(idx, 2)));
	
#define FLT_EXECUTE_CPX_FLT(func, idx)\
	write_float(Res_Index(idx), func(Get_Complex(idx, 1), Get_Float(idx, 2)));

// TODO: This all needs to be changed to treat CONTROL_BUFFER like it has local index instead of global


STRUCT slc_complex read_complex(uint idx){
	STRUCT slc_complex res;
	SLC_SET_COMPLEX(res, read(buffer_in_complex, idx * 2 + 0), read(buffer_in_complex, idx * 2 + 1));
	return res;
}

void write_complex(uint idx, STRUCT slc_complex val)
{
	write(buffer_out_complex, idx * 2 + 0, SLC_REAL(val));
	write(buffer_out_complex, idx * 2 + 1, SLC_IMAG(val));
}

slc_type read_float(uint idx)
{
	return read(buffer_in_float, idx);
}

void write_float(uint idx, slc_type val)
{
	write(buffer_out_float, idx, val);
}

uint Res_Index(uint idx){
	return get_buffer_vector(CONTROL_BUFFER, idx).x;
}

uint OP1_Index(uint idx){
	return get_buffer_vector(CONTROL_BUFFER, idx).y;
}

uint OP2_Index(uint idx){
	return get_buffer_vector(CONTROL_BUFFER, idx).z;
}

uint OP3_Index(uint idx){
	return get_buffer_vector(CONTROL_BUFFER, idx).w;
}

STRUCT slc_complex Get_Complex(uint idx, int slot){
	uvec4 controller = get_buffer_vector(CONTROL_BUFFER, idx);
	uint c_index = controller[slot];
	return read_complex(c_index);
}

slc_type Get_Float(uint idx, int slot){
	uvec4 controller = get_buffer_vector(CONTROL_BUFFER, idx);
	uint c_index = controller[slot];
	return read_float(c_index);
}

#ifndef IMPLEMENT
#define IMPLEMENT(_exec_, _func_) \
void _func_##_main(uint idx) \
{ \
	_exec_(_func_, idx); \
}
#endif

IMPLEMENT(CPX_EXECUTE_CPX2, slc_complex_add)
IMPLEMENT(CPX_EXECUTE_CPX2, slc_complex_sub)
IMPLEMENT(CPX_EXECUTE_CPX2, slc_complex_mul)
IMPLEMENT(CPX_EXECUTE_CPX2, slc_complex_div)

IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_add_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_sub_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_mul_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_div_real)

IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_add_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_sub_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_mul_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_div_imag)


IMPLEMENT(CPX_EXECUTE_CPX1, slc_complex_conjugate)
IMPLEMENT(CPX_EXECUTE_CPX1, slc_complex_inverse)
IMPLEMENT(CPX_EXECUTE_CPX1, slc_complex_negative)


/*IMPLEMENT(CPX_EXECUTE_CPX1, slc_complex_sqrt)
IMPLEMENT(CPX_EXECUTE_FLT1, slc_complex_sqrt_real)

IMPLEMENT(CPX_EXECUTE_CPX1, slc_complex_pow)
IMPLEMENT(CPX_EXECUTE_FLT1, slc_complex_pow_real)


IMPLEMENT(CPX_EXECUTE_CPX1, slc_complex_exp)
IMPLEMENT(CPX_EXECUTE_CPX1, slc_complex_log)
IMPLEMENT(CPX_EXECUTE_CPX1, slc_complex_log10)
IMPLEMENT(CPX_EXECUTE_CPX2, slc_complex_log_b)*/




void Execute(uint x){
	uint func_id = SETTINGS_FUNC();
	switch(func_id){
		case FUNC_ID_COMPLEX_ADD:
			slc_complex_add_main(x);
			break;
		case FUNC_ID_COMPLEX_SUB:
			slc_complex_sub_main(x);
			break;
		case FUNC_ID_COMPLEX_MUL:
			slc_complex_mul_main(x);
			break;
		case FUNC_ID_COMPLEX_DIV:
			slc_complex_div_main(x);
			break;
	}
}











#endif //__SLC_COMPLEX_INC__