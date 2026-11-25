#ifndef _SLC_COMPLEX_INV_TRIG_FUNC_INC_
#define _SLC_COMPLEX_INV_TRIG_FUNC_INC_

/* Inverse Complex Trigonometric Functions */

STRUCT slc_complex slc_complex_arcsin (STRUCT slc_complex a)  /* r=arcsin(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);
	slc_complex z;

	if (I == 0.0)
	{
		z = slc_complex_arcsin_real (R);
	}
	else
	{
		slc_type x = FABS (R), y = FABS (I);
		slc_type r = hypot (x + 1.0, y);
		slc_type s = hypot (x - 1.0, y);
		slc_type A = 0.5 * (r + s);
		slc_type B = x / A;
		slc_type y2 = y * y;

		slc_type real;
		slc_type imag;

		const slc_type A_crossover = 1.5;
		const slc_type B_crossover = 0.6417;

		if (B <= B_crossover)
		{
			real = asin (B);
		}
		else
		{
		if (x <= 1.0)
		{
				slc_type D = 0.5 * (A + x) * (y2 / (r + x + 1.0) + (s + (1.0 - x)));
				real = ATAN (x / sqrt (D));
			}
			else
			{
				slc_type Apx = A + x;
				slc_type D = 0.5 * (Apx / (r + x + 1.0) + Apx / (s + (x - 1.0)));
				real = ATAN (x / (y * sqrt (D)));
			}
		}

		if (A <= A_crossover)
		{
			slc_type Am1;

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

		SLC_SET_COMPLEX (z, (R >= 0.0) ? real : -real, (I >= 0.0) ? imag : -imag);
	}

	return z;
}

STRUCT slc_complex slc_complex_arcsin_real (slc_type a)  /* r=arcsin(a) */
{
	slc_complex z;

	if (FABS (a) <= 1.0)
	{
		SLC_SET_COMPLEX (z, asin (a), 0.0);
	}
	else
	{
		if (a < 0.0)
		{
			SLC_SET_COMPLEX (z, -M_PI_2, acosh (-a));
		}
		else
		{
			SLC_SET_COMPLEX (z, M_PI_2, -acosh (a));
		}
	}

	return z;
}

STRUCT slc_complex slc_complex_arccos (STRUCT slc_complex a)  /* r=arccos(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);
	slc_complex z;

	if (I == 0.0)
	{
		z = slc_complex_arccos_real (R);
	}
	else
	{
		slc_type x = FABS (R), y = FABS (I);
		slc_type r = hypot (x + 1.0, y);
		slc_type s = hypot (x - 1.0, y);
		slc_type A = 0.5 * (r + s);
		slc_type B = x / A;
		slc_type y2 = y * y;

		slc_type real;
		slc_type imag;

		const slc_type A_crossover = 1.5;
		const slc_type B_crossover = 0.6417;

		if (B <= B_crossover)
		{
			real = acos (B);
		}
		else
		{
			if (x <= 1)
			{
				slc_type D = 0.5 * (A + x) * (y2 / (r + x + 1.0) + (s + (1.0 - x)));
				real = atan (sqrt (D) / x);
			}
			else
			{
				slc_type Apx = A + x;
				slc_type D = 0.5 * (Apx / (r + x + 1.0) + Apx / (s + (x - 1.0)));
				real = atan ((y * sqrt (D)) / x);
			}
		}

		if (A <= A_crossover)
		{
			slc_type Am1;

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

		SLC_SET_COMPLEX (z, (R >= 0.0) ? real : M_PI - real, (I >= 0.0) ? -imag : imag);
	}

	return z;
}

STRUCT slc_complex slc_complex_arccos_real (slc_type a)  /* r=arccos(a) */
{
	slc_complex z;

	if (FABS (a) <= 1.0)
	{
		SLC_SET_COMPLEX (z, acos (a), 0.0);
	}
	else
	{
		if (a < 0.0)
		{
			SLC_SET_COMPLEX (z, M_PI, -acosh (-a));
		}
		else
		{
			SLC_SET_COMPLEX (z, 0.0, acosh (a));
		}
	}

	return z;
}

STRUCT slc_complex slc_complex_arcsec (STRUCT slc_complex a)  /* r=arcsec(a) */
{
	slc_complex z = slc_complex_inverse (a);
	return slc_complex_arccos (z);
}

STRUCT slc_complex slc_complex_arcsec_real (slc_type a)  /* r=arcsec(a) */
{
	slc_complex z;

	if (a <= -1.0 || a >= 1.0)
	{
		SLC_SET_COMPLEX (z, acos (1.0 / a), 0.0);
	}
	else
	{
		if (a >= 0.0)
		{
			SLC_SET_COMPLEX (z, 0.0, acosh (1.0 / a));
		}
		else
		{
			SLC_SET_COMPLEX (z, M_PI, -acosh (-1.0 / a));
		}
	}

	return z;
}

STRUCT slc_complex slc_complex_arccsc (STRUCT slc_complex a)  /* r=arccsc(a) */
{
	slc_complex z = slc_complex_inverse (a);
	return slc_complex_arcsin (z);
}

STRUCT slc_complex slc_complex_arccsc_real (slc_type a)  /* r=arccsc(a) */
{
	slc_complex z;

	if (a <= -1.0 || a >= 1.0)
	{
		SLC_SET_COMPLEX (z, asin (1.0 / a), 0.0);
	}
	else
	{
		if (a >= 0.0)
		{
			SLC_SET_COMPLEX (z, M_PI_2, -acosh (1.0 / a));
		}
		else
		{
			SLC_SET_COMPLEX (z, -M_PI_2, acosh (-1.0 / a));
		}
	}

	return z;
}

STRUCT slc_complex slc_complex_arctan (STRUCT slc_complex a)  /* r=arctan(a) */
{
	slc_type R = SLC_REAL (a);
	slc_type I = SLC_IMAG (a);
	slc_complex z;

	if (I == 0.0)
	{
		SLC_SET_COMPLEX (z, ATAN (R), 0);
	}
	else
	{
		/* FIXME: This is a naive implementation which does not fully
		take into account cancellation errors, overflow, underflow
		etc.  It would benefit from the Hull et al treatment. */

		slc_type r = hypot (R, I);

		slc_type imag;

		slc_type u = 2.0 * I / (1.0 + r * r);

		/* FIXME: the following cross-over should be optimized but 0.1
		seems to work ok */

		if (FABS (u) < 0.1)
		{
			imag = 0.25 * (log1p (u) - log1p (-u));
		}
		else
		{
			slc_type A = hypot (R, I + 1.0);
			slc_type B = hypot (R, I - 1.0);
			imag = 0.5 * log (A / B);
		}

		if (R == 0.0)
		{
			if (I > 1.0)
			{
				SLC_SET_COMPLEX (z, M_PI_2, imag);
			}
			else if (I < -1.0)
			{
				SLC_SET_COMPLEX (z, -M_PI_2, imag);
			}
			else
			{
				SLC_SET_COMPLEX (z, 0.0, imag);
			}
		}
		else
		{
			SLC_SET_COMPLEX (z, 0.5 * ATAN2 (2.0 * R, ((1.0 + r) * (1.0 - r))), imag);
		}
	}

	return z;
}

STRUCT slc_complex slc_complex_arccot (STRUCT slc_complex a)  /* r=arccot(a) */
{
	slc_complex z;

	if (SLC_REAL (a) == 0.0 && SLC_IMAG (a) == 0.0)
	{
		SLC_SET_COMPLEX (z, M_PI_2, 0.0);
	}
	else
	{
		z = slc_complex_inverse (a);
		z = slc_complex_arctan (z);
	}

	return z;
}

#endif