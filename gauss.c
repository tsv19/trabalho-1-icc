/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/


#include "gauss.h"


/*
*	Encontra o valor maximo da coluna especificada para usar de pivo
*
*	param	matriz_coef		matriz em que se deseja achar o pivo
*	param	coluna			coluna em q se deseja achar o pivo
*	param	n				dimensao do sistema linear
*/
uint encontra_maximo(double **matriz_coef, uint coluna, uint n){
	uint maximo = i;
	
	for (int j = i + 1; j < n; j++){
		if ( matriz_coef[maximo][i] < matriz_coef[j][i] )
			maximo = j;
	}

	return maximo;
}


/*
*	Troca as linhas da matriz de coeficientes e do vetor de termos independentes
*
*	param	matriz_coef		matriz com as linhas que serao trocadas
*	param 	vet_termos 		vetor que tera as linhas trocadas
*	param 	linha			linha que deseja-se "descer"
*	param 	pivo			linha que deseja-se "subir"
* 	param 	n				dimensao do sistema linear
*/
void troca_linha(double **matriz_coef, double *vet_termos, int linha, uint pivo,
 uint n){
	
	double temp = 0.0;

	for (int j = 0; j < n; j++){
		temp 					= matriz_coef[linha][j];
		matriz_coef[linha][j] 	= matriz_coef[pivo][j];
		matriz_coef[pivo][j] 	= temp;
	}

	temp = vet_termos[linha];
	vet_termos[linha] = vet_termos[pivo];
	vet_termos[pivo] = temp;
}


/*
*	Realiza o metodo de eleminacao de gauss para resolver sistemas lineares
*
*	param	matriz_coef		matriz com coeficientes do sistema linear que se 
*							deseja resolver
*	param	vet_termos		vetor com os termos independentes do sistema linear
*	param	n				dimensao do sistema linear
*/
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


/*
*	Realiza a retrossubstituicao das incognitas,
*	ou seja, substitui os valores das incognitas
*	nas equacoes e utiliza os resultados obtidos
*	para calcular as proximas equacoes.
*
*	param	sl	struct do sistema linear
*
*/ 
void retrossub(SL_T *sl){
	double soma;
	double f_value, f_deriv_value;
	printf("%d\n", sl->n);
	for (int i = (sl->n) - 1; i >= 0; i--){
		soma = 0;
		for (int j = i + 1; j < sl->n; j++){ // nao inclui a diagonal
			printf("%d, %d = %lf\n", i, j, sl->jacobiana[i][j]);
			// f_deriv_value = evaluator_evaluate_x(sl->jacobiana[i][j], sl->incognitas[i]);
		// 	soma += f_deriv_value * sl->incognitas[i];
		}
		// f_value = evaluator_evaluate_x(sl->expressoes[i], sl->incognitas[i]);  // termo indep
		// double coef = evaluator_evaluate_x(sl->jacobiana[i][i], sl->incognitas[i]);
		// sl->incognitas[i] = (f_value - soma) / coef;
		// printf("x%d = %lf\n", i, sl->incognitas[i]);
	}

}