#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED
#include "menu.h"

// VAR IGUAIS AO DO EXEMPLO DO MOODLE
typedef struct {
    int J_ORDER;       // ordem da matriz
    short J_ROW_TEST;  // fila para ser avaliada
    double J_ERROR;    // erro permitido
    long J_ITE_MAX;    // número máximo de iterações
    double** MA;       // matriz A
    double* MB;        // matriz B
    double* inicial;   // vetor inicial
    double* anterior;  // vetor anterior
} matriz;

// STRUCT UTILIZADA NA COMUNICACAO DE THREADS
typedef struct {
	matriz *m;
	int posIni; // REGISTRA O INICIO DA ORDEM
	int posFim;     // REGISTRO O FIM DA ORDEM
} threadParameters;

matriz* loadMatriz(initialParams* ct);
int checkStop(matriz* m, int k);
void getPosInitial(matriz* m);
void getJacobiCalc(matriz* m, int posIni, int posFim);
void getDivision(matriz* m, initialParams* ct, threadParameters* threadParams);
const char * getCorrectDir(char *dir);
int checkConverge(matriz *m);

#endif // MATRIZ_H_INCLUDED
