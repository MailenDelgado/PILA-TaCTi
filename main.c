#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(void);

char tablero[3][3];  // Matriz 3x3 para el tablero de juego
char jugador = 'X';   // El jugador 'X' comienza
//int esBot = 0;        // 0 si el jugador humano, 1 si el jugador es un bot

// Función para inicializar el tablero
void inicializarTablero() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = ' ';  // El tablero comienza vacío
        }
    }
}

// Función para imprimir el tablero
void imprimirTablero() {
    printf("\n");
    printf("\tCol Col Col\n");
    printf("\t 1   2   3\n");

    for (int i = 0; i < 3; i++) {
            printf("Fila %d",i+1);
            printf("\t");
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tablero[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("\t---+---+---\n");
    }
    printf("\n");
}

// Función para verificar si hay un ganador
int verificarGanador() {
    // Verificar filas
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != ' ') {
            return 1;
        }
    }

    // Verificar columnas
    for (int i = 0; i < 3; i++) {
        if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != ' ') {
            return 1;
        }
    }

    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != ' ') {
        return 1;
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != ' ') {
        return 1;
    }

    return 0;  // No hay ganador
}

// Función para verificar si el juego terminó en empate
int verificarEmpate() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') {
                return 0;  // Hay al menos una casilla vacía
            }
        }
    }
    return 1;  // No hay casillas vacías, es empate
}

// Función para realizar un turno
void jugarTurno(int opc) {
    int fila, columna;
    if(opc == 1)
    {
    // Bot: elegir un movimiento aleatorio
    srand(time(NULL));
    int movimientoValido = 0;
    while (!movimientoValido) {
        fila = rand() % 3 + 1;
        columna = rand() % 3 + 1;
        if (tablero[fila-1][columna-1] == ' ') {
            movimientoValido = 1;
        }
    }
    printf("El bot ha jugado en la casilla (%d, %d)\n", fila, columna);
    } else {
        // Jugador: ingresar fila y columna
        printf("Jugador %c, ingresa fila (1-3) y columna (1-3): ", jugador);
        scanf("%d %d", &fila, &columna);

        // Verificar si la casilla está vacía
        if (tablero[fila-1][columna-1] == ' ') {
            tablero[fila-1][columna-1] = jugador;
        } else {
            printf("¡Casilla ocupada! Intenta nuevamente.\n");
            jugarTurno(0);  // Reintentar si la casilla ya está ocupada
            return;
        }
    }
    tablero[fila-1][columna-1] = jugador;
}

// Sorteo de simbolo
void sorteoSimbolo(void){
    int simbolo;
    srand(time(NULL));
    simbolo = rand() % 2;
    if (simbolo == 0) {
        jugador = 'O';
    } else {
        jugador = 'X';
    }
}

// Cambiar de jugador
void cambiarJugador() {
    if (jugador == 'X') {
        jugador = 'O';
    } else {
        jugador = 'X';
    }
}

// Función principal
int main() {

    menu();
    return 0;
}

int jugar(void)
{
    int juegoTerminado = 0;
    int opc = 0;
    sorteoSimbolo();
    while(opc != 1)
    {
        printf("Listo para jugar? ([1] SI, [0] no): ");
        scanf("%d", &opc);
    }
    inicializarTablero();

    while (!juegoTerminado) {
        imprimirTablero();

        if (opc && jugador != 'O') {
            jugarTurno(1);  // El bot juega si es su turno
        } else {
            jugarTurno(0);  // El jugador humano juega si es su turno
        }

        if (verificarGanador()) {
            imprimirTablero();
            printf("Jugador %c ha ganado\n", jugador);
            juegoTerminado = 1;
        } else if (verificarEmpate()) {
            imprimirTablero();
            printf("Empate. El juego ha terminado.\n");
            juegoTerminado = 1;
        } else {
            cambiarJugador();  // Cambiar al siguiente jugador
        }
    }
    return 0;
}

void menu(void){
    char op;
    printf("Eliga una opcion: \n[A]Jugar\n[B]Ver ranking equipo\n[C]Salir\n");
    scanf("%s", &op);
    if(op == 'A' || op == 'a')
    {
        printf("Jugar\n");
        jugar();
        menu();
    }
    else if((op == 'B') || (op == 'b'))
    {
        printf("Ver ranking equipo\n");
        menu();
    }
    else if((op == 'C') || (op == 'c'))
        printf("Salir");
    else
    {
        printf("Opcion incorrecta\n");
        menu();
    }
}
