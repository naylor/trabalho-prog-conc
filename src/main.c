#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "menu.h"
#include "funcao.h"

int main (){

    // VERIFICAR SE O USUARIO
    // CONTINUA OU SAI DO PROGRAMA
    char op=NULL;

    do {
        // CARREGA O MENU
        // RETORNO: ESCOLHA DO ALGORITMO,
        // MATRIZ E QUANTIDADE DE THREADS
        initialParams* ct = menu();

        // VERIFICA SE A MATRIZ
        // FOI ESCOLHIDA CORRETAMENTE
        if ((ct->typeAlg == 's' || ct->typeAlg == 'p')
            && (ct->filePath)) {

            // CARREGA MATRIZ ESCOLHIDA
            matriz *m = loadMatriz(ct);

            timer* tempo; // RELOGIO

            //CARREGA O RELOGIO
            tempo = start_timer();

            switch (ct->typeAlg) {
                case 's':
                    sequencial(m);
                    break;
                case 'p':
                    paralelo(m, ct);
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
            printf("\nOpcao invalida!\n");
        }
        printf("\nPressione 's' para voltar ao menu ou 'n' para sair...\n");
        scanf(" %c", &op);
    } while (op != 'n');

    return 0;
}
