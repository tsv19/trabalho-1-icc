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
	fprintf(output, "# Tempo Total: <tempo total do Método de Newton> %lf\n", tempo_total);
	fprintf(output, "# Tempo Derivadas: <tempo gasto no cálculo das derivadas parciais> %lf\n", tempo_derivadas);
	fprintf(output, "# Tempo Jacobiana: <tempo gasto na construção das Jacobianas> %lf\n", tempo_jacobiana);
	fprintf(output, "# Tempo SL: <tempo gasto na resolução dos sistemas lineares> %lf\n", tempo_sl);
	fprintf(output, "###########\n");
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
	free(sl->jacobiana);
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
	sl->jacobiana = (void ***)malloc(n * sizeof(void **) + n * n * sizeof(void *));
	
	if ( sl->jacobiana == NULL ){
		fprintf(stderr, "Erro ao alocar memoria em \"gera_matriz_jacobiana\"");
		abort();
	}
	sl->jacobiana[0] = (void **)(sl->jacobiana + n) ;
	for (int i = 1; i < n; i++){
  		sl->jacobiana[i] = sl->jacobiana[0] + (i * n) ;
	}

	return sl;
}



/*
*	Retorna tempo em milisegundos
*/ 
double timestamp(void){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

