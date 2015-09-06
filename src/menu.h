#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

typedef struct {
    char* filePath;
    char typeAlg;
    int threadsNum;
} initialParams;

initialParams* menu();


#endif // INTERFACES_H_INCLUDED
