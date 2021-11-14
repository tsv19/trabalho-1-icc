/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include "newtonSNL.h"


/*
*	Retorna a norma do vetor, ou seja,
*	o maior valor do vetor
*
*	@param	vetor	vetor que se quer encontrar a norma
*	@param	n		tamanho do vetor
*
*	@return	maior valor do vetor
*
*/ 
double acha_norma(double *vetor, uint n){
	double maior = vetor[0];

	for (int i = 1; i < n; i++)
		if ( maior - vetor[i] < __DBL_EPSILON__ )
			maior = vetor[i];

	return maior;
}


/*
*	Calcula os valores de F(X), que sao os termos independentes
*
*	@param	termos_indep	vetor com os termos independentes
*	@param	incognitas		vetor com o valor aproximado das incognitas
*	@param	expressoes		vetor com as expressoes das funcoes
*	@param	n				tamanho do vetor
*
*/ 
void calcula_termos_indep(double *termos_indep, double *incognitas, 
int **expressoes, uint n){
	
	int count 		= 0;
	char **names 	= (char **)malloc(n * SIZE_BUFFER);

	for (int linha = 0; linha < n; linha++){
		evaluator_get_variables(expressoes[linha], &names, &count);
		double *valores 		= obtem_variaveis(n, incognitas, names, count);
		termos_indep[linha] 	= - evaluator_evaluate(expressoes[linha], count,
														 		names, valores);
		free(valores);
	}
}


/*
*	Calcula o valor aproximado das incognitas usando o metodo de Newton
*
*	@param	snl					sistema nao linear
*	@param	epsilon				tolerancia
*	@param	max_iter			numero maximo de iteracoes do Newton
*	@param	jacobiana_time		tempo gasto para a jacobiana
*	@param	sl_time				tempo gasto para resolver o sistema linear
*	@param	output				arquivo de saida
*
*/
void newtonMetod(SNL_T *snl, double epsilon, uint max_iter, double *jacobiana_time,
 double *sl_time, FILE *output){
	double jacobiana_time_aux, sl_time_aux;
	double max = 0;

	// Aloca vetor delta
	double *delta = (double *)calloc(snl->n, sizeof(double));
	if ( !delta ){
		fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
		return;
	}

	// Aloca matriz com os resultados das derivadas parciais
	double **result_jacobiana = aloca_result_jacobiana(snl->n);
	if ( !result_jacobiana ){
		fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
		free(delta);
		return;
	}

	for (int iter = 0; iter <= max_iter; iter++){
		// resolva o sl J(X^(i)) * delta^(i) = - F(X^(i))

		// Calcula os termos independentes - F(X^(i))
		calcula_termos_indep(snl->termos_indep, snl->incognitas, snl->expressoes, snl->n);

		// Se ||F(X^(i))|| < epsilon devolva X^(i)
		max = acha_norma(snl->termos_indep, snl->n);
		if ( fabs(max) < epsilon ){
			imprime_x(output, snl->incognitas, snl->n);
			free(delta);
			free(result_jacobiana);
			return;
		}

		imprime_x(output, snl->incognitas, snl->n);

		// Calculo dos valores da jacobiana J(X^(i))
		jacobiana_time_aux = timestamp();
		calcula_jacobiana(snl->derivadas, snl->incognitas, result_jacobiana, snl->n);
		*jacobiana_time += timestamp() - jacobiana_time_aux;

		// Resolver o sistema linear para encontrar o delta^(i)
		sl_time_aux = timestamp();
		eliminacao_gauss(result_jacobiana, snl->termos_indep, snl->n);
		*sl_time += timestamp() - sl_time_aux;
		retrossub(result_jacobiana, snl->termos_indep, delta, snl->n);
		
		for (int i = 0; i < snl->n; i++){
			snl->incognitas[i] += delta[i];  // X^(i+1) = X^(i) + delta^(i)
			delta[i] = fabs(delta[i]);
		}

		// Se ||delta^(i)|| < epsilon devolva X^(i+1)
		max = acha_norma(delta, snl->n);
		if ( fabs(max) < epsilon ){
			imprime_x(output, snl->incognitas, snl->n);
			free(delta);
			free(result_jacobiana);
			return;
		}
	}

	free(delta);
	free(result_jacobiana);
	return;
}
