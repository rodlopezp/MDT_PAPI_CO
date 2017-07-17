#include "matrix_functions.h"

//template <typename T>
//void matrix_transpose_naive(matrix<T>* matrix){
//    int tmp;
//    for(unsigned int i = 0; i < matrix->rows; i++){
//        for(unsigned int j = i; j < matrix->cols; j++){
//            tmp = matrix->elements[i * matrix->rows + j];
//            matrix->elements[i * matrix->rows + j] = matrix->elements[j * matrix->cols + i];
//            matrix->elements[j * matrix->cols + i] = tmp;
//        }
//    }
//}

//template <typename T>
//void print_matrix(matrix<T>* matrix){
//    for(unsigned int i = 0; i < matrix->rows; i++){
//        for(unsigned int j = 0; j < matrix->cols; j++){
//            printf("%d ", matrix->elements[i * matrix->rows + j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}

//template <typename T>
//void alloc_matrix(matrix<T>* matrix, unsigned int rows, unsigned int cols){
//    matrix->elements = (int*) malloc(sizeof(int) * rows * cols);
//    matrix->rows = rows;
//    matrix->cols = cols;
//}

//template <typename T>
//void dealloc_matrix(matrix<T>* matrix){
//    free(matrix->elements);
//}

//template <typename T>
//void randInt_init_matrix(matrix<T>* matrix, unsigned int upper_limit){
//    srand(time(NULL));
//    for(unsigned int i = 0; i < matrix->rows * matrix->cols; i++){
//        matrix->elements[i] = rand() % upper_limit;
//    }
//}
