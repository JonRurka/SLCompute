#include "complex.h"
#include "GPGSL_ComputePool_private.h"
#include "GPGSL_Program.h"
#include "GPGSL_func_ids.h"
#include "Logger.h"

using namespace SLCompute;
using namespace SLCompute::complex;


void SLCompute::complex::gpgsl_complex_add(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
	SL_Complex res_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res));
	SL_Complex a_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a));
	SL_Complex b_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b));
	return gpgsl_complex_add(res_inst, a_inst, b_inst);
}
void SLCompute::complex::gpgsl_complex_add(SL_Complex res, SL_Complex a, SL_Complex b)
{
	Logger::LogDebug(LOG_LOC, "SLCompute::complex::gpgsl_complex_add");

	ComputePool_private* pool = (ComputePool_private*) res->Pool();
	SL_ASSERT(pool, "Null pool");
	ProgramController::ProgramInstance inst = pool->ProgramInstance();
	ProgramController::Execute(inst, PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ADD, res, {a, b});
	//pool->Set_Control(res->Index(), a->Index(), b->Index(), 0);
	//pool->Execute_Func(PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_ADD);
}

void SLCompute::complex::gpgsl_complex_sub(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
	SL_Complex res_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res));
	SL_Complex a_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a));
	SL_Complex b_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b));
	return gpgsl_complex_sub(res_inst, a_inst, b_inst);
}
void SLCompute::complex::gpgsl_complex_sub(SL_Complex res, SL_Complex a, SL_Complex b)
{
	ComputePool_private* pool = (ComputePool_private*)res->Pool();
	if (pool == nullptr)
		return;
	ProgramController::ProgramInstance inst = pool->ProgramInstance();
	ProgramController::Execute(inst, PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SUB, res, {a, b});
	//pool->Set_Control(res->Index(), a->Index(), b->Index(), 0);
	//pool->Execute_Func(PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_SUB);
}

void SLCompute::complex::gpgsl_complex_mul(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
	SL_Complex res_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res));
	SL_Complex a_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a));
	SL_Complex b_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b));
	return gpgsl_complex_mul(res_inst, a_inst, b_inst);
}
void SLCompute::complex::gpgsl_complex_mul(SL_Complex res, SL_Complex a, SL_Complex b)
{
	ComputePool_private* pool = (ComputePool_private*)res->Pool();
	if (pool == nullptr)
		return;
	ProgramController::ProgramInstance inst = pool->ProgramInstance();
	ProgramController::Execute(inst, PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_MUL, res, {a, b});
	//pool->Set_Control(res->Index(), a->Index(), b->Index(), 0);
	//pool->Execute_Func(PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_MUL);
}

void SLCompute::complex::gpgsl_complex_div(ComplexInstance res, ComplexInstance a, ComplexInstance b) {
	SL_Complex res_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(res));
	SL_Complex a_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(a));
	SL_Complex b_inst = dynamic_cast<SL_Complex>(SL_Strided_Buffer_struct::Get(b));
	return gpgsl_complex_div(res_inst, a_inst, b_inst);
}
void SLCompute::complex::gpgsl_complex_div(SL_Complex res, SL_Complex a, SL_Complex b)
{
	ComputePool_private* pool = (ComputePool_private*)res->Pool();
	if (pool == nullptr)
		return;
	ProgramController::ProgramInstance inst = pool->ProgramInstance();
	ProgramController::Execute(inst, PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_DIV, res, {a, b});
	//pool->Set_Control(res->Index(), a->Index(), b->Index(), 0);
	//pool->Execute_Func(PROGRAM_ID_COMPLEX, FUNC_ID_COMPLEX_DIV);
}
