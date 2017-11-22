#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int ID, qtProd, tempo;
} cliente;

typedef struct {
    int tam;
    int logIDs;
    int maxSize;
    int maxTime;
    int waitingTime;
}tdados;

typedef cliente telem;

typedef struct no{
    telem cli;
    struct no* prox;
} tno;

typedef struct{
    tno* startF;
    tno* endF;
    tdados dados;
} tfila;

void iniciarFila(tfila * f);
int inserirElemento(tfila * f, telem elem);
int removerElemento(tfila * f, telem * elem);
int tamanhoFila(tfila f);
void imprimirFila(tfila f);
