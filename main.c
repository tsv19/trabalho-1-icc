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

	// le_opcoes(argc, argv, arquivo);
	
	int opcao					= 0;

    // usa getopt para filtrar as entradas do programa
	while ((opcao = getopt(argc, argv, "o:")) != -1){
		switch (opcao){
			// opcao de saida
			case 'o':
				output = fopen(optarg, "w+");
				if (!output){
					fprintf(stderr, "Erro ao abrir arquivo de saida\n");
					exit(1);
				}
			break;
			
			// caso seja digitada uma opcao diferente
			case '?':
				if ( optopt == 'o')
					fprintf(stderr, "Opcao -%c requer um argumento.\n", optopt);
				else if (isprint (optopt))
					fprintf(stderr, "Opcao desconhecida `-%c'.\n", optopt);
				else
					fprintf(stderr, "Caracter de opcao desconhecido`\\x%x'.\n",
							optopt);
			return 1;
			
			default:
				abort();
		}
	}

    while (!feof(input)){
		double newton_time = 0, deriv_time = 0, jacobiana_time = 0, sl_time = 0;
        sistema_linear = le_input(input, &epsilon, &max_iter);

		deriv_time = timestamp();
		gera_matriz_derivadas(sistema_linear->derivadas, sistema_linear->expressoes, sistema_linear->incognitas, sistema_linear->n);
		deriv_time = timestamp() - deriv_time;

		imprime_expressoes(output, sistema_linear);

		newton_time = timestamp();
		newtonMetod(sistema_linear, epsilon, max_iter, &jacobiana_time, &sl_time, output);  // Resolve cada ENL
		newton_time = timestamp() - newton_time;
		
		imprime_tempo(output, newton_time, deriv_time, jacobiana_time, sl_time);

		destroi_sl(sistema_linear);
    }

	fclose(input);
	fclose(output);
    return EXIT_SUCCESS;
}