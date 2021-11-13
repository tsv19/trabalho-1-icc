/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include "jacobiana.h"


/*
*	Faz o calculo da jacobiana para cada funcao derivada da matriz
*
*	param	jacobiana	: armazena a matriz com as F'(X);
*	param	incognitas	: armazena os valores de X atuais;
*	param	result     	: armazena o resultado do calculo da jacobiana;
*	param	n           : armazena o tamanho do sistema linear ;
*/
void calcula_jacobiana(void ***jacobiana, double *incognitas, double **result, uint n){
	char **names = malloc(n * SIZE_BUFFER);
	int count;
	
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			evaluator_get_variables(jacobiana[i][j], &names, &count);
			result[i][j] = evaluator_evaluate(jacobiana[i][j], count, names, incognitas);
			printf("f'(x): %s === result: %lf == incog: %lf\n", evaluator_get_string(jacobiana[i][j]), result[i][j], incognitas[j]);
			result[i][j] = evaluator_evaluate_x(jacobiana[i][j], incognitas[j]);
		}
		printf("\n");
	}
		printf("\n");

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%lf ", result[i][j]);
			// assert(result[i][j]);
		}
		printf("\n");
	}
}


/*
*	Gera a matriz jacobiana com todos os F'(X)
*
*	param	jacobiana	: armazena a matriz com as F'(X);
*	param	expressoes  : armazena todas das F(X) recebidas do input;
*	param	incognitas  : armazena o resultado do calculo da jacobiana;
*	param	n           : armazena o tamanho do sistema linear ;
*/
void gera_matriz_jacobiana(void ***jacobiana, int **expressoes, double *incognitas, uint n){
	char xj[SIZE_BUFFER+1];

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			sprintf(xj, "x%d", j+1);
			jacobiana[i][j] = evaluator_derivative(expressoes[i], xj);
			// printf(" f'(%s) = %s\n", xj, evaluator_get_string(jacobiana[i][j]));
		}
	}
}