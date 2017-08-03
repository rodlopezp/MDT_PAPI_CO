#include "matrix_tests.h"

template<typename T>
void test_if_equal(matrix<T>& matA, matrix<T>& matB) {
    for(unsigned int i = 0; i < matA->rows; i++) {
        for(unsigned int j = 0; i < matA->cols; j++) {
            assert(matA->elements[i * matA->rows + j] == matB->elements[i * matB->rows + j]);
        }
    }
}

std::ofstream open_test_file(std::string testName) {
    std::ofstream testResults;

    auto test_start = std::chrono::system_clock::now();
    auto start_time = std::chrono::system_clock::to_time_t(test_start);
    std::stringstream timeString;
    timeString << std::put_time(std::localtime(&start_time), "%c %Z");

    std::string fileName = "test_results_" + testName + "_";
    fileName += timeString.str();
    fileName += ".txt";
    testResults.open(fileName);

    return testResults;
}

void run_matrix_algo_iter_float(matrix_transform mat_trans,
                                matrix<float>* matIn, matrix<float>* matOut){;}

void run_matrix_algo_test_naive_float(unsigned int numIter, std::vector<unsigned int> matrix_sizes,
                                std::string testName) {
    std::ofstream testResutls = open_test_file(testName);

    std::vector<long long int> cache_misses_L1, cache_misses_L2;
    std::vector<float> time_spent;
    float test_start, test_end, test_time;
    const int numOfEvents = 2;
    int events[numOfEvents] = {PAPI_L1_TCM, PAPI_L2_TCM};
    long long int values[numOfEvents];
    matrix<float> matIn, matOut;

    for(auto matrixSize : matrix_sizes){
        testResutls << "Tamaño de matriz: " << matrixSize << "\n";
        alloc_matrix(&matIn, matrixSize, matrixSize);
        alloc_matrix(&matOut, matrixSize, matrixSize);
        randFloat_init_matrix(&matIn, 10.0);

        for(unsigned int iter = 0; iter < numIter; iter++){

            test_start = PAPI_getCPUTime();
            PAPI_startCounters(events, numOfEvents);
            matrix_transpose_naive(&matIn, &matOut, matIn.rows, matIn.cols, 0, 0);
            PAPI_readCounters(values, numOfEvents);
            test_end = PAPI_getCPUTime();
            test_time = test_end - test_start;

            PAPI_stopCounters(values, numOfEvents);

            testResutls << "Iteración " << iter << " :\n";
            testResutls << "Tiempo transcurrido: " << (test_time) << "\n";
            testResutls << "L1 total cache misses = " << values[0] << "\n";
            testResutls << "L2 total cache misses = " << values[1] << "\n";

            cache_misses_L1.push_back(values[0]);
            cache_misses_L2.push_back(values[1]);
            time_spent.push_back(test_time);
        }

        dealloc_matrix(&matIn);
        dealloc_matrix(&matOut);
    }
}
