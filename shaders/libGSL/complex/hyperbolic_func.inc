#ifndef _GSL_COMPLEX_HYPERBOLIC_FUNC_INC_
#define _GSL_COMPLEX_HYPERBOLIC_FUNC_INC_

/* Complex Hyperbolic Functions */

STRUCT gsl_complex gsl_complex_sinh (STRUCT gsl_complex a)  /* r=sinh(a) */
{
	gsl_type R = GSL_REAL (a); 
	gsl_type I = GSL_IMAG (a);

	gsl_complex z;
	GSL_SET_COMPLEX (z, sinh (R) * cos (I), cosh (R) * sin (I));
	return z;
}

STRUCT gsl_complex gsl_complex_cosh (STRUCT gsl_complex a)  /* r=coshh(a) */
{
	gsl_type R = GSL_REAL (a);
	gsl_type I = GSL_IMAG (a);

	gsl_complex z;
	GSL_SET_COMPLEX (z, cosh (R) * cos (I), sinh (R) * sin (I));
	return z;
}

STRUCT gsl_complex gsl_complex_sech (STRUCT gsl_complex a)  /* r=sech(a) */
{
	gsl_complex z = gsl_complex_cosh (a);
	return gsl_complex_inverse (z);
}

STRUCT gsl_complex gsl_complex_csch (STRUCT gsl_complex a)  /* r=csch(a) */
{
	gsl_complex z = gsl_complex_sinh (a);
	return gsl_complex_inverse (z);
}

STRUCT gsl_complex gsl_complex_tanh (STRUCT gsl_complex a)  /* r=tanh(a) */
{
	gsl_type R = GSL_REAL (a); 
	gsl_type I = GSL_IMAG (a);

	gsl_complex z;

	if (FABS(R) < 1.0) 
	{
		gsl_type D = pow (cos (I), 2.0) + pow (sinh (R), 2.0);

		GSL_SET_COMPLEX (z, sinh (R) * cosh (R) / D, 0.5 * sin (2.0 * I) / D);
	}
	else
	{
		gsl_type D = pow (cos (I), 2.0) + pow (sinh (R), 2.0);
		gsl_type F = 1.0 + pow (cos (I) / sinh (R), 2.0);

		GSL_SET_COMPLEX (z, 1.0 / (tanh (R) * F), 0.5 * sin (2.0 * I) / D);
	}

	return z;
}

STRUCT gsl_complex gsl_complex_coth (STRUCT gsl_complex a)  /* r=coth(a) */
{
	gsl_complex z = gsl_complex_tanh (a);
	return gsl_complex_inverse (z);
}

#endif