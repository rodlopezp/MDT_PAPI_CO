#ifndef PAPI_UTILS_H_INCLUDED
#define PAPI_UTILS_H_INCLUDED

#include "papi.h"
#include <cstdio>
#include <cstdlib>
#include <cerrno>

/**
 * Retorna el tiempo de CPU en segundos, mediante la función PAPI_get_virt_usec.
 **/
float PAPI_getCPUTime();

/**
 * Realiza una cuenta de los contadores de desempeño disponibles en el procesador, mediante la
 * función PAPI_num_counters(). Imprime errores a stderr.
 **/
void PAPI_counterCheck();

/**
 *  Inicia la cuenta de eventos, indicados por los valores de events. Imprime errores a stderr.
 *  Utiliza la función PAPI_start_countes, de la API de alto nivel.
 **/
void PAPI_startCounters(int* events, unsigned int numEvents);

/**
 *  Lee valores de los contadores, y los almacena en el array de long long indicado por valuesRead.
 *  Imprime errorres a stderr. Utiliza la función PAPI_read_counters de la API de alto nivel.
 **/
void PAPI_readCounters(long long int* valuesRead, unsigned int numEvents);

/**
 *  Inicializa la API de bajo nivel de PAPI.
 **/
void PAPI_init();

/**
 *  Detiene los contadores y copia la cuenta actual a valuesRead. Utiliza la función
 *  PAPI_stop_counters de la API de alto nivel.
 **/
void PAPI_stopCounters(long long int* valuesRead, unsigned int numEvents);

#endif // PAPI_UTILS_H_INCLUDED
