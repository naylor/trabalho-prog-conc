#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "funcao.h"
#include "main.h"

// MENU INICIAL
// AS OPCOES DE MATRIZES SAO CARREGADAS
// AUTOMAGICAMENTE DO DIRETORIO /matrizes/
initialParams* menu(char *argv[]){
    int i = 0;
    int file = NULL;

    initialParams* ct = (initialParams*)calloc(1,sizeof(initialParams));

    files* f = listDir(DIRMAT);

    printf("\tMetodo de Jacobi-Richardson\n\n");
    printf("\tFabio Alves Martins Pereira (NUSP 7987435)\n");
    printf("\tNaylor Garcia Bachiega (NUSP 5567669)\n\n");
    printf("\tPara utilizar a versao de linha de comando,\n\tuse: ./trabalho-prog-conc --help\n\n");

    if (argv[1]) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("Usar: ./trabalho-prog-conc [MATRIZ]... [ALGORITIMO]... [NUMERO THREADS]...\n\n");
            printf("[MATRIZ]: colocar apenas o nome do arquivo (ex. matriz500.txt, omitir o diretorio).\n");
            printf("[ALGORITMO]: \n");
            printf("\ts: sequencial\n");
            printf("\tp: paralelo - Pthreads\n");
            printf("\to: paralelo - OpenMP\n");
            printf("[NUMERO THREADS]: numero de threads no caso dos algoritmos paralelos. Para sequencial, nao informar.\n");
            printf("\nExemplo: ./trabalho-prog-conc matriz500.txt p 2\n\n");
            exit(0);
        }

        if (!argv[2] || ( (argv[2][0]=='p' || argv[2][0]=='o') && (!argv[3] || argv[3][0]=='0'))) {
            printf("Faltando argumentos...\n\n");
            exit(0);
        }

        // VERIFICA SE O NOME DIGITADO
        // É UM ARQUIVO VÁLIDO
        if (!in_array(f->names, f->total, argv[1])) {
            printf("Nome do arquivo da matriz esta incorreto.\nVerifique os nomes no diretorio.\n\n");
            exit(0);
        }
        ct->filePath = (char *) argv[1];
        ct->typeAlg = (char) argv[2][0];
        if (argv[2][0]!='s')
            ct->threadsNum = (int)argv[3][0];

    } else {

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
    }

    free(f);

    return ct;
}
