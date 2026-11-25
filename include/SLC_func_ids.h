#pragma once

#define PROGRAM_NAME_UTILITIES "utilities"
#define PROGRAM_ID_UTILITIES 0

#define PROGRAM_NAME_COMPLEX "complex"
#define PROGRAM_ID_COMPLEX 1


#define FUNCTION_UTILITIES_LOAD_SOURCE_FLOAT 1
#define FUNCTION_UTILITIES_LOAD_SOURCE_COMPLEX 2


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
