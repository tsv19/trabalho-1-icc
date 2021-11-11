
#include "jacobiana.h"

double **calcula_jacobiana(void ***jacobiana, double *incognitas, uint n){
	double **temp = (double **)malloc(n * sizeof(double *)); 

	for (int i = 0; i < n; i++)
		temp[i] = (double *)malloc(n * sizeof(double));
		
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			temp[i][j] = evaluator_evaluate_x(jacobiana[i][j], incognitas[j]);
		}
	}

	return temp;
}


void ***gera_matriz_jacobiana(int **expressoes, double *incognitas, uint n){
	char xj[10];

	void ***jacobiana = (void ***)malloc(n * sizeof(void **) + n * n * sizeof(void *));

	jacobiana[0] = (void **)(jacobiana + n) ;
 
	for (int i = 1; i < n; i++)
  		jacobiana[i] = jacobiana[0] + (i * n) ;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			sprintf(xj, "x%d", j+1);
			jacobiana[i][j] = evaluator_derivative(expressoes[i], xj);
		}
	}

	return jacobiana;
}