/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include "newtonSNL.h"

// Retorna a maior norma
double acha_max(double *vetor, uint n){
	double maior = vetor[0];
	for (int i=1; i<n; i++)
		if (maior < vetor[i])
			maior = vetor[i];
	return maior;
}


// Calcula as normas
void calcula_normas(double *normas, double *incognitas, int **funcoes, uint n){
	int count = 0;
	char **names = malloc(n * SIZE_BUFFER);

	for (int linha=0; linha<n; linha++){
		evaluator_get_variables(funcoes[linha], &names, &count);
		double *incognitas_aux = obtem_variaveis(n, incognitas, names, &count);
		normas[linha] = evaluator_evaluate(funcoes[linha], count, names, incognitas_aux);
	}
}


void calcula_termos_indep(double *termos_indep, double *incognitas, int **expressoes, uint n){
	int count = 0;
	char **names = malloc(n * SIZE_BUFFER);

	for (int linha=0; linha<n; linha++){
		evaluator_get_variables(expressoes[linha], &names, &count);
		double *incognitas_aux = obtem_variaveis(n, incognitas, names, &count);
		termos_indep[linha] = - evaluator_evaluate(expressoes[linha], count, names, incognitas_aux);
	}
}


// calcula metodo de newton
void newtonMetod(SL_T *sl, double epsilon, uint max_iter, double *jacobiana_time,
 double *sl_time, FILE *output){
	double max;
	double *delta = (double *)malloc(sl->n * sizeof(double));
	if ( delta == NULL ){
		fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
		return;
	}
	
	double **result_jacobiana = (double **)malloc(sl->n * sizeof(double *) + sl->n * sizeof(double));
	if ( result_jacobiana == NULL ){
		fprintf(stderr, "Erro ao alocar memoria em \"newtonMetod\"");
		return;
	}
	result_jacobiana[0] = (double *)(result_jacobiana + sl->n) ;
	for (int i = 1; i < sl->n; i++)
  		result_jacobiana[i] = result_jacobiana[0] + (i * sl->n) ;


	for (int i = 0; i < max_iter; i++){
		// Verifica criterio de parada
		double *normas = malloc(sizeof(double) * sl->n);
		calcula_normas(normas, sl->incognitas, sl->expressoes, sl->n);
		max = acha_max(normas, sl->n);
		if (max < epsilon){
			imprime_x(output, sl->incognitas, sl->n);
			return;  // Se ||F(X^(i))|| < epsilon devolva X^(i)
		}

		imprime_x(output, sl->incognitas, sl->n);

		// delta^(i) = resolva o sl J(X^(i)) * delta^(i) = - F(X^(i))
		calcula_termos_indep(sl->termos_indep, sl->incognitas, sl->expressoes, sl->n);

		printf("antes\n");
		for (int k=0; k<sl->n; k++){
			for (int l=0; l<sl->n; l++)
				printf("%lf ", result_jacobiana[k][l]);
			printf("\n");
		}
		printf("\n");


		double jacobiana_time_aux = timestamp();
		calcula_jacobiana(sl->derivadas, sl->incognitas, result_jacobiana, sl->n);
		*jacobiana_time += timestamp() - jacobiana_time_aux;

		// Resolver o sistema linear para encontrar o delta
		double sl_time_aux = timestamp();
		eliminacao_gauss(result_jacobiana, sl->termos_indep, sl->n);
		*sl_time += timestamp() - sl_time_aux;

		printf("depois\n");
		for (int k=0; k<sl->n; k++){
			for (int l=0; l<sl->n; l++)
				printf("%lf ", result_jacobiana[k][l]);
			printf("\n");
		}
		printf("\n");


		retrossub(result_jacobiana, sl->termos_indep, delta, sl->n);

		// X^(i+1) = X^(i) + delta^(i)
		for (int i = 0; i < sl->n; i++)
			sl->incognitas[i] += delta[i]; 

		// Se ||delta^(i)|| < epsilon devolva X^(i+1)
		max = acha_max(delta, sl->n);
		// printf("max: %lf\n", max);
		// if (max < epsilon){
		// 	imprime_x(output, sl->incognitas, sl->n);
		// 	return;  // Se ||delta(X^(i))|| < epsilon devolva X^(i)
		// }
	}
	return;
}
