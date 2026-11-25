#ifndef _SLC_COMPLEX_PROPERTIES_INC_
#define _SLC_COMPLEX_PROPERTIES_INC_

/* Properties of complex numbers */

slc_type slc_complex_arg (STRUCT slc_complex z) /* return arg(z), -pi< arg(z) <=+pi */
{
	slc_type x = SLC_REAL (z);
	slc_type y = SLC_IMAG (z);

	if (x == 0.0 && y == 0.0)
	{
		return 0.0;
	}

	return ATAN2 (y, x);
}

slc_type slc_complex_abs (STRUCT slc_complex z)   /* return |z|   */
{
	return hypot (SLC_REAL (z), SLC_IMAG (z));
}

slc_type slc_complex_abs2 (STRUCT slc_complex z)  /* return |z|^2 */
{
	slc_type x = SLC_REAL (z);
	slc_type y = SLC_IMAG (z);

	return (x * x + y * y);
}

slc_type slc_complex_logabs (STRUCT slc_complex z) /* return log|z| */
{
	slc_type xabs = FABS (SLC_REAL (z));
	slc_type yabs = FABS (SLC_IMAG (z));
	slc_type max, u;

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