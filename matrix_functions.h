#ifndef MATRIX_FUNCTIONS_H_INCLUDED
#define MATRIX_FUNCTIONS_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * Estructura base para una matriz de enteros.
 * La matriz se debe guardar en "row-major order".
 **/
template <typename T>
struct matrix{
    unsigned int rows;
    unsigned int cols;
    T* elements;
};

/**
 * Una implementación naive de transposición de matrices, in-place, para matrices cuadradas.
 **/
template <typename T>
void matrix_transpose_naive(matrix<T>* matrix){
    T tmp;
    for(unsigned int i = 0; i < matrix->rows; i++){
        for(unsigned int j = i; j < matrix->cols; j++){
            tmp = matrix->elements[i * matrix->rows + j];
            matrix->elements[i * matrix->rows + j] = matrix->elements[j * matrix->cols + i];
            matrix->elements[j * matrix->cols + i] = tmp;
        }
    }
}

/**
 * Imprime una matriz en la salida estándar. Esta función utiliza std::cout.
 **/
template <typename T>
void print_matrix(matrix<T>* matrix){
    for(unsigned int i = 0; i < matrix->rows; i++){
        for(unsigned int j = 0; j < matrix->cols; j++){
            std::cout << matrix->elements[i * matrix->rows + j];
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

/**
 *  Reserva espacio para un objeto int_matrix, mediante malloc.
 **/
template <typename T>
void alloc_matrix(matrix<T>* matrix, unsigned int rows, unsigned int cols){
    matrix->elements = (T*) malloc(sizeof(int) * rows * cols);
    matrix->rows = rows;
    matrix->cols = cols;
}

/**
 *  Libera memoria asociada a los elementos de la matriz, mediante free.
 **/
template <typename T>
void dealloc_matrix(matrix<T>* matrix){
    free(matrix->elements);
}

/**
 *  Inicializa la matriz con valores enteros aleatorios entre cero y upper_limit (excluyendo este
 *  último).
 **/
template <typename T>
void randInt_init_matrix(matrix<T>* matrix, unsigned int upper_limit){
    srand(time(NULL));
    for(unsigned int i = 0; i < matrix->rows * matrix->cols; i++){
        matrix->elements[i] = rand() % upper_limit;
    }
}

/**
 *  Inicializa la matriz con valores flotantes aleatorios entre cero y upper_limit (excluyendo este
 *  último).
 **/
template <typename T>
void randFloat_init_matrix(matrix<T>* matrix, float upper_limit){
    srand(time(NULL));
    for(unsigned int i = 0; i < matrix->rows * matrix->cols; i++){
        matrix->elements[i] = static_cast<float>(rand())/static_cast<float>(RAND_MAX / upper_limit);
    }
}

#endif // MATRIX_FUNCTIONS_H_INCLUDED
