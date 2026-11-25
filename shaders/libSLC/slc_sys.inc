#ifndef _SLC_SYS_H_
#define _SLC_SYS_H_

#include "slc_lib_type.inc"

#ifndef FABS
#define FABS(val) abs(val)
#endif

#ifndef MAX
#define MAX(a,b) (max(a, b))
#endif

#ifndef MIN
#define MIN(a,b) (min(a, b))
#endif

#define ROUNT_TO_INT(x) (SLC_CAST(int, round(x)))

#ifdef GLSL
#define ATAN2(y, x) atan(y, x)
#define ATAN(x) atan(x)
#endif

#ifdef HLSL
#define ATAN2(y, x) atan2(y, x)
#define ATAN(x) atan(x)
#endif



struct frexp_res
{
	slc_type result;
	int exp;
};
STRUCT frexp_res frexp_res_new(slc_type x, int exp)
{
	STRUCT frexp_res res;
	res.result = x;
	res.exp = exp;
	return res;
}


slc_type slc_pow_2(const slc_type x) { return x*x;   }
slc_type slc_pow_3(const slc_type x) { return x*x*x; }
slc_type slc_pow_4(const slc_type x) { slc_type x2 = x*x;   return x2*x2;    }
slc_type slc_pow_5(const slc_type x) { slc_type x2 = x*x;   return x2*x2*x;  }
slc_type slc_pow_6(const slc_type x) { slc_type x2 = x*x;   return x2*x2*x2; }
slc_type slc_pow_7(const slc_type x) { slc_type x3 = x*x*x; return x3*x3*x;  }
slc_type slc_pow_8(const slc_type x) { slc_type x2 = x*x;   slc_type x4 = x2*x2; return x4*x4; }
slc_type slc_pow_9(const slc_type x) { slc_type x3 = x*x*x; return x3*x3*x3; }

slc_type slc_log1p (const slc_type x);
slc_type slc_expm1 (const slc_type x);
slc_type slc_hypot (const slc_type x, const slc_type y);
slc_type slc_hypot3 (const slc_type x, const slc_type y, const slc_type z);
slc_type slc_acosh (const slc_type x);
slc_type slc_asinh (const slc_type x);
slc_type slc_atanh (const slc_type x);

bool slc_isnan (const slc_type x);
bool slc_isinf (const slc_type x);
bool slc_finite (const slc_type x);

slc_type slc_nan (void);
slc_type slc_posinf (void);
slc_type slc_neginf (void);
slc_type slc_fdiv (const slc_type x, const slc_type y);

slc_type slc_ldexp(const slc_type x, const int e);
STRUCT frexp_res slc_frexp (const slc_type x, int e);

int slc_fcmp (const slc_type x1, const slc_type x2, const slc_type epsilon);



slc_type slc_log1p(const slc_type x)
{
    slc_type y, z;
    y = 1.0 + x;
    z = y - 1.0;
    return log(y) - (z - x) / y; /* cancels errors with IEEE arithmetic */
}

slc_type slc_expm1 (const slc_type x)
{
	/* FIXME: this should be improved */

	if (FABS(x) < M_LN2)
	{
		/* Compute the taylor series S = x + (1/2!) x^2 + (1/3!) x^3 + ... */

		slc_type i = 1.0;
		slc_type sum = x;
		slc_type term = x / 1.0;

		do
		{
			i++ ;
			term *= x/i;
			sum += term;
		}
		while (FABS(term) > FABS(sum) * SLC_DBL_EPSILON) ;

		return sum;
	}
	else
	{
		return exp(x) - 1.0;
	}
}

slc_type slc_hypot (const slc_type x, const slc_type y)
{
	slc_type xabs = FABS(x);
	slc_type yabs = FABS(y);
	slc_type min;
	slc_type max;

	/* Follow the optional behavior of the ISO C standard and return
	+Inf when any of the argument is +-Inf, even if the other is NaN.
	http://pubs.opengroup.org/onlinepubs/009695399/functions/hypot.html */
	if (slc_isinf(x) || slc_isinf(y))
	{
		return SLC_POSINF;
	}

	if (xabs < yabs) {
		min = xabs;
		max = yabs;
	} else {
		min = yabs;
		max = xabs;
	}

	if (min == 0.0) 
	{
		return max ;
	}

	{
		slc_type u = min / max ;
		return max * sqrt (1.0 + u * u) ;
	}
}

slc_type slc_hypot3(const slc_type x, const slc_type y, const slc_type z)
{
  slc_type xabs = FABS(x);
  slc_type yabs = FABS(y);
  slc_type zabs = FABS(z);
  slc_type w = MAX(xabs, MAX(yabs, zabs));

	if (w == 0.0)
	{
		return (0.0);
	}
	else
	{
		slc_type r = w * sqrt((xabs / w) * (xabs / w) +
							  (yabs / w) * (yabs / w) +
							  (zabs / w) * (zabs / w));
		return r;
	}
}

slc_type slc_acosh (const slc_type x)
{
	#ifdef GLSL
	return acosh(x);
	#else
		
	if (x > 1.0 / SLC_SQRT_EPSILON)
	{
		return log (x) + M_LN2;
	}
	else if (x > 2.0)
	{
		return log (2.0 * x - 1.0 / (sqrt (x * x - 1.0) + x));
	}
	else if (x > 1.0)
	{
		slc_type t = x - 1.0;
		return slc_log1p (t + sqrt (2.0 * t + t * t));
	}
	else if (x == 1.0)
	{
		return 0.0;
	}
	else
	{
		return SLC_NAN;
	}
	#endif
}

slc_type slc_asinh (const slc_type x)
{
	#ifdef GLSL
	return asinh(x);
	#else
	slc_type a = FABS (x);
	slc_type s = (x < 0.0) ? -1.0 : 1.0;

	if (a > 1.0 / SLC_SQRT_EPSILON)
	{
		return s * (log (a) + M_LN2);
	}
	else if (a > 2.0)
	{
		return s * log (2.0 * a + 1.0 / (a + sqrt (a * a + 1.0)));
	}
	else if (a > SLC_SQRT_EPSILON)
	{
		slc_type a2 = a * a;
		return s * slc_log1p (a + a2 / (1.0 + sqrt (1.0 + a2)));
	}
	else
	{
		return x;
	}
	#endif
}

slc_type slc_atanh (const slc_type x)
{
	slc_type a = FABS (x);
	slc_type s = (x < 0.0) ? -1.0 : 1.0;

	if (a > 1.0)
	{
		return SLC_NAN;
	}
	else if (a == 1.0)
	{
		return (x < 0.0) ? SLC_NEGINF : SLC_POSINF;
	}
	else if (a >= 0.5)
	{
		return s * 0.5 * slc_log1p (2.0 * a / (1.0 - a));
	}
	else if (a > SLC_EPSILON)
	{
		return s * 0.5 * slc_log1p (2.0 * a + 2.0 * a * a / (1.0 - a));
	}
	else
	{
		return x;
	}
}

bool slc_isnan (const slc_type x)
{
	//int status = (x != x);
	//return status;

	return !(x < 0.0 || x > 0.0 || x == 0.0);
	//return (asuint(x) & 0x7fffffff) > 0x7f800000;
}

bool slc_isinf (const slc_type x)
{
	return isinf(x);
}

bool slc_finite (const slc_type x)
{
	#ifdef HLSL
	return isfinite (x);
	#else
	const slc_type y = x - x;
	bool status = (y == y);
	return status;
	#endif
}

slc_type slc_nan (void)
{
	return 0.0 / 0.0;
}

slc_type slc_posinf (void)
{
  return +1.0 / 0.0;
}

slc_type slc_neginf (void)
{
  return -1.0 / 0.0;
}

#ifndef slc_coerce
#define slc_coerce(x) SLC_TYPE(x)
#endif

slc_type slc_ldexp (const slc_type x, const int e)
{
	int ex;

	if (x == 0.0)
	{
		return x;
	}

	{
		STRUCT frexp_res fre_res = slc_frexp(x, ex);
		ex = fre_res.exp;
		slc_type y = fre_res.result;//slc_frexp (x, &ex);
		slc_type e2 = e + ex, p2; // TODO

		if (e2 >= MAX_EXP)
		{
			y *= pow (2.0, e2 - MAX_EXP + 1.0);
			e2 = MAX_EXP - 1.0;
		}
		else if (e2 <= MIN_EXP)
		{
			y *= pow (2.0, e2 - MIN_EXP - 1);
			e2 = MIN_EXP + 1.0;
		}

		p2 = pow (2.0, e2);
		return y * p2;
	}
}

STRUCT frexp_res slc_frexp (const slc_type x, int e)
{
	if (x == 0.0)
	{
		e = 0;
		return frexp_res_new(0.0, e);
	}
	else if (!slc_finite (x))
	{
		e = 0;
		return frexp_res_new(x, e);
	}
	else if (FABS (x) >= 0.5 && FABS (x) < 1.0)     /* Handle the common case */
	{
		e = 0;
		return frexp_res_new(x, e);
	}
	else
	{
		slc_type ex = ceil (log (FABS (x)) / M_LN2);
		int ei = SLC_CAST(int, ex);
		slc_type f;

		/* Prevent underflow and overflow of 2**(-ei) */
		if (ei < MIN_EXP)
			ei = MIN_EXP;

		if (ei > -MIN_EXP)
			ei = -MIN_EXP;

		f = x * pow (2.0, -ei);

		if (!slc_finite (f))
		{
			/* This should not happen */
			e = 0;
			return frexp_res_new(f, e);
		}

		while (FABS (f) >= 1.0)
		{
			ei++;
			f /= 2.0;
		}

		while (FABS (f) > 0.0 && FABS (f) < 0.5)
		{
			ei--;
			f *= 2.0;
		}

		e = ei;
		return frexp_res_new(f, e);
	}
}

int slc_fcmp (const slc_type x1, const slc_type x2, const slc_type epsilon)
{
	int exponent;
	slc_type delta, difference;

	/* Find exponent of largest absolute value */

	{
		slc_type max = (FABS (x1) > FABS (x2)) ? x1 : x2;

		exponent = slc_frexp (max, exponent).exp;
	}

	/* Form a neighborhood of size  2 * delta */

	delta = slc_ldexp (epsilon, exponent);

	difference = x1 - x2;

	if (difference > delta)       /* x1 > x2 */
	{
		return 1;
	}
	else if (difference < -delta) /* x1 < x2 */
	{
		return -1;
	}
	else                          /* -delta <= difference <= delta */
	{
		return 0;                 /* x1 ~=~ x2 */
	}
}

slc_type slc_pow_uint(slc_type x, uint n)
{
	slc_type value = 1.0;

	/* repeated squaring method 
	 * returns 0.0^0 = 1.0, so continuous in x
	 */
	do {
		if((n & 1) == 1) value *= x;  /* for n odd */
		n >>= 1;
		x *= x;
	} while (n != 0);

	return value;
}

slc_type slc_pow_int(slc_type x, int n)
{
	uint un;

	if(n < 0) {
		x = 1.0/x;
		un = -n;
	} else {
		un = n;
	}

	return slc_pow_uint(x, un);
}

#ifndef hypot
#define hypot slc_hypot
#endif

#ifndef log1p
#define log1p slc_log1p
#endif

#ifndef expm1
#define expm1 slc_expm1
#endif


#ifndef GLSL

#ifndef acosh
#define acosh slc_acosh
#endif

#ifndef asinh
#define asinh slc_asinh
#endif

#ifndef atanh
#define atanh slc_atanh
#endif

#endif

#ifndef ldexp
#define ldexp slc_ldexp
#endif

#ifndef frexp
#define frexp slc_frexp
#endif

#ifndef isinf
//#define isinf slc_isinf
#endif

#ifndef HLSL
#ifndef isfinite
#define isfinite slc_finite
#endif
#endif

#ifndef finite
#define finite slc_finite
#endif

#ifndef isnan
#define isnan slc_isnan
#endif

#endif //__SLC_SYS_H__