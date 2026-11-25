#ifndef _SLC_COMPLEX_TRIG_FUNC_INC_
#define _SLC_COMPLEX_TRIG_FUNC_INC_

/* Complex Trigonometric Functions */

STRUCT slc_complex slc_complex_sin (STRUCT slc_complex a)  /* r=sin(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);

	slc_complex z;

	if (I == 0.0) 
	{
		/* avoid returing negative zero (-0.0) for the imaginary part  */

		SLC_SET_COMPLEX (z, sin (R), 0.0);
	} 
	else 
	{
		SLC_SET_COMPLEX (z, sin (R) * cosh (I), cos (R) * sinh (I));
	}

	return z;
}

STRUCT slc_complex slc_complex_cos (STRUCT slc_complex a)  /* r=cos(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);

	slc_complex z;

	if (I == 0.0) 
	{
		/* avoid returing negative zero (-0.0) for the imaginary part  */

		SLC_SET_COMPLEX (z, cos (R), 0.0);
	} 
	else 
	{
		SLC_SET_COMPLEX (z, cos (R) * cosh (I), sin (R) * sinh (-I));
	}

	return z;
}

STRUCT slc_complex slc_complex_sec (STRUCT slc_complex a)  /* r=sec(a) */
{
	slc_complex z = slc_complex_cos (a);
	return slc_complex_inverse (z);
}

STRUCT slc_complex slc_complex_csc (STRUCT slc_complex a)  /* r=csc(a) */
{
	slc_complex z = slc_complex_sin (a);
	return slc_complex_inverse(z);
}

STRUCT slc_complex slc_complex_tan (STRUCT slc_complex a)  /* r=tan(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);

	slc_complex z;

	if (FABS (I) < 1.0)
	{
		slc_type D = pow (cos (R), 2.0) + pow (sinh (I), 2.0);

		SLC_SET_COMPLEX (z, 0.5 * sin (2.0 * R) / D, 0.5 * sinh (2.0 * I) / D);
	}
	else
	{
		slc_type D = pow (cos (R), 2.0) + pow (sinh (I), 2.0);
		slc_type F = 1.0 + pow(cos (R)/sinh (I), 2.0);

		SLC_SET_COMPLEX (z, 0.5 * sin (2.0 * R) / D, 1.0 / (tanh (I) * F));
	}

	return z;
}

STRUCT slc_complex slc_complex_cot (STRUCT slc_complex a)  /* r=cot(a) */
{
	slc_complex z = slc_complex_tan (a);
	return slc_complex_inverse (z);
}

#endif