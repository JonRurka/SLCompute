#ifndef _SLC_COMPLEX_IMP_INC_
#define _SLC_COMPLEX_IMP_INC_


#define INCLUDE_COMPLEX_ACCESSORS 1

#include "slc_core.inc"
#include "complex.inc"
#include "standard_buffers.inc"


// Function IDs

// 2-complex → complex
#define FUNC_ID_COMPLEX_ADD         1
#define FUNC_ID_COMPLEX_SUB         2
#define FUNC_ID_COMPLEX_MUL         3
#define FUNC_ID_COMPLEX_DIV         4

// 1-complex → float (properties)
#define FUNC_ID_COMPLEX_ARG         5
#define FUNC_ID_COMPLEX_ABS         6
#define FUNC_ID_COMPLEX_ABS2        7
#define FUNC_ID_COMPLEX_LOGABS      8

// complex + real → complex (arithmetic mixed)
#define FUNC_ID_COMPLEX_ADD_REAL    9
#define FUNC_ID_COMPLEX_SUB_REAL    10
#define FUNC_ID_COMPLEX_MUL_REAL    11
#define FUNC_ID_COMPLEX_DIV_REAL    12
#define FUNC_ID_COMPLEX_ADD_IMAG    13
#define FUNC_ID_COMPLEX_SUB_IMAG    14
#define FUNC_ID_COMPLEX_MUL_IMAG    15
#define FUNC_ID_COMPLEX_DIV_IMAG    16

// 1-complex → complex (arithmetic unary)
#define FUNC_ID_COMPLEX_CONJUGATE   17
#define FUNC_ID_COMPLEX_INVERSE     18
#define FUNC_ID_COMPLEX_NEGATIVE    19

// Elementary functions
#define FUNC_ID_COMPLEX_SQRT        20
#define FUNC_ID_COMPLEX_SQRT_REAL   21
#define FUNC_ID_COMPLEX_POW         22
#define FUNC_ID_COMPLEX_POW_REAL    23
#define FUNC_ID_COMPLEX_EXP         24
#define FUNC_ID_COMPLEX_LOG         25
#define FUNC_ID_COMPLEX_LOG10       26
#define FUNC_ID_COMPLEX_LOG_B       27

// Trigonometric
#define FUNC_ID_COMPLEX_SIN         28
#define FUNC_ID_COMPLEX_COS         29
#define FUNC_ID_COMPLEX_SEC         30
#define FUNC_ID_COMPLEX_CSC         31
#define FUNC_ID_COMPLEX_TAN         32
#define FUNC_ID_COMPLEX_COT         33

// Inverse trigonometric
#define FUNC_ID_COMPLEX_ARCSIN      34
#define FUNC_ID_COMPLEX_ARCSIN_REAL 35
#define FUNC_ID_COMPLEX_ARCCOS      36
#define FUNC_ID_COMPLEX_ARCCOS_REAL 37
#define FUNC_ID_COMPLEX_ARCSEC      38
#define FUNC_ID_COMPLEX_ARCSEC_REAL 39
#define FUNC_ID_COMPLEX_ARCCSC      40
#define FUNC_ID_COMPLEX_ARCCSC_REAL 41
#define FUNC_ID_COMPLEX_ARCTAN      42
#define FUNC_ID_COMPLEX_ARCCOT      43

// Hyperbolic
#define FUNC_ID_COMPLEX_SINH        44
#define FUNC_ID_COMPLEX_COSH        45
#define FUNC_ID_COMPLEX_SECH        46
#define FUNC_ID_COMPLEX_CSCH        47
#define FUNC_ID_COMPLEX_TANH        48
#define FUNC_ID_COMPLEX_COTH        49

// Inverse hyperbolic
#define FUNC_ID_COMPLEX_ARCSINH         50
#define FUNC_ID_COMPLEX_ARCCOSH         51
#define FUNC_ID_COMPLEX_ARCCOSH_REAL    52
#define FUNC_ID_COMPLEX_ARCSECH         53
#define FUNC_ID_COMPLEX_ARCCSCH         54
#define FUNC_ID_COMPLEX_ARCTANH         55
#define FUNC_ID_COMPLEX_ARCTANH_REAL    56
#define FUNC_ID_COMPLEX_ARCCOTH         57




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




// Function implementations

// 2-complex → complex
IMPLEMENT(CPX_EXECUTE_CPX2,   slc_complex_add)
IMPLEMENT(CPX_EXECUTE_CPX2,   slc_complex_sub)
IMPLEMENT(CPX_EXECUTE_CPX2,   slc_complex_mul)
IMPLEMENT(CPX_EXECUTE_CPX2,   slc_complex_div)

// 1-complex → float
IMPLEMENT(FLT_EXECUTE_CPX1,   slc_complex_arg)
IMPLEMENT(FLT_EXECUTE_CPX1,   slc_complex_abs)
IMPLEMENT(FLT_EXECUTE_CPX1,   slc_complex_abs2)
IMPLEMENT(FLT_EXECUTE_CPX1,   slc_complex_logabs)

// complex + real → complex
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_add_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_sub_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_mul_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_div_real)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_add_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_sub_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_mul_imag)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_div_imag)

// unary complex → complex
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_conjugate)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_inverse)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_negative)

// elementary functions
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_sqrt)
IMPLEMENT(CPX_EXECUTE_FLT1,   slc_complex_sqrt_real)
IMPLEMENT(CPX_EXECUTE_CPX2,   slc_complex_pow)
IMPLEMENT(CPX_EXECUTE_CPX_FLT, slc_complex_pow_real)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_exp)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_log)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_log10)
IMPLEMENT(CPX_EXECUTE_CPX2,   slc_complex_log_b)

// trig
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_sin)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_cos)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_sec)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_csc)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_tan)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_cot)

// inverse trig
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arcsin)
IMPLEMENT(CPX_EXECUTE_FLT1,   slc_complex_arcsin_real)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arccos)
IMPLEMENT(CPX_EXECUTE_FLT1,   slc_complex_arccos_real)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arcsec)
IMPLEMENT(CPX_EXECUTE_FLT1,   slc_complex_arcsec_real)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arccsc)
IMPLEMENT(CPX_EXECUTE_FLT1,   slc_complex_arccsc_real)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arctan)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arccot)

// hyperbolic
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_sinh)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_cosh)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_sech)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_csch)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_tanh)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_coth)

// inverse hyperbolic
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arcsinh)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arccosh)
IMPLEMENT(CPX_EXECUTE_FLT1,   slc_complex_arccosh_real)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arcsech)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arccsch)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arctanh)
IMPLEMENT(CPX_EXECUTE_FLT1,   slc_complex_arctanh_real)
IMPLEMENT(CPX_EXECUTE_CPX1,   slc_complex_arccoth)




// Main entry point
void Execute(uint x){
	uint func_id = SETTINGS_FUNC();
	switch(func_id){
		// 2-complex → complex
		case FUNC_ID_COMPLEX_ADD:           slc_complex_add_main(x);           break;
		case FUNC_ID_COMPLEX_SUB:           slc_complex_sub_main(x);           break;
		case FUNC_ID_COMPLEX_MUL:           slc_complex_mul_main(x);           break;
		case FUNC_ID_COMPLEX_DIV:           slc_complex_div_main(x);           break;

		// 1-complex → float
		case FUNC_ID_COMPLEX_ARG:           slc_complex_arg_main(x);           break;
		case FUNC_ID_COMPLEX_ABS:           slc_complex_abs_main(x);           break;
		case FUNC_ID_COMPLEX_ABS2:          slc_complex_abs2_main(x);          break;
		case FUNC_ID_COMPLEX_LOGABS:        slc_complex_logabs_main(x);        break;

		// complex + real → complex
		case FUNC_ID_COMPLEX_ADD_REAL:      slc_complex_add_real_main(x);      break;
		case FUNC_ID_COMPLEX_SUB_REAL:      slc_complex_sub_real_main(x);      break;
		case FUNC_ID_COMPLEX_MUL_REAL:      slc_complex_mul_real_main(x);      break;
		case FUNC_ID_COMPLEX_DIV_REAL:      slc_complex_div_real_main(x);      break;
		case FUNC_ID_COMPLEX_ADD_IMAG:      slc_complex_add_imag_main(x);      break;
		case FUNC_ID_COMPLEX_SUB_IMAG:      slc_complex_sub_imag_main(x);      break;
		case FUNC_ID_COMPLEX_MUL_IMAG:      slc_complex_mul_imag_main(x);      break;
		case FUNC_ID_COMPLEX_DIV_IMAG:      slc_complex_div_imag_main(x);      break;

		// unary complex → complex
		case FUNC_ID_COMPLEX_CONJUGATE:     slc_complex_conjugate_main(x);     break;
		case FUNC_ID_COMPLEX_INVERSE:       slc_complex_inverse_main(x);       break;
		case FUNC_ID_COMPLEX_NEGATIVE:      slc_complex_negative_main(x);      break;

		// elementary functions
		case FUNC_ID_COMPLEX_SQRT:          slc_complex_sqrt_main(x);          break;
		case FUNC_ID_COMPLEX_SQRT_REAL:     slc_complex_sqrt_real_main(x);     break;
		case FUNC_ID_COMPLEX_POW:           slc_complex_pow_main(x);           break;
		case FUNC_ID_COMPLEX_POW_REAL:      slc_complex_pow_real_main(x);      break;
		case FUNC_ID_COMPLEX_EXP:           slc_complex_exp_main(x);           break;
		case FUNC_ID_COMPLEX_LOG:           slc_complex_log_main(x);           break;
		case FUNC_ID_COMPLEX_LOG10:         slc_complex_log10_main(x);         break;
		case FUNC_ID_COMPLEX_LOG_B:         slc_complex_log_b_main(x);         break;

		// trig
		case FUNC_ID_COMPLEX_SIN:           slc_complex_sin_main(x);           break;
		case FUNC_ID_COMPLEX_COS:           slc_complex_cos_main(x);           break;
		case FUNC_ID_COMPLEX_SEC:           slc_complex_sec_main(x);           break;
		case FUNC_ID_COMPLEX_CSC:           slc_complex_csc_main(x);           break;
		case FUNC_ID_COMPLEX_TAN:           slc_complex_tan_main(x);           break;
		case FUNC_ID_COMPLEX_COT:           slc_complex_cot_main(x);           break;

		// inverse trig
		case FUNC_ID_COMPLEX_ARCSIN:        slc_complex_arcsin_main(x);        break;
		case FUNC_ID_COMPLEX_ARCSIN_REAL:   slc_complex_arcsin_real_main(x);   break;
		case FUNC_ID_COMPLEX_ARCCOS:        slc_complex_arccos_main(x);        break;
		case FUNC_ID_COMPLEX_ARCCOS_REAL:   slc_complex_arccos_real_main(x);   break;
		case FUNC_ID_COMPLEX_ARCSEC:        slc_complex_arcsec_main(x);        break;
		case FUNC_ID_COMPLEX_ARCSEC_REAL:   slc_complex_arcsec_real_main(x);   break;
		case FUNC_ID_COMPLEX_ARCCSC:        slc_complex_arccsc_main(x);        break;
		case FUNC_ID_COMPLEX_ARCCSC_REAL:   slc_complex_arccsc_real_main(x);   break;
		case FUNC_ID_COMPLEX_ARCTAN:        slc_complex_arctan_main(x);        break;
		case FUNC_ID_COMPLEX_ARCCOT:        slc_complex_arccot_main(x);        break;

		// hyperbolic
		case FUNC_ID_COMPLEX_SINH:          slc_complex_sinh_main(x);          break;
		case FUNC_ID_COMPLEX_COSH:          slc_complex_cosh_main(x);          break;
		case FUNC_ID_COMPLEX_SECH:          slc_complex_sech_main(x);          break;
		case FUNC_ID_COMPLEX_CSCH:          slc_complex_csch_main(x);          break;
		case FUNC_ID_COMPLEX_TANH:          slc_complex_tanh_main(x);          break;
		case FUNC_ID_COMPLEX_COTH:          slc_complex_coth_main(x);          break;

		// inverse hyperbolic
		case FUNC_ID_COMPLEX_ARCSINH:       slc_complex_arcsinh_main(x);       break;
		case FUNC_ID_COMPLEX_ARCCOSH:       slc_complex_arccosh_main(x);       break;
		case FUNC_ID_COMPLEX_ARCCOSH_REAL:  slc_complex_arccosh_real_main(x);  break;
		case FUNC_ID_COMPLEX_ARCSECH:       slc_complex_arcsech_main(x);       break;
		case FUNC_ID_COMPLEX_ARCCSCH:       slc_complex_arccsch_main(x);       break;
		case FUNC_ID_COMPLEX_ARCTANH:       slc_complex_arctanh_main(x);       break;
		case FUNC_ID_COMPLEX_ARCTANH_REAL:  slc_complex_arctanh_real_main(x);  break;
		case FUNC_ID_COMPLEX_ARCCOTH:       slc_complex_arccoth_main(x);       break;

		default: break;
	}
}




#endif
