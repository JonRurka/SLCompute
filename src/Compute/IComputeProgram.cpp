#include "IComputeProgram.h"
#include "IComputeBuffer.h"
#include "IComputeProgram_private.h"
#include "Logger.h"

using namespace DynamicCompute::Compute;

void IComputeProgram::AddIncludeDirectory(std::string directory)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	p_inst->AddIncludeDirectory(directory);
}

void IComputeProgram::AddDefine(std::string name, std::string value)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	p_inst->AddDefine(name, value);
}

int IComputeProgram::Build()
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->Build();
}

int IComputeProgram::FinishBuild()
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->FinishBuild();
}

int IComputeProgram::GetKernelID(std::string name)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->GetKernelID(name);
}

void IComputeProgram::KernelSetWorkGroupSize(std::string k_name, glm::uvec3 size)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	p_inst->KernelSetWorkGroupSize(k_name, size);
}

int IComputeProgram::KernelSetBuffer(std::string k_name, IComputeBuffer* buffer, BindIndex arg)
{
	//Logger::LogDebug(LOG_LOC, "IComputeProgram::KernelSetBuffer");
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	SL_ASSERT(buffer != nullptr, "buffer is null");
	return p_inst->KernelSetBuffer(k_name, buffer->p_inst, *reinterpret_cast<IComputeProgram_private::BindIndex *>(&arg));
}

int IComputeProgram::RunKernel(std::string k_name, int size_x, int size_y, int size_z)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->RunKernel(k_name, size_x, size_y, size_z);
}

int IComputeProgram::RunKernel(int kernel_id, int size_x, int size_y, int size_z)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->RunKernel(kernel_id, size_x, size_y, size_z);
}

int IComputeProgram::RunKernel(std::string k_name, int num, int size_x, int size_y, int size_z)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->RunKernel(k_name, num, size_x, size_y, size_z);
}

int IComputeProgram::RunKernel(int kernel_id, int num, int size_x, int size_y, int size_z)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->RunKernel(kernel_id, num, size_x, size_y, size_z);
}

void* IComputeProgram::GetKernelFunction(int kernel_id)
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->GetKernelFunction(kernel_id);
}

IComputeProgram::ProgramBuildState IComputeProgram::GetState()
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	IComputeProgram_private::ProgramBuildState val = p_inst->GetState();
	return *((IComputeProgram::ProgramBuildState*)&val);
}

int IComputeProgram::GetBuildResultCode()
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->GetBuildResultCode();
}

std::string IComputeProgram::GetBuildErrorMessage()
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->GetBuildErrorMessage();
}

std::string IComputeProgram::GetProgramName()
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	return p_inst->GetProgramName();
}

void IComputeProgram::Dispose()
{
	SL_ASSERT(p_inst != nullptr, "p_inst is null");
	p_inst->Dispose();
	p_inst = nullptr;
}
