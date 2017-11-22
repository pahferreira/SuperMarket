#include "TadFila.h"

void iniciarFila(tfila * f){

    f->endF = NULL;
    f->startF = NULL;
    f->dados.tam = 0;

}

int inserirElemento(tfila * f, telem elem){
    tno* novo;

    novo = (tno*)malloc(sizeof(tno));
    if(novo == NULL) return 0;

    novo->cli = elem;
    novo->prox = NULL;

    if(f->dados.tam == 0)
        f->startF = novo;
    else
        f->endF->prox = novo;

    f->endF = novo;
    (f->dados.tam)++;
    return 1;
}

int removerElemento(tfila * f, telem * elem){
    tno* aux;

    if(f->dados.tam == 0) return 0;

    aux = f->startF;
    f->startF = f->startF->prox;
    if(f->startF == NULL)
        f->endF == NULL;

    free(aux);
    aux = NULL;

    (f->dados.tam)--;
    return 1;
}

int tamanhoFila(tfila f){
    return f.dados.tam;
}

void imprimirFila(tfila f){
    while(f.startF != NULL){
        printf("%d ", f.startF->cli.ID);
        f.startF = f.startF->prox;
    }
}
