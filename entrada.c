/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include "entrada.h"

/*
*	Le opcoes passadas quando o programa eh chamado
*
*	param	argc	quantidade de argumentos
*	param	argv	argumentos passados
*	param	output	arquivo que sera utilizado para armazenar a solucao
*
*/ 
// int le_opcoes(int argc, char *argv[]){
//     int opcao					= 0;
// 	FILE *output;
//     // usa getopt para filtrar as entradas do programa
// 	while ((opcao = getopt(argc, argv, "o:")) != -1){
// 		switch (opcao){
// 			// opcao de saida
// 			case 'o':
// 				output = fopen(optarg, "w+");
// 				if (!output){
// 					fprintf(stderr, "Erro ao abrir arquivo de saida\n");
// 					exit(1);
// 				}
// 			break;
			
// 			// caso seja digitada uma opcao diferente
// 			case '?':
// 				if ( optopt == 'o')
// 					fprintf(stderr, "Opcao -%c requer um argumento.\n", optopt);
// 				else if (isprint (optopt))
// 					fprintf(stderr, "Opcao desconhecida `-%c'.\n", optopt);
// 				else
// 					fprintf(stderr, "Caracter de opcao desconhecido`\\x%x'.\n",
// 							optopt);
// 			return 1;
			
// 			default:
// 				abort();
// 		}
// 	}
//     return 1;
// }


/*
*	Le o arquivo passado na entrada padrao
*
*	param	input		arquivo da entrada padrao
*	param	epsilon		tolerancia epsilon (criterio de parada)
*	param	max_iter	numero maximo de iteracoes para o metodo de newton
*
*/ 
SL_T *le_input(FILE *input, double *epsilon, uint *max_iter){
	int **expressoes;
	uint n;
	double *incognitas;

	// dimensao do SNL
	fscanf(input, "%u", &n);
    // fprintf(output, "%u\n", n);

	// string da expressão da função fi(x), sem espaços, na variável x.
	char fx[SIZE_BUFFER + 1];
	expressoes = (int **)malloc((n) * sizeof(void *));
	if ( expressoes == NULL ){
		fprintf(stderr, "Erro ao alocar memoria em \"le_input\"");
		abort();
	}

	for (int i = 0; i < n; i++){
		fscanf(input, "%s", fx);
		expressoes[i] = evaluator_create(fx);
		assert(expressoes[i]);
        // fprintf(output, "%s\n", fx);
	}

    // aproximacao inicial
    incognitas = (double *)malloc(n * sizeof(double));
	if ( incognitas == NULL ){
		fprintf(stderr, "Erro ao alocar memoria em \"le_input\"");
		abort();
	}

	for (int i = 0; i < n; i++){
		fscanf(input, "%lf", &incognitas[i]);
        // fprintf(stdout, "%lf\n", incognitas[i]);
	}

    fscanf(input, "%lf", epsilon);
    fscanf(input, "%u\n", max_iter);
	// sl = aloca_sistema_linear(n, expressoes, incognitas);

	return aloca_sistema_linear(n, expressoes, incognitas);
}
