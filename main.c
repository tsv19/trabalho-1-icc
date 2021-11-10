#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include "newtonSNL.h"
#include "utils.h"


int main(int argc, char *argv[]){
    FILE *arquivo_saida = stdout;
    FILE *arquivo = stdin;

    while ( !feof(arquivo) ){
        read_input();
    }


    return EXIT_SUCCESS;
}