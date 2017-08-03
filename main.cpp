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

    unsigned int initial_size = 8;
    std::vector<unsigned int> matrix_sizes(5);
    std::string test_name = "test_naive";
    std::generate(matrix_sizes.begin(), matrix_sizes.end(),
                  [&]{return initial_size *= 2;});
    run_matrix_algo_test_naive_float(100, matrix_sizes, test_name);

    return 0;
}
