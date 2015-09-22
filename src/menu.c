#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "funcao.h"

// MENU INICIAL
// AS OPCOES DE MATRIZES SAO CARREGADAS
// AUTOMAGICAMENTE DO DIRETORIO /matrizes/
initialParams* menu(){
    int i = 0;
    int file = NULL;

    initialParams* ct = (initialParams*)calloc(1,sizeof(initialParams));

    matrizFiles* f = listDir();

    printf("\tMetodo de Jacobi-Richardson\n\n");
    printf("\tFabio Alves Martins Pereira (NUSP 7987435)\n");
    printf("\tNaylor Garcia Bachiega (NUSP 5567669)\n\n");

    for(i = 0; i < f->total; i++) {
        printf("\t%d - %s\n", i, f->names[i]);
    }
    printf("\n\t%d - Sair\n", i);
    printf("\n\tEscolha uma matriz: ");
    scanf(" %d", &file);

    if (file == i) //Sair
        exit(1);

    ct->filePath = f->names[file];

    printf("\n");
    printf("\ts - Serial\n");
    printf("\tp - Paralelo - Pthreads\n");
    printf("\to - Paralelo - OMP\n\n");
    printf("\tEscolha o tipo de execucao: ");
    scanf(" %c", &ct->typeAlg);
    printf("\n");
    if (ct->typeAlg == 'p' || ct->typeAlg == 'o') {
        printf("\tEscolha o numero de threads: ");
        scanf(" %d", &ct->threadsNum);
        printf("\n");
    }

    free(f);

    return ct;
}
