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
*	param	n           : armazena o tamanho do sistema linear;
*	
*	return	deriv_time	: tempo gasto para o calculo das derivadas;
*/
void calcula_jacobiana(void ***derivadas, double *incognitas, double **result, uint n){
	char **names = malloc(n * SIZE_BUFFER);
	int count = 0;
	
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			evaluator_get_variables(derivadas[i][j], &names, &count);
			double *valores = obtem_variaveis(n, incognitas, names, count);
			result[i][j] = evaluator_evaluate(derivadas[i][j], count, names, valores);
		}
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
void gera_matriz_derivadas(void ***derivadas, int **expressoes, double *incognitas, uint n){
	char xj[SIZE_BUFFER+1];

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			sprintf(xj, "x%d", j+1);
			derivadas[i][j] = evaluator_derivative(expressoes[i], xj);
		}
	}
}