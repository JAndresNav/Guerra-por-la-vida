//José Andrés Navarro Ozuna
//Bryan Edgardo Romo Gonzalez

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crearTablero(char *tablero, int col, int row) {
    time_t t;
    srand((unsigned)time(&t));
    int temp;
    int contadorX = 0;
    int contadorO = 0;

    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            temp = rand() % 3;

            if (temp != 0 && contadorO == 50 && contadorX == 50) {
                temp = 0;
            } else if (temp != 0 && temp != 1 && contadorX == 50) {
                while (temp == 2) {
                    temp = rand() % 3;
                }
            } else if (temp != 0 && temp != 2 && contadorO == 50) {
                while (temp == 1) {
                    temp = rand() % 3;
                }
            }

            if (temp == 1) {
                *(tablero + i * row + j) = 'O';
                contadorO++;
            } else if (temp == 2) {
                *(tablero + i * row + j) = 'X';
                contadorX++;
            } else {
                *(tablero + i * row + j) = ' ';
            }
        }
    }
    printf("contador O = %i\ncontador X = %i\n", contadorO, contadorX);
}

void imprimirTablero(char *tablero, int col, int row) {
    for (int i = 0; i < col; ++i) {
        printf("\n");
        for (int j = 0; j < row; ++j) {
            printf(" %c ", *(tablero + i * row + j));
        }
    }
}

int contarVecinos(char *tablero, int col, int row, int x, int y) {
    int contador = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;  // No contar la celda actual
            }

            int nuevaX = x + i;
            int nuevaY = y + j;

            if (nuevaX >= 0 && nuevaX < col && nuevaY >= 0 && nuevaY < row &&
                *(tablero + nuevaX * row + nuevaY) != ' ') {
                contador++;
            }
        }
    }

    return contador;
}

int Vecinosindividual(char *tablero, int col, int row, int x, int y,char celula) {
    int contador = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;  // No contar la celda actual
            }

            int nuevaX = x + i;
            int nuevaY = y + j;

            if (nuevaX >= 0 && nuevaX < col && nuevaY >= 0 && nuevaY < row &&
                *(tablero + nuevaX * row + nuevaY) == celula) {
                contador++;
            }
        }
    }
    return contador;
}


void GuerraPorLaVida(char *tablero, int col, int row,char * tableroTemporal) {


    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            int Totalvecinos = contarVecinos((char *)tablero, col, row, i, j);
            int vecinosX = Vecinosindividual((char *)tablero, col, row, i, j,'X');
            int vecinosO = Vecinosindividual((char *)tablero, col, row, i, j,'O');

            //printf("Vecinos X %i y vecinos O %i de %i,%i\n",vecinosX,vecinosO,i,j); ya jalan las varibales, falta evaluar las reglas

            char estadoActual = *(tablero + i * row + j);

            if (estadoActual == ' ') {

                if (Totalvecinos == 3) {
                    if (contarVecinos((char *)tablero, col, row, i, j) >= 2) {
                        *(tableroTemporal + i * row + j) = 'X';
                    } else {
                        *(tableroTemporal + i * row + j) = 'O';
                    }
                } else {
                    *(tableroTemporal + i * row + j) = ' ';
                }
            } else {

                if (Totalvecinos < 2 || Totalvecinos > 3 || contarVecinos((char *)tablero, col, row, i, j) < 2) {
                    *(tableroTemporal + i * row + j) = ' ';
                } else {
                    *(tableroTemporal + i * row + j) = estadoActual;
                }
            }
        }
    }


    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            *(tablero + i * row + j) = *(tableroTemporal + i * row + j);
        }
    }
}

int main() {
    int flag = 0;
    char tablero[25][25];
    char tableroTemporal[25][25];

    crearTablero((char *)tablero, 25, 25);

    while (flag != 1) {
        imprimirTablero((char *)tablero, 25, 25);

        printf("\n");
        printf("Para continuar presiona 2\nSi quieres terminar presiona 1\n");
        scanf("%i", &flag);

        // Aquí se evalúa el juego de la vida
        GuerraPorLaVida((char *)tablero, 25, 25,(char *)tableroTemporal);
    }

    return 0;
}


/*
//José Andrés Navarro Ozuna
//Bryan Edgardo Romo Gonzalez

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crearTablero(char *tablero, int col, int row) {
    time_t t;
    srand((unsigned)time(&t));
    int temp;
    int contadorX = 0;
    int contadorO = 0;

    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            temp = rand() % 3;

            if (temp != 0 && contadorO == 50 && contadorX == 50) {
                temp = 0;
            } else if (temp != 0 && temp != 1 && contadorX == 50) {
                while (temp == 2) {
                    temp = rand() % 3;
                }
            } else if (temp != 0 && temp != 2 && contadorO == 50) {
                while (temp == 1) {
                    temp = rand() % 3;
                }
            }

            if (temp == 1) {
                *(tablero + i * row + j) = 'O';
                contadorO++;
            } else if (temp == 2) {
                *(tablero + i * row + j) = 'X';
                contadorX++;
            } else {
                *(tablero + i * row + j) = ' ';
            }
        }
    }
    printf("contador O = %i\ncontador X = %i\n", contadorO, contadorX);
}

void imprimirTablero(char *tablero, int col, int row) {
    for (int i = 0; i < col; ++i) {
        printf("\n");
        for (int j = 0; j < row; ++j) {
            printf(" %c ", *(tablero + i * row + j));
        }
    }
}

int contarVecinos(char *tablero, int col, int row, int x, int y) {
    int contador = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;  // No contar la celda actual
            }

            int nuevaX = x + i;
            int nuevaY = y + j;

            if (nuevaX >= 0 && nuevaX < col && nuevaY >= 0 && nuevaY < row &&
                *(tablero + nuevaX * row + nuevaY) != ' ') {
                contador++;
            }
        }
    }

    return contador;
}

int Vecinosindividual(char *tablero, int col, int row, int x, int y,char celula) {
    int contador = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;  // No contar la celda actual
            }

            int nuevaX = x + i;
            int nuevaY = y + j;

            if (nuevaX >= 0 && nuevaX < col && nuevaY >= 0 && nuevaY < row &&
                *(tablero + nuevaX * row + nuevaY) == celula) {
                contador++;
            }
        }
    }
    return contador;
}


void GuerraPorLaVida(char* tablero, int col, int row, char* tableroTemporal) {
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            int TotalVecinos = contarVecinos(tablero, col, row, i, j);
            int VecinosX = Vecinosindividual(tablero, col, row, i, j, 'X');
            int VecinosO = Vecinosindividual(tablero, col, row, i, j, 'O');

            char estadoActual = *(tablero + i * row + j);

            if (estadoActual == ' ') {
                if (TotalVecinos == 3) {
                    if (VecinosX >= 2) {
                        *(tableroTemporal + i * row + j) = 'X';
                    } else if (VecinosO >= 2) {
                        *(tableroTemporal + i * row + j) = 'O';
                    } else {
                        *(tableroTemporal + i * row + j) = ' ';
                    }
                } else {
                    *(tableroTemporal + i * row + j) = ' ';
                }
            } else {
                if (TotalVecinos < 2 || TotalVecinos > 3) {
                    *(tableroTemporal + i * row + j) = ' ';
                } else if (TotalVecinos == 2) {
                    if (VecinosX == 2 && VecinosO == 0) {
                        *(tableroTemporal + i * row + j) = 'X';
                    } else if (VecinosO == 2 && VecinosX == 0) {
                        *(tableroTemporal + i * row + j) = 'O';
                    } else {
                        *(tableroTemporal + i * row + j) = ' ';
                    }
                } else {
                    if (estadoActual == 'X' && VecinosX >= 2) {
                        *(tableroTemporal + i * row + j) = 'X';
                    } else if (estadoActual == 'O' && VecinosO >= 2) {
                        *(tableroTemporal + i * row + j) = 'O';
                    } else {
                        *(tableroTemporal + i * row + j) = ' ';
                    }
                }
            }
        }
    }

    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            *(tablero + i * row + j) = *(tableroTemporal + i * row + j);
        }
    }
}


int main() {
    int flag = 0;
    char tablero[25][25];
    char tableroTemporal[25][25];

    crearTablero((char *)tablero, 25, 25);

    while (flag != 1) {
        imprimirTablero((char *)tablero, 25, 25);

        printf("\n");
        printf("Para continuar presiona 2\nSi quieres terminar presiona 1\n");
        scanf("%i", &flag);

        // Se evalúa el juego de la vida
        GuerraPorLaVida((char *)tablero, 25, 25,(char *)tableroTemporal);
    }

    return 0;
}
*/
