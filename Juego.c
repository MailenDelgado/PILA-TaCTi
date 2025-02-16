#include "Juego.h"
#include "API.h"

void menu(void){
    char op;
    printf("\nElija una opcion: \n[A]Jugar\n[B]Ver ranking equipo\n[C]Salir\n");
    scanf("%s", &op);
    if(op == 'A' || op == 'a')
    {

        iniciarJuego();
        system("cls");
        grafica();
        menu();
    }
    else if((op == 'B') || (op == 'b'))
    {

        printf("Ver ranking equipo\n");
        recuperar_de_api();

        system("pause");
        system("cls");
        grafica();
        menu();
    }
    else if((op == 'C') || (op == 'c'))
        printf("Salir");
    else
    {
        printf("Opcion incorrecta\n");
        system("cls");///lo malo de esta linea es que nunca va mostrar "Opcion incorrecta", en caso contrario comentarla
        grafica();
        menu();
    }
}

int iniciarJuego(){
    int cantidadJugadores=0,
        cantPartidas,
        i = 0,
        njugador=0,
        *orden,
        *porden,
        resultado;
    char ganador[10],
         tablero[TAM][TAM];
    tLista  list_jugadores,
            list_partidas;
    tConfig config;
    tJugador *jugador;//es un puntero porque en realidad es el jugador encontrado en la lista

    cargarConfig(NOMBRE_ARCH_CONFIG, &config);

    cantPartidas = config.cantPartidas;
    resultado = ingresoJugadores(&list_jugadores,&cantidadJugadores) ;

    if(!resultado) //si no se ingresaron jugadores vuelve al menu
        return 0;
    orden= malloc(cantidadJugadores * sizeof(int));

    if (orden == NULL){
        printf("Error al asignar memoria para vector de Orden\n");
        return 0;
    }

    porden = orden;

    // Inicializa la semilla para los numeros aleatorios
    srand(time(NULL));

    sortearJugadores(&list_jugadores,cantidadJugadores,orden);

    crearLista(&list_partidas);
    system("cls");

    //Partidas
    do{
        jugador = buscarporPos(&list_jugadores,*porden); //obtener jugador

        for(i=0;i<cantPartidas;i++){
            printf("\n\tTurno de: %s. Partida %d de %d", jugador->nombre,i+1,cantPartidas);
            resultado = jugar(tablero);

            if(!resultado){
                free(orden);
                vaciarLista(&list_jugadores);
                return 0;
            }

            jugador->puntos += resultado; //actualizo puntaje y lo muestro
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
        printf("INGRESE EL NOMBRE DEL JUGADOR(0 PARA FINALIZAR EL INGRESO DE JUGADORES): \n");

        scanf("%19s", jugador.nombre);
        jugador.puntos = 0; //inicializo todos los puntajes en 0
        r=listaLlena(list_jugadores, sizeof(tJugador));

        if (!r && strcmp(jugador.nombre,"0")){ ///Si la lista no est� llena y el nombre del jugador no es 0
            if((strcmp(jugador.nombre,"A") > 0 && strcmp(jugador.nombre,"Z") < 0) ||
              (strcmp(jugador.nombre,"a") > 0 && strcmp(jugador.nombre,"z") < 0))///si por error un nombre de un solo caracter que no sea una letra(como por ejemplo numeros y simbolos)
              {
                ponerEnLista(list_jugadores, &jugador, sizeof(tJugador));
                (*cantidad)++;
              }else
              {
                //system("cls");/// se puede comentar para limpie la pantalla
                printf("Ingreso por error un numero o simbolo. ingrese de vuelta un nombre\n");
                system("pause");

              }
        }else if(r){
            printf("Error al ingresar nombre, LISTA LLENA ");
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
    for (i = 0; i < cantidad; i++) {
        jugador = (tJugador *)buscarporPos(list_jugadores,orden[i]);
        if(jugador){
        printf(" Jugador %d: %s\n", i + 1, jugador->nombre);
        }
        else{
            printf("Jugador %d: (No encontrado)",i+1); /// esta linea nunca se uso o nunca se va convocar por pantalla
        }
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
        indices[j] = temp; //intercambia el �ltimo con el indice elegido
    }
}

int jugar(char tablero[TAM][TAM]){
    int juegoTerminado = 0,
        opc = 0,
        band = 0;
    char jugador = sortearSimbolo();

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

    if (jugador == 'X') {
        band = 1;
        opc = 0;  // El jugador humano juega si es su turno
        printf("\n\t Sos la X, empezas vos\n");
    }else{
        opc = 1; // El bot juega si es su turno
        jugador ='X'; //EL BOT EMPIEZA CON LA X
        printf("\n\t Sos el O, empieza la maquina\n");
    }
    printf("\t-------------------------\n");
    system("pause");
    system("cls");
    while (!juegoTerminado){
        juegoTerminado = finalizaJuego(tablero, &jugador, &opc, band);
/*        imprimirTablero(tablero);
        jugarTurno(tablero,jugador,opc);
        if (verificarGanador(tablero)){
            imprimirTablero(tablero);
            printf("Jugador %c ha ganado\n", jugador);
            juegoTerminado = 1;

            if(band==1){ //X ES EL HUMANO
                return (jugador == 'X')?3:-1;
            }
            else{
                return (jugador == 'O')?3:-1;
            }

        }else if (verificarEmpate(tablero)) {
            imprimirTablero(tablero);
            printf("Empate. El juego ha terminado.\n");
            juegoTerminado = 1;
            return 2;
        }
        if (!juegoTerminado) {
            opc = (opc == 1) ? 0 : 1;   // Cambia entre 1 y 0 para alternar el turno entre humano y maquina
            jugador = (jugador == 'X')? 'O' : 'X';// Cambia entre X y O para alternar el turno
        }*/
    }
    return juegoTerminado;
}

char sortearSimbolo(void) {
    int orden[2];
    sorteo(orden, 2);                    //EL PRIMER ELEMENTO ES EL SIMBOLO CON EL QUE EMPEZAR� EL USUARIO
    return (orden[0] == 0) ? 'O' : 'X'; //Si no hubo intercambio de indices entonces el usuario empieza con O, sino con X.
}

void inicializarTablero(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = ' ';  // El tablero comienza vac�o
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
    int columna,
        fila,
        r;
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
            r = verificafilacol(fila,columna);
            if(!r){
                printf("Ingrese un numero de fila y columna validos, separados por un espacio.\n");
            }
        }while(!r);
        // Verificar si la casilla est� vac�a
        if (tablero[fila-1][columna-1] == ' ') {
            tablero[fila-1][columna-1] = jugador;
        } else {
            printf("Casilla ocupada. Intenta nuevamente.\n");
            jugarTurno(tablero, jugador, 0);  // Reintentar si la casilla ya est� ocupada
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

// Funci�n para verificar si hay un ganador
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

// Funci�n para verificar si el juego termin� en empate
int verificarEmpate(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') {
                return 0;  // Hay al menos una casilla vac�a
            }
        }
    }
    return 1;  // No hay casillas vac�as, es empate
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

int mostrarJugadores(const void *a, const void *b){
   tJugador * jug = (tJugador *)a;
   enviar_a_api((char*)b, jug->nombre, jug->puntos);
   return 1;
}

int generoAPI(const void *a, const void *b){
    tJugador *jugador = (tJugador*)a;
    enviar_a_api((char*)b,jugador->nombre, jugador->puntos);
    return 1;
}

int generarInforme(tLista *list_partidas, tLista *list_jugadores){
    char nombrearch[40], codigoGrupo[] = "PILAR";
    int i,
        j,
        result;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tPartida partida;

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
     recorroLista(list_jugadores, codigoGrupo, 0, generoAPI);
     fclose(pl);
     return 0;
}

void generarRanking(tLista *pl, FILE *pf){
    ordenarLista(pl, comparoPorPuntaje);
    fprintf(pf, "\tRanking\n");
    fprintf(pf,"\tNombre \tPuntos\n");
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

int finalizaJuego(char tablero[3][3], char *jugador, int *opc, int band){
    int juegoTerminado = 0;
    imprimirTablero(tablero);
    jugarTurno(tablero, *jugador, *opc);
    //system("cls");
    if (verificarGanador(tablero)){
        imprimirTablero(tablero);
        printf("Jugador %c ha ganado\n", *jugador);
        juegoTerminado = 1;
        if(band == 1){ //X ES EL HUMANO
            juegoTerminado = (*jugador == 'X')?3:-1;
        }
        else{
            juegoTerminado = (*jugador == 'O')?3:-1;
        }
    }else if (verificarEmpate(tablero)) {
        imprimirTablero(tablero);
        printf("Empate. El juego ha terminado.\n");
        juegoTerminado = 2;
    }
    if (!juegoTerminado) {
            *opc = (*opc == 1) ? 0 : 1;   // Cambia entre 1 y 0 para alternar el turno entre humano y maquina
            *jugador = (*jugador == 'X')? 'O' : 'X';// Cambia entre X y O para alternar el turno
    }
    return juegoTerminado;
}


void grafica(void){

    printf("\n\t***************************************************************************");
    printf("\n\t///////////////////////////////////////////////////////////////////////////");
    printf("\n\t**                                                                       **");
    printf("\n\t**   _________       __             _______         _________    ___     **");
    printf("\n\t**  |___   ___||    /  \\           /   ____||      |___   ___|| |   ||   **");
    printf("\n\t**      |  ||      / /\\ \\     __   |  ||       __      |  ||    |   ||   **");
    printf("\n\t**      |  ||     /  __  \\   |__|| |  ||___   |__||    |  ||    |   ||   **");
    printf("\n\t**      |__||    /__/  \\ _\\        |_______||          |__||    |___||   **");
    printf("\n\t**                                                                       **");
    printf("\n\t///////////////////////////////////////////////////////////////////////////");
    printf("\n\t***************************************************************************\n\n\n");
    printf("\t\tUn desarrollo de \"PILA\" ");
    printf("\n\t\t\t - DELGADO MAILEN ");
    printf("\n\t\t\t - MAMANI LUCAS ");
    printf("\n\t\t\t - RAMIREZ KEVIN ");
    printf("\n\t\t\t - TESTA TOMAS ");
    printf("\n");


}

