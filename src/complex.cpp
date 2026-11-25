#include "complex.h"
#include "SLC_ComputePool_private.h"
#include "SLC_Program.h"
#include "SLC_func_ids.h"
#include "Logger.h"

using namespace SLCompute;
using namespace SLCompute::complex;


// ---- helpers ----

static ComputePool_private* get_pool(SL_Strided_Buffer b) {
    SL_ASSERT(b != nullptr, "Null pool");
    return static_cast<ComputePool_private *>(b->Pool());
}


// ---- 2-complex → complex ----

void SLCompute::complex::slc_complex_add(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
    slc_complex_add(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b)));
}
void SLCompute::complex::slc_complex_add(SL_Complex res, SL_Complex a, SL_Complex b) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ADD, res, {a, b});
}

void SLCompute::complex::slc_complex_sub(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
    slc_complex_sub(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b)));
}
void SLCompute::complex::slc_complex_sub(SL_Complex res, SL_Complex a, SL_Complex b) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SUB, res, {a, b});
}

void SLCompute::complex::slc_complex_mul(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
    slc_complex_mul(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b)));
}
void SLCompute::complex::slc_complex_mul(SL_Complex res, SL_Complex a, SL_Complex b) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_MUL, res, {a, b});
}

void SLCompute::complex::slc_complex_div(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
    slc_complex_div(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b)));
}
void SLCompute::complex::slc_complex_div(SL_Complex res, SL_Complex a, SL_Complex b) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_DIV, res, {a, b});
}


// ---- 1-complex → float (properties) ----

void SLCompute::complex::slc_complex_arg(FloatInstance res, ComplexInstance z) {
    slc_complex_arg(
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(z)));
}
void SLCompute::complex::slc_complex_arg(SL_Float res, SL_Complex z) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARG, res, {z});
}

void SLCompute::complex::slc_complex_abs(FloatInstance res, ComplexInstance z) {
    slc_complex_abs(
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(z)));
}
void SLCompute::complex::slc_complex_abs(SL_Float res, SL_Complex z) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ABS, res, {z});
}

void SLCompute::complex::slc_complex_abs2(FloatInstance res, ComplexInstance z) {
    slc_complex_abs2(
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(z)));
}
void SLCompute::complex::slc_complex_abs2(SL_Float res, SL_Complex z) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ABS2, res, {z});
}

void SLCompute::complex::slc_complex_logabs(FloatInstance res, ComplexInstance z) {
    slc_complex_logabs(
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(z)));
}
void SLCompute::complex::slc_complex_logabs(SL_Float res, SL_Complex z) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_LOGABS, res, {z});
}


// ---- complex + real → complex ----

void SLCompute::complex::slc_complex_add_real(ComplexInstance res, ComplexInstance a, FloatInstance x) {
    slc_complex_add_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(x)));
}
void SLCompute::complex::slc_complex_add_real(SL_Complex res, SL_Complex a, SL_Float x) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ADD_REAL, res, {a, x});
}

void SLCompute::complex::slc_complex_sub_real(ComplexInstance res, ComplexInstance a, FloatInstance x) {
    slc_complex_sub_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(x)));
}
void SLCompute::complex::slc_complex_sub_real(SL_Complex res, SL_Complex a, SL_Float x) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SUB_REAL, res, {a, x});
}

void SLCompute::complex::slc_complex_mul_real(ComplexInstance res, ComplexInstance a, FloatInstance x) {
    slc_complex_mul_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(x)));
}
void SLCompute::complex::slc_complex_mul_real(SL_Complex res, SL_Complex a, SL_Float x) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_MUL_REAL, res, {a, x});
}

void SLCompute::complex::slc_complex_div_real(ComplexInstance res, ComplexInstance a, FloatInstance x) {
    slc_complex_div_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(x)));
}
void SLCompute::complex::slc_complex_div_real(SL_Complex res, SL_Complex a, SL_Float x) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_DIV_REAL, res, {a, x});
}

void SLCompute::complex::slc_complex_add_imag(ComplexInstance res, ComplexInstance a, FloatInstance y) {
    slc_complex_add_imag(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(y)));
}
void SLCompute::complex::slc_complex_add_imag(SL_Complex res, SL_Complex a, SL_Float y) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ADD_IMAG, res, {a, y});
}

void SLCompute::complex::slc_complex_sub_imag(ComplexInstance res, ComplexInstance a, FloatInstance y) {
    slc_complex_sub_imag(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(y)));
}
void SLCompute::complex::slc_complex_sub_imag(SL_Complex res, SL_Complex a, SL_Float y) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SUB_IMAG, res, {a, y});
}

void SLCompute::complex::slc_complex_mul_imag(ComplexInstance res, ComplexInstance a, FloatInstance y) {
    slc_complex_mul_imag(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(y)));
}
void SLCompute::complex::slc_complex_mul_imag(SL_Complex res, SL_Complex a, SL_Float y) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_MUL_IMAG, res, {a, y});
}

void SLCompute::complex::slc_complex_div_imag(ComplexInstance res, ComplexInstance a, FloatInstance y) {
    slc_complex_div_imag(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(y)));
}
void SLCompute::complex::slc_complex_div_imag(SL_Complex res, SL_Complex a, SL_Float y) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_DIV_IMAG, res, {a, y});
}


// ---- unary complex → complex ----

void SLCompute::complex::slc_complex_conjugate(ComplexInstance res, ComplexInstance z) {
    slc_complex_conjugate(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(z)));
}
void SLCompute::complex::slc_complex_conjugate(SL_Complex res, SL_Complex z) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_CONJUGATE, res, {z});
}

void SLCompute::complex::slc_complex_inverse(ComplexInstance res, ComplexInstance z) {
    slc_complex_inverse(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(z)));
}
void SLCompute::complex::slc_complex_inverse(SL_Complex res, SL_Complex z) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_INVERSE, res, {z});
}

void SLCompute::complex::slc_complex_negative(ComplexInstance res, ComplexInstance z) {
    slc_complex_negative(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(z)));
}
void SLCompute::complex::slc_complex_negative(SL_Complex res, SL_Complex z) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_NEGATIVE, res, {z});
}


// ---- elementary functions ----

void SLCompute::complex::slc_complex_sqrt(ComplexInstance res, ComplexInstance z) {
    slc_complex_sqrt(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(z)));
}
void SLCompute::complex::slc_complex_sqrt(SL_Complex res, SL_Complex z) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SQRT, res, {z});
}

void SLCompute::complex::slc_complex_sqrt_real(ComplexInstance res, FloatInstance x) {
    slc_complex_sqrt_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(x)));
}
void SLCompute::complex::slc_complex_sqrt_real(SL_Complex res, SL_Float x) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SQRT_REAL, res, {x});
}

void SLCompute::complex::slc_complex_pow(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
    slc_complex_pow(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b)));
}
void SLCompute::complex::slc_complex_pow(SL_Complex res, SL_Complex a, SL_Complex b) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_POW, res, {a, b});
}

void SLCompute::complex::slc_complex_pow_real(ComplexInstance res, ComplexInstance a, FloatInstance b) {
    slc_complex_pow_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(b)));
}
void SLCompute::complex::slc_complex_pow_real(SL_Complex res, SL_Complex a, SL_Float b) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_POW_REAL, res, {a, b});
}

void SLCompute::complex::slc_complex_exp(ComplexInstance res, ComplexInstance a) {
    slc_complex_exp(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_exp(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_EXP, res, {a});
}

void SLCompute::complex::slc_complex_log(ComplexInstance res, ComplexInstance a) {
    slc_complex_log(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_log(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_LOG, res, {a});
}

void SLCompute::complex::slc_complex_log10(ComplexInstance res, ComplexInstance a) {
    slc_complex_log10(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_log10(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_LOG10, res, {a});
}

void SLCompute::complex::slc_complex_log_b(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
    slc_complex_log_b(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b)));
}
void SLCompute::complex::slc_complex_log_b(SL_Complex res, SL_Complex a, SL_Complex b) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_LOG_B, res, {a, b});
}


// ---- trigonometric ----

void SLCompute::complex::slc_complex_sin(ComplexInstance res, ComplexInstance a) {
    slc_complex_sin(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_sin(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SIN, res, {a});
}

void SLCompute::complex::slc_complex_cos(ComplexInstance res, ComplexInstance a) {
    slc_complex_cos(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_cos(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_COS, res, {a});
}

void SLCompute::complex::slc_complex_sec(ComplexInstance res, ComplexInstance a) {
    slc_complex_sec(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_sec(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SEC, res, {a});
}

void SLCompute::complex::slc_complex_csc(ComplexInstance res, ComplexInstance a) {
    slc_complex_csc(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_csc(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_CSC, res, {a});
}

void SLCompute::complex::slc_complex_tan(ComplexInstance res, ComplexInstance a) {
    slc_complex_tan(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_tan(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_TAN, res, {a});
}

void SLCompute::complex::slc_complex_cot(ComplexInstance res, ComplexInstance a) {
    slc_complex_cot(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_cot(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_COT, res, {a});
}


// ---- inverse trigonometric ----

void SLCompute::complex::slc_complex_arcsin(ComplexInstance res, ComplexInstance a) {
    slc_complex_arcsin(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arcsin(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCSIN, res, {a});
}

void SLCompute::complex::slc_complex_arcsin_real(ComplexInstance res, FloatInstance a) {
    slc_complex_arcsin_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arcsin_real(SL_Complex res, SL_Float a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCSIN_REAL, res, {a});
}

void SLCompute::complex::slc_complex_arccos(ComplexInstance res, ComplexInstance a) {
    slc_complex_arccos(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccos(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCOS, res, {a});
}

void SLCompute::complex::slc_complex_arccos_real(ComplexInstance res, FloatInstance a) {
    slc_complex_arccos_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccos_real(SL_Complex res, SL_Float a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCOS_REAL, res, {a});
}

void SLCompute::complex::slc_complex_arcsec(ComplexInstance res, ComplexInstance a) {
    slc_complex_arcsec(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arcsec(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCSEC, res, {a});
}

void SLCompute::complex::slc_complex_arcsec_real(ComplexInstance res, FloatInstance a) {
    slc_complex_arcsec_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arcsec_real(SL_Complex res, SL_Float a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCSEC_REAL, res, {a});
}

void SLCompute::complex::slc_complex_arccsc(ComplexInstance res, ComplexInstance a) {
    slc_complex_arccsc(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccsc(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCSC, res, {a});
}

void SLCompute::complex::slc_complex_arccsc_real(ComplexInstance res, FloatInstance a) {
    slc_complex_arccsc_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccsc_real(SL_Complex res, SL_Float a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCSC_REAL, res, {a});
}

void SLCompute::complex::slc_complex_arctan(ComplexInstance res, ComplexInstance a) {
    slc_complex_arctan(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arctan(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCTAN, res, {a});
}

void SLCompute::complex::slc_complex_arccot(ComplexInstance res, ComplexInstance a) {
    slc_complex_arccot(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccot(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCOT, res, {a});
}


// ---- hyperbolic ----

void SLCompute::complex::slc_complex_sinh(ComplexInstance res, ComplexInstance a) {
    slc_complex_sinh(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_sinh(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SINH, res, {a});
}

void SLCompute::complex::slc_complex_cosh(ComplexInstance res, ComplexInstance a) {
    slc_complex_cosh(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_cosh(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_COSH, res, {a});
}

void SLCompute::complex::slc_complex_sech(ComplexInstance res, ComplexInstance a) {
    slc_complex_sech(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_sech(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SECH, res, {a});
}

void SLCompute::complex::slc_complex_csch(ComplexInstance res, ComplexInstance a) {
    slc_complex_csch(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_csch(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_CSCH, res, {a});
}

void SLCompute::complex::slc_complex_tanh(ComplexInstance res, ComplexInstance a) {
    slc_complex_tanh(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_tanh(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_TANH, res, {a});
}

void SLCompute::complex::slc_complex_coth(ComplexInstance res, ComplexInstance a) {
    slc_complex_coth(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_coth(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_COTH, res, {a});
}


// ---- inverse hyperbolic ----

void SLCompute::complex::slc_complex_arcsinh(ComplexInstance res, ComplexInstance a) {
    slc_complex_arcsinh(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arcsinh(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCSINH, res, {a});
}

void SLCompute::complex::slc_complex_arccosh(ComplexInstance res, ComplexInstance a) {
    slc_complex_arccosh(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccosh(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCOSH, res, {a});
}

void SLCompute::complex::slc_complex_arccosh_real(ComplexInstance res, FloatInstance a) {
    slc_complex_arccosh_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccosh_real(SL_Complex res, SL_Float a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCOSH_REAL, res, {a});
}

void SLCompute::complex::slc_complex_arcsech(ComplexInstance res, ComplexInstance a) {
    slc_complex_arcsech(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arcsech(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCSECH, res, {a});
}

void SLCompute::complex::slc_complex_arccsch(ComplexInstance res, ComplexInstance a) {
    slc_complex_arccsch(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccsch(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCSCH, res, {a});
}

void SLCompute::complex::slc_complex_arctanh(ComplexInstance res, ComplexInstance a) {
    slc_complex_arctanh(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arctanh(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCTANH, res, {a});
}

void SLCompute::complex::slc_complex_arctanh_real(ComplexInstance res, FloatInstance a) {
    slc_complex_arctanh_real(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Float>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arctanh_real(SL_Complex res, SL_Float a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCTANH_REAL, res, {a});
}

void SLCompute::complex::slc_complex_arccoth(ComplexInstance res, ComplexInstance a) {
    slc_complex_arccoth(
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res)),
        dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a)));
}
void SLCompute::complex::slc_complex_arccoth(SL_Complex res, SL_Complex a) {
    ComputePool_private* pool = get_pool(res);
    SL_ASSERT(pool, "Null pool");
    ProgramController::Execute(pool->ProgramInstance(), PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ARCCOTH, res, {a});
}
