#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#include "funcao.h"

int in_array(char *array[], int size, void *lookfor)
{
    int i;

    for (i = 0; i < size; i++)
        if (strcmp(lookfor, array[i]) == 0)
            return 1;
    return 0;
}

// FUNCAO QUE IMPRIME A SAIDA
// PARA A TELA, CONFORME MOODLE
void sendToScreen(matriz* m, int k) {
    int i;
	double total = 0;
	for(i = 0; i < m->J_ORDER; i++)
	    total += m->MA[m->J_ROW_TEST][i]*m->inicial[i];

    printf("\n-------------------------------------------------------");
    printf("\nIterations: %d", k);
    printf("\nRowTest: %d => [%lf] =? %lf\n", m->J_ROW_TEST, total, m->MB[m->J_ROW_TEST]);
    printf("-------------------------------------------------------\n");
}

// LIMPAR MEMORIA
void cleanMemory(matriz* m, timer* t, initialParams* ct) {
    int i;
    for(i=0;i<(m->J_ORDER);i++){
        if(m->MA[i] != NULL){
            free(m->MA[i]);
        }
    }
    if(m->MA != NULL)
        free(m->MA);
    if(m->MB != NULL)
        free(m->MB);
    if(ct != NULL)
        free(ct);
    if(t != NULL)
        free(t);
}

void writeFile(matriz* m, timer* tempo, initialParams* ct) {
	//clock time
	#ifdef __linux__ // || _unix_ || _unix
		struct timespec spec;
		clock_gettime(CLOCK_REALTIME, &spec);
		long timestamp = floor(spec.tv_sec * 1.0e8 + spec.tv_nsec / 100.0);
	# else
    	long timestamp = 0;
	#endif

    //date and time as string
	time_t rawtime;
	time(&rawtime);
	struct tm *timeinfo = localtime(&rawtime);
	char datetime[100];
	strftime((char*) &datetime, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

	//filename
	char filename[200];
	if (ct->typeAlg == 's') {
		sprintf((char*) &filename, "%s%c_%i.txt", getCorrectDir(DIRRES), ct->typeAlg, m->J_ORDER);
	} else {
		sprintf((char*) &filename, "%s%c_%d_%i.txt", getCorrectDir(DIRRES), ct->typeAlg, m->J_ORDER, ct->threadsNum);
	}

   	//write to file
	FILE* f = fopen(filename, "a");
	if (f == NULL) {
        printf("\nNao foi possivel gravar o arquivo no diretorio dos resultados: %s\n\n", filename);
		exit(0);
	}
	fprintf(f, "%i\t%i\t%s\t%li\t%.9f\t%.9f\t%i\t%.9f\t\n",
        m->J_ORDER,
		ct->threadsNum,
		datetime,
		timestamp,
		tempo->timeval_diff,
		tempo->timespec_diff,
		(int) tempo->clock_diff,
		tempo->clock_diff_time);

	fclose(f);
}

// LISTA OS ARQUIVOS DE MATRIZES
// DISPONÍVEIS NO DIRETÓRIO
files* listDir(char *dir) {
    int n, i;
    i=0;

    struct dirent **namelist;
    files* f = (files*)calloc(1,sizeof(files));

    n = scandir(getCorrectDir(dir), &namelist, 0, alphasort);
    if (n < 0)
        printf("\nNao foi possivel achar o diretorio: %s\n\n", getCorrectDir(dir));
    else {
        while(n--) {
            if ((strcmp(namelist[n]->d_name, ".")!=0)
            && (strcmp(namelist[n]->d_name, "..")!=0)) {
                f->names[i] =  namelist[n]->d_name;
                i++;
                free(namelist[n]);
            }
        }
        free(namelist);
    }

    f->total = i;
    return f;
}

// FUNCAO QUE VERIFICA SE A EXECUCAO
// E FORA OU DENTRO DO DIRETORIO SRC
// PROBLEMA NO CODE::BLOCKS
// A EXECUCAO É DIFERENTE DO TERMINAL
const char* getCorrectDir(char *dir) {

	static char dirname[200];
    if (0 != access(dir, F_OK)) {
		sprintf((char*) dirname, "../%s", dir);
    } else {
        sprintf((char*) dirname, "%s", dir);
    }

    return dirname;
}
