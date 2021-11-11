#include "utils.h"


void imprime_tempo(FILE *output, double tempo_total, double tempo_derivadas, 
double tempo_jacobiana, double tempo_sl){
	fprintf(output, "###########\n");
	fprintf(output, "# Tempo Total: <tempo total do Método de Newton> %lf\n", tempo_total);
	fprintf(output, "# Tempo Derivadas: <tempo gasto no cálculo das derivadas parciais> %lf\n", tempo_derivadas);
	fprintf(output, "# Tempo Jacobiana: <tempo gasto na construção das Jacobianas> %lf\n", tempo_jacobiana);
	fprintf(output, "# Tempo SL: <tempo gasto na resolução dos sistemas lineares> %lf\n", tempo_sl);
	fprintf(output, "###########\n");
}


// 
SL_T *aloca_sistema_linear(unsigned int n, int **expressoes, double *incognitas){
	SL_T *sl = (SL_T *)malloc(sizeof(SL_T));
	sl->n = n;
	sl->expressoes	 = expressoes;
	sl->incognitas	 = incognitas;
	sl->termos_indep	 = malloc(n * sizeof(double));
	return sl;
}


// le a os dados de entrada
SL_T *le_input(FILE *input, double *epsilon, unsigned int *max_iter){
	int **temp;
	unsigned int n;
	double *incognitas;


	// dimensao do SNL
	fscanf(input, "%u", &n);
    // fprintf(output, "%u\n", n);

	// string da expressão da função fi(x), sem espaços, na variável x.
	char fx[SIZE_BUFFER + 1];
	temp = (int **)malloc((n) * sizeof(void *));
	
	for (int i = 0; i < n; i++){
		fscanf(input, "%s", fx);
		temp[i] = evaluator_create(fx);
        // fprintf(output, "%s\n", fx);
	}

    // aproximacao inicial
    incognitas = malloc(n * sizeof(double));
	for (int i = 0; i < n; i++){
		fscanf(input, "%lf", &incognitas[i]);
        // fprintf(output, "%lf\n", incognitas[i]);
	}

    fscanf(input, "%lf", epsilon);
    fscanf(input, "%u\n", max_iter);
	return aloca_sistema_linear(n, temp, incognitas);
}


// so para desenvolver - apagar depois
void imprime_sistena_linear(SL_T *sl){
	printf("n = %d\n", sl->n);

	// printf("derivadas:\n");
	// for (int i=0; i<; i++)
	// 	for (int j=0; j<; j++)
	// 		printf("derivadas[%d][%d] = %d", i, j, sl->derivadas[i][j]);
	// printf("\n");

	// printf("expressoes:");

	// printf("incognitas:\n");
	// for (int i=0; i<sl->n; i++)
	// 	printf("expressoes[%d] = %d\n", i, *(sl->expressoes[i]));
	// printf("\n");
}


//  Retorna tempo em milisegundos
double timestamp(void){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

