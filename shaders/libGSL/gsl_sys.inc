#ifndef _GSL_SYS_H_
#define _GSL_SYS_H_

#include "gsl_lib_type.inc"

#ifndef FABS
#define FABS(val) abs(val)
#endif

#ifndef MAX
#define MAX(a,b) (max(a, b))
#endif

#ifndef MIN
#define MIN(a,b) (min(a, b))
#endif

#define ROUNT_TO_INT(x) (GSL_CAST(int, round(x)))

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
	gsl_type result;
	int exp;
};
STRUCT frexp_res frexp_res_new(gsl_type x, int exp)
{
	STRUCT frexp_res res;
	res.result = x;
	res.exp = exp;
	return res;
}


gsl_type gsl_pow_2(const gsl_type x) { return x*x;   }
gsl_type gsl_pow_3(const gsl_type x) { return x*x*x; }
gsl_type gsl_pow_4(const gsl_type x) { gsl_type x2 = x*x;   return x2*x2;    }
gsl_type gsl_pow_5(const gsl_type x) { gsl_type x2 = x*x;   return x2*x2*x;  }
gsl_type gsl_pow_6(const gsl_type x) { gsl_type x2 = x*x;   return x2*x2*x2; }
gsl_type gsl_pow_7(const gsl_type x) { gsl_type x3 = x*x*x; return x3*x3*x;  }
gsl_type gsl_pow_8(const gsl_type x) { gsl_type x2 = x*x;   gsl_type x4 = x2*x2; return x4*x4; }
gsl_type gsl_pow_9(const gsl_type x) { gsl_type x3 = x*x*x; return x3*x3*x3; }

gsl_type gsl_log1p (const gsl_type x);
gsl_type gsl_expm1 (const gsl_type x);
gsl_type gsl_hypot (const gsl_type x, const gsl_type y);
gsl_type gsl_hypot3 (const gsl_type x, const gsl_type y, const gsl_type z);
gsl_type gsl_acosh (const gsl_type x);
gsl_type gsl_asinh (const gsl_type x);
gsl_type gsl_atanh (const gsl_type x);

bool gsl_isnan (const gsl_type x);
bool gsl_isinf (const gsl_type x);
bool gsl_finite (const gsl_type x);

gsl_type gsl_nan (void);
gsl_type gsl_posinf (void);
gsl_type gsl_neginf (void);
gsl_type gsl_fdiv (const gsl_type x, const gsl_type y);

gsl_type gsl_ldexp(const gsl_type x, const int e);
STRUCT frexp_res gsl_frexp (const gsl_type x, int e);

int gsl_fcmp (const gsl_type x1, const gsl_type x2, const gsl_type epsilon);



gsl_type gsl_log1p(const gsl_type x)
{
    gsl_type y, z;
    y = 1.0 + x;
    z = y - 1.0;
    return log(y) - (z - x) / y; /* cancels errors with IEEE arithmetic */
}

gsl_type gsl_expm1 (const gsl_type x)
{
	/* FIXME: this should be improved */

	if (FABS(x) < M_LN2)
	{
		/* Compute the taylor series S = x + (1/2!) x^2 + (1/3!) x^3 + ... */

		gsl_type i = 1.0;
		gsl_type sum = x;
		gsl_type term = x / 1.0;

		do
		{
			i++ ;
			term *= x/i;
			sum += term;
		}
		while (FABS(term) > FABS(sum) * GSL_DBL_EPSILON) ;

		return sum;
	}
	else
	{
		return exp(x) - 1.0;
	}
}

gsl_type gsl_hypot (const gsl_type x, const gsl_type y)
{
	gsl_type xabs = FABS(x);
	gsl_type yabs = FABS(y);
	gsl_type min;
	gsl_type max;

	/* Follow the optional behavior of the ISO C standard and return
	+Inf when any of the argument is +-Inf, even if the other is NaN.
	http://pubs.opengroup.org/onlinepubs/009695399/functions/hypot.html */
	if (gsl_isinf(x) || gsl_isinf(y)) 
	{
		return GSL_POSINF;
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
		gsl_type u = min / max ;
		return max * sqrt (1.0 + u * u) ;
	}
}

gsl_type gsl_hypot3(const gsl_type x, const gsl_type y, const gsl_type z)
{
  gsl_type xabs = FABS(x);
  gsl_type yabs = FABS(y);
  gsl_type zabs = FABS(z);
  gsl_type w = MAX(xabs, MAX(yabs, zabs));

	if (w == 0.0)
	{
		return (0.0);
	}
	else
	{
		gsl_type r = w * sqrt((xabs / w) * (xabs / w) +
							  (yabs / w) * (yabs / w) +
							  (zabs / w) * (zabs / w));
		return r;
	}
}

gsl_type gsl_acosh (const gsl_type x)
{
	#ifdef GLSL
	return acosh(x);
	#else
		
	if (x > 1.0 / GSL_SQRT_EPSILON)
	{
		return log (x) + M_LN2;
	}
	else if (x > 2.0)
	{
		return log (2.0 * x - 1.0 / (sqrt (x * x - 1.0) + x));
	}
	else if (x > 1.0)
	{
		gsl_type t = x - 1.0;
		return gsl_log1p (t + sqrt (2.0 * t + t * t));
	}
	else if (x == 1.0)
	{
		return 0.0;
	}
	else
	{
		return GSL_NAN;
	}
	#endif
}

gsl_type gsl_asinh (const gsl_type x)
{
	#ifdef GLSL
	return asinh(x);
	#else
	gsl_type a = FABS (x);
	gsl_type s = (x < 0.0) ? -1.0 : 1.0;

	if (a > 1.0 / GSL_SQRT_EPSILON)
	{
		return s * (log (a) + M_LN2);
	}
	else if (a > 2.0)
	{
		return s * log (2.0 * a + 1.0 / (a + sqrt (a * a + 1.0)));
	}
	else if (a > GSL_SQRT_EPSILON)
	{
		gsl_type a2 = a * a;
		return s * gsl_log1p (a + a2 / (1.0 + sqrt (1.0 + a2)));
	}
	else
	{
		return x;
	}
	#endif
}

gsl_type gsl_atanh (const gsl_type x)
{
	gsl_type a = FABS (x);
	gsl_type s = (x < 0.0) ? -1.0 : 1.0;

	if (a > 1.0)
	{
		return GSL_NAN;
	}
	else if (a == 1.0)
	{
		return (x < 0.0) ? GSL_NEGINF : GSL_POSINF;
	}
	else if (a >= 0.5)
	{
		return s * 0.5 * gsl_log1p (2.0 * a / (1.0 - a));
	}
	else if (a > GSL_EPSILON)
	{
		return s * 0.5 * gsl_log1p (2.0 * a + 2.0 * a * a / (1.0 - a));
	}
	else
	{
		return x;
	}
}

bool gsl_isnan (const gsl_type x)
{
	//int status = (x != x);
	//return status;

	return !(x < 0.0 || x > 0.0 || x == 0.0);
	//return (asuint(x) & 0x7fffffff) > 0x7f800000;
}

bool gsl_isinf (const gsl_type x)
{
	return isinf(x);
}

bool gsl_finite (const gsl_type x)
{
	#ifdef HLSL
	return isfinite (x);
	#else
	const gsl_type y = x - x;
	bool status = (y == y);
	return status;
	#endif
}

gsl_type gsl_nan (void)
{
	return 0.0 / 0.0;
}

gsl_type gsl_posinf (void)
{
  return +1.0 / 0.0;
}

gsl_type gsl_neginf (void)
{
  return -1.0 / 0.0;
}

#ifndef gsl_coerce
#define gsl_coerce(x) GSL_TYPE(x)
#endif

gsl_type gsl_ldexp (const gsl_type x, const int e)
{
	int ex;

	if (x == 0.0)
	{
		return x;
	}

	{
		STRUCT frexp_res fre_res = gsl_frexp(x, ex);
		ex = fre_res.exp;
		gsl_type y = fre_res.result;//gsl_frexp (x, &ex);
		gsl_type e2 = e + ex, p2; // TODO

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

STRUCT frexp_res gsl_frexp (const gsl_type x, int e)
{
	if (x == 0.0)
	{
		e = 0;
		return frexp_res_new(0.0, e);
	}
	else if (!gsl_finite (x))
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
		gsl_type ex = ceil (log (FABS (x)) / M_LN2);
		int ei = GSL_CAST(int, ex);
		gsl_type f;

		/* Prevent underflow and overflow of 2**(-ei) */
		if (ei < MIN_EXP)
			ei = MIN_EXP;

		if (ei > -MIN_EXP)
			ei = -MIN_EXP;

		f = x * pow (2.0, -ei);

		if (!gsl_finite (f))
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

int gsl_fcmp (const gsl_type x1, const gsl_type x2, const gsl_type epsilon)
{
	int exponent;
	gsl_type delta, difference;

	/* Find exponent of largest absolute value */

	{
		gsl_type max = (FABS (x1) > FABS (x2)) ? x1 : x2;

		exponent = gsl_frexp (max, exponent).exp;
	}

	/* Form a neighborhood of size  2 * delta */

	delta = gsl_ldexp (epsilon, exponent);

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

gsl_type gsl_pow_uint(gsl_type x, uint n)
{
	gsl_type value = 1.0;

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

gsl_type gsl_pow_int(gsl_type x, int n)
{
	uint un;

	if(n < 0) {
		x = 1.0/x;
		un = -n;
	} else {
		un = n;
	}

	return gsl_pow_uint(x, un);
}

#ifndef hypot
#define hypot gsl_hypot
#endif

#ifndef log1p
#define log1p gsl_log1p
#endif

#ifndef expm1
#define expm1 gsl_expm1
#endif


#ifndef GLSL

#ifndef acosh
#define acosh gsl_acosh
#endif

#ifndef asinh
#define asinh gsl_asinh
#endif

#ifndef atanh
#define atanh gsl_atanh
#endif

#endif

#ifndef ldexp
#define ldexp gsl_ldexp
#endif

#ifndef frexp
#define frexp gsl_frexp
#endif

#ifndef isinf
//#define isinf gsl_isinf
#endif

#ifndef HLSL
#ifndef isfinite
#define isfinite gsl_finite
#endif
#endif

#ifndef finite
#define finite gsl_finite
#endif

#ifndef isnan
#define isnan gsl_isnan
#endif

#endif //__GSL_SYS_H__