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

    unsigned int half_initial_size = 8;
    std::vector<unsigned int> matrix_sizes(8);
    std::generate(matrix_sizes.begin(), matrix_sizes.end(),
                  [&]{return half_initial_size *= 2;});

    run_matrix_algo_test(matrix_transpose_naive<float>, 100, matrix_sizes, "naive");
    run_matrix_algo_test(matrix_transpose_co<float>, 100, matrix_sizes, "co");

    return 0;
}
