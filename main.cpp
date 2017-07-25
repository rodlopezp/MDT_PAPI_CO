/*
 * Main entry point para uso de PAPI.
 */

#include "matrix_functions.h"
#include "papi_utils.h"

const int DEBUG = 0;

int main ()
{
    PAPI_init();
    PAPI_counterCheck();

    matrix<int> test, outTest, outTest2;
    const unsigned int matDim = 1024;
    alloc_matrix(&test, matDim, matDim); alloc_matrix(&outTest, matDim, matDim);
    alloc_matrix(&outTest2, matDim, matDim);
    randInt_init_matrix(&test, 10);

    if (DEBUG == 1) { print_matrix(&test); }

    int events[1] = {PAPI_L1_DCM};
    long long values[1];

    float t0 = PAPI_getCPUTime(); //Timestamp inicial.
    PAPI_startCounters(events, 1);

    matrix_transpose_naive(&test, &outTest, test.rows, test.cols, 0, 0);

    PAPI_readCounters(values, 1);
    float t1 = PAPI_getCPUTime();  //Timestamp final.

    printf("Time elapsed = %fs\n", (t1-t0));
    printf("L1 data cache misses = %lld\n", values[0]);

    if (DEBUG == 1) { print_matrix(&outTest); }

    //TODO: Refactorizar en función.
    if (int retVal = PAPI_stop_counters(values, 1) != PAPI_OK){
        fprintf(stderr, "PAPI failed to stop counters: %s\n", PAPI_strerror(retVal));
        exit(1);
    }

    t0 = PAPI_getCPUTime();
    PAPI_startCounters(events, 1);

    matrix_transpose_co(&outTest, &outTest2, test.rows, test.cols, 0, 0);

    PAPI_readCounters(values, 1);
    t1 = PAPI_getCPUTime();  //Timestamp final.

    printf("Time elapsed = %fs\n", (t1-t0));
    printf("L1 data cache misses = %lld\n", values[0]);

    if (DEBUG == 1) { print_matrix(&test); }

    dealloc_matrix(&test);

    return 0;
}
