#include "matrix_tests.h"

template<typename T>
void test_if_equal(matrix<T>& matA, matrix<T>& matB){
    for(unsigned int i = 0; i < matA->rows; i++){
        for(unsigned int j = 0; i < matA->cols; j++){
            assert(matA->elements[i * matA->rows + j] == matB->elements[i * matB->rows + j]);
        }
    }
}

std::ofstream open_test_file(std::string testName){
    std::ofstream testResults;
    testResults.open("test_results.txt");

    std::chrono::time_point<std::chrono::system_clock> test_start;
    test_start = std::chrono::system_clock::now();

    std::time_t start_time = std::chrono::system_clock::to_time_t(test_start);
    testResults << "Fecha de inicio de prueba para " + testName + " :" <<  std::ctime(&start_time);

    return testResults;
}

template<typename T>
void run_matrix_algo_test(matrix_transform<T> mat_trans, matrix<T>* matIn, matrix<T>* matOut,
                          unsigned int numIter, std::vector<unsigned int>& matrix_sizes,
                          std::string testName){
    std::ofstream testResutls = open_test_file(testName);


}
