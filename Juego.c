#include "Juego.h"

void menu(void){
    char op;
    printf("Eliga una opcion: \n[A]Jugar\n[B]Ver ranking equipo\n[C]Salir\n");
    scanf("%s", &op);
    if(op == 'A' || op == 'a')
    {
        printf("Jugar\n");
        iniciarJuego();
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

int iniciarJuego(){
    int cantPartidas;
    tLista list_jugadores;
    tLista list_partidas;
    tConfig config;
    tJugador *jugador;//es un puntero porque en realidad es el jugador encontrado en la lista
    cargarConfig("D:\\Documentos\\GitHub\\PILA-TaCTi\\config\\config.txt", &config);
    cantPartidas = config.cantPartidas;
    int cantidadJugadores=0,
        i=0,
        njugador=0,
        resultado,
        *orden,
        *porden;
    char ganador[10],
         tablero[TAM][TAM];

        resultado= ingresoJugadores(&list_jugadores,&cantidadJugadores) ;
        if(!resultado) //si no se ingresaron jugadores vuelve al menu
        return 0;

        orden= malloc(cantidadJugadores * sizeof(int));

        if (orden == NULL) {
        printf("Error al asignar memoria para vector de Orden\n");
        return 0;
        }

        porden = orden;

        // Inicializa la semilla para los números aleatorios
        srand(time(NULL));
        sortearJugadores(&list_jugadores,cantidadJugadores,orden);

        crearLista(&list_partidas);
        system("cls");

        //Partidas
        do{
            jugador = buscarporPos(&list_jugadores,*porden); //obtener jugador


            for(i=0;i<cantPartidas;i++){
                printf("\n\tTurno de: %s. Partida %d de %d", jugador->nombre,i+1,cantPartidas);
                resultado=jugar(tablero);

                if(!resultado){
                free(orden);
                vaciarLista(&list_jugadores);
                return 0;
                }

                jugador->puntos+=resultado; //actualizo puntaje y lo muestro
                printf("\nPuntaje de %s es %d\n",jugador->nombre, jugador->puntos );
                system("pause");
                if(resultado == 3){
                    strcpy(ganador,jugador->nombre);
                }
                else if(resultado == -1){
                    strcpy(ganador,"MAQUINA");
                }
                else{
                    strcpy(ganador,"EMPATE");
                }
                guardarPartida(&list_partidas,tablero,i+1,*porden,ganador,resultado,*jugador);
            }

            actualizaEnPosLista(&list_jugadores,jugador,sizeof(tJugador), *porden, actualizardato); //actualizo el puntaje del jugador en la lista

            porden++;
            njugador++;
        }while( njugador < cantidadJugadores );

    free(orden);

    printf("\n\n\tRESULTADOS");
    printf("\n\t----------");
    mostrarLista(&list_jugadores, verJugador);
    system("pause");
    generarInforme(&list_partidas, &list_jugadores);

    vaciarLista(&list_jugadores);
    vaciarLista(&list_partidas);
    return 1;
}

int ingresoJugadores(tLista *list_jugadores, int *cantidad){
    int r;
    tJugador jugador;
    crearLista(list_jugadores);

    do
    {
    system("cls");
    printf("\t\t\t----------------\n");
    printf("ingrese los nombres de los jugadores o para terminar ingrese 0: \n");

    scanf("%19s", jugador.nombre);
    jugador.puntos = 0; //inicializo todos los puntajes en 0
    r=listaLlena(list_jugadores, sizeof(tJugador));

    if( !r && strcmp(jugador.nombre,"0") ){ ///Si la lista no está llena y el nombre del jugador no es 0

       ponerEnLista(list_jugadores, &jugador, sizeof(tJugador));
       (*cantidad)++;
    }
    else if (r){
                printf(" Error al ingresar nombre, LISTA LLENA ");
                return 0;
            }

    }while(strcmp(jugador.nombre, "0"));

    if(!*cantidad){
        return 0;
    }
    return 1;
}

// Sorteo de jugadores
int sortearJugadores(tLista *list_jugadores, int cantidad, int *orden) {

    int i;

    tJugador *jugador;

    sorteo(orden, cantidad);

    system("cls");

    printf("\n\t\t\tOrden aleatorio de jugadores:\n");
    printf("\n\t\t\t------------------------------\n");
    for ( i = 0; i < cantidad; i++) {
        jugador = (tJugador *)buscarporPos(list_jugadores,orden[i]);
        printf(" Jugador %d: %s\n", i + 1, jugador->nombre);
    }
    system("pause");
    return 1;
}

void sorteo(int *indices, int n) { ///fisher yates: algoritmo de desordenamiento aleatorio
    int i,
        j,
        temp;
    ///cargo el vector con el numero de su indice
    for (i = 0; i < n; i++) {
        indices[i] = i;
    }

    for (i = n - 1; i > 0; i--) { // empieza desde el ultimo
        j = rand() % (i + 1); //elije un indice aleatorio entre 0 e i
        temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp; //intercambia el último con el indice elegido
    }
}

int jugar(char tablero[TAM][TAM]){

    int juegoTerminado = 0;
    int opc=0, band=0;
    char jugador= sortearSimbolo();

    while(opc != 1)
    {
        printf("\nListo para jugar? ([1] SI, [0] no): ");
        scanf("%d", &opc);
        if(opc==0){
            printf("\n Volver al menu? ([1] SI, [0] no):");
            scanf("%d", &opc);
            if(opc==1){
                return 0;
            }
        }
    }
    inicializarTablero(tablero);

    if ( jugador == 'X') {
            band=1;
            opc = 0;  // El jugador humano juega si es su turno
            printf("\n\t Sos la X, empezas vos\n");
        }
        else {
            opc = 1; // El bot juega si es su turno
            jugador ='X'; //EL BOT EMPIEZA CON LA X
            printf("\n\t Sos el O, empieza la maquina\n");
        }
    printf("\t-------------------------\n");
    system("pause");
    system("cls");
    while (!juegoTerminado) {
        imprimirTablero(tablero);

        jugarTurno(tablero,jugador,opc);

        if (verificarGanador(tablero)) {
            imprimirTablero(tablero);
            printf("Jugador %c ha ganado\n", jugador);
            juegoTerminado = 1;

            if(band==1){ //X ES EL HUMANO
                return (jugador == 'X')?3:-1;
            }
            else{
                return (jugador == 'O')?3:-1;
            }

        } else if (verificarEmpate(tablero)) {
            imprimirTablero(tablero);
            printf("Empate. El juego ha terminado.\n");
            juegoTerminado = 1;

            return 2;
            }
        if (!juegoTerminado) {
        opc = (opc == 1) ? 0 : 1;   // Cambia entre 1 y 0 para alternar el turno entre humano y maquina
        jugador = (jugador == 'X')? 'O' : 'X';// Cambia entre X y O para alternar el turno
        }
    }
    return 0;
}

char sortearSimbolo(void) {
    int orden[2];
    sorteo(orden, 2);                    //EL PRIMER ELEMENTO ES EL SIMBOLO CON EL QUE EMPEZARÁ EL USUARIO
    return (orden[0] == 0) ? 'O' : 'X'; //Si no hubo intercambio de indices entonces el usuario empieza con O, sino con X.
}

void inicializarTablero(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = ' ';  // El tablero comienza vacío
        }
    }
}

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

void jugarTurno(char tablero[TAM][TAM],char jugador,int opc) {

    int fila, columna,r;
    if(opc == 1)
    {
        if(intentarGanar(&fila, &columna, tablero, &jugador)== 1){
            printf("El bot ha jugado en la casilla (%d, %d)\n", fila, columna);
        }
        else if(bloquearVictoria(&fila, &columna, tablero, &jugador)== 1){
            printf("El bot ha jugado en la casilla (%d, %d)\n", fila, columna);
        }
        else{
            // Bot: elegir un movimiento aleatorio
//            srand(time(NULL));
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
    } else {
        // Jugador: ingresar fila y columna
        do{
        printf("Jugador %c, ingresa fila (1-3) y columna (1-3): ", jugador);
        scanf("%d %d", &fila, &columna);
        r=verificafilacol(fila,columna);
        if(!r){
            printf("Ingrese un numero de fila y columna validos, separados por un espacio.\n");
        }
        }while(!r);
        // Verificar si la casilla está vacía
        if (tablero[fila-1][columna-1] == ' ') {
            tablero[fila-1][columna-1] = jugador;
        } else {
            printf("Casilla ocupada. Intenta nuevamente.\n");
            jugarTurno(tablero, jugador, 0);  // Reintentar si la casilla ya está ocupada
            return;
        }
    }
    tablero[fila-1][columna-1] = jugador;
}

//Funciones de estrategia bot
int intentarGanar(int *f, int *c, char tablero[3][3], char *jugador){
    // Verificar filas
    for (int i = 0; i < 3; i++) {
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

int verificafilacol(int fila, int columna){
    if(fila<1 || fila>TAM){
        return 0;
    }
    if(columna<1 || columna>TAM){
        return 0;
    }
    return 1;
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

void guardarPartida(tLista *list_partidas, char tablero[TAM][TAM],int numPartida, int numJugador ,const char *ganador, int puntaje, tJugador jugador){
    int result;
    tPartida partida;

    memcpy(partida.tablero, tablero, sizeof(partida.tablero));
    partida.numJugador=numJugador;
    partida.puntaje=puntaje;
    partida.numPartida=numPartida;
    strcpy(partida.ganador,ganador);
    strcpy(partida.jugador,jugador.nombre);

    result= ponerEnLista(list_partidas,&partida,sizeof(partida));
    if(!result){
        printf("\nNO SE PUDO PONER EN LISTA");
        system("pause");
    }
}

int generarInforme(tLista *list_partidas, tLista *list_jugadores){
    tPartida partida;
    int result,i,j;
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     char nombrearch[40];
     sprintf(nombrearch,"informe-juego_%04d-%02d-%02d-%02d-%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

     FILE *pl = fopen(nombrearch,"wt");

    if(!pl){
        printf("\nError al crear el informe");
        return 0;
    }

    result=sacarDeLista(list_partidas,&partida,sizeof(partida));

    while(result!=0){

        fprintf(pl,"JUGADOR: %-19s\nPartida: %d\nGanador: %-10s\nPuntaje: %d\n",partida.jugador,partida.numPartida,partida.ganador,partida.puntaje);

          // Escribir el tablero de la partida
        fputs("TABLERO:\n", pl);
        for (i = 0; i < TAM; i++) {
            for (j = 0; j < TAM; j++) {
                fprintf(pl, " %c ", partida.tablero[i][j]);
                if (j < TAM - 1)
                    fprintf(pl, "|"); // Separadores verticales
            }
            fputs("\n", pl);
            if (i < TAM - 1)
                fputs("---+---+---\n", pl); // Separadores horizontales
        }
        fputs("-----------------------------------\n", pl);

        result=sacarDeLista(list_partidas,&partida,sizeof(partida));
     }
     generarRanking(list_jugadores, pl);
     fclose(pl);
     return 0;
}

void generarRanking(tLista *pl, FILE *pf){
    ordenarLista(pl, comparoPorPuntaje);
    printf("\tRanking\n");
    printf("\tNombre \tPuntos\n");
    fprintf(pf, "\tRanking\n");
    fprintf(pf,"\tNombre \tPuntos\n");
    recorroLista(pl, NULL, 0, imprimoRanking);
    recorroLista(pl, pf, 0, imprimoRankingEnArchivo);
}

int comparoPorPuntaje(const void *d1, const void *d2){
    tJugador *jug1 = (tJugador*)d1;
    tJugador *jug2 = (tJugador*)d2;
    return(jug1->puntos - jug2->puntos);
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

int imprimoRanking(const void *d1, const void *d2){
    tJugador *jugador = (tJugador*)d1;
    printf("\t%s\t%-4d\n", jugador->nombre, jugador->puntos);
    return 1;
}

int imprimoRankingEnArchivo(const void *d1, const void *d2){
    FILE *pf = (FILE *)d2;
    tJugador *jugador = (tJugador*)d1;
    fprintf(pf,"\t%s\t%-4d\n", jugador->nombre, jugador->puntos);
    return 1;
}

void actualizardato(void *dest, const void *org){
    tJugador *jugador = (tJugador *)dest,
             *actualizar = (tJugador *)org;

    jugador->puntos = actualizar->puntos;
}

void verJugador (const void *dato){
    tJugador *jugador =(tJugador *) dato;
    printf("\nNOMBRE    PUNTAJE\n");
    printf("%s        %d\n", jugador->nombre, jugador->puntos);
}

