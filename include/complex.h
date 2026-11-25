#pragma once

#include "slcompute.h"
#include "SLC_Structures.h"

namespace SLCompute {
	namespace complex {

		inline static const std::string LOG_LOC{ "SLCompute::complex" };


		// ---- 2-complex → complex ----

		SLCOMPUTE_EXPORT void slc_complex_add(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_add(SL_Complex res, SL_Complex a, SL_Complex b);

		SLCOMPUTE_EXPORT void slc_complex_sub(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_sub(SL_Complex res, SL_Complex a, SL_Complex b);

		SLCOMPUTE_EXPORT void slc_complex_mul(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_mul(SL_Complex res, SL_Complex a, SL_Complex b);

		SLCOMPUTE_EXPORT void slc_complex_div(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_div(SL_Complex res, SL_Complex a, SL_Complex b);


		// ---- 1-complex → float (properties) ----

		SLCOMPUTE_EXPORT void slc_complex_arg(FloatInstance res, ComplexInstance z);
		SLCOMPUTE_EXPORT void slc_complex_arg(SL_Float res, SL_Complex z);

		SLCOMPUTE_EXPORT void slc_complex_abs(FloatInstance res, ComplexInstance z);
		SLCOMPUTE_EXPORT void slc_complex_abs(SL_Float res, SL_Complex z);

		SLCOMPUTE_EXPORT void slc_complex_abs2(FloatInstance res, ComplexInstance z);
		SLCOMPUTE_EXPORT void slc_complex_abs2(SL_Float res, SL_Complex z);

		SLCOMPUTE_EXPORT void slc_complex_logabs(FloatInstance res, ComplexInstance z);
		SLCOMPUTE_EXPORT void slc_complex_logabs(SL_Float res, SL_Complex z);


		// ---- complex + real → complex ----

		SLCOMPUTE_EXPORT void slc_complex_add_real(ComplexInstance res, ComplexInstance a, FloatInstance x);
		SLCOMPUTE_EXPORT void slc_complex_add_real(SL_Complex res, SL_Complex a, SL_Float x);

		SLCOMPUTE_EXPORT void slc_complex_sub_real(ComplexInstance res, ComplexInstance a, FloatInstance x);
		SLCOMPUTE_EXPORT void slc_complex_sub_real(SL_Complex res, SL_Complex a, SL_Float x);

		SLCOMPUTE_EXPORT void slc_complex_mul_real(ComplexInstance res, ComplexInstance a, FloatInstance x);
		SLCOMPUTE_EXPORT void slc_complex_mul_real(SL_Complex res, SL_Complex a, SL_Float x);

		SLCOMPUTE_EXPORT void slc_complex_div_real(ComplexInstance res, ComplexInstance a, FloatInstance x);
		SLCOMPUTE_EXPORT void slc_complex_div_real(SL_Complex res, SL_Complex a, SL_Float x);

		SLCOMPUTE_EXPORT void slc_complex_add_imag(ComplexInstance res, ComplexInstance a, FloatInstance y);
		SLCOMPUTE_EXPORT void slc_complex_add_imag(SL_Complex res, SL_Complex a, SL_Float y);

		SLCOMPUTE_EXPORT void slc_complex_sub_imag(ComplexInstance res, ComplexInstance a, FloatInstance y);
		SLCOMPUTE_EXPORT void slc_complex_sub_imag(SL_Complex res, SL_Complex a, SL_Float y);

		SLCOMPUTE_EXPORT void slc_complex_mul_imag(ComplexInstance res, ComplexInstance a, FloatInstance y);
		SLCOMPUTE_EXPORT void slc_complex_mul_imag(SL_Complex res, SL_Complex a, SL_Float y);

		SLCOMPUTE_EXPORT void slc_complex_div_imag(ComplexInstance res, ComplexInstance a, FloatInstance y);
		SLCOMPUTE_EXPORT void slc_complex_div_imag(SL_Complex res, SL_Complex a, SL_Float y);


		// ---- unary complex → complex ----

		SLCOMPUTE_EXPORT void slc_complex_conjugate(ComplexInstance res, ComplexInstance z);
		SLCOMPUTE_EXPORT void slc_complex_conjugate(SL_Complex res, SL_Complex z);

		SLCOMPUTE_EXPORT void slc_complex_inverse(ComplexInstance res, ComplexInstance z);
		SLCOMPUTE_EXPORT void slc_complex_inverse(SL_Complex res, SL_Complex z);

		SLCOMPUTE_EXPORT void slc_complex_negative(ComplexInstance res, ComplexInstance z);
		SLCOMPUTE_EXPORT void slc_complex_negative(SL_Complex res, SL_Complex z);


		// ---- elementary functions ----

		SLCOMPUTE_EXPORT void slc_complex_sqrt(ComplexInstance res, ComplexInstance z);
		SLCOMPUTE_EXPORT void slc_complex_sqrt(SL_Complex res, SL_Complex z);

		SLCOMPUTE_EXPORT void slc_complex_sqrt_real(ComplexInstance res, FloatInstance x);
		SLCOMPUTE_EXPORT void slc_complex_sqrt_real(SL_Complex res, SL_Float x);

		SLCOMPUTE_EXPORT void slc_complex_pow(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_pow(SL_Complex res, SL_Complex a, SL_Complex b);

		SLCOMPUTE_EXPORT void slc_complex_pow_real(ComplexInstance res, ComplexInstance a, FloatInstance b);
		SLCOMPUTE_EXPORT void slc_complex_pow_real(SL_Complex res, SL_Complex a, SL_Float b);

		SLCOMPUTE_EXPORT void slc_complex_exp(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_exp(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_log(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_log(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_log10(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_log10(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_log_b(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_log_b(SL_Complex res, SL_Complex a, SL_Complex b);


		// ---- trigonometric ----

		SLCOMPUTE_EXPORT void slc_complex_sin(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_sin(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_cos(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_cos(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_sec(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_sec(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_csc(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_csc(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_tan(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_tan(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_cot(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_cot(SL_Complex res, SL_Complex a);


		// ---- inverse trigonometric ----

		SLCOMPUTE_EXPORT void slc_complex_arcsin(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arcsin(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arcsin_real(ComplexInstance res, FloatInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arcsin_real(SL_Complex res, SL_Float a);

		SLCOMPUTE_EXPORT void slc_complex_arccos(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccos(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arccos_real(ComplexInstance res, FloatInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccos_real(SL_Complex res, SL_Float a);

		SLCOMPUTE_EXPORT void slc_complex_arcsec(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arcsec(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arcsec_real(ComplexInstance res, FloatInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arcsec_real(SL_Complex res, SL_Float a);

		SLCOMPUTE_EXPORT void slc_complex_arccsc(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccsc(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arccsc_real(ComplexInstance res, FloatInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccsc_real(SL_Complex res, SL_Float a);

		SLCOMPUTE_EXPORT void slc_complex_arctan(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arctan(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arccot(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccot(SL_Complex res, SL_Complex a);


		// ---- hyperbolic ----

		SLCOMPUTE_EXPORT void slc_complex_sinh(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_sinh(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_cosh(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_cosh(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_sech(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_sech(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_csch(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_csch(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_tanh(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_tanh(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_coth(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_coth(SL_Complex res, SL_Complex a);


		// ---- inverse hyperbolic ----

		SLCOMPUTE_EXPORT void slc_complex_arcsinh(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arcsinh(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arccosh(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccosh(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arccosh_real(ComplexInstance res, FloatInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccosh_real(SL_Complex res, SL_Float a);

		SLCOMPUTE_EXPORT void slc_complex_arcsech(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arcsech(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arccsch(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccsch(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arctanh(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arctanh(SL_Complex res, SL_Complex a);

		SLCOMPUTE_EXPORT void slc_complex_arctanh_real(ComplexInstance res, FloatInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arctanh_real(SL_Complex res, SL_Float a);

		SLCOMPUTE_EXPORT void slc_complex_arccoth(ComplexInstance res, ComplexInstance a);
		SLCOMPUTE_EXPORT void slc_complex_arccoth(SL_Complex res, SL_Complex a);

	}
}
