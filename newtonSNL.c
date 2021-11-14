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
*	param	vetor	vetor que 
*
*/ 
double acha_max(double *vetor, uint n){
	double maior = vetor[0];

	for (int i = 1; i < n; i++)
		if ( maior - vetor[i] < __DBL_EPSILON__ )
			maior = vetor[i];
	
	return maior;
}


// Calcula as normas
void calcula_normas(double *normas, double *incognitas, int **funcoes, uint n){
	int count 		= 0;
	char **names 	= (char **)malloc(n * SIZE_BUFFER);

	for (int linha = 0; linha < n; linha++){
		evaluator_get_variables(funcoes[linha], &names, &count);
		double *valores 		= obtem_variaveis(n, incognitas, names, count);
		normas[linha] 			= fabs(evaluator_evaluate(funcoes[linha], count, 
														names, valores));
		free(valores);
	}
}


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


// calcula metodo de newton
void newtonMetod(SL_T *sl, double epsilon, uint max_iter, double *jacobiana_time,
 double *sl_time, FILE *output){
	
	double max = 0;
	

	double *delta = (double *)calloc(sl->n, sizeof(double));
	if ( !delta ){
		fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
		return;
	}
	

	double **result_jacobiana = (double **)malloc(sl->n * sizeof(double *) + 
												sl->n * sl->n * sizeof(double));
	if ( !result_jacobiana ){
		fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
		free(delta);
		return;
	}
	
	// ajustando ponteiros para a jacobiana
	result_jacobiana[0] = (double *)(result_jacobiana + sl->n) ;
	for (int i = 1; i < sl->n; i++)
  		result_jacobiana[i] = result_jacobiana[0] + (i * sl->n) ;
	
	// incializando jacobiana
	for (int i = 0; i < sl->n; i++)
		for (int j = 0; j < sl->n; j++)
			result_jacobiana[i][j] = 0;

	double *normas = (double *)malloc(sizeof(double) * sl->n);
	if (!normas){
		fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
		free(delta);
		free(result_jacobiana);
		return;
	}

	for (int iter = 0; iter <= max_iter; iter++){
		// Verifica criterio de parada

		// Se ||F(X^(i))|| < epsilon devolva X^(i)
		calcula_normas(normas, sl->incognitas, sl->expressoes, sl->n);
		max = acha_max(normas, sl->n);
		if ( fabs(max) < epsilon ){
			imprime_x(output, sl->incognitas, sl->n);

			free(delta);
			free(normas);
			free(result_jacobiana);
			return;
		}


		imprime_x(output, sl->incognitas, sl->n);


		// delta^(i) = resolva o sl J(X^(i)) * delta^(i) = - F(X^(i))
		calcula_termos_indep(sl->termos_indep, sl->incognitas, sl->expressoes, sl->n);

		double jacobiana_time_aux = timestamp();
		calcula_jacobiana(sl->derivadas, sl->incognitas, result_jacobiana, sl->n);
		*jacobiana_time += timestamp() - jacobiana_time_aux;

		// Resolver o sistema linear para encontrar o delta
		double sl_time_aux = timestamp();
		eliminacao_gauss(result_jacobiana, sl->termos_indep, sl->n);
		*sl_time += timestamp() - sl_time_aux;
		retrossub(result_jacobiana, sl->termos_indep, delta, sl->n);
		
		
		// X^(i+1) = X^(i) + delta^(i)
		for (int i = 0; i < sl->n; i++)
			sl->incognitas[i] += delta[i]; 


		// Se ||delta^(i)|| < epsilon devolva X^(i+1)
		for (int i = 0; i < sl->n; i++)
			delta[i] = fabs(delta[i]);

		max = acha_max(delta, sl->n);
		if ( fabs(max) < epsilon ){
			imprime_x(output, sl->incognitas, sl->n);
			
			free(delta);
			free(normas);
			free(result_jacobiana);
			return;
		}
	}

	free(delta);
	free(normas);
	free(result_jacobiana);
	return;
}
