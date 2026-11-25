#ifndef _GSL_LIB_TYPE_H_
#define _GSL_LIB_TYPE_H_

#ifndef STRUCT
#define STRUCT
#endif

#ifdef GSL_FLOAT
//typedef float gsl_type;
#define gsl_type float
#define FOUND_TYPE
#endif
	
#ifdef  GSL_DOUBLE
//typedef double gsl_type;
#define gsl_type double
#define FOUND_TYPE
#endif
	
#ifndef FOUND_TYPE
//typedef float gsl_type;
#define gsl_type float
#define GSL_FLOAT
#endif

#ifdef HLSL
#define GSL_TYPE(x) gsl_type(x)
#define GSL_CAST(t, x) t(x)
#define FOUND_LANG
#endif

#ifdef GLSL
#define GSL_TYPE(x) (gsl_type)(x)
#define GSL_CAST(t, x) t(x)
#define FOUND_LANG
#endif

#define POOL_TYPE_DYNAMIC 1
#define POOL_TYPE_STATIC 2

#ifndef FOUND_LANG
You need to define either HLSL or GLSL
#endif

#endif // __GSL_LIB_TYPE_H__