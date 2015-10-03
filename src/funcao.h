#ifndef FUNCAO_H_INCLUDED
#define FUNCAO_H_INCLUDED
#include "timer.h"
#include "menu.h"
#include "matriz.h"

typedef struct {
    int total;
    char *names[20];
} files;

void cleanMemory(matriz* m, timer* t, initialParams* ct);
void writeFile(matriz* m, timer* tempo, initialParams* ct);
files* listDir();
void sendToScreen(matriz* m, int k);
const char * getCorrectDir(char *dir);
int in_array(char *array[], int size, void *lookfor);

#endif // FUNCAO_H_INCLUDED
