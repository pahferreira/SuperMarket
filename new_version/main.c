#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include "TadFila.h"

#define PROC_PROD 0.20
#define CR_LIMIT 25
#define SIMULATION_TIME 720
#define CAIXAS 6

typedef struct{
    int ID;
} listaCaixas;

void inserir(tfila * box, int * next, int prods);
void inicializarDados(tfila *f);
void countTime(tfila * box);
void maxRowSize(tfila *box);
int aberturaCaixa(tfila boxs[], int test);
int menorFila(tfila boxs[], int boxTest);

int main(){
    int timer, next, i, boxTest = 2, filaMenor, prods;
    char opt;
    tfila boxs[CAIXAS];
    listaCaixas boxStatus[CAIXAS];

    printf("-------------------------------------------------------------------------------------------------\n");
    printf("                                     SUPER MARKET SIMULATOR                                      \n");
    printf("-------------------------------------------------------------------------------------------------\n\n");
    printf("Quantidade de caixas                   [6]\n\n");
    printf("Tempo para chegada de novo cliente     [1 - 5]\n\n");
    printf("Quantidade de produtos                 [1 - 101]\n\n");
    printf("Tempo de atendimento no caixa          [Produtos * %.2f]  (Arrendondado para cima)\n\n", PROC_PROD);
    printf("Caixas 4 e 5 Inicialmente fechados, abertura quando necessario\n\n");

    printf("[ENTER] Start Simulation               [ESC] Exit\n");
    if((opt = getch()) == 27) return 0;

    for(i = 0; i < CAIXAS; i++){
        iniciarFila(&boxs[i]);
        inicializarDados(&boxs[i]);
    }

    next = (rand() % 4) + 1;

    for(timer = 0; timer < SIMULATION_TIME; timer++){

            if(next == 0){
                prods = (rand() % 100)+1;
                if (prods <= 25)
                    filaMenor = 0;
                else
                filaMenor = menorFila(boxs, boxTest);
                inserir(&boxs[filaMenor], &next, prods);
            }

            ///system("cls");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. R | "); imprimirFila(boxs[0]); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("   | Cx. 1 | "); imprimirFila(boxs[1]); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. 2 | "); imprimirFila(boxs[2]); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. 3 | "); imprimirFila(boxs[3]); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. 4 | "); (boxTest = aberturaCaixa(boxs, boxTest)) == 2 ? printf("FECHADO"): imprimirFila(boxs[4]); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. 5 | "); (boxTest = aberturaCaixa(boxs, boxTest)) >= 1 ? printf("FECHADO"): imprimirFila(boxs[5]); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");

            for(i = 0; i < CAIXAS; i++)
                countTime(&boxs[i]);
            next--;
            //getch();

    }

    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("                                         DADOS OBTIDOS                                           \n");
    printf("-------------------------------------------------------------------------------------------------\n\n");
    printf("* Tamanho maximo de fila *\n\n");
    for(i = 0; i < CAIXAS; i++){
        i == 0 ? printf("Cx. %c : ", 'R') : printf("Cx. %d : ", i);
        printf("%d\n", boxs[i].dados.maxSize);
    }

    printf("\n* Tamanho de espera maxima *\n\n");
    for(i = 0; i < CAIXAS; i++){
        i == 0 ? printf("Cx. %c : ", 'R') : printf("Cx. %d : ", i);
        printf("%d min\n", boxs[i].dados.maxTime);
    }


    return 0;
}

void inserir(tfila * box, int * next, int prods){
    telem elem;

    elem.ID = ++(box->dados.logIDs);
    elem.qtProd = prods;
    elem.tempo = ceil(prods * PROC_PROD);
    inserirElemento(box, elem);
    *next = (rand() % 4) + 1;

    if(box->dados.waitingTime > box->dados.maxTime)
        box->dados.maxTime = box->dados.waitingTime;
    box->dados.waitingTime += elem.tempo;
}

void countTime(tfila * box){
    telem removido;

    if(box->startF != NULL){
        box->startF->cli.tempo--;
        (box->dados.waitingTime)--;
        if(box->startF->cli.tempo == 0)
            removerElemento(box, &removido);
    }
    maxRowSize(box);
}

int menorFila(tfila boxs[], int boxTest){
    int i, filaMenor, auxTam = 9999;

    for(i = 1; i < CAIXAS - boxTest; i++){
        if(boxs[i].dados.tam < auxTam){
            auxTam = boxs[i].dados.tam;
            filaMenor = i;
        }
    }
    return filaMenor;
}
void inicializarDados(tfila *f){
    f->dados.logIDs = 0;
    f->dados.maxSize = 0;
    f->dados.maxTime = 0;
    f->dados.waitingTime = 0;
}
void maxRowSize(tfila *box){
    if(box->dados.tam > box->dados.maxSize)
        box->dados.maxSize = box->dados.tam;
}
int aberturaCaixa(tfila boxs[], int test){
    int i, tamTotal = 0;

    for(i = 1; i < CAIXAS - test; i++){
        tamTotal += boxs[i].dados.tam;
    }

    if(tamTotal < 9){
        return 2;
    } else if(tamTotal < 12){
        return 1;
    } else{
        return 0;
    }
}

