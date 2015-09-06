#ifndef FUNCAO_H_INCLUDED
#define FUNCAO_H_INCLUDED
#include "timer.h"
#include "menu.h"

// VAR IGUAIS AO DO EXEMPLO DO MOODLE
typedef struct {
    int J_ORDER;       // ordem da matriz
    short J_ROW_TEST;  // fila para ser avaliada
    double J_ERROR;    // erro permitido
    long J_ITE_MAX;    // n�mero m�ximo de itera��es
    double** MA;       // matriz A
    double* MB;        // matriz B
    double* inicial;   // vetor inicial
    double* anterior;  // vetor anterior
} matriz;

typedef struct {
    int total;
    char *names[20];
} matrizFiles;

void cleanMemory(matriz* m, timer* t, initialParams* ct);
int checkStop(matriz* m, int k);
matriz* loadMatriz(initialParams* ct);
void writeFile(matriz* m, timer* tempo, initialParams* ct);
matrizFiles* listDir();

#endif // FUNCAO_H_INCLUDED
