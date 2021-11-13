/* Trabalho 1 -CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "utils.h"

/*
*	Le opcoes passadas quando o programa eh chamado
*
*	param	argc	quantidade de argumentos
*	param	argv	argumentos passados
*	param	output	arquivo que sera utilizado para armazenar a solucao
*
*/
int le_opcoes(int argc, char *argv[], FILE *output);


/*
*	Le o arquivo passado na entrada padrao
*
*	param	input		arquivo da entrada padrao
*	param	epsilon		tolerancia epsilon (criterio de parada)
*	param	max_iter	numero maximo de iteracoes para o metodo de newton
*
*/  
SL_T *le_input(FILE *output, double *epsilon, uint *max_iter);
