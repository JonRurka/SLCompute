#ifndef _SLC_COMPLEX_ELEM_FUNC_INC_
#define _SLC_COMPLEX_ELEM_FUNC_INC_

/* Elementary Complex Functions */

STRUCT slc_complex slc_complex_sqrt (STRUCT slc_complex a)  /* r=sqrt(z) */
{
	slc_complex z;
	
	slc_type a_real = SLC_REAL (a);
	slc_type a_imag = SLC_IMAG (a);

	if (a_real == 0.0 && a_imag == 0.0)
	{
		SLC_SET_COMPLEX (z, 0.0, 0.0);
	}
	else
	{
		slc_type x = FABS (a_real);
		slc_type y = FABS (a_imag);
		slc_type w;

		if (x >= y)
		{
			slc_type t = y / x;
			w = sqrt (x) * sqrt (0.5 * (1.0 + sqrt (1.0 + t * t)));
		}
		else
		{
			slc_type t = x / y;
			w = sqrt (y) * sqrt (0.5 * (t + sqrt (1.0 + t * t)));
		}

		if (a_real >= 0.0)
		{
			slc_type ai = a_imag;
			SLC_SET_COMPLEX (z, w, ai / (2.0 * w));
		}
		else
		{
			slc_type ai = a_imag;
			slc_type vi = (ai >= 0.0) ? w : -w;
			SLC_SET_COMPLEX (z, ai / (2.0 * vi), vi);
		}
	}

	return z;
}

STRUCT slc_complex slc_complex_sqrt_real (slc_type x)  /* r=sqrt(x) (x<0 ok) */
{
	slc_complex z;

	if (x >= 0.0)
	{
		SLC_SET_COMPLEX (z, sqrt (x), 0.0);
	}
	else
	{
		SLC_SET_COMPLEX (z, 0.0, sqrt (-x));
	}

	return z;
}

STRUCT slc_complex slc_complex_pow (STRUCT slc_complex a, STRUCT slc_complex b)  /* r=a^b */
{
	slc_complex z;

	if (SLC_REAL (a) == 0.0 && SLC_IMAG (a) == 0.0)
	{
		if (SLC_REAL (b) == 0.0 && SLC_IMAG (b) == 0.0)
		{
			SLC_SET_COMPLEX (z, 1.0, 0.0);
		}
		else 
		{
			SLC_SET_COMPLEX (z, 0.0, 0.0);
		}
	}
	else if (SLC_REAL (b) == 1.0 && SLC_IMAG (b) == 0.0)
	{
		return a;
	}
	else if (SLC_REAL (b) == -1.0 && SLC_IMAG (b) == 0.0)
	{
		return slc_complex_inverse (a);
	}
	else
	{
		slc_type logr = slc_complex_logabs (a);
		slc_type theta = slc_complex_arg (a);

		slc_type br = SLC_REAL (b), bi = SLC_IMAG (b);

		slc_type rho = exp (logr * br - bi * theta);
		slc_type beta = theta * br + bi * logr;

		SLC_SET_COMPLEX (z, rho * cos (beta), rho * sin (beta));
	}

	return z;
}

STRUCT slc_complex slc_complex_pow_real (STRUCT slc_complex a, slc_type b)  /* r=a^b */
{
	slc_complex z;

	if (SLC_REAL (a) == 0.0 && SLC_IMAG (a) == 0.0)
	{
		if (b == 0.0)
		{
			SLC_SET_COMPLEX (z, 1.0, 0.0);
		}
		else
		{
			SLC_SET_COMPLEX (z, 0.0, 0.0);
		}
	}
	else
	{
		slc_type logr = slc_complex_logabs (a);
		slc_type theta = slc_complex_arg (a);
		slc_type rho = exp (logr * b);
		slc_type beta = theta * b;
		SLC_SET_COMPLEX (z, rho * cos (beta), rho * sin (beta));
	}

	return z;
}

STRUCT slc_complex slc_complex_exp (STRUCT slc_complex a)    /* r=exp(a) */
{
	slc_type rho = exp (SLC_REAL (a));
	slc_type theta = SLC_IMAG (a);

	slc_complex z;
	SLC_SET_COMPLEX (z, rho * cos (theta), rho * sin (theta));
	return z;
}

STRUCT slc_complex slc_complex_log (STRUCT slc_complex a)    /* r=log(a) (base e) */
{
	slc_type logr = slc_complex_logabs (a);
	slc_type theta = slc_complex_arg (a);

	slc_complex z;
	SLC_SET_COMPLEX (z, logr, theta);
	return z;
}

STRUCT slc_complex slc_complex_log10 (STRUCT slc_complex a)  /* r=log10(a) (base 10) */
{
	return slc_complex_mul_real (slc_complex_log (a), 1.0 / log (10.0));
}

STRUCT slc_complex slc_complex_log_b (STRUCT slc_complex a, STRUCT slc_complex b)   /* r=log_b(a) (base=b) */
{
	return slc_complex_div (slc_complex_log (a), slc_complex_log (b));
}

#endif