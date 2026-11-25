#include "slcompute.h"
#include <vector>
#include <string>

#include <SLC_Program.h>
#include <SLC_ComputePool.h>
#include <SLC_Structures.h>
#include <complex.h>

#include <SLC_ComputePool_private.h>

using namespace SLCompute;

int main() {
    slcompute();


    ProgramController::ProgramSettings settings{};

    printf("Test_Package: Enable Complex Program.\n");
    ProgramController::Enable(ProgramController::Programs::COMPLEX);

    printf("Test_Package: Enable Complex Datatype.\n");
    SL_Complex_struct::Enable();

    printf("Test_Package: Create program controller.\n");
    ProgramController::ProgramInstance program = ProgramController::Create(settings);

    ProgramController::PoolSettings pool_settings{};
    pool_settings.x_size = 1;
    pool_settings.type = PoolType::Static;
    printf("Test_Package: Create Pool.\n");
    PoolInstance pool_instance = ProgramController::CreatePool(program, pool_settings);

    printf("Test_Package: Test compute buffer engine.\n");
    pool_instance->Test_Buffer_Engine(9, 10);
    pool_instance->Test_Buffer_Engine(11, 10);
    pool_instance->Test_Buffer_Engine(30, 10);

    printf("Test_Package: Create Complex 1.\n");
    SL_Complex complex_buf_1 = pool_instance->Get_Complex({{1,3}});
    printf("Test_Package: Create Complex 2.\n");
    SL_Complex complex_buf_2 = pool_instance->Get_Complex({{2,4}});
    printf("Test_Package: Create Complex res.\n");
    SL_Complex complex_buf_res = pool_instance->Get_Complex({{12,13}});

    printf("Test_Package: Start program controller.\n");
    ProgramController::Start(program);

    printf("Test_Package: Execute program kernel function.\n");
    complex::slc_complex_add(complex_buf_res, complex_buf_1, complex_buf_2);

    printf("Test_Package: Extract data.\n");
    std::vector<Complex> res_buf = pool_instance->Extract_Complex(complex_buf_res);

    printf("Test_Package: value: %f, %f.\n", res_buf[0].real, res_buf[0].imaginary);

    printf("Test_Package: Dispose program controller.\n");
    ProgramController::DisposeProgram(program);

    std::vector<std::string> vec;
    vec.push_back("test_package");

    slcompute_print_vector(vec);

    return 0;
}
