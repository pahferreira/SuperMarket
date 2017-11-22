#include "supermarket.h"


void startBoxs(tlista * boxs){
    int i;

    for(i=0; i < CAIXAS; i++){
        boxs->caixa[i].endF = NULL;
        boxs->caixa[i].startF = NULL;
        boxs->caixa[i].tam = 0;
        boxs->logIDs[i] = 0;
        boxs->maxSize[i] = 0;
        boxs->maxTime[i] = 0;
        boxs->waitingTime[i] = 0;
    }
}

void imprimirFila(tlista box, int numBox){
    numBox--;

    while (box.caixa[numBox].startF != NULL){
        printf("%d ", box.caixa[numBox].startF->ID);
        box.caixa[numBox].startF = box.caixa[numBox].startF->prox;
    }
}

void inserir(tlista *boxs, int * next){
    int i, menorFila = 0, tamFila = 9999;
    int prods, boxTest = 2;
    tno* novo;

    boxTest = aberturaCaixa(*boxs, boxTest);

    /// Criando novo nó

    novo = (tno*) malloc(sizeof(tno));
    prods = (rand() % 100)+1;
    novo->qtProd = prods;
    novo->tempo = ceil(novo->qtProd * PROC_PROD);
    novo->prox = NULL;


    /// Verificando a quantidade de produtos para ir ao caixa rápido
    if (prods > CR_LIMIT){
        for(i=1; i < CAIXAS-boxTest; i++){
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

    novo->ID =  ++boxs->logIDs[menorFila];

    if(boxs->waitingTime[menorFila] > boxs->maxTime[menorFila])
        boxs->maxTime[menorFila] = boxs->waitingTime[menorFila];
    boxs->waitingTime[menorFila] += novo->tempo;
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

    for(i=0; i < CAIXAS; i++){

        if(boxs->caixa[i].startF != NULL){
            boxs->caixa[i].startF->tempo--;
            boxs->waitingTime[i]--;
            if(boxs->caixa[i].startF->tempo == 0){
                remover(&boxs->caixa[i]);
            }
        }

    }

    maxRowSize(boxs);
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


void maxRowSize(tlista * boxs){
    int i;

    for(i = 0; i < CAIXAS; i++){
        if(boxs->caixa[i].tam > boxs->maxSize[i])
            boxs->maxSize[i] = boxs->caixa[i].tam;
    }
}

int aberturaCaixa(tlista boxs, int test){
    int i, tamTotal = 0;


    for(i = 1; i < CAIXAS - test; i++){
        tamTotal += boxs.caixa[i].tam;
    }

    if(tamTotal < 9){
        return 2;
    } else if(tamTotal < 12){
        return 1;
    } else{
        return 0;
    }
}
