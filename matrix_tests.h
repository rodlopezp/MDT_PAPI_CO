#ifndef MATRIX_TESTS_H_INCLUDED
#define MATRIX_TESTS_H_INCLUDED

#include "matrix_functions.h"
#include "papi_utils.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>

/**
 *  Prueba si dos matrices son iguales.
 **/
template<typename T>
void test_if_equal(matrix<T>& matA, matrix<T>& matB);

/**
 * Abre un archivo de texto, imprime la fecha actual a ese archivo, y devuelve un std::ofstream& a
 * ese archivo.
 **/
std::ofstream open_test_file(std::string testName);

/**
 *  Ejecuta la función mat_trans, para matIn y matOut, un número de veces (indicado por numIter),
 *  para los tamaños indicados por matrix_sizes. Los resultados de la prueba deben guardarse en un
 *  archivo de texto para su posterior procesamiento. El archivo de texto llevará la
 *  fecha en que se realizó la prueba en la primera línea, y qué algoritmo se probó.
 **/
template<typename T>
using matrix_transform = void (*) (matrix<T>*, matrix<T>*, unsigned int, unsigned int, unsigned int,
                                   unsigned int);

template<typename T>
void run_matrix_algo_test(matrix_transform<T> mat_trans, matrix<T>* matIn, matrix<T>* matOut,
                          unsigned int numIter, std::vector<unsigned int>& matrix_sizes,
                          std::string test_name);

#endif // MATRIX_TESTS_H_INCLUDED
