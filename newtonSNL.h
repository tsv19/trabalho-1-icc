/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#ifndef __NEWTON_H__
#define __NEWTON_H__

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "jacobiana.h"
#include "gauss.h"
#include "utils.h"


/*
*	Calcula o valor aproximado das incognitas usando o metodo de Newton
*
*	@param	snl					sistema nao linear
*	@param	epsilon				tolerancia
*	@param	max_iter			numero maximo de iteracoes do Newton
*	@param	jacobiana_time		tempo gasto para a jacobiana
*	@param	sl_time				tempo gasto para resolver o sistema linear
*	@param	output				arquivo de saida
*
*/
void newtonMetod(SNL_T *sl, double epsilon, uint max_iter, double *jacobiana_time, double *sl_time, FILE *output);

#endif