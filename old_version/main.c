#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "supermarket.h"



int main(){
    int timer, next, i, boxTest = 2;
    char opt;
    tlista boxs;

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
    srand(time(NULL));


    startBoxs(&boxs);
    inserir(&boxs, &next);

    for(timer = 0; timer < SIMULATION_TIME; timer++){

            if(next == 0)
                inserir(&boxs, &next);

            system("cls");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. R | "); imprimirFila(boxs, 1); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("   | Cx. 1 | "); imprimirFila(boxs, 2); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. 2 | "); imprimirFila(boxs, 3); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. 3 | "); imprimirFila(boxs, 4); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. 4 | "); (boxTest = aberturaCaixa(boxs, boxTest)) == 2 ? printf("FECHADO"): imprimirFila(boxs, 5); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");
            printf("_________________________________________________________________________________________________\n");
            printf("   | Cx. 5 | "); (boxTest = aberturaCaixa(boxs, boxTest)) >= 1 ? printf("FECHADO"): imprimirFila(boxs, 6); printf("\n");
            printf("_________________________________________________________________________________________________\n\n");

            countTime(&boxs);
            next--;
            //getch();

    }

    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("                                         DADOS OBTIDOS                                           \n");
    printf("-------------------------------------------------------------------------------------------------\n\n");
    printf("* Tamanho maximo de fila *\n\n");
    for(i = 0; i < CAIXAS; i++){
        i == 0 ? printf("Cx. %c : ", 'R') : printf("Cx. %d : ", i);
        printf("%d\n", boxs.maxSize[i]);
    }

    printf("\n* Tamanho de espera maxima *\n\n");
    for(i = 0; i < CAIXAS; i++){
        i == 0 ? printf("Cx. %c : ", 'R') : printf("Cx. %d : ", i);
        printf("%d min\n", boxs.maxTime[i]);
    }


    return 0;
}
