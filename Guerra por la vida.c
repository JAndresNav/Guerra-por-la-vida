//José Andrés Navarro Ozuna
//Bryan Edgardo Romo Gonzalez

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crearTablero(char *tablero,int col,int row){
    time_t t;
    srand((unsigned) time(&t));
    int temp;
    int contadorX = 0;
    int contadorO = 0;

    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            temp = rand() % 3;

            if(temp != 0 && contadorO == 50 && contadorX == 50){
                temp = 0;
            }else if(temp != 0 && temp != 1 && contadorX == 50){
                while(temp == 2){
                    //printf("temporal 2 (X) %d\n",temp);
                    temp = rand() % 3;

                }
            }else if(temp != 0 && temp != 2 && contadorO == 50){
                while(temp == 1){
                    //printf("temporal 1 (O) %d\n",temp);
                    temp = rand() % 3;
                }
            }

            if(temp == 1){
                *(tablero + i * row + j) = 'O';
                contadorO ++;
            }else if(temp == 2){
                *(tablero + i * row + j) = 'X';
                contadorX ++;
            }else{
                *(tablero + i * row + j) = ' ';
            }
        }
    }
    printf("contador O = %i\ncontador X = %i\n",contadorO,contadorX);
}

void imprimirTablero(char *tablero,int col,int row){

    for (int i = 0; i < 25; ++i) {
        printf("\n");
        for (int j = 0; j < 25; ++j) {
            printf(" %c ",*(tablero + i * row + j));
        }
    }

}

int main() {

    int flag = 0;
    char tablero[25][25];

    crearTablero((char *)tablero,25,25);

    while (flag != 1){

        imprimirTablero((char *)tablero,25,25);


        printf("\n");

        printf("Para continuar presiona 2\nSi quieres terminar presiona 1\n");
        scanf("%i",&flag);


        //aqui se evalúa el juego de la vida

    }


    return 0;
}
