#include "entrada.h"


int le_opcoes(int argc, char *argv[], FILE *output){
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
    return 1;
}