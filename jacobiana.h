#ifndef __JACOBIANA_H__
#define __JACOBIANA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <matheval.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include "utils.h"

double **calcula_jacobiana(void ***jacobiana, double *incognitas, uint n);
void ***gera_matriz_jacobiana(int **expressoes, double *incognitas, uint n);

#endif