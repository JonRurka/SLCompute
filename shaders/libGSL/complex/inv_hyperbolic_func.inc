#ifndef _GSL_COMPLEX_INV_HYPERBOLIC_FUNC_INC_
#define _GSL_COMPLEX_INV_HYPERBOLIC_FUNC_INC_

/* Inverse Complex Hyperbolic Functions */

STRUCT gsl_complex gsl_complex_arcsinh (STRUCT gsl_complex a)  /* r=arcsinh(a) */
{
	gsl_complex z = gsl_complex_mul_imag(a, 1.0);
	z = gsl_complex_arcsin (z);
	z = gsl_complex_mul_imag (z, -1.0);
	return z;
}

STRUCT gsl_complex gsl_complex_arccosh (STRUCT gsl_complex a)  /* r=arccosh(a) */
{
	gsl_complex z = gsl_complex_arccos (a);
	z = gsl_complex_mul_imag (z, GSL_IMAG(z) > 0.0 ? -1.0 : 1.0);
	return z;
}

STRUCT gsl_complex gsl_complex_arccosh_real (gsl_type a)  /* r=arccosh(a) */
{
	gsl_complex z;

	if (a >= 1.0)
	{
		GSL_SET_COMPLEX (z, acosh (a), 0.0);
	}
	else
	{
		if (a >= -1.0)
		{
			GSL_SET_COMPLEX (z, 0.0, acos (a));
		}
		else
		{
			GSL_SET_COMPLEX (z, acosh (-a), M_PI);
		}
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arcsech (STRUCT gsl_complex a)  /* r=arcsech(a) */
{
	gsl_complex t = gsl_complex_inverse (a);
	return gsl_complex_arccosh (t);
}

STRUCT gsl_complex gsl_complex_arccsch (STRUCT gsl_complex a)  /* r=arccsch(a) */
{
	gsl_complex t = gsl_complex_inverse (a);
	return gsl_complex_arcsinh (t);
}

STRUCT gsl_complex gsl_complex_arctanh (STRUCT gsl_complex a)  /* r=arctanh(a) */
{
	if (GSL_IMAG (a) == 0.0)
	{
		return gsl_complex_arctanh_real (GSL_REAL (a));
	}
	else
	{
		gsl_complex z = gsl_complex_mul_imag(a, 1.0);
		z = gsl_complex_arctan (z);
		z = gsl_complex_mul_imag (z, -1.0);
		return z;
	}
}

STRUCT gsl_complex gsl_complex_arctanh_real (gsl_type a)  /* r=arctanh(a) */
{
	gsl_complex z;

	if (a > -1.0 && a < 1.0)
	{
		GSL_SET_COMPLEX (z, atanh (a), 0.0);
	}
	else
	{
		GSL_SET_COMPLEX (z, atanh (1.0 / a), (a < 0.0) ? M_PI_2 : -M_PI_2);
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arccoth (STRUCT gsl_complex a)  /* r=arccoth(a) */
{
	gsl_complex t = gsl_complex_inverse (a);
	return gsl_complex_arctanh (t);
}

#endif