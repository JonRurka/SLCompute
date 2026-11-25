#ifndef _SLC_COMPLEX_CORE_INC_
#define _SLC_COMPLEX_CORE_INC_

#ifndef TYPE
#define TYPE slc_type;
#endif


/* Properties of complex numbers */

slc_type slc_complex_arg (STRUCT slc_complex z); /* return arg(z), -pi< arg(z) <=+pi */
slc_type slc_complex_abs (STRUCT slc_complex z);   /* return |z|   */
slc_type slc_complex_abs2 (STRUCT slc_complex z);  /* return |z|^2 */
slc_type slc_complex_logabs (STRUCT slc_complex z); /* return log|z| */

/* Complex arithmetic operators */

STRUCT slc_complex slc_complex_add (STRUCT slc_complex a, STRUCT slc_complex b);  /* r=a+b */
STRUCT slc_complex slc_complex_sub (STRUCT slc_complex a, STRUCT slc_complex b);  /* r=a-b */
STRUCT slc_complex slc_complex_mul (STRUCT slc_complex a, STRUCT slc_complex b);  /* r=a*b */
STRUCT slc_complex slc_complex_div (STRUCT slc_complex a, STRUCT slc_complex b);  /* r=a/b */
                                                           
STRUCT slc_complex slc_complex_add_real (STRUCT slc_complex a, slc_type x);  /* r=a+x */
STRUCT slc_complex slc_complex_sub_real (STRUCT slc_complex a, slc_type x);  /* r=a-x */
STRUCT slc_complex slc_complex_mul_real (STRUCT slc_complex a, slc_type x);  /* r=a*x */
STRUCT slc_complex slc_complex_div_real (STRUCT slc_complex a, slc_type x);  /* r=a/x */

STRUCT slc_complex slc_complex_add_imag (STRUCT slc_complex a, slc_type y);  /* r=a+iy */
STRUCT slc_complex slc_complex_sub_imag (STRUCT slc_complex a, slc_type y);  /* r=a-iy */
STRUCT slc_complex slc_complex_mul_imag (STRUCT slc_complex a, slc_type y);  /* r=a*iy */
STRUCT slc_complex slc_complex_div_imag (STRUCT slc_complex a, slc_type y);  /* r=a/iy */

STRUCT slc_complex slc_complex_conjugate (STRUCT slc_complex z);  /* r=conj(z) */
STRUCT slc_complex slc_complex_inverse (STRUCT slc_complex a);    /* r=1/a */
STRUCT slc_complex slc_complex_negative (STRUCT slc_complex a);    /* r=-a */

/* Elementary Complex Functions */

STRUCT slc_complex slc_complex_sqrt (STRUCT slc_complex z);  /* r=sqrt(z) */
STRUCT slc_complex slc_complex_sqrt_real (slc_type x);  /* r=sqrt(x) (x<0 ok) */

STRUCT slc_complex slc_complex_pow (STRUCT slc_complex a, STRUCT slc_complex b);  /* r=a^b */
STRUCT slc_complex slc_complex_pow_real (STRUCT slc_complex a, slc_type b);  /* r=a^b */

STRUCT slc_complex slc_complex_exp (STRUCT slc_complex a);    /* r=exp(a) */
STRUCT slc_complex slc_complex_log (STRUCT slc_complex a);    /* r=log(a) (base e) */
STRUCT slc_complex slc_complex_log10 (STRUCT slc_complex a);  /* r=log10(a) (base 10) */
STRUCT slc_complex slc_complex_log_b (STRUCT slc_complex a, STRUCT slc_complex b);   /* r=log_b(a) (base=b) */

/* Complex Trigonometric Functions */

STRUCT slc_complex slc_complex_sin (STRUCT slc_complex a);  /* r=sin(a) */
STRUCT slc_complex slc_complex_cos (STRUCT slc_complex a);  /* r=cos(a) */
STRUCT slc_complex slc_complex_sec (STRUCT slc_complex a);  /* r=sec(a) */
STRUCT slc_complex slc_complex_csc (STRUCT slc_complex a);  /* r=csc(a) */
STRUCT slc_complex slc_complex_tan (STRUCT slc_complex a);  /* r=tan(a) */
STRUCT slc_complex slc_complex_cot (STRUCT slc_complex a);  /* r=cot(a) */

/* Inverse Complex Trigonometric Functions */

STRUCT slc_complex slc_complex_arcsin (STRUCT slc_complex a);  /* r=arcsin(a) */
STRUCT slc_complex slc_complex_arcsin_real (slc_type a);  /* r=arcsin(a) */
STRUCT slc_complex slc_complex_arccos (STRUCT slc_complex a);  /* r=arccos(a) */
STRUCT slc_complex slc_complex_arccos_real (slc_type a);  /* r=arccos(a) */
STRUCT slc_complex slc_complex_arcsec (STRUCT slc_complex a);  /* r=arcsec(a) */
STRUCT slc_complex slc_complex_arcsec_real (slc_type a);  /* r=arcsec(a) */
STRUCT slc_complex slc_complex_arccsc (STRUCT slc_complex a);  /* r=arccsc(a) */
STRUCT slc_complex slc_complex_arccsc_real (slc_type a);  /* r=arccsc(a) */
STRUCT slc_complex slc_complex_arctan (STRUCT slc_complex a);  /* r=arctan(a) */
STRUCT slc_complex slc_complex_arccot (STRUCT slc_complex a);  /* r=arccot(a) */

/* Complex Hyperbolic Functions */

STRUCT slc_complex slc_complex_sinh (STRUCT slc_complex a);  /* r=sinh(a) */
STRUCT slc_complex slc_complex_cosh (STRUCT slc_complex a);  /* r=coshh(a) */
STRUCT slc_complex slc_complex_sech (STRUCT slc_complex a);  /* r=sech(a) */
STRUCT slc_complex slc_complex_csch (STRUCT slc_complex a);  /* r=csch(a) */
STRUCT slc_complex slc_complex_tanh (STRUCT slc_complex a);  /* r=tanh(a) */
STRUCT slc_complex slc_complex_coth (STRUCT slc_complex a);  /* r=coth(a) */

/* Inverse Complex Hyperbolic Functions */

STRUCT slc_complex slc_complex_arcsinh (STRUCT slc_complex a);  /* r=arcsinh(a) */
STRUCT slc_complex slc_complex_arccosh (STRUCT slc_complex a);  /* r=arccosh(a) */
STRUCT slc_complex slc_complex_arccosh_real (slc_type a);  /* r=arccosh(a) */
STRUCT slc_complex slc_complex_arcsech (STRUCT slc_complex a);  /* r=arcsech(a) */
STRUCT slc_complex slc_complex_arccsch (STRUCT slc_complex a);  /* r=arccsch(a) */
STRUCT slc_complex slc_complex_arctanh (STRUCT slc_complex a);  /* r=arctanh(a) */
STRUCT slc_complex slc_complex_arctanh_real (slc_type a);  /* r=arctanh(a) */
STRUCT slc_complex slc_complex_arccoth (STRUCT slc_complex a);  /* r=arccoth(a) */


#include "properties.inc"
#include "arithmetic_op.inc"
#include "elem_func.inc"
#include "trig_func.inc"
#include "inv_trig_func.inc"
#include "hyperbolic_func.inc"
#include "inv_hyperbolic_func.inc"

#endif //__SLC_COMPLEX_CORE_INC__