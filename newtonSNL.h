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


// Criterio de parada escolhido: erro relativo aproximado (ERa)
double calc_crit_stop(double x_atual, double x_anterior);

// Criterio de parada escolhido: erro relativo aproximado (ERa)
double calc_new_x(double x, double numerador, double denominador);

// calcula o metodo de newton 
void newtonMetod(SL_T *sl, double epsilon, uint max_iter);

#endif