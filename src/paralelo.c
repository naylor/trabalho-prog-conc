#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "funcao.h"
#include "paralelo.h"

// THREAD
void *paraleloThread (void *argument) {
	threadParameters *threadParams = (threadParameters *) argument;

    // CARREGA OS VALORES
    // PARA A THREADS
	matriz *m = threadParams->m;

    // FUNCAO QUE CALCULO O
    // METODO DE JACOBI
    getJacobiCalc(m, threadParams->posIni, threadParams->posFim);

   return 0;

}

double* paralelo(matriz *m, initialParams* ct) {

    // ALOCA MEMORIA PARA A TTHREAD
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

    // DEFINIDO
	int numDiv = ceil((double) m->J_ORDER / ct->threadsNum);
	int posIni = 0;
	for (t = 0; t < ct->threadsNum; t++) {
		threadParams[t].posIni = posIni;
		threadParams[t].posFim = posIni + (numDiv-1);
		threadParams[t].m = m;
		posIni += numDiv;
		if (t == ((m->J_ORDER % ct->threadsNum) - 1))
            numDiv--;
	}

    // INICIANDO O LOOP
	do {

		// INICIANDO AS THREADS
		for (t = 0; t < ct->threadsNum; t++) {
			pthread_create(
					&threads[t],
					NULL,
					paraleloThread,
					(void *) &threadParams[t]);
		}

		// JOIN
		for (t = 0; t < ct->threadsNum; t++) {
			pthread_join(threads[t], NULL);
		}

        if(k%1000 == 0 ){
            printf("Mostrando execuacao: %d\n", k);
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
