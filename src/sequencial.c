#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"
#include "sequencial.h"

// FUNCAO DO ALGORITMO SEQUENCIAL DE JACOBI
// ENTRADA: MATRIZ
// RETORNO: RESULTADO
double* sequencial(matriz* m) {


	// REGISTRAR A QUANTIDADE DE INTERACOES
	int k = 0;

    // VETOR INICIAL
    getPosInitial(m);

    // INICIANDO O LOOP
    do {

        // FUNCAO QUE CALCULO O
        // METODO DE JACOBI
        getJacobiCalc(m, 0, m->J_ORDER-1);

        if(k%1000 == 0 ){
            printf("Mostrando execuacao: %d\n", k);
        }
	    k++;

    // CHECANDO AS CONDICOES DE PARADA
	} while(checkStop(m, k));

	//IMPRIME MENSAGEM
	sendToScreen(m, k);

	return 0;
}
