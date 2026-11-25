#pragma once

#include "slcompute.h"
#include "SLC_Structures.h"

namespace SLCompute {
	namespace complex {

		inline static const std::string LOG_LOC{ "SLCompute::complex" };

		SLCOMPUTE_EXPORT void slc_complex_add(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_add(SL_Complex res, SL_Complex a, SL_Complex b);


		SLCOMPUTE_EXPORT void slc_complex_sub(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_sub(SL_Complex res, SL_Complex a, SL_Complex b);


		SLCOMPUTE_EXPORT void slc_complex_mul(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_mul(SL_Complex res, SL_Complex a, SL_Complex b);


		SLCOMPUTE_EXPORT void slc_complex_div(ComplexInstance res, ComplexInstance a, ComplexInstance b);
		SLCOMPUTE_EXPORT void slc_complex_div(SL_Complex res, SL_Complex a, SL_Complex b);

	}
}