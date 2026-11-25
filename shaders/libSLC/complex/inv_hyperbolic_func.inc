#ifndef _SLC_COMPLEX_INV_HYPERBOLIC_FUNC_INC_
#define _SLC_COMPLEX_INV_HYPERBOLIC_FUNC_INC_

/* Inverse Complex Hyperbolic Functions */

STRUCT slc_complex slc_complex_arcsinh (STRUCT slc_complex a)  /* r=arcsinh(a) */
{
	slc_complex z = slc_complex_mul_imag(a, 1.0);
	z = slc_complex_arcsin (z);
	z = slc_complex_mul_imag (z, -1.0);
	return z;
}

STRUCT slc_complex slc_complex_arccosh (STRUCT slc_complex a)  /* r=arccosh(a) */
{
	slc_complex z = slc_complex_arccos (a);
	z = slc_complex_mul_imag (z, SLC_IMAG(z) > 0.0 ? -1.0 : 1.0);
	return z;
}

STRUCT slc_complex slc_complex_arccosh_real (slc_type a)  /* r=arccosh(a) */
{
	slc_complex z;

	if (a >= 1.0)
	{
		SLC_SET_COMPLEX (z, acosh (a), 0.0);
	}
	else
	{
		if (a >= -1.0)
		{
			SLC_SET_COMPLEX (z, 0.0, acos (a));
		}
		else
		{
			SLC_SET_COMPLEX (z, acosh (-a), M_PI);
		}
	}

	return z;
}

STRUCT slc_complex slc_complex_arcsech (STRUCT slc_complex a)  /* r=arcsech(a) */
{
	slc_complex t = slc_complex_inverse (a);
	return slc_complex_arccosh (t);
}

STRUCT slc_complex slc_complex_arccsch (STRUCT slc_complex a)  /* r=arccsch(a) */
{
	slc_complex t = slc_complex_inverse (a);
	return slc_complex_arcsinh (t);
}

STRUCT slc_complex slc_complex_arctanh (STRUCT slc_complex a)  /* r=arctanh(a) */
{
	if (SLC_IMAG (a) == 0.0)
	{
		return slc_complex_arctanh_real (SLC_REAL (a));
	}
	else
	{
		slc_complex z = slc_complex_mul_imag(a, 1.0);
		z = slc_complex_arctan (z);
		z = slc_complex_mul_imag (z, -1.0);
		return z;
	}
}

STRUCT slc_complex slc_complex_arctanh_real (slc_type a)  /* r=arctanh(a) */
{
	slc_complex z;

	if (a > -1.0 && a < 1.0)
	{
		SLC_SET_COMPLEX (z, atanh (a), 0.0);
	}
	else
	{
		SLC_SET_COMPLEX (z, atanh (1.0 / a), (a < 0.0) ? M_PI_2 : -M_PI_2);
	}

	return z;
}

STRUCT slc_complex slc_complex_arccoth (STRUCT slc_complex a)  /* r=arccoth(a) */
{
	slc_complex t = slc_complex_inverse (a);
	return slc_complex_arctanh (t);
}

#endif