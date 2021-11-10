#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include "newtonSNL.h"
#include "utils.h"


int main(int argc, char *argv[]){
	FILE* input  				= stdin;
	FILE *output				= stdout;

	SL_T *sistema_linear		= NULL;

	double *epsilon 			= 0; 
	
	int max_iter				= 0;
	// int ret						= 0;
    int opcao					= 0;
	opterr						= 0;

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

    while ( !feof(input) ){
        sistema_linear = le_input(output, &epsilon, &max_iter);

		
    }

    return EXIT_SUCCESS;
}