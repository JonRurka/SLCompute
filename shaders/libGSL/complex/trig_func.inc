#ifndef _GSL_COMPLEX_TRIG_FUNC_INC_
#define _GSL_COMPLEX_TRIG_FUNC_INC_

/* Complex Trigonometric Functions */

STRUCT gsl_complex gsl_complex_sin (STRUCT gsl_complex a)  /* r=sin(a) */
{
	gsl_type R = GSL_REAL (a);
	gsl_type I = GSL_IMAG (a);

	gsl_complex z;

	if (I == 0.0) 
	{
		/* avoid returing negative zero (-0.0) for the imaginary part  */

		GSL_SET_COMPLEX (z, sin (R), 0.0);  
	} 
	else 
	{
		GSL_SET_COMPLEX (z, sin (R) * cosh (I), cos (R) * sinh (I));
	}

	return z;
}

STRUCT gsl_complex gsl_complex_cos (STRUCT gsl_complex a)  /* r=cos(a) */
{
	gsl_type R = GSL_REAL (a);
	gsl_type I = GSL_IMAG (a);

	gsl_complex z;

	if (I == 0.0) 
	{
		/* avoid returing negative zero (-0.0) for the imaginary part  */

		GSL_SET_COMPLEX (z, cos (R), 0.0);  
	} 
	else 
	{
		GSL_SET_COMPLEX (z, cos (R) * cosh (I), sin (R) * sinh (-I));
	}

	return z;
}

STRUCT gsl_complex gsl_complex_sec (STRUCT gsl_complex a)  /* r=sec(a) */
{
	gsl_complex z = gsl_complex_cos (a);
	return gsl_complex_inverse (z);
}

STRUCT gsl_complex gsl_complex_csc (STRUCT gsl_complex a)  /* r=csc(a) */
{
	gsl_complex z = gsl_complex_sin (a);
	return gsl_complex_inverse(z);
}

STRUCT gsl_complex gsl_complex_tan (STRUCT gsl_complex a)  /* r=tan(a) */
{
	gsl_type R = GSL_REAL (a);
	gsl_type I = GSL_IMAG (a);

	gsl_complex z;

	if (FABS (I) < 1.0)
	{
		gsl_type D = pow (cos (R), 2.0) + pow (sinh (I), 2.0);

		GSL_SET_COMPLEX (z, 0.5 * sin (2.0 * R) / D, 0.5 * sinh (2.0 * I) / D);
	}
	else
	{
		gsl_type D = pow (cos (R), 2.0) + pow (sinh (I), 2.0);
		gsl_type F = 1.0 + pow(cos (R)/sinh (I), 2.0);

		GSL_SET_COMPLEX (z, 0.5 * sin (2.0 * R) / D, 1.0 / (tanh (I) * F));
	}

	return z;
}

STRUCT gsl_complex gsl_complex_cot (STRUCT gsl_complex a)  /* r=cot(a) */
{
	gsl_complex z = gsl_complex_tan (a);
	return gsl_complex_inverse (z);
}

#endif