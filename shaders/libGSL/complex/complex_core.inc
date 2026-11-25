#ifndef _GSL_COMPLEX_CORE_INC_
#define _GSL_COMPLEX_CORE_INC_

#ifndef TYPE
#define TYPE gsl_type;
#endif

struct gsl_complex
{
	gsl_type dat[2];
};

#define GSL_REAL(z) ((z).dat[0])
#define GSL_IMAG(z) ((z).dat[1])
#define GSL_REAL_INT(z) (ROUNT_TO_INT((z).dat[0]))
#define GSL_IMAG_INT(z) (ROUNT_TO_INT((z).dat[1]))
#define GSL_COMPLEX_P(zp) ((zp)->dat)
#define GSL_COMPLEX_P_REAL(zp) ((zp).dat[0])
#define GSL_COMPLEX_P_IMAG(zp) ((zp).dat[1])

// TODO: should probably use gsl_fcmp
#define GSL_COMPLEX_EQ(z1,z2) (((z1).dat[0] == (z2).dat[0]) && ((z1).dat[1] == (z2).dat[1]))

#define GSL_SET_COMPLEX(zp,x,y)  do {(zp).dat[0]=(x); (zp).dat[1]=(y);} while(false)
#define GSL_SET_REAL(zp,x)       do {(zp)->dat[0]=(x);} while(false)
#define GSL_SET_IMAG(zp,y)       do {(zp)->dat[1]=(y);} while(false)

/* Complex numbers */

STRUCT gsl_complex gsl_complex_polar (gsl_type r, gsl_type theta) /* r= r e^(i theta) */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, r * cos (theta), r * sin (theta));
	return z;
}

STRUCT gsl_complex gsl_complex_rect (gsl_type x, gsl_type y)  /* r= real+i*imag */
{
	/* return z = x + i y */
	gsl_complex z;
	GSL_SET_COMPLEX (z, x, y);
	return z;
}

#define GSL_COMPLEX_ONE (gsl_complex_rect(1.0,0.0))
#define GSL_COMPLEX_ZERO (gsl_complex_rect(0.0,0.0))
#define GSL_COMPLEX_NEGONE (gsl_complex_rect(-1.0,0.0))

/* Properties of complex numbers */

gsl_type gsl_complex_arg (STRUCT gsl_complex z); /* return arg(z), -pi< arg(z) <=+pi */
gsl_type gsl_complex_abs (STRUCT gsl_complex z);   /* return |z|   */
gsl_type gsl_complex_abs2 (STRUCT gsl_complex z);  /* return |z|^2 */
gsl_type gsl_complex_logabs (STRUCT gsl_complex z); /* return log|z| */

/* Complex arithmetic operators */

STRUCT gsl_complex gsl_complex_add (STRUCT gsl_complex a, STRUCT gsl_complex b);  /* r=a+b */
STRUCT gsl_complex gsl_complex_sub (STRUCT gsl_complex a, STRUCT gsl_complex b);  /* r=a-b */
STRUCT gsl_complex gsl_complex_mul (STRUCT gsl_complex a, STRUCT gsl_complex b);  /* r=a*b */
STRUCT gsl_complex gsl_complex_div (STRUCT gsl_complex a, STRUCT gsl_complex b);  /* r=a/b */
                                                           
STRUCT gsl_complex gsl_complex_add_real (STRUCT gsl_complex a, gsl_type x);  /* r=a+x */
STRUCT gsl_complex gsl_complex_sub_real (STRUCT gsl_complex a, gsl_type x);  /* r=a-x */
STRUCT gsl_complex gsl_complex_mul_real (STRUCT gsl_complex a, gsl_type x);  /* r=a*x */
STRUCT gsl_complex gsl_complex_div_real (STRUCT gsl_complex a, gsl_type x);  /* r=a/x */

STRUCT gsl_complex gsl_complex_add_imag (STRUCT gsl_complex a, gsl_type y);  /* r=a+iy */
STRUCT gsl_complex gsl_complex_sub_imag (STRUCT gsl_complex a, gsl_type y);  /* r=a-iy */
STRUCT gsl_complex gsl_complex_mul_imag (STRUCT gsl_complex a, gsl_type y);  /* r=a*iy */
STRUCT gsl_complex gsl_complex_div_imag (STRUCT gsl_complex a, gsl_type y);  /* r=a/iy */

STRUCT gsl_complex gsl_complex_conjugate (STRUCT gsl_complex z);  /* r=conj(z) */
STRUCT gsl_complex gsl_complex_inverse (STRUCT gsl_complex a);    /* r=1/a */
STRUCT gsl_complex gsl_complex_negative (STRUCT gsl_complex a);    /* r=-a */

/* Elementary Complex Functions */

STRUCT gsl_complex gsl_complex_sqrt (STRUCT gsl_complex z);  /* r=sqrt(z) */
STRUCT gsl_complex gsl_complex_sqrt_real (gsl_type x);  /* r=sqrt(x) (x<0 ok) */

STRUCT gsl_complex gsl_complex_pow (STRUCT gsl_complex a, STRUCT gsl_complex b);  /* r=a^b */
STRUCT gsl_complex gsl_complex_pow_real (STRUCT gsl_complex a, gsl_type b);  /* r=a^b */

STRUCT gsl_complex gsl_complex_exp (STRUCT gsl_complex a);    /* r=exp(a) */
STRUCT gsl_complex gsl_complex_log (STRUCT gsl_complex a);    /* r=log(a) (base e) */
STRUCT gsl_complex gsl_complex_log10 (STRUCT gsl_complex a);  /* r=log10(a) (base 10) */
STRUCT gsl_complex gsl_complex_log_b (STRUCT gsl_complex a, STRUCT gsl_complex b);   /* r=log_b(a) (base=b) */

/* Complex Trigonometric Functions */

STRUCT gsl_complex gsl_complex_sin (STRUCT gsl_complex a);  /* r=sin(a) */
STRUCT gsl_complex gsl_complex_cos (STRUCT gsl_complex a);  /* r=cos(a) */
STRUCT gsl_complex gsl_complex_sec (STRUCT gsl_complex a);  /* r=sec(a) */
STRUCT gsl_complex gsl_complex_csc (STRUCT gsl_complex a);  /* r=csc(a) */
STRUCT gsl_complex gsl_complex_tan (STRUCT gsl_complex a);  /* r=tan(a) */
STRUCT gsl_complex gsl_complex_cot (STRUCT gsl_complex a);  /* r=cot(a) */

/* Inverse Complex Trigonometric Functions */

STRUCT gsl_complex gsl_complex_arcsin (STRUCT gsl_complex a);  /* r=arcsin(a) */
STRUCT gsl_complex gsl_complex_arcsin_real (gsl_type a);  /* r=arcsin(a) */
STRUCT gsl_complex gsl_complex_arccos (STRUCT gsl_complex a);  /* r=arccos(a) */
STRUCT gsl_complex gsl_complex_arccos_real (gsl_type a);  /* r=arccos(a) */
STRUCT gsl_complex gsl_complex_arcsec (STRUCT gsl_complex a);  /* r=arcsec(a) */
STRUCT gsl_complex gsl_complex_arcsec_real (gsl_type a);  /* r=arcsec(a) */
STRUCT gsl_complex gsl_complex_arccsc (STRUCT gsl_complex a);  /* r=arccsc(a) */
STRUCT gsl_complex gsl_complex_arccsc_real (gsl_type a);  /* r=arccsc(a) */
STRUCT gsl_complex gsl_complex_arctan (STRUCT gsl_complex a);  /* r=arctan(a) */
STRUCT gsl_complex gsl_complex_arccot (STRUCT gsl_complex a);  /* r=arccot(a) */

/* Complex Hyperbolic Functions */

STRUCT gsl_complex gsl_complex_sinh (STRUCT gsl_complex a);  /* r=sinh(a) */
STRUCT gsl_complex gsl_complex_cosh (STRUCT gsl_complex a);  /* r=coshh(a) */
STRUCT gsl_complex gsl_complex_sech (STRUCT gsl_complex a);  /* r=sech(a) */
STRUCT gsl_complex gsl_complex_csch (STRUCT gsl_complex a);  /* r=csch(a) */
STRUCT gsl_complex gsl_complex_tanh (STRUCT gsl_complex a);  /* r=tanh(a) */
STRUCT gsl_complex gsl_complex_coth (STRUCT gsl_complex a);  /* r=coth(a) */

/* Inverse Complex Hyperbolic Functions */

STRUCT gsl_complex gsl_complex_arcsinh (STRUCT gsl_complex a);  /* r=arcsinh(a) */
STRUCT gsl_complex gsl_complex_arccosh (STRUCT gsl_complex a);  /* r=arccosh(a) */
STRUCT gsl_complex gsl_complex_arccosh_real (gsl_type a);  /* r=arccosh(a) */
STRUCT gsl_complex gsl_complex_arcsech (STRUCT gsl_complex a);  /* r=arcsech(a) */
STRUCT gsl_complex gsl_complex_arccsch (STRUCT gsl_complex a);  /* r=arccsch(a) */
STRUCT gsl_complex gsl_complex_arctanh (STRUCT gsl_complex a);  /* r=arctanh(a) */
STRUCT gsl_complex gsl_complex_arctanh_real (gsl_type a);  /* r=arctanh(a) */
STRUCT gsl_complex gsl_complex_arccoth (STRUCT gsl_complex a);  /* r=arccoth(a) */


#include "properties.inc"
#include "arithmetic_op.inc"
#include "elem_func.inc"
#include "trig_func.inc"
#include "inv_trig_func.inc"
#include "hyperbolic_func.inc"
#include "inv_hyperbolic_func.inc"

#endif //__GSL_COMPLEX_CORE_INC__