#ifndef _GSL_COMPLEX_ARITHMETIC_OP_INC_
#define _GSL_COMPLEX_ARITHMETIC_OP_INC_

/* Complex arithmetic operators */

STRUCT gsl_complex gsl_complex_add (STRUCT gsl_complex a, STRUCT gsl_complex b)  /* r=a+b */
{
	gsl_type ar = GSL_REAL (a);
	gsl_type ai = GSL_IMAG (a);
	gsl_type br = GSL_REAL (b);
	gsl_type bi = GSL_IMAG (b);

	gsl_complex z;
	GSL_SET_COMPLEX (z, ar + br, ai + bi);
	return z;
}

STRUCT gsl_complex gsl_complex_sub (STRUCT gsl_complex a, STRUCT gsl_complex b)  /* r=a-b */
{
	gsl_type ar = GSL_REAL (a);
	gsl_type ai = GSL_IMAG (a);
	gsl_type br = GSL_REAL (b);
	gsl_type bi = GSL_IMAG (b);

	gsl_complex z;
	GSL_SET_COMPLEX (z, ar - br, ai - bi);
	return z;
}

STRUCT gsl_complex gsl_complex_mul (STRUCT gsl_complex a, STRUCT gsl_complex b)  /* r=a*b */
{
	gsl_type ar = GSL_REAL (a);
	gsl_type ai = GSL_IMAG (a);
	gsl_type br = GSL_REAL (b);
	gsl_type bi = GSL_IMAG (b);

	gsl_complex z;
	GSL_SET_COMPLEX (z, ar * br - ai * bi, ar * bi + ai * br);
	return z;
}

STRUCT gsl_complex gsl_complex_div (STRUCT gsl_complex a, STRUCT gsl_complex b)  /* r=a/b */
{
	gsl_type ar = GSL_REAL (a);
	gsl_type ai = GSL_IMAG (a);
	gsl_type br = GSL_REAL (b);
	gsl_type bi = GSL_IMAG (b);

	gsl_type s = 1.0 / gsl_complex_abs (b);

	gsl_type sbr = s * br;
	gsl_type sbi = s * bi;

	gsl_type zr = (ar * sbr + ai * sbi) * s;
	gsl_type zi = (ai * sbr - ar * sbi) * s;

	gsl_complex z;
	GSL_SET_COMPLEX (z, zr, zi);
	return z;
}
                                                           
STRUCT gsl_complex gsl_complex_add_real (STRUCT gsl_complex a, gsl_type x)  /* r=a+x */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, GSL_REAL (a) + x, GSL_IMAG (a));
	return z;
}

STRUCT gsl_complex gsl_complex_sub_real (STRUCT gsl_complex a, gsl_type x)  /* r=a-x */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, GSL_REAL (a) - x, GSL_IMAG (a));
	return z;
}

STRUCT gsl_complex gsl_complex_mul_real (STRUCT gsl_complex a, gsl_type x)  /* r=a*x */
{
	gsl_complex z;
  GSL_SET_COMPLEX (z, x * GSL_REAL (a), x * GSL_IMAG (a));
  return z;
}

STRUCT gsl_complex gsl_complex_div_real (STRUCT gsl_complex a, gsl_type x)  /* r=a/x */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, GSL_REAL (a) / x, GSL_IMAG (a) / x);
	return z;
}

STRUCT gsl_complex gsl_complex_add_imag (STRUCT gsl_complex a, gsl_type y)  /* r=a+iy */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, GSL_REAL (a), GSL_IMAG (a) + y);
	return z;
}

STRUCT gsl_complex gsl_complex_sub_imag (STRUCT gsl_complex a, gsl_type y)  /* r=a-iy */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, GSL_REAL (a), GSL_IMAG (a) - y);
	return z;
}

STRUCT gsl_complex gsl_complex_mul_imag (STRUCT gsl_complex a, gsl_type y)  /* r=a*iy */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, -y * GSL_IMAG (a), y * GSL_REAL (a));
	return z;
}

STRUCT gsl_complex gsl_complex_div_imag (STRUCT gsl_complex a, gsl_type y)  /* r=a/iy */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, GSL_IMAG (a) / y,  - GSL_REAL (a) / y);
	return z;
}

STRUCT gsl_complex gsl_complex_conjugate (STRUCT gsl_complex a)  /* r=conj(z) */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, GSL_REAL (a), -GSL_IMAG (a));
	return z;
}

STRUCT gsl_complex gsl_complex_inverse (STRUCT gsl_complex a)    /* r=1/a */
{
	gsl_type s = 1.0 / gsl_complex_abs (a);

	gsl_complex z;
	GSL_SET_COMPLEX (z, (GSL_REAL (a) * s) * s, -(GSL_IMAG (a) * s) * s);
	return z;
}

STRUCT gsl_complex gsl_complex_negative (STRUCT gsl_complex a)   /* r=-a */
{
	gsl_complex z;
	GSL_SET_COMPLEX (z, -GSL_REAL (a), -GSL_IMAG (a));
	return z;
}

#endif