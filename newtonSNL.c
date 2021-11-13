/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include "newtonSNL.h"

// Retorna a maior norma
double acha_max(double *normas, uint n){
	double maior = 0.0;
	for (int i=0; i<n; i++)
		if (maior < normas[i])
			maior = normas[i];
	return maior;
}


// Calcula as normas
void calcula_normas(double *normas, double *incognitas, int **funcoes, int n){
	char **names = malloc(n * SIZE_BUFFER);
	int count;
	for (int linha=0; linha<n; linha++){
		evaluator_get_variables(funcoes[linha], &names, &count);
		normas[linha] = evaluator_evaluate(funcoes[linha], count, names, incognitas);
	}
}


void calcula_termos_indep(double *termos_indep, double *incognitas, int **expressoes, uint n){
	char **names = malloc(n * SIZE_BUFFER);
	int count;
	for (int linha=0; linha<n; linha++){
		evaluator_get_variables(expressoes[linha], &names, &count);
		termos_indep[linha] = - evaluator_evaluate(expressoes[linha], count, names, incognitas);
	}
}


// F'(X) * delta = - F(X)
double calcula_newton(int *funcao, uint n, uint max_iter, double epsilon){
	double f_value, f_deriv_value, delta, aproximacao, nova_aproximacao;
	aproximacao = 0;
	void *f_deriv = evaluator_derivative_x(funcao);

	for (int i=0; i<max_iter; i++){
		f_value = evaluator_evaluate_x(funcao, aproximacao);
		f_deriv_value = evaluator_evaluate_x(f_deriv, aproximacao);

		nova_aproximacao = aproximacao - (f_value - f_deriv_value);

		// Confere se ja esta proximo o suficiente
		delta = fabs(nova_aproximacao - aproximacao);
		if (delta < epsilon)
			return delta;

		aproximacao = nova_aproximacao;
	}
	delta = fabs(nova_aproximacao - aproximacao);
	return delta;
}


// calcula metodo de newton
void newtonMetod(SL_T *sl, double *delta, double **result_jacobiana, double epsilon, uint max_iter){
	result_jacobiana[0] = (double *)(result_jacobiana + sl->n) ;
	for (int i = 1; i < sl->n; i++)
  		result_jacobiana[i] = result_jacobiana[0] + (i * sl->n) ;


	for (int i = 0; i < max_iter; i++){
		// Verifica criterio de parada
		double *normas = malloc(sizeof(double) * sl->n);
		calcula_normas(normas, sl->incognitas, sl->expressoes, sl->n);
		double max = acha_max(normas, sl->n);
		if (max < epsilon)
			return;  // Se ||F(X^(i))|| < epsilon devolva X^(i)


		// delta^(i) = resolva o sl J(X^(i)) * delta^(i) = - F(X^(i))
		calcula_termos_indep(sl->termos_indep, sl->incognitas, sl->expressoes, sl->n);
		calcula_jacobiana(sl->jacobiana, sl->incognitas, result_jacobiana, sl->n);

		// for (int i = 0; i < sl->n; i++){
		// 	for (int j = 0; j < sl->n; j++)
		// 		printf("jac %lf ", result_jacobiana[i][j]);
		// 	printf("\n");
		// }

		// Resolver o sistema linear para encontrar o delta
		eliminacao_gauss(result_jacobiana, sl->termos_indep, sl->n);
		retrossub(result_jacobiana, sl->termos_indep, delta, sl->n);

		// for (int i = 0; i < sl->n; i++){
		// 	for (int j = 0; j < sl->n; j++)
		// 		printf("jac_gauss %lf ", result_jacobiana[i][j]);
		// 	printf("\n");
		// }


		// X^(i+1) = X^(i) + delta^(i)
		for (int i = 0; i < sl->n; i++)
			sl->incognitas[i] += delta[i]; 
		
		// Se ||delta^(i)|| < epsilon devolva X^(i+1)
		// if (norma(delta, sl->incognitas, sl->n) < epsilon )
		// 	return;


		// for (int i = 0; i < sl->n; i++)
		// 	printf("delta(x%d) = %lf \n", i, delta[i]);
		// printf("\n");
	}

	return;
}


	// // Imprime Result
	// for (int i=0; i<n; i++){
	// 	for (int j=0; j<n; j++)
	// 		printf("%d, %d = %lf\n", i, j, matriz_coef[i][j]);
	// 	printf("\n");
	// }