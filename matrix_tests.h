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
using matrix_transform = void (*) (matrix<float>*, matrix<float>*, unsigned int, unsigned int,
                                   unsigned int, unsigned int);
/**
 *  Función que ejecuta matrix_transform sobre matIn, y guarda el resultado en matOut.
 **/
void run_matrix_algo_iter_float(matrix_transform mat_trans,
                                matrix<float>* matIn, matrix<float>* matOut);

/**
 *  Ejecuta pruebas para el algoritmo matrix_transpose_naive un número de veces (indicado por
 *  numIter), para matrices de tamaños indicados por matrix_sizes, y guarda los resultados bajo el
 *  nombre testName en un archivo de texto.
 **/
//template<typename T>
void run_matrix_algo_test_naive_float(unsigned int numIter, std::vector<unsigned int> matrix_sizes,
                                std::string testName);
#endif // MATRIX_TESTS_H_INCLUDED
