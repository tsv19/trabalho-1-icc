
#include "gauss.h"


uint encontra_maximo(double **matriz_coef, uint i, uint n){
	uint maximo = i;
	
	for (int j = i + 1; j < n; j++){
		if ( matriz_coef[maximo][i] < matriz_coef[j][i] )
			maximo = j;
	}

	return maximo;
}


void troca_linha(double **matriz_coef, double *vet_termos, int i, uint pivo,
 uint n){
	
	double temp = 0.0;

	for (int j = 0; j < n; j++){
		temp 					= matriz_coef[i][j];
		matriz_coef[i][j] 		= matriz_coef[pivo][j];
		matriz_coef[pivo][j] 	= temp;
	}

	temp = vet_termos[i];
	vet_termos[i] = vet_termos[pivo];
	vet_termos[pivo] = temp;
}


void eliminacao_gauss(double **matriz_coef, double *vet_termos, uint n){
	for (int i = 0; i < n; i++){
		uint pivo = encontra_maximo(matriz_coef, i, n);
		
		if ( i != pivo )
			troca_linha(matriz_coef, vet_termos, i, pivo, n);

		for (int k = i + 1; k < n; k++){
			double m = matriz_coef[k][i] / matriz_coef[i][i];
			
			matriz_coef[k][i] = 0.0;
			
			for (int j = i + 1; j < n; ++j)
				matriz_coef[k][j] -= matriz_coef[i][j] * m;
			
			vet_termos[k] -= vet_termos[i] * m;
		}

	}	
}