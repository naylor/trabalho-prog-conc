#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "menu.h"
#include "funcao.h"
#include "sequencial.h"
#include "p_omp.h"
#include "p_pthread.h"

int main (int argc, char *argv[]){
    // VERIFICAR SE O USUARIO
    // CONTINUA OU SAI DO PROGRAMA
    char op=NULL;

    do {
        // CARREGA O MENU OU SETA AS OPCOES
        // CASO INSERIDAS NA LINHA DE COMANDO
        // RETORNO: ESCOLHA DO ALGORITMO,
        // MATRIZ E QUANTIDADE DE THREADS
        initialParams* ct = menu(argv);

        // VERIFICA SE A MATRIZ
        // FOI ESCOLHIDA CORRETAMENTE
        if ((ct->typeAlg == 's' || ct->typeAlg == 'p' || ct->typeAlg == 'o')
            && (ct->filePath)) {

            // CARREGA MATRIZ ESCOLHIDA
            matriz *m = loadMatriz(ct);

            // VERIFICA SE A MATRIZ CONVERGE
            if(!checkConverge(m)) {
                printf("\n\t\tMatriz nao converge!\n");
                break;
            }

            timer* tempo; // RELOGIO

            //CARREGA O RELOGIO
            tempo = start_timer();

            switch (ct->typeAlg) {
                case 's':
                    printf("Sequencial\n");
                    sequencial(m);
                    break;
                case 'p':
                    printf("Pthreads\n");
                    p_pthread(m, ct);
                    break;
                case 'o':
                    printf("OpenMP\n");
                    p_omp(m, ct);
                    break;
            }

            // PARA O RELOGIO
            stop_timer(tempo);

            // ESCREVENDO OS RESULTADOS
            // NO ARQUIVO /resultados/
            writeFile(m, tempo, ct);

            // LIMPANDO A MEMORIA
            cleanMemory(m, tempo, ct);

        } else {
            printf("\nOpcao invalida!\n\n");
        }

        if (!argv[1]) {
            printf("\nPressione 's' para voltar ao menu ou 'n' para sair...\n");
            scanf(" %c", &op);
        } else {
            op = 'n';
        }

    } while (op != 'n');

    return 0;
}
