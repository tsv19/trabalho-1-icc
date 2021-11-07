#include "newtonSNL.h"


// le a os dados de entrada
void read_input(){
	unsigned int n, max_iter;
	int **temp, *incognitas;

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
    incognitas = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++){
		scanf("%u", &incognitas[i]);
        printf("%u\n", incognitas[i]);
	}

    double epsilon;
    scanf("%lf", &epsilon);
    printf("%lf\n", epsilon);
    scanf("%u", &max_iter);
    printf("%u\n", max_iter);

    // linha que separa os blocos
    scanf("\n");
}
