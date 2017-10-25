#ifndef MATRIX_TESTS_H_INCLUDED
#define MATRIX_TESTS_H_INCLUDED

#include "matrix_functions.h"
#include "papi_utils.h"

#include <vector>
#include <assert.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <numeric>

/**
 *  Prueba si dos matrices son iguales.
 **/
template<typename T>
void test_if_equal(matrix<T>& matA, matrix<T>& matB);

/**
 * Abre un archivo de texto, imprime la fecha actual a ese archivo, y devuelve un objeto
 * std::ofstream a ese archivo.
 **/
std::ofstream open_test_file(std::string testName);

/**
 *  Alias para un puntero a función, que apunta a una de las funciones de matrices.
 **/
template<typename T>
using matrix_transform = void (*) (matrix<T>*, matrix<T>*, unsigned int, unsigned int,
                                   unsigned int, unsigned int, const unsigned int);
/**
 *  Función template que ejecuta matTrans sobre matIn, y guarda el resultado en matOut. Las
 *  mediciones se guardan en testResults.
 **/
template <typename T>
void run_matrix_algo_iter(matrix_transform<T> matTrans, unsigned int iter, matrix<T>* matIn,
                          matrix<T>* matOut, std::vector<long long>& cache_misses_L1,
                          std::vector<long long>& cache_misses_L2,
                          std::vector<float>& time_spent,
                          const unsigned int minSubMatrixSize){
    float test_start, test_end, test_time;
    const int numOfEvents = 2;
    int events[numOfEvents] = {PAPI_L1_TCM, PAPI_L2_TCM};
    long long int values[numOfEvents];

    test_start = PAPI_getCPUTime();
    PAPI_startCounters(events, numOfEvents);

    matTrans(matIn, matOut, matIn->rows, matIn->cols, 0, 0, minSubMatrixSize);

    PAPI_stopCounters(values, numOfEvents);
    test_end = PAPI_getCPUTime();

    test_time = test_end - test_start;

    cache_misses_L1.push_back(values[0]);
    cache_misses_L2.push_back(values[1]);
    //cache_misses_L2.push_back(values[2]);
    time_spent.push_back(test_time);
}

template <typename T>
T get_average(std::vector<T> values){
    T avgValue = std::accumulate(values.begin(), values.end(), 0);
    avgValue = avgValue / static_cast<T>(values.size());
    return avgValue;
}

/**
 *  Ejecuta pruebas para el algoritmo matTrans un número de veces (indicado por
 *  numIter), para matrices de tamaños indicados por matrix_sizes, y guarda los resultados bajo el
 *  nombre testName en un archivo de texto.
 **/
template<typename T>
void run_matrix_algo_test(matrix_transform<T> matTrans, unsigned int numIter,
                          std::vector<unsigned int> matrixSizes, std::string testName,
                          const std::vector<unsigned int>& leafSizes){
    std::ofstream testResults = open_test_file(testName);
    matrix<T> matIn, matOut;
    std::vector<long long int> cache_misses_L1(numIter), cache_misses_L2(numIter);

    std::vector<float> time_spent(numIter);
    std::size_t avg_L1_misses, avg_L2_misses;
    float avg_time_spent;
    std::cout << "Ejecutando prueba " << testName << "...\n";

    for(auto leafSize : leafSizes){
        std::cout << "Tamaño de submatriz: " << leafSize << '\n';
        testResults << "Tamaño mínimo de submatriz: " << leafSize << "\n";
        for(auto matrixSize : matrixSizes){
            cache_misses_L1.clear();
            cache_misses_L2.clear();
            time_spent.clear();

            testResults << "Tamaño de matriz: " << matrixSize << "\n";
            alloc_matrix(&matIn, matrixSize, matrixSize);
            alloc_matrix(&matOut, matrixSize, matrixSize);
            randFloat_init_matrix(&matIn, 10.0);

            std::cout << "Ejecutando prueba para matriz " << matrixSize << 'x' << matrixSize << "...\n";

            for(unsigned int iter = 0; iter < numIter; iter++){
                run_matrix_algo_iter(matTrans,iter, &matIn, &matOut, cache_misses_L1, cache_misses_L2,
                                     time_spent, leafSize);
            }

            dealloc_matrix(&matIn);
            dealloc_matrix(&matOut);

//            avg_L1_misses = std::accumulate(cache_misses_L1.begin(), cache_misses_L1.end(), 0LL);
//            avg_L1_misses = avg_L1_misses / cache_misses_L1.size();
            avg_L1_misses = get_average(cache_misses_L1);

//            avg_L2_misses = std::accumulate(cache_misses_L2.begin(), cache_misses_L2.end(), 0LL);
//            avg_L2_misses = avg_L2_misses / cache_misses_L2.size();
            avg_L2_misses = get_average(cache_misses_L2);

//            avg_time_spent = std::accumulate(time_spent.begin(), time_spent.end(), 0.0f);
//            avg_time_spent = avg_time_spent / static_cast<float>(time_spent.size());
            avg_time_spent = get_average(time_spent);

            testResults << "Tiempo de ejecución promedio: " << avg_time_spent << "s\n";
            testResults << "Promedio de fallas de cache L1 totales: " << avg_L1_misses << "\n";
            testResults << "Promedio de fallas de cache L2 totales: " << avg_L2_misses << "\n";
        }
    }
}

#endif // MATRIX_TESTS_H_INCLUDED
