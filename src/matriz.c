#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matriz.h"
#include "main.h"

// FAZ A DIVISAO DA MATRIZ
// PARA SER CALCULADA POR PARTES
void getDivision(matriz* m, initialParams* ct, threadParameters* threadParams) {

    int t = 0;
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
}

// VERIFCA SE A MATRIZ CONVERGE
int checkConverge(matriz *m){
    int i, j;
    double sum, aux, max = 0;

    for(i = 0; i < m->J_ORDER ; i++) {
        sum = 0;
        if(m->MA[i][i] == 0)
            return 0;
        for(j = 0; j < m->J_ORDER; j++) {
            if(i != j) {
                aux = m->MA[i][j]/m->MA[i][i];
                if(aux < 0)
                    aux = -1*aux;
                sum = sum + aux;
            }
        }
        if(sum > max)
            max = sum;
    }

    if(max >= 1)
        return 0;
    else
        return 1;
}

// REALIZA O METODO DE JACOBI
// DIVIDINDO A MATRIZ EM COLUNAS
// DE ACORDO COM A QUANTIDADE DE THREADS
void getJacobiCalc(matriz* m, int posIni, int posFim) {
	double total;
	int i, j;

    // REGISTRANDO O RESULTADO DA INTERACAO ANTERIOR
	for (i = posIni; i <= posFim; i++) {
        m->anterior[i] = m->inicial[i];
    }

    // CALCULA O VALOR DE CADA X1, X2 E X3
	for (i = posIni; i <= posFim; i++) {
        total = 0;
        for(j = 0; j <= m->J_ORDER; j++) {
            if(i != j) { // ELEMENTO DA DIAGONAL
                total += (m->MA[i][j] * m->anterior[j]) / m->MA[i][i];
            }
        }
        // DEFININDO O VALOR DE X1, X2 E X3
        m->inicial[i] = (m->MB[i] / m->MA[i][i] - total);
    }
}

// RETORNA A POSICAO INICIAL DO VETOR
// PREENCHENDO O VI COM O RESULTADO DA DIVISAO DE MB/MA
// OBTEVE A MELHORA EM 1 INTERAÇÃO, DO QUE INICIANDO
// O VETOR INICIAL POR ZERO
void getPosInitial(matriz* m) {
    int i;
    for (i = 0; i < m->J_ORDER; i++) {
		m->inicial[i] = m->MB[i]/m->MA[i][i];
    }
}

// ESSA FUNCAO CALCULO A CONDICAO DE PARADA
int checkStop(matriz* m, int k) {
	double mx, mxAnt, total;
	int i;

    // CALCULO O CRITERIO DE PARADA MAX
    // X - XANT
    mxAnt = 0;
    mx = 0;

    for(i = 0; i < m->J_ORDER; i++) {
        total = m->inicial[i] - m->anterior[i];
        if(total < 0)
            total = (-1)*total;
        if(total > mxAnt)
            mxAnt = total;

        total = m->inicial[i];
        if(total < 0)
            total = (-1)*total;
        if(total > mx)
            mx = total;
    }

    // PARE SE O ERRO FOI ATINGIDO
    if (mx != 0 && ((mxAnt/mx) > m->J_ERROR)) {
        return 1;
    }

    // PARA SE O NUMERO MAXIMO DE
    // INTERACOES FOI ATINGIDO
    if (k > m->J_ITE_MAX) {
        return 1;
    }

    return 0;
}

// ESSA FUNCAO CARREGA O ARQUIVO ESCOLHIDO
// ALOCA AS MEMORIAS E CARREGA OS VALORES
// ENTRADA: ESCOLHA DO USUARIO, TIPO DE ALGORITMO,
// MATRIZ E NUMERO DE THREADS
// RETORNO: MATRIZEZ E PARÂMETROS PREENCHIDOS
matriz* loadMatriz(initialParams* ct) {
	int i, j;

    // ALOCANDO MEMORIA PARA M
    matriz* m = (matriz*)calloc(1,sizeof(matriz));

    // ABRINDO O ARQUIVO
    FILE *file;
    char path[512];
    snprintf(path, sizeof(path), "%s%s", getCorrectDir(DIRMAT), ct->filePath);
	file = fopen(path, "r");

    // CARREGANDO VALORES (VER TAREFA MOODLE)
    fscanf(file,"%d",&m->J_ORDER);
    fscanf(file,"%hd",&m->J_ROW_TEST);
    fscanf(file,"%lf",&m->J_ERROR);
    fscanf(file,"%ld",&m->J_ITE_MAX);

    // ALOCANDO MEMÓRIA PARA A MA
    m->MA = (double **) malloc(m->J_ORDER*sizeof(double*));
    for(i = 0; i < m->J_ORDER; i++)
        m->MA[i] = (double *) malloc(m->J_ORDER*sizeof(double));

    // ALOCANDO MEMÓRIA PARA A MB
    m->MB = (double *) malloc(m->J_ORDER*sizeof(double));

    // ALOCANDO MEMÓRIA PARA O VETOR
    m->anterior = (double *) malloc(m->J_ORDER*sizeof(double));
    m->inicial = (double *) malloc(m->J_ORDER*sizeof(double));

    // POPULANDO A MATRIZ MA
    for(i = 0; i < m->J_ORDER; i++) {
        for(j = 0; j < m->J_ORDER; j++) {
            fscanf(file, "%lf", &m->MA[i][j]);
        }
    }

    // POPULANDO A MATRIZ MB
    for(i = 0; i < m->J_ORDER; i++) {
        fscanf(file, "%lf", &m->MB[i]);
    }

    // FECHANDO ARQUIVO
    fclose(file);

    // RETORNANO A MATRIZ COM
    // VALORES DE ENTRADA
    return m;
}
