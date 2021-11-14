/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define SIZE_BUFFER 1024

typedef struct SL_T {
	unsigned int n;
	int **expressoes;  // expressoes das funcoes nao lineares que compoem o sistema
	void ***derivadas;
	double *incognitas;  // aproximacao das ingonitas
	double *termos_indep;
} SL_T;


// 
void imprime_x(FILE *output, double *xi, uint n);

// 
void imprime_expressoes(FILE *output, SL_T * sl);

// 
void imprime_tempo(FILE *output, double tempo_total, double tempo_derivadas, 
double tempo_jacobiana, double tempo_sl);

// 
void destroi_sl(SL_T *sl);

// 
SL_T *aloca_sistema_linear(uint n, int **expressoes, double *incognitas);


//  Retorna tempo em milisegundos
double timestamp(void);

// 
double * obtem_variaveis(uint n, double *incognitas, char **names, int *count);

#endif