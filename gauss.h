#ifndef __GAUSS_H__
#define __GAUSS_H__

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include "utils.h"

uint encontra_maximo(double **matriz_coef, uint i, uint n);
void troca_linha(double **matriz_coef, double *vet_termos, int i, uint pivo,
 uint n);
void eliminacao_gauss(double **matriz_coef, double *vet_termos, uint n);



#endif