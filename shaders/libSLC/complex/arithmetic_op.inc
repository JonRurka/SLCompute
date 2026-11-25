#ifndef _SLC_COMPLEX_ARITHMETIC_OP_INC_
#define _SLC_COMPLEX_ARITHMETIC_OP_INC_

/* Complex arithmetic operators */

STRUCT slc_complex slc_complex_add (STRUCT slc_complex a, STRUCT slc_complex b)  /* r=a+b */
{
	slc_type ar = SLC_REAL (a);
	slc_type ai = SLC_IMAG (a);
	slc_type br = SLC_REAL (b);
	slc_type bi = SLC_IMAG (b);

	slc_complex z;
	SLC_SET_COMPLEX (z, ar + br, ai + bi);
	return z;
}

STRUCT slc_complex slc_complex_sub (STRUCT slc_complex a, STRUCT slc_complex b)  /* r=a-b */
{
	slc_type ar = SLC_REAL (a);
	slc_type ai = SLC_IMAG (a);
	slc_type br = SLC_REAL (b);
	slc_type bi = SLC_IMAG (b);

	slc_complex z;
	SLC_SET_COMPLEX (z, ar - br, ai - bi);
	return z;
}

STRUCT slc_complex slc_complex_mul (STRUCT slc_complex a, STRUCT slc_complex b)  /* r=a*b */
{
	slc_type ar = SLC_REAL (a);
	slc_type ai = SLC_IMAG (a);
	slc_type br = SLC_REAL (b);
	slc_type bi = SLC_IMAG (b);

	slc_complex z;
	SLC_SET_COMPLEX (z, ar * br - ai * bi, ar * bi + ai * br);
	return z;
}

STRUCT slc_complex slc_complex_div (STRUCT slc_complex a, STRUCT slc_complex b)  /* r=a/b */
{
	slc_type ar = SLC_REAL (a);
	slc_type ai = SLC_IMAG (a);
	slc_type br = SLC_REAL (b);
	slc_type bi = SLC_IMAG (b);

	slc_type s = 1.0 / slc_complex_abs (b);

	slc_type sbr = s * br;
	slc_type sbi = s * bi;

	slc_type zr = (ar * sbr + ai * sbi) * s;
	slc_type zi = (ai * sbr - ar * sbi) * s;

	slc_complex z;
	SLC_SET_COMPLEX (z, zr, zi);
	return z;
}
                                                           
STRUCT slc_complex slc_complex_add_real (STRUCT slc_complex a, slc_type x)  /* r=a+x */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, SLC_REAL (a) + x, SLC_IMAG (a));
	return z;
}

STRUCT slc_complex slc_complex_sub_real (STRUCT slc_complex a, slc_type x)  /* r=a-x */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, SLC_REAL (a) - x, SLC_IMAG (a));
	return z;
}

STRUCT slc_complex slc_complex_mul_real (STRUCT slc_complex a, slc_type x)  /* r=a*x */
{
	slc_complex z;
  SLC_SET_COMPLEX (z, x * SLC_REAL (a), x * SLC_IMAG (a));
  return z;
}

STRUCT slc_complex slc_complex_div_real (STRUCT slc_complex a, slc_type x)  /* r=a/x */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, SLC_REAL (a) / x, SLC_IMAG (a) / x);
	return z;
}

STRUCT slc_complex slc_complex_add_imag (STRUCT slc_complex a, slc_type y)  /* r=a+iy */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, SLC_REAL (a), SLC_IMAG (a) + y);
	return z;
}

STRUCT slc_complex slc_complex_sub_imag (STRUCT slc_complex a, slc_type y)  /* r=a-iy */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, SLC_REAL (a), SLC_IMAG (a) - y);
	return z;
}

STRUCT slc_complex slc_complex_mul_imag (STRUCT slc_complex a, slc_type y)  /* r=a*iy */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, -y * SLC_IMAG (a), y * SLC_REAL (a));
	return z;
}

STRUCT slc_complex slc_complex_div_imag (STRUCT slc_complex a, slc_type y)  /* r=a/iy */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, SLC_IMAG (a) / y,  - SLC_REAL (a) / y);
	return z;
}

STRUCT slc_complex slc_complex_conjugate (STRUCT slc_complex a)  /* r=conj(z) */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, SLC_REAL (a), -SLC_IMAG (a));
	return z;
}

STRUCT slc_complex slc_complex_inverse (STRUCT slc_complex a)    /* r=1/a */
{
	slc_type s = 1.0 / slc_complex_abs (a);

	slc_complex z;
	SLC_SET_COMPLEX (z, (SLC_REAL (a) * s) * s, -(SLC_IMAG (a) * s) * s);
	return z;
}

STRUCT slc_complex slc_complex_negative (STRUCT slc_complex a)   /* r=-a */
{
	slc_complex z;
	SLC_SET_COMPLEX (z, -SLC_REAL (a), -SLC_IMAG (a));
	return z;
}

#endif