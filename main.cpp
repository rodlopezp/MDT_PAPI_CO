/*
 * Main entry point para uso de PAPI.
 */

#include "matrix_functions.h"
#include "papi_utils.h"
#include "matrix_tests.h"

enum DEBUG_MODE{
    NODEBUG =   0,
    PRINT   =   1,
    ASSERT  =   2,
};

DEBUG_MODE DEBUG = ASSERT;

int main ()
{
    PAPI_init();
    PAPI_counterCheck();

    matrix<float> test, outTest, outTest2;
    const unsigned int matDim = 1024;

    alloc_matrix(&test, matDim, matDim);
    alloc_matrix(&outTest, matDim, matDim);
    alloc_matrix(&outTest2, matDim, matDim);

    randFloat_init_matrix(&test, 1.0);

    if (DEBUG == PRINT) { print_matrix(&test); }

    int events[2] = {PAPI_L1_TCM, PAPI_L2_TCM};
    long long values[2];

    float t0 = PAPI_getCPUTime(); //Timestamp inicial.
    PAPI_startCounters(events, 1);

    matrix_transpose_naive(&test, &outTest, test.rows, test.cols, 0, 0);

    PAPI_readCounters(values, 1);
    float t1 = PAPI_getCPUTime();  //Timestamp final.

    printf("Time elapsed = %fs\n", (t1-t0));
    printf("L1 total cache misses = %lld\n", values[0]);
    printf("L2 total cache misses = %lld\n", values[1]);

    if (DEBUG == PRINT) { print_matrix(&outTest); }

    PAPI_stopCounters(values, 1);

    t0 = PAPI_getCPUTime();
    PAPI_startCounters(events, 1);

    matrix_transpose_co(&outTest, &outTest2, test.rows, test.cols, 0, 0);

    PAPI_readCounters(values, 1);
    t1 = PAPI_getCPUTime();  //Timestamp final.

    printf("Time elapsed = %fs\n", (t1-t0));
    printf("L1 total cache misses = %lld\n", values[0]);
    printf("L2 total cache misses = %lld\n", values[1]);

    if (DEBUG == PRINT) { print_matrix(&test); }

    dealloc_matrix(&test);

    return 0;
}
