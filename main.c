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

	double epsilon 			= 0; 
	unsigned int max_iter				= 0;

	le_opcoes(argc, argv, output);

    while (!feof(input)){
        sistema_linear = le_input(input, &epsilon, &max_iter);
		sistema_linear->jacobiana = gera_matriz_jacobiana(sistema_linear->expressoes, sistema_linear->incognitas, sistema_linear->n);
		newtonMetod(sistema_linear, epsilon, max_iter);
		eliminacao_gauss(sistema_linear->jacobiana, sistema_linear->termos_indep, sistema_linear->n);
		// retrossub(sistema_linear->jacobiana, sistema_linear->termos_indep, sistema_linear->n);
    }

	fclose(input);
	fclose(output);
    return EXIT_SUCCESS;
}