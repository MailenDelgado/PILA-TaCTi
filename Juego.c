#include "Juego.h"

//char tablero[3][3];  // Matriz 3x3 para el tablero de juego
//char jugador = 'X';   // El jugador 'X' comienza

//Funciones de jugadas bot
int intentarGanar(int *f, int *c, char tablero[3][3], char *jugador){


    // Verificar filas
    for (int i = 0; i < 3; i+=3) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][0] != ' ' && tablero[i][0] == *jugador && tablero[i][2] == ' ') {
            *f = i+1;
            *c = 3;
            return 1;
        }else if(tablero[i][1] == tablero[i][2] && tablero[i][1] != ' ' && tablero[i][1] == *jugador && tablero[i][0] == ' '){
            *f = i+1;
            *c = 1;
            return 1;
        }else if(tablero[i][0] == tablero[i][2] && tablero[i][0] != ' ' && tablero[i][0] == *jugador && tablero[i][1] == ' '){
            *f = i+1;
            *c = 2;
            return 1;
        }
    }

    // Verificar columnas
    for (int i = 0; i < 3; i++) {
        if (tablero[0][i] == tablero[1][i] && tablero[0][i] != ' ' && tablero[0][i] == *jugador && tablero[2][i] == ' ') {
            *f = 3;
            *c = i+1;
            return 1;
        }else if(tablero[1][i] == tablero[2][i] && tablero[1][i] != ' ' && tablero[1][i] == *jugador && tablero[0][i] == ' '){
            *f = 1;
            *c = i+1;
            return 1;
        }else if(tablero[0][i] == tablero[2][i] && tablero[0][i] != ' ' && tablero[0][i] == *jugador && tablero[1][i] == ' '){
            *f = 2;
            *c = i+1;
            return 1;
        }
    }

    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[0][0] != ' ' && tablero[0][0] == *jugador && tablero[2][2] == ' ') {
        *f = 3;
        *c = 3;
        return 1;
    }
    if(tablero[1][1] == tablero[2][2] && tablero[1][1] != ' ' && tablero[1][1] == *jugador && tablero[0][0] == ' '){
        *f = 1;
        *c = 1;
        return 1;
    }
    if(tablero[0][0] == tablero[2][2] && tablero[0][0] != ' ' && tablero[0][0] == *jugador && tablero[1][1] == ' '){
        *f = 2;
        *c = 2;
        return 1;
    }

    if (tablero[0][2] == tablero[1][1] && tablero[0][2] != ' ' && tablero[0][2] == *jugador && tablero[2][0] == ' '){
        *f = 3;
        *c = 1;
        return 1;
    }

    if(tablero[1][1] == tablero[2][0] && tablero[1][1] != ' ' && tablero[1][1] == *jugador && tablero[0][2] == ' '){
        *f = 1;
        *c = 3;
        return 1;
    }
    return 0;
}

int bloquearVictoria(int *f, int *c, char tablero[3][3], char *jugador){

    // Verificar filas
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][0] != ' ' && tablero[i][0] != *jugador && tablero[i][2] == ' ') {
            *f = i+1;
            *c = 3;
            return 1;
        }else if(tablero[i][1] == tablero[i][2] && tablero[i][1] != ' ' && tablero[i][1] != *jugador && tablero[i][0] == ' '){
            *f = i+1;
            *c = 1;
            return 1;
        }else if(tablero[i][0] == tablero[i][2] && tablero[i][0] != ' ' && tablero[i][0] != *jugador && tablero[i][1] == ' '){
            *f = i+1;
            *c = 2;
            return 1;
        }
    }

    // Verificar columnas
    for (int i = 0; i < 3; i++) {
        if (tablero[0][i] == tablero[1][i] && tablero[0][i] != ' ' && tablero[0][i] != *jugador && tablero[2][i] == ' ') {
            *f = 3;
            *c = i+1;
            return 1;
        }else if(tablero[1][i] == tablero[2][i] && tablero[1][i] != ' ' && tablero[1][i] != *jugador && tablero[0][i] == ' '){
            *f = 1;
            *c = i+1;
            return 1;
        }else if(tablero[0][i] == tablero[2][i] && tablero[0][i] != ' ' && tablero[0][i] != *jugador && tablero[1][i] == ' '){
            *f = 2;
            *c = i+1;
            return 1;
        }
    }

    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[0][0] != ' ' && tablero[0][0] != *jugador && tablero[2][2] == ' ') {
        *f = 3;
        *c = 3;
        return 1;
    }
    if(tablero[1][1] == tablero[2][2] && tablero[1][1] != ' ' && tablero[1][1] != *jugador && tablero[0][0] == ' '){
        *f = 1;
        *c = 1;
        return 1;
    }
    if(tablero[0][0] == tablero[2][2] && tablero[0][0] != ' ' && tablero[0][0] != *jugador && tablero[1][1] == ' '){
        *f = 2;
        *c = 2;
        return 1;
    }

    if (tablero[0][2] == tablero[1][1] && tablero[0][2] != ' ' && tablero[0][2] != *jugador && tablero[2][0] == ' '){
        *f = 3;
        *c = 1;
        return 1;
    }

    if(tablero[1][1] == tablero[2][0] && tablero[1][1] != ' ' && tablero[1][1] != *jugador && tablero[0][2] == ' '){
        *f = 1;
        *c = 3;
        return 1;
    }
    return 0;
}

// Función para inicializar el tablero
void inicializarTablero(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = ' ';  // El tablero comienza vacío
        }
    }
}

// Función para imprimir el tablero
void imprimirTablero(char tablero[3][3]) {
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

void imprimirTableroEnArchivo(FILE *pf, char tablero[3][3]) {
    fprintf(pf, "\n");
    fprintf(pf, "\tCol Col Col\n");
    fprintf(pf, "\t 1   2   3\n");

    for (int i = 0; i < 3; i++) {
            fprintf(pf, "Fila %d",i+1);
            fprintf(pf, "\t");
        for (int j = 0; j < 3; j++) {
            fprintf(pf, " %c ", tablero[i][j]);
            if (j < 2) fprintf(pf, "|");
        }
        fprintf(pf, "\n");
        if (i < 2) fprintf(pf, "\t---+---+---\n");
    }
    fprintf(pf, "\n");
}

// Función para verificar si hay un ganador
int verificarGanador(char tablero[3][3]) {
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
int verificarEmpate(char tablero[3][3]) {
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
void jugarTurno(int opc, char tablero[3][3], char *jugador) {
        int fila, columna;
    if(opc == 1)
    {
        if(intentarGanar(&fila, &columna, tablero, jugador)== 1){
            printf("El bot ha jugado en la casilla (%d, %d)\n", fila, columna);
        }
        else if(bloquearVictoria(&fila, &columna, tablero, jugador)== 1){
            printf("El bot ha jugado en la casilla (%d, %d)\n", fila, columna);
        }
        else{
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
        }
    }
    else{
        // Jugador: ingresar fila y columna
        printf("Jugador %c, ingresa fila (1-3) y columna (1-3): ", *jugador);
        scanf("%d %d", &fila, &columna);

        // Verificar si la casilla está vacía
        if (tablero[fila-1][columna-1] == ' ') {
            tablero[fila-1][columna-1] = *jugador;
        }else{
            printf("¡Casilla ocupada! Intenta nuevamente.\n");
            jugarTurno(0, tablero, jugador);  // Reintentar si la casilla ya está ocupada
            return;
        }
    }
    tablero[fila-1][columna-1] = *jugador;
}

// Sorteo de simbolo
int sorteoSimbolo(void){
    int simbolo;
    srand(time(NULL));
    simbolo = rand() % 2;
    return simbolo;
}

void cambiarSorteo(int *sorteo) {
    if (*sorteo == 1) {
        *sorteo = 0;
    } else {
        *sorteo = 1;
    }
}

void sorteoOrden(int n, int *vec){
    int ordenInvalido = 1, orden, i, j;
//    for(i = 0; i < n; i++)
//        vec[i] = 0;
    i = 0;
    srand(time(NULL));
    while(i < n)
    {
        ordenInvalido = 1;
        while(ordenInvalido){
            orden = rand() % n + 1;
            if(*(vec+i) == 0)
            {
                j = 0;
                while(*(vec+j) != orden && j < n)
                {
                    j++;
                }
                if(j > n - 1){
                    ordenInvalido = 0;
                }
            }
        }
        *(vec+i) = orden;
        i++;
    }
}

// Cambiar de jugador
void cambiarJugador(char *jugador) {
    if (*jugador == 'X') {
        *jugador = 'O';
    } else {
        *jugador = 'X';
    }
}
/*
int jugar(void){
    FILE *pf = fopen("puntajes.txt", "wb");
    if(feof(pf))
    {
        printf("Error archivo");
        fclose(pf);
    }
    fprintf(pf, "Nombre\tPuntos\n");
    tJugador player, jugadorSacado;
    tLista listaJugadores;
    int juegoTerminado = 0, opc = 1, partidas = CANT_PARTIDAS, sorteo, i = 0, vecOrden[N] = {0};
    crearLista(&listaJugadores);
    while(opc != 0)
    {
        printf("Ingresar nombre del jugador: ");
        fflush(stdin);
        gets(player.nombre);
        player.puntos = 0;
        printf("\n%s\n", player.nombre);
        ponerEnLista(&listaJugadores, &player, sizeof(player));
        i++;
        printf("[1] Ingresar nuevo jugador: \n[0] Para finalizar ingresos: \n");
        fflush(stdin);
        scanf("%d",&opc);
    }
    printf("Van a jugar %d jugadores\n", i);
    sorteoOrden(i, vecOrden);
    recorroLista(&listaJugadores, vecOrden, sizeof(int), modificoOrdenLista);
    ordenarLista(&listaJugadores, comparoPorOrden);
    printf("Nombre\tOrden\n");
    recorroLista(&listaJugadores, NULL, sizeof(int), imprimoOrden);
//    printf("Ingresar Nombre: ");
//    scanf("%s", player.nombre);
    player.puntos = 0;
    sorteo = sorteoSimbolo();
    while(i){
        verPrimeroDeLista(&listaJugadores, &player, sizeof(player));
        while(partidas)
        {
            jugador = 'X';
            while(opc != 1)
            {
                printf("%s listo para jugar? ([1] SI, [0] no): ", player.nombre);
                scanf("%d", &opc);
            }
            inicializarTablero();
            player.puntos += 0;
            while (!juegoTerminado) {
                imprimirTablero();

                if (opc && sorteo == 0 && jugador == 'X') {
                    jugarTurno(1);  // El bot juega si es su turno
                } else if (opc && sorteo == 1 && jugador == 'X'){
                jugarTurno(0);  // El jugador humano juega si es su turno
                }else if((opc && sorteo == 0 && jugador == 'O')){
                    jugarTurno(0);  // El bot juega si es su turno
                }else if((opc == 1 && sorteo == 1 && jugador == 'O')){
                    jugarTurno(1);  // El bot juega si es su turno
                }
                if (verificarGanador()) {
                    imprimirTablero();
                    printf("Jugador %c ha ganado\n", jugador);
                    if((jugador == 'X' && sorteo == 0)||(jugador == 'O' && sorteo == 1))
                        player.puntos += DERROTA;
                    else
                        player.puntos += VICTORIA;
                    juegoTerminado = 1;
                } else if (verificarEmpate()) {
                    imprimirTablero();
                    printf("Empate. El juego ha terminado.\n");
                    player.puntos += EMPATE;
                    juegoTerminado = 1;
                } else {
                    cambiarJugador();  // Cambiar al siguiente jugador
                }
            }
            cambiarSorteo(&sorteo);
            partidas--;
            opc = 0;
            juegoTerminado = 0;
        }
        fprintf(pf, "%s\t%d\n", player.nombre, player.puntos);
        sacarPrimeroDeLista(&listaJugadores, &jugadorSacado, sizeof(jugadorSacado));
        partidas = CANT_PARTIDAS;
        i--;
    }
    fclose(pf);
    return 0;
}
*/
int comparoPorOrden(const void *d1, const void *d2){
    tJugador *jug1 = (tJugador*)d1;
    tJugador *jug2 = (tJugador*)d2;
    return(jug1->orden - jug2->orden);
}

int imprimoOrden(const void *d1, const void *d2){
    tJugador *jug = (tJugador*)d1;
    printf("%s\t%d\n", jug->nombre, jug->orden);
    return 1;
}

int modificoOrdenLista(const void *pd1, const void *pd2){
    tJugador *player = (tJugador*)pd1;
    int *orden = (int*)pd2;
    player->orden = *orden;
    return 1;
}

int jugar2(int cantPartidas){ //VERSION ACTUALIZADA DE FUNCION JUGAR
    char tablero[3][3];  // Matriz 3x3 para el tablero de juego
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char nombrearch[40];
    char jugador;
    sprintf(nombrearch,"informe-juego_%04d-%02d-%02d-%02d-%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

    FILE *pf = fopen(nombrearch,"wt");

//    FILE *pf = fopen("informe-juego_.txt", "wb");
    if(feof(pf))
    {
        printf("Error archivo");
        fclose(pf);
    }
    tJugador player, jugadorSacado;
    tLista listaJugadores;
    int juegoTerminado = 0, opc = 1, partidas = cantPartidas, sorteo, i = 0, vecOrden[N] = {0};
    crearLista(&listaJugadores);
    while(opc != 0)
    {
        i += ingresarJugadores(&listaJugadores, &player, sizeof(player), &opc);
    }
    printf("Van a jugar %d jugadores\n", i);
    sorteoOrden(i, vecOrden);
    recorroLista(&listaJugadores, vecOrden, sizeof(int), modificoOrdenLista);
    ordenarLista(&listaJugadores, comparoPorOrden);
    printf("Nombre\tOrden\n");
    recorroLista(&listaJugadores, NULL, sizeof(int), imprimoOrden);
//    printf("Ingresar Nombre: ");
//    scanf("%s", player.nombre);
//    player.puntos = 0;
    while(i){
        verPrimeroDeLista(&listaJugadores, &player, sizeof(player));
        fprintf(pf, "Partida/s de %s\n", player.nombre);
        while(partidas)
        {
            jugador = 'X';
            sorteo = sorteoSimbolo();
            while(opc != 1)
            {
                printf("%s listo para jugar? ([1] SI, [0] no): ", player.nombre);
                scanf("%d", &opc);
            }
            inicializarTablero(tablero);///MODIFICADA
//            player.puntos += 0;
            while (!juegoTerminado) {
                imprimirTablero(tablero);///MODIFICADA

                if (opc && sorteo == 0 && jugador == 'X') {
                    jugarTurno(1, tablero, &jugador);  /// El bot juega si es su turno MODIFICADA
                } else if (opc && sorteo == 1 && jugador == 'X'){
                jugarTurno(0, tablero, &jugador);  /// El jugador humano juega si es su turno MODIFICADA
                }else if((opc && sorteo == 0 && jugador == 'O')){
                    jugarTurno(0, tablero, &jugador);  /// El bot juega si es su turno MODIFICADA
                }else if((opc == 1 && sorteo == 1 && jugador == 'O')){
                    jugarTurno(1, tablero, &jugador);  /// El jugador humano juega si es su turno MODIFICADA
                }
                if (verificarGanador(tablero)) {
                    imprimirTablero(tablero);///MODIFICADA
                    imprimirTableroEnArchivo(pf, tablero);///MODIFICADA
                    printf("Jugador %c ha ganado\n", jugador);
                    if((jugador == 'X' && sorteo == 0)||(jugador == 'O' && sorteo == 1))
                    {
                        player.puntos += DERROTA;
                        fprintf(pf, "%s ha perdido. Resta 1 punto\n", player.nombre);
                    }
                    else
                    {
                        player.puntos += VICTORIA;
                        fprintf(pf, "%s ha ganado. Suma 3 puntos\n", player.nombre);
                    }

                    juegoTerminado = 1;
                } else if (verificarEmpate(tablero)) {
                    imprimirTablero(tablero);///MODIFICADA
                    imprimirTableroEnArchivo(pf, tablero);///MODIFICADA
                    printf("Empate. El juego ha terminado.\n");
                    fprintf(pf, "Empate. %s suma 2 puntos\n", player.nombre);
                    player.puntos += EMPATE;
                    juegoTerminado = 1;
                } else {
                    cambiarJugador(&jugador);  // Cambiar al siguiente jugador
                }
            }
            cambiarSorteo(&sorteo);
            partidas--;
            opc = 0;
            juegoTerminado = 0;
        }
        fprintf(pf, "Nombre\tPuntos\n");
        fprintf(pf, "%s\t%d\n", player.nombre, player.puntos);
        sacarPrimeroDeLista(&listaJugadores, &jugadorSacado, sizeof(jugadorSacado));
        partidas = cantPartidas;
        i--;
    }
    fclose(pf);
    return 0;
}

int ingresarJugadores(tLista *pl, void *pd, unsigned tam, int *val){
    int i = 0;
    tJugador *player = (tJugador*)pd;
    printf("Ingresar nombre del jugador: ");
    fflush(stdin);
    gets(player->nombre);
    player->puntos = 0;
    printf("\n%s\n", player->nombre);
    ponerEnLista(pl, player, sizeof(tJugador));
    i++;
    printf("[1] Ingresar nuevo jugador: \n[0] Para finalizar ingresos: \n");
    fflush(stdin);
    scanf("%d", val);
    return i;
}

