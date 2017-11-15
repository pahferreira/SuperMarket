#include "supermarket.h"

void startBoxs(tlista * boxs){
    int i;

    for(i=0; i < CAIXAS; i++){
        boxs->caixa[i].endF = NULL;
        boxs->caixa[i].startF = NULL;
        boxs->caixa[i].tam = 0;
    }
}

void imprimirFila(tlista box, int numBox){
    int i;
    numBox--;

    while (box.caixa[numBox].startF != NULL){
        printf("%d ", box.caixa[numBox].startF->ID);
        box.caixa[numBox].startF = box.caixa[numBox].startF->prox;
    }
}

void inserir(tlista *boxs, int * next){
    int i, menorFila, tamFila = 9999;
    int newID, prods;
    tno* novo;

    /// Criando novo nó

    novo = (tno*) malloc(sizeof(tno));
    prods = (rand() % 100)+1;
    novo->qtProd = prods;
    novo->tempo = ceil(novo->qtProd * 0.28);
    novo->prox = NULL;
    /// novo->ID = (boxs->caixa[menorFila].tam) + 1;

    /// Verificando a quantidade de produtos para ir ao caixa rápido
    if (prods > 30){
        for(i=1; i < CAIXAS; i++){
            if(boxs->caixa[i].tam < tamFila) {
                tamFila = boxs->caixa[i].tam;
                menorFila = i;
            }
            if(tamFila == 0) break;
        }
    }else {
        menorFila = 0;
        tamFila = boxs->caixa[0].tam;
    }
    newID = (boxs->caixa[menorFila].endF) == NULL ? 0 : (boxs->caixa[menorFila].endF->ID);
    novo->ID =  newID + 1;
   /// Fim da criação do nó

   if(tamFila == 0)
    boxs->caixa[menorFila].startF = novo;
   else
    boxs->caixa[menorFila].endF->prox = novo;

   boxs->caixa[menorFila].endF = novo;
   boxs->caixa[menorFila].tam++;
   *next = (rand() % 4) + 1;
}

void countTime(tlista * boxs){
    int i;
    int test;

    for(i=0; i < CAIXAS; i++){
        test = 0;
        if(boxs->caixa[i].startF != NULL){
            boxs->caixa[i].startF->tempo--;
            if(boxs->caixa[i].startF->tempo == 0){
                test = remover(&boxs->caixa[i]);
                /// Esse if é para o caso de remover um elemento, ou seja, ele ser atendido
                /// sendo atendido, todos os elementos da fila irão andar 1 casa, onde o segundo passa a ser o primeiro e etc...
                /// if (test = 1)
                    /// função feita para fazer a fila andar, foi comentada e usada outra abordagem por ter ficado confuso
                    /// alterar(&boxs->caixa[i]);
            }
        }
    }
}

int remover(tfila * caixa){
    tno* aux;

    if(caixa->tam == 0) return 0;

    aux = caixa->startF;
    caixa->startF = caixa->startF->prox;
    if(caixa->startF == NULL)
        caixa->endF = NULL;

    caixa->tam--;

    free(aux);
    aux = NULL;

    return 1;
}
void alterar(tfila *caixa){
    tno *aux;
    aux = caixa->startF;
    while (aux != NULL){
        aux->ID = (aux->ID) - 1;
        aux = aux->prox;
    }
}

