#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "funcao.h"
#include "p_omp.h"

// THREAD
double* p_omp(matriz *m, initialParams* ct) {

	int t, k = 0;

    // ALOCA MEMORIA PARA A THREAD
	threadParameters *threadParams = malloc(m->J_ORDER * sizeof(threadParameters));

    // VETOR INICIAL
    getPosInitial(m);

    // NAO DEIXAR ESCOLHER MAIS
    // THREADS DO QUE ORDEM DA MATRIZ
	if (ct->threadsNum > m->J_ORDER) {
		ct->threadsNum = m->J_ORDER;
	}

    // FUNCAO QUE FAZ A DIVISAO DA MATRIZ
    // PARA SER CALCULADA POR PARTES
    // RETORNA A DIVISAO EM threadParams
	getDivision(m, ct, threadParams);

    // INICIANDO O LOOP
	do {

		// INICIANDO AS THREADS
		#pragma omp parallel for schedule(static, ct->threadsNum) num_threads(ct->threadsNum)
        for (t = 0; t < ct->threadsNum; t++) {
            getJacobiCalc(threadParams[t].m, threadParams[t].posIni, threadParams[t].posFim);
        }

        // BARREIRA PARA ESPERAR TODAS
		// AS THREADS
		#pragma omp barrier
        if(k%1000 == 0 ){
            printf("Mostrando execucao: %d\n", k);
        }
	    k++;

    // CHECANDO AS CONDICOES DE PARADA
	} while(checkStop(m, k));

	//IMPRIME MENSAGEM
	sendToScreen(m, k);

    // LIBERANDO MEMORIA
	free(threadParams);

	return 0;
}
