#include "utils.h"


void imprime_tempo(FILE *output, double tempo_total, double tempo_derivadas, 
double tempo_jacobiana, double tempo_sl){
	fprintf(output, "###########\n");
	fprintf(output, "# Tempo Total: <tempo total do Método de Newton>\n");
	fprintf(output, "# Tempo Derivadas: <tempo gasto no cálculo das derivadas parciais>\n");
	fprintf(output, "# Tempo Jacobiana: <tempo gasto na construção das Jacobianas>\n");
	fprintf(output, "# Tempo SL: <tempo gasto na resolução dos sistemas lineares>\n");
	fprintf(output, "###########\n");
}


// 
SL_T *aloca_sistema_linear(unsigned int n, int **expressoes, double *incognitas){
	SL_T *sl = (SL_T *)malloc(sizeof(SL_T));
	sl->n = n;
	sl->expressoes	 = expressoes;
	sl->incognitas	 = incognitas;
	sl->derivadas	 = (int **)malloc((n) * sizeof(void *));
	
	return sl;
}


// le a os dados de entrada
SL_T *le_input(FILE *output, double *epsilon, unsigned int *max_iter){
	int **temp;
	unsigned int n;
	double *incognitas;

	// dimensao do SNL
	scanf("%u", &n);
    fprintf(output, "%u\n", n);

	// string da expressão da função fi(x), sem espaços, na variável x.
	char fx[SIZE_BUFFER + 1];
	temp = (int **)malloc((n) * sizeof(void *));
	for (int i = 0; i < n; i++){
		scanf("%s", fx);
		temp[i] = evaluator_create(fx);
        fprintf(output, "%s\n", fx);
	}

    // aproximacao inicial
    incognitas = malloc(n * sizeof(double));
	for (int i = 0; i < n; i++){
		scanf("%lf", &incognitas[i]);
        // fprintf(output, "%lf\n", incognitas[i]);
	}

    scanf("%lf", epsilon);
    scanf("%u", max_iter);
    // linha que separa os blocos
    scanf("\n");

    // fprintf(output, "%lf\n", epsilon);
    // fprintf(output, "%u\n", max_iter);
	// fprintf(output, "\n");

	return aloca_sistema_linear(n, temp, incognitas);
}


//  Retorna tempo em milisegundos
double timestamp(void){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

