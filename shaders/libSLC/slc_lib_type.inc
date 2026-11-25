#ifndef _SLC_LIB_TYPE_H_
#define _SLC_LIB_TYPE_H_

#ifndef STRUCT
#define STRUCT
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef SLC_FLOAT
//typedef float slc_type;
#define slc_type float
#define FOUND_TYPE
#endif
	
#ifdef  SLC_DOUBLE
//typedef double slc_type;
#define slc_type double
#define FOUND_TYPE
#endif
	
#ifndef FOUND_TYPE
//typedef float slc_type;
#define slc_type float
#define SLC_FLOAT
#endif

#ifdef HLSL
#define SLC_TYPE(x) slc_type(x)
#define SLC_CAST(t, x) t(x)
#define FOUND_LANG
#endif

#ifdef GLSL
#define SLC_TYPE(x) (slc_type)(x)
#define SLC_CAST(t, x) t(x)
#define FOUND_LANG
#endif

// Complex data type
#define COMPLEX_TYPE_STRIDE 2
struct slc_complex
{
	slc_type dat[2];
};
#define SLC_REAL(z) ((z).dat[0])
#define SLC_IMAG(z) ((z).dat[1])
#define SLC_REAL_INT(z) (ROUNT_TO_INT((z).dat[0]))
#define SLC_IMAG_INT(z) (ROUNT_TO_INT((z).dat[1]))
#define SLC_COMPLEX_P(zp) ((zp)->dat)
#define SLC_COMPLEX_P_REAL(zp) ((zp).dat[0])
#define SLC_COMPLEX_P_IMAG(zp) ((zp).dat[1])

// TODO: should probably use slc_fcmp
#define SLC_COMPLEX_EQ(z1,z2) (((z1).dat[0] == (z2).dat[0]) && ((z1).dat[1] == (z2).dat[1]))

#define SLC_SET_COMPLEX(zp,x,y)  do {(zp).dat[0]=(x); (zp).dat[1]=(y);} while(false)
#define SLC_SET_REAL(zp,x)       do {(zp)->dat[0]=(x);} while(false)
#define SLC_SET_IMAG(zp,y)       do {(zp)->dat[1]=(y);} while(false)

/* Complex numbers */

STRUCT slc_complex slc_complex_polar (slc_type r, slc_type theta) /* r= r e^(i theta) */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, r * cos (theta), r * sin (theta));
	return z;
}

STRUCT slc_complex slc_complex_rect (slc_type x, slc_type y)  /* r= real+i*imag */
{
	/* return z = x + i y */
	slc_complex z;
	SLC_SET_COMPLEX (z, x, y);
	return z;
}

#define SLC_COMPLEX_ONE (slc_complex_rect(1.0,0.0))
#define SLC_COMPLEX_ZERO (slc_complex_rect(0.0,0.0))
#define SLC_COMPLEX_NEGONE (slc_complex_rect(-1.0,0.0))


#ifndef FOUND_LANG
You need to define either HLSL or GLSL
#endif

#endif // __SLC_LIB_TYPE_H__