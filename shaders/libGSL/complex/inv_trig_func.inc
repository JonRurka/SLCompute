#ifndef _GSL_COMPLEX_INV_TRIG_FUNC_INC_
#define _GSL_COMPLEX_INV_TRIG_FUNC_INC_

/* Inverse Complex Trigonometric Functions */

STRUCT gsl_complex gsl_complex_arcsin (STRUCT gsl_complex a)  /* r=arcsin(a) */
{
	gsl_type R = GSL_REAL (a); 
	gsl_type I = GSL_IMAG (a);
	gsl_complex z;

	if (I == 0.0)
	{
		z = gsl_complex_arcsin_real (R);
	}
	else
	{
		gsl_type x = FABS (R), y = FABS (I);
		gsl_type r = hypot (x + 1.0, y); 
		gsl_type s = hypot (x - 1.0, y);
		gsl_type A = 0.5 * (r + s);
		gsl_type B = x / A;
		gsl_type y2 = y * y;

		gsl_type real;
		gsl_type imag;

		const gsl_type A_crossover = 1.5;
		const gsl_type B_crossover = 0.6417;

		if (B <= B_crossover)
		{
			real = asin (B);
		}
		else
		{
		if (x <= 1.0)
		{
				gsl_type D = 0.5 * (A + x) * (y2 / (r + x + 1.0) + (s + (1.0 - x)));
				real = ATAN (x / sqrt (D));
			}
			else
			{
				gsl_type Apx = A + x;
				gsl_type D = 0.5 * (Apx / (r + x + 1.0) + Apx / (s + (x - 1.0)));
				real = ATAN (x / (y * sqrt (D)));
			}
		}

		if (A <= A_crossover)
		{
			gsl_type Am1;

			if (x < 1.0)
			{
				Am1 = 0.5 * (y2 / (r + (x + 1.0)) + y2 / (s + (1.0 - x)));
			}
			else
			{
				Am1 = 0.5 * (y2 / (r + (x + 1.0)) + (s + (x - 1.0)));
			}

			imag = log1p (Am1 + sqrt (Am1 * (A + 1.0)));
		}
		else
		{
			imag = log (A + sqrt (A * A - 1.0));
		}

		GSL_SET_COMPLEX (z, (R >= 0.0) ? real : -real, (I >= 0.0) ? imag : -imag);
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arcsin_real (gsl_type a)  /* r=arcsin(a) */
{
	gsl_complex z;

	if (FABS (a) <= 1.0)
	{
		GSL_SET_COMPLEX (z, asin (a), 0.0);
	}
	else
	{
		if (a < 0.0)
		{
			GSL_SET_COMPLEX (z, -M_PI_2, acosh (-a));
		}
		else
		{
			GSL_SET_COMPLEX (z, M_PI_2, -acosh (a));
		}
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arccos (STRUCT gsl_complex a)  /* r=arccos(a) */
{
	gsl_type R = GSL_REAL (a);
	gsl_type I = GSL_IMAG (a);
	gsl_complex z;

	if (I == 0.0)
	{
		z = gsl_complex_arccos_real (R);
	}
	else
	{
		gsl_type x = FABS (R), y = FABS (I);
		gsl_type r = hypot (x + 1.0, y);
		gsl_type s = hypot (x - 1.0, y);
		gsl_type A = 0.5 * (r + s);
		gsl_type B = x / A;
		gsl_type y2 = y * y;

		gsl_type real;
		gsl_type imag;

		const gsl_type A_crossover = 1.5;
		const gsl_type B_crossover = 0.6417;

		if (B <= B_crossover)
		{
			real = acos (B);
		}
		else
		{
			if (x <= 1)
			{
				gsl_type D = 0.5 * (A + x) * (y2 / (r + x + 1.0) + (s + (1.0 - x)));
				real = atan (sqrt (D) / x);
			}
			else
			{
				gsl_type Apx = A + x;
				gsl_type D = 0.5 * (Apx / (r + x + 1.0) + Apx / (s + (x - 1.0)));
				real = atan ((y * sqrt (D)) / x);
			}
		}

		if (A <= A_crossover)
		{
			gsl_type Am1;

			if (x < 1.0)
			{
				Am1 = 0.5 * (y2 / (r + (x + 1.0)) + y2 / (s + (1.0 - x)));
			}
			else
			{
				Am1 = 0.5 * (y2 / (r + (x + 1.0)) + (s + (x - 1.0)));
			}

			imag = log1p (Am1 + sqrt (Am1 * (A + 1.0)));
		}
		else
		{
			imag = log (A + sqrt (A * A - 1.0));
		}

		GSL_SET_COMPLEX (z, (R >= 0.0) ? real : M_PI - real, (I >= 0.0) ? -imag : imag);
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arccos_real (gsl_type a)  /* r=arccos(a) */
{
	gsl_complex z;

	if (FABS (a) <= 1.0)
	{
		GSL_SET_COMPLEX (z, acos (a), 0.0);
	}
	else
	{
		if (a < 0.0)
		{
			GSL_SET_COMPLEX (z, M_PI, -acosh (-a));
		}
		else
		{
			GSL_SET_COMPLEX (z, 0.0, acosh (a));
		}
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arcsec (STRUCT gsl_complex a)  /* r=arcsec(a) */
{
	gsl_complex z = gsl_complex_inverse (a);
	return gsl_complex_arccos (z);
}

STRUCT gsl_complex gsl_complex_arcsec_real (gsl_type a)  /* r=arcsec(a) */
{
	gsl_complex z;

	if (a <= -1.0 || a >= 1.0)
	{
		GSL_SET_COMPLEX (z, acos (1.0 / a), 0.0);
	}
	else
	{
		if (a >= 0.0)
		{
			GSL_SET_COMPLEX (z, 0.0, acosh (1.0 / a));
		}
		else
		{
			GSL_SET_COMPLEX (z, M_PI, -acosh (-1.0 / a));
		}
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arccsc (STRUCT gsl_complex a)  /* r=arccsc(a) */
{
	gsl_complex z = gsl_complex_inverse (a);
	return gsl_complex_arcsin (z);
}

STRUCT gsl_complex gsl_complex_arccsc_real (gsl_type a)  /* r=arccsc(a) */
{
	gsl_complex z;

	if (a <= -1.0 || a >= 1.0)
	{
		GSL_SET_COMPLEX (z, asin (1.0 / a), 0.0);
	}
	else
	{
		if (a >= 0.0)
		{
			GSL_SET_COMPLEX (z, M_PI_2, -acosh (1.0 / a));
		}
		else
		{
			GSL_SET_COMPLEX (z, -M_PI_2, acosh (-1.0 / a));
		}
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arctan (STRUCT gsl_complex a)  /* r=arctan(a) */
{
	gsl_type R = GSL_REAL (a);
	gsl_type I = GSL_IMAG (a);
	gsl_complex z;

	if (I == 0.0)
	{
		GSL_SET_COMPLEX (z, ATAN (R), 0);
	}
	else
	{
		/* FIXME: This is a naive implementation which does not fully
		take into account cancellation errors, overflow, underflow
		etc.  It would benefit from the Hull et al treatment. */

		gsl_type r = hypot (R, I);

		gsl_type imag;

		gsl_type u = 2.0 * I / (1.0 + r * r);

		/* FIXME: the following cross-over should be optimized but 0.1
		seems to work ok */

		if (FABS (u) < 0.1)
		{
			imag = 0.25 * (log1p (u) - log1p (-u));
		}
		else
		{
			gsl_type A = hypot (R, I + 1.0);
			gsl_type B = hypot (R, I - 1.0);
			imag = 0.5 * log (A / B);
		}

		if (R == 0.0)
		{
			if (I > 1.0)
			{
				GSL_SET_COMPLEX (z, M_PI_2, imag);
			}
			else if (I < -1.0)
			{
				GSL_SET_COMPLEX (z, -M_PI_2, imag);
			}
			else
			{
				GSL_SET_COMPLEX (z, 0.0, imag);
			}
		}
		else
		{
			GSL_SET_COMPLEX (z, 0.5 * ATAN2 (2.0 * R, ((1.0 + r) * (1.0 - r))), imag);
		}
	}

	return z;
}

STRUCT gsl_complex gsl_complex_arccot (STRUCT gsl_complex a)  /* r=arccot(a) */
{
	gsl_complex z;

	if (GSL_REAL (a) == 0.0 && GSL_IMAG (a) == 0.0)
	{
		GSL_SET_COMPLEX (z, M_PI_2, 0.0);
	}
	else
	{
		z = gsl_complex_inverse (a);
		z = gsl_complex_arctan (z);
	}

	return z;
}

#endif