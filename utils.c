/* Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Autores:
Tiago Serique Valadares (GRR20195138)
Fernanda Yukari Kawasaki (GRR20185057)
*/

#include "utils.h"

/*
*	Imprime a saida no arquivo indicado
*
*	param	output				arquivo onde a saida sera armazenada
*	param	tempo_total			tempo
*	param	tempo_derivadas		tempo gasto no calculo das derivadas parciais
*	param	tempo_jacobiana		tempo gasto para gerar a matriz jacobiana
*	param	tempo_sl			tempo gasto para resolver os sistemas lineares
*/
void imprime_tempo(FILE *output, double tempo_total, double tempo_derivadas, 
double tempo_jacobiana, double tempo_sl){
	fprintf(output, "###########\n");
	fprintf(output, "# Tempo Total: %lf\n", tempo_total);
	fprintf(output, "# Tempo Derivadas: %lf\n", tempo_derivadas);
	fprintf(output, "# Tempo Jacobiana: %lf\n", tempo_jacobiana);
	fprintf(output, "# Tempo SL: %lf\n", tempo_sl);
	fprintf(output, "###########\n\n");
}


/*
*	Libera a memoria ocupada pela struct SL_T (sistema linear)
*
*	param	sl	apontador para o sistema linear
*/
void destroi_sl(SL_T *sl){
	free(sl->expressoes);
	free(sl->incognitas);
	free(sl->termos_indep);
	free(sl->derivadas);
	free(sl);
}


/*
*	Aloca espaco na memoria para o sistema linear
*
*	param	n			dimensao do sistema
*	param	expressoes	expressoes das funcoes nao lineares
*	param	incognitas	vetor com aproximacao das incognitas
*
*/ 
SL_T *aloca_sistema_linear(uint n, int **expressoes, double *incognitas){
	SL_T *sl = (SL_T *)malloc(sizeof(SL_T));
	if ( sl == NULL ){
		fprintf(stderr, "Erro ao alocar memoria em \"aloca_sistema_linear\"");
		abort();
	}

	sl->n = n;
	sl->expressoes	 = expressoes;
	sl->incognitas	 = incognitas;
	
	sl->termos_indep	 = (double *)malloc(n * sizeof(double));
	
	if ( sl->termos_indep == NULL ){
		fprintf(stderr, "Erro ao alocar memoria em \"aloca_sistema_linear\"");
		abort();
	}

	// void ***
	sl->derivadas = (void ***)malloc(n * sizeof(void **) + n * n * sizeof(void *));
	
	if ( sl->derivadas == NULL ){
		fprintf(stderr, "Erro ao alocar memoria em \"gera_matriz_jacobiana\"");
		abort();
	}
	sl->derivadas[0] = (void **)(sl->derivadas + n);
	for (int i = 1; i < n; i++){
  		sl->derivadas[i] = sl->derivadas[0] + (i * n);
	}

	return sl;
}


double * obtem_variaveis(uint n, double *incognitas, char **names, int *count){
	double *variaveis = (double *)malloc(n * sizeof(double));
	for (int linha=0; linha<n; linha++){
		// Obtem os valores das incognitas correspondentes
		// Para x1, retorna o valor de x1 que esta no vetor de incognitas
		for (int m=0; m<*count; m++ ){
			int indice = atoi(names[m]+1)-1;
			variaveis[indice] = incognitas[indice];
		}
	}
	return variaveis;
}


void imprime_x(FILE *output, double *xi, uint n){
	fprintf(output, "#\n");
	
	for (int i = 0; i < n; i++)
		fprintf(output, "x%d = %lf\n", i+1, xi[i]);
}


void imprime_expressoes(FILE *output, SL_T * sl){
	fprintf(output, "%u\n", sl->n);
	for (int i = 0; i < sl->n; i++)
		fprintf(output, "%s = 0\n", evaluator_get_string(sl->expressoes[i]));
}


/*
*	Retorna tempo em milisegundos
*/ 
double timestamp(void){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

