#include "papi_utils.h"

float PAPI_getCPUTime(){
    return ((float)PAPI_get_virt_usec() / 1000000.0);
}

void PAPI_init(){
    int retval = PAPI_library_init(PAPI_VER_CURRENT);

    if (retval != PAPI_VER_CURRENT && retval > 0) {
	  fprintf(stderr,"PAPI library version mismatch!\n");
	  exit(1);
	}

	if (retval < 0) {
	  fprintf(stderr, "Initialization error! Code: %d\n", retval);
	  exit(1);
	}

    fprintf(stdout, "PAPI Version Number\n");
    fprintf(stdout, "MAJOR:    %d\n", PAPI_VERSION_MAJOR(retval));
    fprintf(stdout, "MINOR:    %d\n", PAPI_VERSION_MINOR(retval));
    fprintf(stdout, "REVISION: %d\n", PAPI_VERSION_REVISION(retval));
    fprintf(stdout, "INCREMENT: %d\n", PAPI_VERSION_INCREMENT(retval));

}

void PAPI_counterCheck(){
    if (PAPI_num_counters() < 2){
        fprintf(stderr, "No hardware counters here, or PAPI not supported.\n");
        exit(1);
    }
    else{
        printf("Available performance counters: %d\n", PAPI_num_counters());
    }
}

void PAPI_startCounters(int* events, unsigned int numEvents){
    int retVal;
    if ((retVal = PAPI_start_counters(events, numEvents)) != PAPI_OK){
        fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(retVal));
        exit(1);
    }
}

void PAPI_readCounters(long long int* valuesRead, unsigned int numEvents){
    int retVal;
    if ((retVal = PAPI_read_counters(valuesRead, numEvents)) != PAPI_OK){
        fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(retVal));
        exit(1);
    }
}

void PAPI_stopCounters(long long int* valuesRead, unsigned int numEvents){
    int retVal;
    if ((retVal = PAPI_stop_counters(valuesRead, numEvents)) != PAPI_OK){
        fprintf(stderr, "PAPI failed to stop counters: %s\n", PAPI_strerror(retVal));
        exit(1);
    }
}
