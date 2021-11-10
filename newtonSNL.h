#ifndef __NEWTON_H__
#define __NEWTON_H__

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>


// Criterio de parada escolhido: erro relativo aproximado (ERa)
double calc_crit_stop(double x_atual, double x_anterior);

// Criterio de parada escolhido: erro relativo aproximado (ERa)
double calc_new_x(double x, double numerador, double denominador);

// calcula o metodo de newton 
void newtonMetod(void *f, void* f_deriv, double epsilon, double *newton_x, 
double *newton_x_prev, double *newton_crit, int *newton_stop);

#endif