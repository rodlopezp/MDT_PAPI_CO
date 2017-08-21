/*
 * Main entry point para uso de PAPI.
 */

#include "matrix_functions.h"
#include "papi_utils.h"
#include "matrix_tests.h"

#include <algorithm>



int main ()
{
    PAPI_init();
    PAPI_counterCheck();

    matrix<float> matOut, matA, matB;
    const int matSize = 1024;
    alloc_matrix(&matOut, matSize, matSize);
    alloc_matrix(&matA, matSize, matSize);
    alloc_matrix(&matB, matSize, matSize);

    randFloat_init_matrix(&matA, 10.0);
    randFloat_init_matrix(&matB, 10.0);

    float timeStart = PAPI_getCPUTime();
    matrix_multiply_naive(&matOut, &matA, &matB);
    float timeEnd = PAPI_getCPUTime();

    std::cout << "Tiempo de ejecución: " << (timeEnd - timeStart) << "s\n";

//    unsigned int half_initial_size = 8;
//    std::vector<unsigned int> matrix_sizes(10);
//    std::generate(matrix_sizes.begin(), matrix_sizes.end(),
//                  [&]{return half_initial_size *= 2;});
//
//    run_matrix_algo_test(matrix_transpose_naive<float>, 256, matrix_sizes, "naive");
//    run_matrix_algo_test(matrix_transpose_co<float>, 256, matrix_sizes, "co");

    return 0;
}
