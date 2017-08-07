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


