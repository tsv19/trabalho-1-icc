#include "utils.h"


// le a os dados de entrada
void read_input(){
	unsigned int n, max_iter;
	int **temp;
	double *incognitas;

	// dimensao do SNL
	scanf("%u", &n);
    printf("%u\n", n);

	// string da expressão da função fi(x), sem espaços, na variável x.
	char fx[SIZE_BUFFER + 1];
	temp = (int **)malloc((n) * sizeof(void *));
	for (int i = 0; i < n; i++){
		scanf("%s", fx);
		temp[i] = evaluator_create(fx);
        printf("%s\n", fx);
	}

    // aproximacao inicial
    incognitas = malloc(n * sizeof(double));
	for (int i = 0; i < n; i++){
		scanf("%lf", &incognitas[i]);
        printf("%lf\n", incognitas[i]);
	}

    double epsilon;
    scanf("%lf", &epsilon);
    printf("%lf\n", epsilon);
    scanf("%u", &max_iter);
    printf("%u\n", max_iter);

    // linha que separa os blocos
    scanf("\n");
	printf("\n");
}


//  Retorna tempo em milisegundos
double timestamp(void){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

