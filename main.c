/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz


Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include "entrada.h"
#include "newtonSNL.h"
#include "jacobiana.h"
#include "gauss.h"
#include "utils.h"


int main(int argc, char *argv[]){
	FILE* input  				= stdin;
	FILE *output				= stdout;
	SL_T *sistema_linear		= NULL;

	double epsilon 				= 0; 
	unsigned int max_iter		= 0;

	le_opcoes(argc, argv, output);


    while (!feof(input)){
        sistema_linear = le_input(input, &epsilon, &max_iter);

		gera_matriz_jacobiana(sistema_linear->jacobiana, sistema_linear->expressoes, sistema_linear->incognitas, sistema_linear->n);
		

		// TESTA CALCULA_JACOBIANA, ELIMINACAO DE GAUSS E RETROSSUB (TEMPORARIO, DEVE IR DENTRO DE NEWTON)
		// double *delta = (double *)malloc(sistema_linear->n * sizeof(double));
		// if ( delta == NULL ){
		// 	fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
		// 	return EXIT_FAILURE;
		// }

		double **result_jacobiana = (double **)malloc(sistema_linear->n * sizeof(double *) + sistema_linear->n * sizeof(double));
		if ( result_jacobiana == NULL ){
			fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
			return EXIT_FAILURE;
		}
		// result_jacobiana[0] = (double *)(result_jacobiana + sistema_linear->n) ;
		// for (int i = 1; i < sistema_linear->n; i++){
		// 	result_jacobiana[i] = result_jacobiana[0] + (i * sistema_linear->n) ;
		// }

		// calcula_jacobiana(sistema_linear->jacobiana, sistema_linear->incognitas, result_jacobiana, sistema_linear->n);
		// eliminacao_gauss(result_jacobiana, sistema_linear->termos_indep, sistema_linear->n);
		// retrossub(result_jacobiana, sistema_linear->termos_indep, delta, sistema_linear->n);

		double *delta = (double *)malloc(sistema_linear->n * sizeof(double));
		newtonMetod(sistema_linear, delta, result_jacobiana, epsilon, max_iter);  // Resolve cada ENL

		imprime_resultados(sistema_linear, delta, result_jacobiana);

		// break;
		printf("\n");
    }

	fclose(input);
	fclose(output);
    return EXIT_SUCCESS;
}