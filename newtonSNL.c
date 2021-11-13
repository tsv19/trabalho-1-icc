/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include "newtonSNL.h"



// Criterio de parada escolhido: erro relativo aproximado (ERa)
double calc_crit_stop(double x_atual, double x_prev){
    return fabs((x_atual - x_prev) / x_atual) * 100;
}


// Calcula o proximo valor
double calc_new_x(double x, double numerador, double denominador){
    return x - (numerador/denominador);
}


// // Retorna o maior valor encontrado
// double acha_max(double *vetor, int n){
// 	double maior = 0.0;
// 	for (int i=0; i<n; i++)
// 		if (maior < vetor[i])
// 			maior = vetor[i];
// 	return maior;
// }


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
void newtonMetod(SL_T *sl, double epsilon, uint max_iter){
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

		// Se ||F(X^(i))|| < epsilon devolva X^(i)
		// if ( norma(sl->expressoes, sl->incognitas, sl->n) < epsilon )
		// 	return; 
		
		// delta^(i) = resolva o sl J(X^(i)) * delta^(i) = - F(X^(i))
		calcula_jacobiana(sl->jacobiana, sl->incognitas, result_jacobiana, sl->n);
		eliminacao_gauss(result_jacobiana, sl->termos_indep, sl->n);


		// X^(i+1) = X^(i) + delta^(i)
		for (int i = 0; i < sl->n; i++){
			sl->incognitas[i] += delta[i]; 
		}
		
		// Se ||delta^(i)|| < epsilon devolva X^(i+1)
		// if ( norma(delta, sl->incognitas, sl->n) < epsilon )
			// 	return;
	}

	free(delta);
	free(result_jacobiana);
	return;
}