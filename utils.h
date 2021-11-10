#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>

#define SIZE_BUFFER 1024

typedef struct SL_T {
	unsigned int n;
	int **derivadas;
	int **expressoes;
	double *incognitas;
} SL_T;


// 
void imprime_tempo(FILE *output, double tempo_total, double tempo_derivadas, 
double tempo_jacobiana, double tempo_sl);

// 
SL_T *aloca_sistema_linear(unsigned int n, int **expressoes, double *incognitas);

// 
SL_T *le_input(FILE *output, double *epsilon, unsigned int *max_iter);

//  Retorna tempo em milisegundos
double timestamp(void);

#endif