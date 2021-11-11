#include "newtonSNL.h"


// Criterio de parada escolhido: erro relativo aproximado (ERa)
double calc_crit_stop(double x_atual, double x_prev){
    return fabs((x_atual - x_prev) / x_atual) * 100;
}


// Calcula o proximo valor
double calc_new_x(double x, double numerador, double denominador){
    return x - (numerador/denominador);
}


// Retorna o maior valor encontrado
double acha_max(double *vetor, int n){
	double maior = 0.0;
	for (int i=0; i<n; i++)
		if (maior < vetor[i])
			maior = vetor[i];
	return maior;
}


// calcula metodo de newton
void newtonMetod(SL_T *sl, double epsilon, uint max_iter){
	double f_value, f_deriv_value;
	void *f_deriv = malloc(sizeof(int));

	for (int i=0; i<max_iter; i++){
		for (int j=0; j<sl->n; j++){
			// Newton
			// Calcula funcao de iteracao do metodo de Newton-Raphson
			f_value = evaluator_evaluate_x(sl->expressoes[j], sl->incognitas[j]);
			f_deriv = evaluator_derivative_x(sl->expressoes[j]);
			f_deriv_value = evaluator_evaluate_x(f_deriv, sl->incognitas[j]);

			double new_x = sl->incognitas[j] - (f_value - f_deriv_value);

			// Atualiza valor
			sl->incognitas[j] = new_x;
		}

		// Confere se ja esta proximo o suficiente
		if (fabs(acha_max(sl->incognitas, sl->n)) < epsilon)
			return;
	}
	return;
}