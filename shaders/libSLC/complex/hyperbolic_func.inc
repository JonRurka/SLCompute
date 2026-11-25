#ifndef _SLC_COMPLEX_HYPERBOLIC_FUNC_INC_
#define _SLC_COMPLEX_HYPERBOLIC_FUNC_INC_

/* Complex Hyperbolic Functions */

STRUCT slc_complex slc_complex_sinh (STRUCT slc_complex a)  /* r=sinh(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);

	slc_complex z;
	SLC_SET_COMPLEX (z, sinh (R) * cos (I), cosh (R) * sin (I));
	return z;
}

STRUCT slc_complex slc_complex_cosh (STRUCT slc_complex a)  /* r=coshh(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);

	slc_complex z;
	SLC_SET_COMPLEX (z, cosh (R) * cos (I), sinh (R) * sin (I));
	return z;
}

STRUCT slc_complex slc_complex_sech (STRUCT slc_complex a)  /* r=sech(a) */
{
	slc_complex z = slc_complex_cosh (a);
	return slc_complex_inverse (z);
}

STRUCT slc_complex slc_complex_csch (STRUCT slc_complex a)  /* r=csch(a) */
{
	slc_complex z = slc_complex_sinh (a);
	return slc_complex_inverse (z);
}

STRUCT slc_complex slc_complex_tanh (STRUCT slc_complex a)  /* r=tanh(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);

	slc_complex z;

	if (FABS(R) < 1.0) 
	{
		slc_type D = pow (cos (I), 2.0) + pow (sinh (R), 2.0);

		SLC_SET_COMPLEX (z, sinh (R) * cosh (R) / D, 0.5 * sin (2.0 * I) / D);
	}
	else
	{
		slc_type D = pow (cos (I), 2.0) + pow (sinh (R), 2.0);
		slc_type F = 1.0 + pow (cos (I) / sinh (R), 2.0);

		SLC_SET_COMPLEX (z, 1.0 / (tanh (R) * F), 0.5 * sin (2.0 * I) / D);
	}

	return z;
}

STRUCT slc_complex slc_complex_coth (STRUCT slc_complex a)  /* r=coth(a) */
{
	slc_complex z = slc_complex_tanh (a);
	return slc_complex_inverse (z);
}

#endif