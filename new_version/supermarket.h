#define CAIXAS 6
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define PROC_PROD 0.20
#define CR_LIMIT 25
#define SIMULATION_TIME 720


typedef struct no{
    int ID, qtProd, tempo;
    struct no* prox;
} tno;

typedef struct{
    tno* startF;
    tno* endF;
    int tam;
} tfila;


typedef struct{
    tfila caixa[CAIXAS];
    int IdCaixa;
    int logIDs[CAIXAS];
    int maxSize[CAIXAS];
    int maxTime[CAIXAS];
    int waitingTime[CAIXAS];
} tlista;


void startBoxs(tlista * boxs);
void imprimirFila(tlista box, int numBox);
void inserir(tlista * boxs, int * next);
int remover(tfila * caixa);
void countTime(tlista * boxs);
int aberturaCaixa(tlista boxs, int test);
void maxRowSize(tlista * boxs);
