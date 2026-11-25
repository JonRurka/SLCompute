#ifndef _GSL_COMPLEX_PROPERTIES_INC_
#define _GSL_COMPLEX_PROPERTIES_INC_

/* Properties of complex numbers */

gsl_type gsl_complex_arg (STRUCT gsl_complex z) /* return arg(z), -pi< arg(z) <=+pi */
{
	gsl_type x = GSL_REAL (z);
	gsl_type y = GSL_IMAG (z);

	if (x == 0.0 && y == 0.0)
	{
		return 0.0;
	}

	return ATAN2 (y, x);
}

gsl_type gsl_complex_abs (STRUCT gsl_complex z)   /* return |z|   */
{
	return hypot (GSL_REAL (z), GSL_IMAG (z));
}

gsl_type gsl_complex_abs2 (STRUCT gsl_complex z)  /* return |z|^2 */
{
	gsl_type x = GSL_REAL (z);
	gsl_type y = GSL_IMAG (z);

	return (x * x + y * y);
}

gsl_type gsl_complex_logabs (STRUCT gsl_complex z) /* return log|z| */
{
	gsl_type xabs = FABS (GSL_REAL (z));
	gsl_type yabs = FABS (GSL_IMAG (z));
	gsl_type max, u;

	if (xabs >= yabs)
	{
		max = xabs;
		u = yabs / xabs;
	}
	else
	{
		max = yabs;
		u = xabs / yabs;
	}

	/* Handle underflow when u is close to 0 */

	return log (max) + 0.5 * log1p (u * u);
}


#endif