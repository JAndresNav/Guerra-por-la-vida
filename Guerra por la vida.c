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


void GuerraPorLaVida(char *tablero, int col, int row, char *tableroTemporal) {
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            int Totalvecinos = Vecinosindividual((char *)tablero, col, row, i, j,' ');
            int vecinosX = Vecinosindividual((char *)tablero, col, row, i, j, 'X');
            int vecinosO = Vecinosindividual((char *)tablero, col, row, i, j, 'O');

            char estadoActual = *(tablero + i * row + j);

            if (estadoActual == ' ') {
                // Regla de nacimiento
                if (Totalvecinos == 3) {
                    if (vecinosX >= 2) {
                        // Nace una célula de tipo X
                        *(tableroTemporal + i * row + j) = 'X';
                    } else if (vecinosO >= 2) {
                        // Nace una célula de tipo O
                        *(tableroTemporal + i * row + j) = 'O';
                    } else {
                        // No nace ninguna célula
                        *(tableroTemporal + i * row + j) = ' ';
                    }
                } else {
                    // Célula muerta
                    *(tableroTemporal + i * row + j) = ' ';
                }
            } else {
                // Reglas de supervivencia y muerte
                if (Totalvecinos < 2 || Totalvecinos > 3) {
                    // Muere por aislamiento o sobrepoblación
                    *(tableroTemporal + i * row + j) = ' ';
                } else if (Totalvecinos == 2) {
                    if (vecinosX >= 1 && vecinosO == 0) {
                        // Sobrevive si al menos uno de los vecinos es de tipo X
                        *(tableroTemporal + i * row + j) = 'X';
                    } else if (vecinosO >= 1 && vecinosX == 0) {
                        // Sobrevive si al menos uno de los vecinos es de tipo O
                        *(tableroTemporal + i * row + j) = 'O';
                    } else {
                        // Muere si los dos vecinos son de diferente tipo
                        *(tableroTemporal + i * row + j) = ' ';
                    }
                } else if (Totalvecinos == 3) {
                    if (vecinosX >= 2) {
                        // Sobrevive si al menos dos vecinos son de tipo X
                        *(tableroTemporal + i * row + j) = 'X';
                    } else if (vecinosO >= 2) {
                        // Sobrevive si al menos dos vecinos son de tipo O
                        *(tableroTemporal + i * row + j) = 'O';
                    } else {
                        // Muere por desventaja
                        *(tableroTemporal + i * row + j) = ' ';
                    }
                } else {
                    // Sobrevive
                    *(tableroTemporal + i * row + j) = estadoActual;
                }
            }
        }
    }

    // Actualizar el tablero original con el temporal
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            *(tablero + i * row + j) = *(tableroTemporal + i * row + j);
        }
    }
}


int main() {
    char tablero[25][25];
    char tableroTemporal[25][25];

    crearTablero((char *)tablero, 25, 25);

    while (1) {
        imprimirTablero((char *)tablero, 25, 25);

        printf("\n");
        printf("Presiona Enter para continuar o introduce cualquier otro carácter para terminar\n");

        // Lee un carácter
        int inputChar = getchar();

        // Verifica si el carácter es un salto de línea (Enter)
        if (inputChar == '\n') {
            // Aquí se evalúa el juego de la vida
            GuerraPorLaVida((char *)tablero, 25, 25, (char *)tableroTemporal);
        } else {
            // Si se ingresa un carácter diferente de Enter, termina el bucle
            break;
        }
    }

    return 0;
}

