#ifndef _GSL_COMPLEX_ELEM_FUNC_INC_
#define _GSL_COMPLEX_ELEM_FUNC_INC_

/* Elementary Complex Functions */

STRUCT gsl_complex gsl_complex_sqrt (STRUCT gsl_complex a)  /* r=sqrt(z) */
{
	gsl_complex z;
	
	gsl_type a_real = GSL_REAL (a);
	gsl_type a_imag = GSL_IMAG (a);

	if (a_real == 0.0 && a_imag == 0.0)
	{
		GSL_SET_COMPLEX (z, 0.0, 0.0);
	}
	else
	{
		gsl_type x = FABS (a_real);
		gsl_type y = FABS (a_imag);
		gsl_type w;

		if (x >= y)
		{
			gsl_type t = y / x;
			w = sqrt (x) * sqrt (0.5 * (1.0 + sqrt (1.0 + t * t)));
		}
		else
		{
			gsl_type t = x / y;
			w = sqrt (y) * sqrt (0.5 * (t + sqrt (1.0 + t * t)));
		}

		if (a_real >= 0.0)
		{
			gsl_type ai = a_imag;
			GSL_SET_COMPLEX (z, w, ai / (2.0 * w));
		}
		else
		{
			gsl_type ai = a_imag;
			gsl_type vi = (ai >= 0.0) ? w : -w;
			GSL_SET_COMPLEX (z, ai / (2.0 * vi), vi);
		}
	}

	return z;
}

STRUCT gsl_complex gsl_complex_sqrt_real (gsl_type x)  /* r=sqrt(x) (x<0 ok) */
{
	gsl_complex z;

	if (x >= 0.0)
	{
		GSL_SET_COMPLEX (z, sqrt (x), 0.0);
	}
	else
	{
		GSL_SET_COMPLEX (z, 0.0, sqrt (-x));
	}

	return z;
}

STRUCT gsl_complex gsl_complex_pow (STRUCT gsl_complex a, STRUCT gsl_complex b)  /* r=a^b */
{
	gsl_complex z;

	if (GSL_REAL (a) == 0.0 && GSL_IMAG (a) == 0.0)
	{
		if (GSL_REAL (b) == 0.0 && GSL_IMAG (b) == 0.0)
		{
			GSL_SET_COMPLEX (z, 1.0, 0.0);
		}
		else 
		{
			GSL_SET_COMPLEX (z, 0.0, 0.0);
		}
	}
	else if (GSL_REAL (b) == 1.0 && GSL_IMAG (b) == 0.0) 
	{
		return a;
	}
	else if (GSL_REAL (b) == -1.0 && GSL_IMAG (b) == 0.0) 
	{
		return gsl_complex_inverse (a);
	}
	else
	{
		gsl_type logr = gsl_complex_logabs (a);
		gsl_type theta = gsl_complex_arg (a);

		gsl_type br = GSL_REAL (b), bi = GSL_IMAG (b);

		gsl_type rho = exp (logr * br - bi * theta);
		gsl_type beta = theta * br + bi * logr;

		GSL_SET_COMPLEX (z, rho * cos (beta), rho * sin (beta));
	}

	return z;
}

STRUCT gsl_complex gsl_complex_pow_real (STRUCT gsl_complex a, gsl_type b)  /* r=a^b */
{
	gsl_complex z;

	if (GSL_REAL (a) == 0.0 && GSL_IMAG (a) == 0.0)
	{
		if (b == 0.0)
		{
			GSL_SET_COMPLEX (z, 1.0, 0.0);
		}
		else
		{
			GSL_SET_COMPLEX (z, 0.0, 0.0);
		}
	}
	else
	{
		gsl_type logr = gsl_complex_logabs (a);
		gsl_type theta = gsl_complex_arg (a);
		gsl_type rho = exp (logr * b);
		gsl_type beta = theta * b;
		GSL_SET_COMPLEX (z, rho * cos (beta), rho * sin (beta));
	}

	return z;
}

STRUCT gsl_complex gsl_complex_exp (STRUCT gsl_complex a)    /* r=exp(a) */
{
	gsl_type rho = exp (GSL_REAL (a));
	gsl_type theta = GSL_IMAG (a);

	gsl_complex z;
	GSL_SET_COMPLEX (z, rho * cos (theta), rho * sin (theta));
	return z;
}

STRUCT gsl_complex gsl_complex_log (STRUCT gsl_complex a)    /* r=log(a) (base e) */
{
	gsl_type logr = gsl_complex_logabs (a);
	gsl_type theta = gsl_complex_arg (a);

	gsl_complex z;
	GSL_SET_COMPLEX (z, logr, theta);
	return z;
}

STRUCT gsl_complex gsl_complex_log10 (STRUCT gsl_complex a)  /* r=log10(a) (base 10) */
{
	return gsl_complex_mul_real (gsl_complex_log (a), 1.0 / log (10.0));
}

STRUCT gsl_complex gsl_complex_log_b (STRUCT gsl_complex a, STRUCT gsl_complex b)   /* r=log_b(a) (base=b) */
{
	return gsl_complex_div (gsl_complex_log (a), gsl_complex_log (b));
}

#endif