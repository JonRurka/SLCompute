#ifndef _GSL_COMPLEX_IMP_INC_
#define _GSL_COMPLEX_IMP_INC_

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

/*gsl_type read(uint index)
{
	return get_buffer_scalar(IN_BUFFER, index);
}

void write(uint index, gsl_type val)
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

gsl_type gsl_complex_arg 	(STRUCT gsl_complex z); 	
gsl_type gsl_complex_abs 	(STRUCT gsl_complex z);   
gsl_type gsl_complex_abs2 	(STRUCT gsl_complex z);  
gsl_type gsl_complex_logabs (STRUCT gsl_complex z);

STRUCT gsl_complex gsl_complex_add (STRUCT gsl_complex a, STRUCT gsl_complex b); 
STRUCT gsl_complex gsl_complex_sub (STRUCT gsl_complex a, STRUCT gsl_complex b); 
STRUCT gsl_complex gsl_complex_mul (STRUCT gsl_complex a, STRUCT gsl_complex b);
STRUCT gsl_complex gsl_complex_div (STRUCT gsl_complex a, STRUCT gsl_complex b);
                                                           
STRUCT gsl_complex gsl_complex_add_real (STRUCT gsl_complex a, gsl_type x);
STRUCT gsl_complex gsl_complex_sub_real (STRUCT gsl_complex a, gsl_type x);
STRUCT gsl_complex gsl_complex_mul_real (STRUCT gsl_complex a, gsl_type x);
STRUCT gsl_complex gsl_complex_div_real (STRUCT gsl_complex a, gsl_type x);

STRUCT gsl_complex gsl_complex_add_imag (STRUCT gsl_complex a, gsl_type y);
STRUCT gsl_complex gsl_complex_sub_imag (STRUCT gsl_complex a, gsl_type y);
STRUCT gsl_complex gsl_complex_mul_imag (STRUCT gsl_complex a, gsl_type y);
STRUCT gsl_complex gsl_complex_div_imag (STRUCT gsl_complex a, gsl_type y);

STRUCT gsl_complex gsl_complex_conjugate (STRUCT gsl_complex z);
STRUCT gsl_complex gsl_complex_inverse  (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_negative (STRUCT gsl_complex a); 


STRUCT gsl_complex gsl_complex_sqrt 	(STRUCT gsl_complex z); 
STRUCT gsl_complex gsl_complex_sqrt_real (gsl_type x);  	

STRUCT gsl_complex gsl_complex_pow 		(STRUCT gsl_complex a, STRUCT gsl_complex b);
STRUCT gsl_complex gsl_complex_pow_real (STRUCT gsl_complex a, gsl_type b);  	

STRUCT gsl_complex gsl_complex_exp   (STRUCT gsl_complex a);    
STRUCT gsl_complex gsl_complex_log   (STRUCT gsl_complex a);    
STRUCT gsl_complex gsl_complex_log10 (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_log_b (STRUCT gsl_complex a, STRUCT gsl_complex b);   



STRUCT gsl_complex gsl_complex_sin (STRUCT gsl_complex a); 
STRUCT gsl_complex gsl_complex_cos (STRUCT gsl_complex a); 
STRUCT gsl_complex gsl_complex_sec (STRUCT gsl_complex a); 
STRUCT gsl_complex gsl_complex_csc (STRUCT gsl_complex a); 
STRUCT gsl_complex gsl_complex_tan (STRUCT gsl_complex a); 
STRUCT gsl_complex gsl_complex_cot (STRUCT gsl_complex a); 



STRUCT gsl_complex gsl_complex_arcsin (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arcsin_real (gsl_type a);  		
STRUCT gsl_complex gsl_complex_arccos (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arccos_real (gsl_type a);  		
STRUCT gsl_complex gsl_complex_arcsec (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arcsec_real (gsl_type a);  		
STRUCT gsl_complex gsl_complex_arccsc (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arccsc_real (gsl_type a);  		
STRUCT gsl_complex gsl_complex_arctan (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arccot (STRUCT gsl_complex a);  


STRUCT gsl_complex gsl_complex_sinh (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_cosh (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_sech (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_csch (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_tanh (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_coth (STRUCT gsl_complex a);  


STRUCT gsl_complex gsl_complex_arcsinh (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arccosh (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arccosh_real (gsl_type a);  		
STRUCT gsl_complex gsl_complex_arcsech (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arccsch (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arctanh (STRUCT gsl_complex a);  
STRUCT gsl_complex gsl_complex_arctanh_real (gsl_type a); 		
STRUCT gsl_complex gsl_complex_arccoth (STRUCT gsl_complex a);  

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


STRUCT gsl_complex read_complex(uint idx){
	STRUCT gsl_complex res;
	GSL_SET_COMPLEX(res, read(buffer_in_complex, idx * 2 + 0), read(buffer_in_complex, idx * 2 + 1));
	return res;
}

void write_complex(uint idx, STRUCT gsl_complex val)
{
	write(buffer_out_complex, idx * 2 + 0, GSL_REAL(val));
	write(buffer_out_complex, idx * 2 + 1, GSL_IMAG(val));
}

gsl_type read_float(uint idx)
{
	return read(buffer_in_float, idx);
}

void write_float(uint idx, gsl_type val)
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

STRUCT gsl_complex Get_Complex(uint idx, int slot){
	uvec4 controller = get_buffer_vector(CONTROL_BUFFER, idx);
	uint c_index = controller[slot];
	return read_complex(c_index);
}

gsl_type Get_Float(uint idx, int slot){
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

IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_add)
IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_sub)
IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_mul)
IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_div)

IMPLEMENT(CPX_EXECUTE_CPX_FLT, gsl_complex_add_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, gsl_complex_sub_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, gsl_complex_mul_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, gsl_complex_div_real)

IMPLEMENT(CPX_EXECUTE_CPX_FLT, gsl_complex_add_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, gsl_complex_sub_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, gsl_complex_mul_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, gsl_complex_div_imag)


IMPLEMENT(CPX_EXECUTE_CPX1, gsl_complex_conjugate)
IMPLEMENT(CPX_EXECUTE_CPX1, gsl_complex_inverse)
IMPLEMENT(CPX_EXECUTE_CPX1, gsl_complex_negative)


/*IMPLEMENT(CPX_EXECUTE_CPX1, gsl_complex_sqrt)
IMPLEMENT(CPX_EXECUTE_FLT1, gsl_complex_sqrt_real)

IMPLEMENT(CPX_EXECUTE_CPX1, gsl_complex_pow)	
IMPLEMENT(CPX_EXECUTE_FLT1, gsl_complex_pow_real)


IMPLEMENT(CPX_EXECUTE_CPX1, gsl_complex_exp)
IMPLEMENT(CPX_EXECUTE_CPX1, gsl_complex_log) 
IMPLEMENT(CPX_EXECUTE_CPX1, gsl_complex_log10)
IMPLEMENT(CPX_EXECUTE_CPX2, gsl_complex_log_b)*/




void Execute(uint x){
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
	}
}











#endif //__GSL_COMPLEX_INC__