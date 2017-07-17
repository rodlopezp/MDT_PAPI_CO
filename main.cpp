/*
 * Main entry point para uso de PAPI.
 */

#include "matrix_functions.h"
#include "papi_utils.h"

int main ()
{
    PAPI_init();
    PAPI_counterCheck();

    matrix<float> test; const unsigned int matDim = 1024 * 4;
    alloc_matrix(&test, matDim, matDim);
    randFloat_init_matrix(&test, 1.0);
    //print_matrix(&test);

    int events[1] = {PAPI_L1_DCM};
    long long values[1];

    float t0 = PAPI_getCPUTime(); //Timestamp inicial.
    PAPI_startCounters(events, 1);

    matrix_transpose_naive(&test);

    //PAPI_stop_counters();

    PAPI_readCounters(values, 1);
    float t1 = PAPI_getCPUTime();  //Timestamp final.

    dealloc_matrix(&test);

    printf("Time elapsed = %fs\n", (t1-t0));
    //printf("Total FLOPS = %lld\n",values[0]);
    printf("L1 data cache misses = %lld\n", values[0]);

    return 0;
}
