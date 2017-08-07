/*
 * Main entry point para uso de PAPI.
 */

#include <algorithm>

#include "matrix_functions.h"
#include "papi_utils.h"
#include "matrix_tests.h"


enum DEBUG_MODE {
    NODEBUG =   0,
    PRINT   =   1,
    ASSERT  =   2,
};

DEBUG_MODE DEBUG = ASSERT;

int main ()
{
    PAPI_init();
    PAPI_counterCheck();

    unsigned int half_initial_size = 8;
    std::vector<unsigned int> matrix_sizes(5);
    std::string test_name = "test_co";
    std::generate(matrix_sizes.begin(), matrix_sizes.end(),
                  [&]{return half_initial_size *= 2;});

    run_matrix_algo_test(matrix_transpose_naive<float>, 100, matrix_sizes, "test_naive");
    run_matrix_algo_test(matrix_transpose_co<float>, 100, matrix_sizes, test_name);

    return 0;
}
