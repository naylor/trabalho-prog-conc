#ifndef PARALELO_H_INCLUDED
#define PARALELO_H_INCLUDED

// STRUCT UTILIZADA NA COMUNICACAO DE THREADS
typedef struct {
	matriz *m;
	int posIni; // REGISTRA O INICIO DA ORDEM
	int posFim;     // REGISTRO O FIM DA ORDEM
} threadParameters;

void *paraleloThread (void *argument);
double* paralelo(matriz *m, initialParams* ct);

#endif // PARALELO_H_INCLUDED
