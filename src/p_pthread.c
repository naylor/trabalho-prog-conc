#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "funcao.h"
#include "p_pthread.h"

// THREAD
void *callThread (void *argument) {
	threadParameters *threadParams = (threadParameters *) argument;

    // CARREGA OS VALORES
    // PARA A THREADS
	matriz *m = threadParams->m;

    // FUNCAO QUE CALCULO O
    // METODO DE JACOBI
    getJacobiCalc(m, threadParams->posIni, threadParams->posFim);

   return 0;

}

double* p_pthread(matriz *m, initialParams* ct) {

    // ALOCA MEMORIA PARA A THREAD
	pthread_t *threads = malloc(m->J_ORDER * sizeof(pthread_t));
	threadParameters *threadParams = malloc(m->J_ORDER * sizeof(threadParameters));

	int t, k = 0;

    // VETOR INICIAL
    getPosInitial(m);

    // NAO DEIXAR ESCOLHER MAIS
    // THREADS DO QUE ORDEM DA MATRIZ
	if (ct->threadsNum > m->J_ORDER) {
		ct->threadsNum = m->J_ORDER;
	}

    // FUNCAO QUE FAZ A DIVISAO DA MATRIZ
    // PARA SER CALCULADA POR PARTES
	getDivision(m, ct, threadParams);

    // INICIANDO O LOOP
	do {

		// INICIANDO AS THREADS
		for (t = 0; t < ct->threadsNum; t++) {
			pthread_create(
					&threads[t],
					NULL,
					callThread,
					(void *) &threadParams[t]);
		}

		// JOIN
		for (t = 0; t < ct->threadsNum; t++) {
			pthread_join(threads[t], NULL);
		}

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
