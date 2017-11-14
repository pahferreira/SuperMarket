#define CAIXAS 6
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


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
} tlista;


void startBoxs(tlista * boxs);
void imprimirFila(tlista box, int numBox);
void inserir(tlista * boxs, int * next);
int remover(tfila * caixa);
void countTime(tlista * boxs);
void alterar(tfila * caixa);
