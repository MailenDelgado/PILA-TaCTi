#include "Juego.h"
#include "API.h"
//puntajes
#define GANAR 3
#define PERDER -1
#define EMPATE 2

void menu(void)
{
    char op;
    printf("\n\tElija una opcion: \n\t[A]Jugar\n\t[B]Ver ranking equipo\n\t[C]Salir\n");
    scanf("%s", &op);
    if(op == 'A' || op == 'a')
    {

        iniciarJuego();
        pausarPantalla();
        limpiarPantalla();
        grafica(0);
        menu();
    }
    else if((op == 'B') || (op == 'b'))
    {

        printf("Ver ranking equipo\n");
        recuperar_de_api();
        pausarPantalla();
        limpiarPantalla();
        grafica(0);
        menu();
    }
    else if((op == 'C') || (op == 'c'))
        printf("Salir");
    else
    {
        printf("Opcion incorrecta\n");
//      limpiarPantalla(); ///lo malo de esta linea es que nunca va mostrar "Opcion incorrecta", en caso contrario comentarla
        grafica(0);
        menu();
    }
}

int iniciarJuego()
{
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
    tJugador *jugador;//es un puntero al jugador encontrado en la lista

    cargarConfig(NOMBRE_ARCH_CONFIG, &config);

    cantPartidas = config.cantPartidas;

    resultado = ingresoJugadores(&list_jugadores,&cantidadJugadores) ;

    if(!resultado) //si no se ingresaron jugadores vuelve al menu
        return 0;

    //pedir memoria para el vector de ordenamiento
    orden= malloc(cantidadJugadores * sizeof(int));

    if (orden == NULL)
    {
        printf("Error al asignar memoria para vector de Orden\n");
        return 0;
    }

    porden = orden;

    // Inicializa la semilla para los numeros aleatorios
    srand(time(NULL));

    sortearJugadores(&list_jugadores,cantidadJugadores,orden);

    crearLista(&list_partidas);
    limpiarPantalla();

    //Partidas
    do
    {
        jugador = buscarporPos(&list_jugadores,*porden); //obtener jugador segun su posicion en la lista

        for(i=0; i<cantPartidas; i++)
        {
            limpiarPantalla();
            printf("\n\t=====================================================");
            printf("\n\tES EL TURNO DE: %s. Partida %d de %d\n", jugador->nombre,i+1,cantPartidas);

            resultado = jugar(tablero);

            if(!resultado)
            {
                free(orden);
                vaciarLista(&list_jugadores);
                return 0;
            }


            if(resultado == GANAR)
            {
                strcpy(ganador,jugador->nombre);
                grafica(1);
            }
            else if(resultado == PERDER)
            {
                strcpy(ganador,"MAQUINA");
                grafica(2);
            }
            else
            {
                strcpy(ganador,"EMPATE");
                grafica(3);
            }

            jugador->puntos += resultado; //actualizo puntaje y lo muestro
            printf("\nPuntaje de %s es %d\n",jugador->nombre, jugador->puntos );
            pausarPantalla();

            guardarPartida(&list_partidas,tablero,i+1,*porden,ganador,resultado,*jugador);
        }

        actualizaEnPosLista(&list_jugadores,jugador,sizeof(tJugador), *porden, actualizardato); //actualizo el puntaje del jugador en la lista

        porden++;
        njugador++;
    }
    while( njugador < cantidadJugadores );

    free(orden);

    generarInforme(&list_partidas, &list_jugadores);

    vaciarLista(&list_jugadores);
    vaciarLista(&list_partidas);
    return 1;
}

int ingresoJugadores(tLista *list_jugadores, int *cantidad)
{
    int r,i=1;
    tJugador jugador;
    crearLista(list_jugadores);
    limpiarPantalla();
    printf("\n\t\t ========================================================");
    printf("\n\t\t|\t\t   INGRESO DE JUGADORES                  |");
    printf("\n\t\t|\t\t   --------------------                  |");
    printf("\n\t\t|\t Ingrese el nombre de los jugadores de su equipo.|");
    printf("\n\t\t|\t\t Para Finalizar ingrese [0].             |");
    printf("\n\t\t ========================================================\n\n");

    do
    {
        printf("Jugador %d: ",i);

        scanf("%19s", jugador.nombre);
        jugador.puntos = 0; //inicializo todos los puntajes en 0
        r=listaLlena(list_jugadores, sizeof(tJugador));

        if (!r && strcmp(jugador.nombre,"0"))  ///Si la lista no esta llena y el nombre del jugador no es 0
        {
            if((strcmp(jugador.nombre,"A") >= 0 && strcmp(jugador.nombre,"Z") <= 0) ||
                    (strcmp(jugador.nombre,"a") >= 0 && strcmp(jugador.nombre,"z") <= 0))///si por error ingresa un nombre de un solo caracter que no sea una letra(como por ejemplo numeros y simbolos)
            {
                ponerEnLista(list_jugadores, &jugador, sizeof(tJugador));
                (*cantidad)++;
                i++;
            }
            else
            {
                //limpiarPantalla();/// se puede comentar para limpie la pantalla
                printf("Ingreso por error un numero o simbolo. ingrese de vuelta un nombre\n");
                pausarPantalla();

            }
        }
        else if(r)
        {
            printf("Error al ingresar nombre, LISTA LLENA ");
            return 0;
        }

    }
    while(strcmp(jugador.nombre, "0"));

    if(!*cantidad)
    {
        return 0;
    }
    return 1;
}

// Sorteo de jugadores
int sortearJugadores(tLista *list_jugadores, int cantidad, int *orden)
{
    int i;
    tJugador *jugador;
    sorteo(orden, cantidad);
    limpiarPantalla();
    printf("\n\t\t =========================================");
    printf("\n\t\t|\tOrden aleatorio de jugadores:     |");
    printf("\n\t\t|\t----------------------------      |");
    printf("\n\t\t =========================================\n\n");
    for (i = 0; i < cantidad; i++)
    {
        jugador = (tJugador *)buscarporPos(list_jugadores,orden[i]);
        if(jugador)
        {
            printf(" Jugador %d: %s\n", i + 1, jugador->nombre);
        }
        else
        {
            printf("Jugador %d: (No encontrado)",i+1); /// esta linea nunca se uso o nunca se va convocar por pantalla
        }
    }
    pausarPantalla();
    return 1;
}

void sorteo(int *indices, int n)   ///fisher yates: algoritmo de desordenamiento aleatorio
{
    int i,
        j,
        temp;
    ///cargo el vector con el numero de su indice
    for (i = 0; i < n; i++)
    {
        indices[i] = i;
    }
    for (i = n - 1; i > 0; i--)   // empieza desde el ultimo
    {
        j = rand() % (i + 1); //elije un indice aleatorio entre 0 e i
        temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp; //intercambia el ultimo con el indice elegido
    }
}

int jugar(char tablero[TAM][TAM])
{
    int juegoTerminado = 0,
        opc = 0,  //indica si juega el humano "0" o la maquina "1" a lo largo de los turnos.
        entradaValida;
    char jugador = sortearSimbolo(); //se sortea el simbolo con el que jugará la persona. Si sale 0 es O, si sale 1 es X.
    while(opc != 1)
    {
        do
        {
            printf("\nListo para jugar? ([1] SI, [0] NO): ");
            entradaValida = scanf("%d", &opc);/// scanf me duelve 0 si se ingreso un caracter o un simbolo, en caso contrario me devuelve 1
            if (entradaValida != 1 || (opc != 0 && opc != 1))
            {
                printf("Entrada invalida. Ingrese 0 o 1.\n");
                limpiarBuffer();
            }
        }
        while (entradaValida != 1 || (opc != 0 && opc != 1));   /// Se repite hasta que ingrese 0 o 1
        if (opc == 0)
        {
            do
            {
                printf("\nVolver al menu? ([1] SI, [0] NO): ");
                entradaValida = scanf("%d", &opc);
                if (entradaValida != 1)
                {
                    printf("Entrada invalida. Ingrese 0 o 1.\n");
                    limpiarBuffer();
                }
                else
                {
                    if(opc == 1)/// regreso al menu
                        return 0;
                }
            }
            while (entradaValida != 1 || (opc != 0 && opc != 1));   /// Se repite hasta que ingrese 0 o 1
            if (opc == 0)
            {
                opc = -1;  /// Para que vuelva a preguntar "Listo para jugar?"
            }
        }
    }
    inicializarTablero(tablero);

    if (jugador == 'X')       //Si en el sorteo salio X comienza el jugando el humano opc=0
    {
        opc = 0;
        printf("\n\t Sos la X. Empezas vos\n");
    }
    else                      //si salio sorteado el O comienza jugando la maquina opc=1
    {
        opc = 1;
        jugador ='X'; //Debo cambiar a X para que el bot comience jugando con el simbolo correcto.
        printf("\n\t Sos el O. Empieza la IA.\n");
    }
    printf("\t-------------------------\n");
    printf("\t=====================================================\n");
    pausarPantalla();
    limpiarPantalla();

    while (!juegoTerminado)
    {
        juegoTerminado = finalizaJuego(tablero, &jugador, &opc);
    }

    return juegoTerminado;

}

char sortearSimbolo(void)
{
    int orden[2];
    sorteo(orden, 2);                    //EL PRIMER ELEMENTO ES EL SIMBOLO CON EL QUE EMPEZAR� EL USUARIO
    return (orden[0] == 0) ? 'O' : 'X'; //Si no hubo intercambio de indices entonces el usuario empieza con O, sino con X.
}

void inicializarTablero(char tablero[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tablero[i][j] = ' ';  // El tablero comienza vac�o
        }
    }
}

void imprimirTablero(char tablero[3][3])
{
    printf("\n");
    printf("\tCol Col Col\n");
    printf("\t 1   2   3\n");

    for (int i = 0; i < 3; i++)
    {
        printf("Fila %d",i+1);
        printf("\t");
        for (int j = 0; j < 3; j++)
        {
            printf(" %c ", tablero[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("\t---+---+---\n");
    }
    printf("\n");
}

void jugarTurno(char tablero[TAM][TAM],char jugador,int opc)
{
    int columna,
        fila,
        result,
        entradaValida;
    if(opc == 1) //juega bot segun estrategias
    {
        if(intentarGanar(&fila, &columna, tablero, &jugador)== 1)
        {
            printf("El bot ha jugado en la casilla (%d, %d)\n", fila, columna);
        }
        else if(bloquearVictoria(&fila, &columna, tablero, &jugador)== 1)
        {
            printf("El bot ha jugado en la casilla (%d, %d)\n", fila, columna);
        }
        else
        {
            // Bot: elegir un movimiento aleatorio
            int movimientoValido = 0;
            while (!movimientoValido)
            {
                fila = rand() % 3 + 1;
                columna = rand() % 3 + 1;
                if (tablero[fila-1][columna-1] == ' ')
                {
                    movimientoValido = 1;
                }
            }
            printf("El bot ha jugado en la casilla (%d, %d)\n", fila, columna);
        }
    }
    else
    {
        // Jugador humano: ingresar fila y columna
        do
        {
            //por si ingresa un caracter o un simbolo por error
            entradaValida = 0;
            while(!entradaValida)
            {
                printf("Jugador %c, ingresa fila (1-3) y columna (1-3): ", jugador);
                if((scanf("%d %d", &fila, &columna)) == 2)
                {
                    entradaValida = 1;
                }
                else
                {
                    limpiarBuffer();
                }
            }

            result = verificafilacol(fila,columna);
            if(!result)
            {
                printf("Ingrese un numero de fila y columna validos, separados por un espacio.\n");
            }
        }
        while(!result);
        // Verificar si la casilla est� vac�a
        if (tablero[fila-1][columna-1] == ' ')
        {
            tablero[fila-1][columna-1] = jugador;
        }
        else
        {
            printf("Casilla ocupada. Intenta nuevamente.\n");
            jugarTurno(tablero, jugador, 0);  // Reintentar si la casilla ya esta ocupada
            return;
        }
    }
    tablero[fila-1][columna-1] = jugador;
}

//Funciones de estrategia bot
int intentarGanar(int *f, int *c, char tablero[3][3], char *jugador)
{
    // Verificar filas
    for (int i = 0; i < 3; i++)
    {
        if (tablero[i][0] == tablero[i][1] && tablero[i][0] != ' ' && tablero[i][0] == *jugador && tablero[i][2] == ' ')
        {
            *f = i+1;
            *c = 3;
            return 1;
        }
        else if(tablero[i][1] == tablero[i][2] && tablero[i][1] != ' ' && tablero[i][1] == *jugador && tablero[i][0] == ' ')
        {
            *f = i+1;
            *c = 1;
            return 1;
        }
        else if(tablero[i][0] == tablero[i][2] && tablero[i][0] != ' ' && tablero[i][0] == *jugador && tablero[i][1] == ' ')
        {
            *f = i+1;
            *c = 2;
            return 1;
        }
    }

    // Verificar columnas
    for (int i = 0; i < 3; i++)
    {
        if (tablero[0][i] == tablero[1][i] && tablero[0][i] != ' ' && tablero[0][i] == *jugador && tablero[2][i] == ' ')
        {
            *f = 3;
            *c = i+1;
            return 1;
        }
        else if(tablero[1][i] == tablero[2][i] && tablero[1][i] != ' ' && tablero[1][i] == *jugador && tablero[0][i] == ' ')
        {
            *f = 1;
            *c = i+1;
            return 1;
        }
        else if(tablero[0][i] == tablero[2][i] && tablero[0][i] != ' ' && tablero[0][i] == *jugador && tablero[1][i] == ' ')
        {
            *f = 2;
            *c = i+1;
            return 1;
        }
    }

    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[0][0] != ' ' && tablero[0][0] == *jugador && tablero[2][2] == ' ')
    {
        *f = 3;
        *c = 3;
        return 1;
    }
    if(tablero[1][1] == tablero[2][2] && tablero[1][1] != ' ' && tablero[1][1] == *jugador && tablero[0][0] == ' ')
    {
        *f = 1;
        *c = 1;
        return 1;
    }
    if(tablero[0][0] == tablero[2][2] && tablero[0][0] != ' ' && tablero[0][0] == *jugador && tablero[1][1] == ' ')
    {
        *f = 2;
        *c = 2;
        return 1;
    }

    if (tablero[0][2] == tablero[1][1] && tablero[0][2] != ' ' && tablero[0][2] == *jugador && tablero[2][0] == ' ')
    {
        *f = 3;
        *c = 1;
        return 1;
    }

    if(tablero[1][1] == tablero[2][0] && tablero[1][1] != ' ' && tablero[1][1] == *jugador && tablero[0][2] == ' ')
    {
        *f = 1;
        *c = 3;
        return 1;
    }
    return 0;
}

int bloquearVictoria(int *f, int *c, char tablero[3][3], char *jugador)
{
    // Verificar filas
    for (int i = 0; i < 3; i++)
    {
        if (tablero[i][0] == tablero[i][1] && tablero[i][0] != ' ' && tablero[i][0] != *jugador && tablero[i][2] == ' ')
        {
            *f = i+1;
            *c = 3;
            return 1;
        }
        else if(tablero[i][1] == tablero[i][2] && tablero[i][1] != ' ' && tablero[i][1] != *jugador && tablero[i][0] == ' ')
        {
            *f = i+1;
            *c = 1;
            return 1;
        }
        else if(tablero[i][0] == tablero[i][2] && tablero[i][0] != ' ' && tablero[i][0] != *jugador && tablero[i][1] == ' ')
        {
            *f = i+1;
            *c = 2;
            return 1;
        }
    }

    // Verificar columnas
    for (int i = 0; i < 3; i++)
    {
        if (tablero[0][i] == tablero[1][i] && tablero[0][i] != ' ' && tablero[0][i] != *jugador && tablero[2][i] == ' ')
        {
            *f = 3;
            *c = i+1;
            return 1;
        }
        else if(tablero[1][i] == tablero[2][i] && tablero[1][i] != ' ' && tablero[1][i] != *jugador && tablero[0][i] == ' ')
        {
            *f = 1;
            *c = i+1;
            return 1;
        }
        else if(tablero[0][i] == tablero[2][i] && tablero[0][i] != ' ' && tablero[0][i] != *jugador && tablero[1][i] == ' ')
        {
            *f = 2;
            *c = i+1;
            return 1;
        }
    }

    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[0][0] != ' ' && tablero[0][0] != *jugador && tablero[2][2] == ' ')
    {
        *f = 3;
        *c = 3;
        return 1;
    }
    if(tablero[1][1] == tablero[2][2] && tablero[1][1] != ' ' && tablero[1][1] != *jugador && tablero[0][0] == ' ')
    {
        *f = 1;
        *c = 1;
        return 1;
    }
    if(tablero[0][0] == tablero[2][2] && tablero[0][0] != ' ' && tablero[0][0] != *jugador && tablero[1][1] == ' ')
    {
        *f = 2;
        *c = 2;
        return 1;
    }

    if (tablero[0][2] == tablero[1][1] && tablero[0][2] != ' ' && tablero[0][2] != *jugador && tablero[2][0] == ' ')
    {
        *f = 3;
        *c = 1;
        return 1;
    }

    if(tablero[1][1] == tablero[2][0] && tablero[1][1] != ' ' && tablero[1][1] != *jugador && tablero[0][2] == ' ')
    {
        *f = 1;
        *c = 3;
        return 1;
    }
    return 0;
}

int verificafilacol(int fila, int columna)
{
    if(fila<1 || fila>TAM)
    {
        return 0;
    }
    if(columna<1 || columna>TAM)
    {
        return 0;
    }
    return 1;
}

// Funci�n para verificar si hay un ganador
int verificarGanador(char tablero[3][3])
{
    // Verificar filas
    for (int i = 0; i < 3; i++)
    {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != ' ')
        {
            return 1;
        }
    }

    // Verificar columnas
    for (int i = 0; i < 3; i++)
    {
        if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != ' ')
        {
            return 1;
        }
    }

    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != ' ')
    {
        return 1;
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != ' ')
    {
        return 1;
    }

    return 0;  // No hay ganador
}

// Funcion para verificar si el juego termin� en empate
int verificarEmpate(char tablero[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tablero[i][j] == ' ')
            {
                return 0;  // Hay al menos una casilla vac�a
            }
        }
    }
    return 1;  // No hay casillas vacias, es empate
}

void guardarPartida(tLista *list_partidas, char tablero[TAM][TAM],int numPartida, int numJugador,const char *ganador, int puntaje, tJugador jugador)
{
    int result;
    tPartida partida;
    memcpy(partida.tablero, tablero, sizeof(partida.tablero));
    partida.numJugador=numJugador;
    partida.puntaje=puntaje;
    partida.numPartida=numPartida;
    strcpy(partida.ganador,ganador);
    strcpy(partida.jugador,jugador.nombre);

    result= ponerEnLista(list_partidas,&partida,sizeof(partida));
    if(!result)
    {
        printf("\nNO SE PUDO PONER EN LISTA");
        pausarPantalla();
    }
}

int obtengoJugador(const void *a, const void *b)
{
    tJugador *jugadorA = (tJugador*)a;
    tJugador *jugadorB = (tJugador*)b;
    memcpy(jugadorB->nombre, jugadorA->nombre, sizeof(jugadorA->nombre));
    jugadorB->puntos = jugadorA->puntos;
    return 1;
}

int generarInforme(tLista *list_partidas, tLista *list_jugadores)
{
    char nombrearch[40], codigoGrupo[] = "PILAR";
    int i,
        j,
        result;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tPartida partida;

    sprintf(nombrearch,"informe-juego_%04d-%02d-%02d-%02d-%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

    FILE *pl = fopen(nombrearch,"wt");

    if(!pl)
    {
        printf("\nError al crear el informe");
        return 0;
    }

    result=sacarDeLista(list_partidas,&partida,sizeof(partida));

    while(result!=0)
    {
        fprintf(pl,"JUGADOR: %-19s\nPartida: %d\nGanador: %-10s\nPuntaje: %d\n",partida.jugador,partida.numPartida,partida.ganador,partida.puntaje);

        // Escribir el tablero de la partida
        fputs("TABLERO:\n", pl);
        for (i = 0; i < TAM; i++)
        {
            for (j = 0; j < TAM; j++)
            {
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
    recorroListaYmandoDatosAPI(list_jugadores, codigoGrupo, 0, obtengoJugador);
    fclose(pl);
    return 0;
}

void generarRanking(tLista *pl, FILE *pf)
{
    ordenarLista(pl, comparoPorPuntaje);
    fprintf(pf, "\tRanking\n");
    fprintf(pf,"\tNombre \tPuntos\n");
    recorroLista(pl, pf, 0, imprimoRankingEnArchivo);

}

int comparoPorPuntaje(const void *d1, const void *d2)
{
    tJugador *jug1 = (tJugador*)d1;
    tJugador *jug2 = (tJugador*)d2;
    return(jug1->puntos - jug2->puntos);
}

void imprimirTableroEnArchivo(FILE *pf, char tablero[3][3])
{
    fprintf(pf, "\n");
    fprintf(pf, "\tCol Col Col\n");
    fprintf(pf, "\t 1   2   3\n");

    for (int i = 0; i < 3; i++)
    {
        fprintf(pf, "Fila %d",i+1);
        fprintf(pf, "\t");
        for (int j = 0; j < 3; j++)
        {
            fprintf(pf, " %c ", tablero[i][j]);
            if (j < 2) fprintf(pf, "|");
        }
        fprintf(pf, "\n");
        if (i < 2) fprintf(pf, "\t---+---+---\n");
    }
    fprintf(pf, "\n");
}

int imprimoRanking(const void *d1, const void *d2)
{
    tJugador *jugador = (tJugador*)d1;
    printf("\t\t\t\t%s\t%-4d\n", jugador->nombre, jugador->puntos);
    return 1;
}

int imprimoRankingEnArchivo(const void *d1, const void *d2)
{
    FILE *pf = (FILE *)d2;
    tJugador *jugador = (tJugador*)d1;
    fprintf(pf,"\t%s\t%-4d\n", jugador->nombre, jugador->puntos);
    return 1;
}

void actualizardato(void *dest, const void *org)
{
    tJugador *jugador = (tJugador *)dest,
              *actualizar = (tJugador *)org;

    jugador->puntos = actualizar->puntos;
}

void verJugador (const void *dato)
{
    tJugador *jugador =(tJugador *) dato;
    printf("\nNOMBRE    PUNTAJE\n");
    printf("%s        %d\n", jugador->nombre, jugador->puntos);
}

//Funcion que verifica en cada turno si hay un ganador, devuelve 0 si no termino el juego y sino devuelve los puntos que
//le corresponden al jugador humano.
int finalizaJuego(char tablero[3][3], char *jugador, int *opc)
{
    int juegoTerminado = 0;
    imprimirTablero(tablero);

    jugarTurno(tablero, *jugador, *opc); //se juega el turno enviando con OPC quién juega.

    //luego del turno se verifica si hay un ganador o empate.

    if (verificarGanador(tablero))    //Si se gano en este turno, verifica quien gano
    {
        imprimirTablero(tablero);

        printf("Jugador %c ha ganado\n", *jugador);
        system("pause");
//        juegoTerminado = 1;
//        if(band == 1){ //Si X es el humano (por la bandera=1) y el jugador ganador es la X, devuelve 3, sino -1.
//            juegoTerminado = (*jugador == 'X')?3:-1;
//        }
//        else{ //Al contrario, si el humano es O (bandera = 0) y el jugador ganador es el O, devuelve 3, sino -1.
//            juegoTerminado = (*jugador == 'O')?3:-1;
//        }

        juegoTerminado = (*opc == 0)?3:-1;

    }
    else if (verificarEmpate(tablero))
    {
        imprimirTablero(tablero);
        system("pause");
        juegoTerminado = 2;
    }
    if (!juegoTerminado)
    {
        *opc = (*opc == 1) ? 0 : 1;   // Cambia entre 1 y 0 para alternar el turno entre humano y maquina
        *jugador = (*jugador == 'X')? 'O' : 'X';// Cambia entre X y O para alternar el turno
    }
    return juegoTerminado; //si no hubo ganador/empate, devuelve juegoTerminado = 0 para que se juegue el siguiente turno.
}                          //si hubo un ganador/empate, esta funcion devolvera los puntos que le corresponden al usuario.

void recorroListaYmandoDatosAPI(tLista *pl, void *pd, unsigned tam, int (*accion)(const void *, const void *))
{
    tJugador jugador;
    // Crear el objeto JSON raiz
    cJSON *json_raiz = cJSON_CreateObject();
    cJSON_AddStringToObject(json_raiz, "CodigoGrupo", pd);

    // Crear el array "Jugadores"
    cJSON *array_jugadores = cJSON_CreateArray();

    while(*pl)
    {
        accion((*pl)->info, &jugador);
        cJSON *json_jugador = cJSON_CreateObject();
        cJSON_AddStringToObject(json_jugador, "nombre", (const char * const)&jugador.nombre);
        cJSON_AddNumberToObject(json_jugador, "puntos", jugador.puntos);
        // Agregar el jugador al array
        cJSON_AddItemToArray(array_jugadores, json_jugador);
        pl = &(*pl)->sig;
    }

    // Agregar el array al objeto raiz
    cJSON_AddItemToObject(json_raiz, "Jugadores", array_jugadores);

    // Convertir a cadena JSON
    char *json_str = cJSON_PrintUnformatted(json_raiz);
    if (!json_str)
    {
        fprintf(stderr, "Error al generar JSON\n");
        cJSON_Delete(json_raiz);
        return;
    }
    printf("JSON enviado:\n%s\n", json_str);

    // Inicializar curl
    CURL *curl = curl_easy_init();
    if (curl)
    {
        CURLcode res;

        // Configurar URL
        curl_easy_setopt(curl, CURLOPT_URL, URL_API);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Configurar headers (indicamos que enviamos JSON)
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Configurar datos a enviar
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Ejecutar la peticion
        res = curl_easy_perform(curl);

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        printf("Codigo de respuesta HTTP: %ld\n", response_code);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "Error en la peticion: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("Datos enviados con exito\n");
        }

        // Liberar recursos
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    // Liberar memoria JSON
    cJSON_Delete(json_raiz);
    free(json_str);
}

void grafica(int opc)
{
    if(opc == 0)
    {
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
    }

    if(opc == 1) //victoria
    {
        system("cls");
        printf("\n\t************************************************************************************************");
        printf("\n\t////////////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t**                                                                                            **");
        printf("\n\t**     ___    ___   __    _______    _________    ______    ______     __        __           **");
        printf("\n\t**     \\  \\  /  // |  || /    ___|| |___   ___|| /  __  \\  ||  _  \\   |  ||     /  \\\\         **");
        printf("\n\t**     ___    ___   __    _______    _________    ______    ______     __        __           **");
        printf("\n\t**     \\  \\  /  // |  || /    ___|| |___   ___|| /  __  \\  ||  _  \\   |  ||     /  \\\\         **");
        printf("\n\t**     ___    ___   __    _______    _________    ______    ______     __        __           **");
        printf("\n\t**     \\  \\  /  // |  || /    ___|| |___   ___|| /  __  \\  ||  _  \\   |  ||     /  \\\\         **");
        printf("\n\t**      \\  \\/  //  |  || |   ||         |  ||    | |  | || || |_| ||  |  ||    /    \\\\        **");
        printf("\n\t**       \\    //   |  || |  ||          |  ||    | |  | || |     //   |  ||   / /__\\ \\\\       **");
        printf("\n\t**        \\  //    |  || |   ||___      |  ||    | |__| || ||  |\\  \\  |  ||  /   __   \\\\      **");
        printf("\n\t**         \\//     |__||  \\______||     |__||    |______|| ||__| \\__\\ |__|| /___/  \\___\\\\     **");
        printf("\n\t**                                                                                            **");
        printf("\n\t////////////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t************************************************************************************************\n\n\n");
        printf("\t\t\t Felicitaciones. Te has impuesto con maestria ante la IA.\n\n");
    }
    if(opc == 2) //Derrota
    {
        system("cls");
        printf("\n\t*****************************************************************************************");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t**                                                                                     **");
        printf("\n\t**     _____      ____     _____      _____     _______    _________       __          **");
        printf("\n\t**    |     \\    |  __|| ||  _  \\   ||  _  \\   /  ___  \\  |___   ___||    /  \\\\        **");
        printf("\n\t**     _____      ____     _____      _____     _______    _________       __          **");
        printf("\n\t**    |     \\    |  __|| ||  _  \\   ||  _  \\   /  ___  \\  |___   ___||    /  \\\\        **");
        printf("\n\t**     _____      ____     _____      _____     _______    _________       __          **");
        printf("\n\t**    |     \\    |  __|| ||  _  \\   ||  _  \\   /  ___  \\  |___   ___||    /  \\\\        **");
        printf("\n\t**    |  __  \\   |  |_   || |_| ||  || |_| ||  | |   | ||     |  ||      /    \\\\       **");
        printf("\n\t**    | |  |  || |  __|| ||     //  ||     //  | |   | ||     |  ||     / /__\\ \\\\      **");
        printf("\n\t**    | |__|  || |  |_   ||  |\\  \\  ||  |\\  \\  | |___| ||     |  ||    /   __   \\\\     **");
        printf("\n\t**    |______//  |____|| ||__| \\__\\ ||__| \\__\\ |_______||     |__||   /___/  \\___\\\\    **");
        printf("\n\t**                                                                                     **");
        printf("\n\t**                                                                                     **");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t*****************************************************************************************\n\n\n");
        printf("\t\t\t Tu oponente se impone. Vuelve a intentarlo.\n\n");
    }

    if(opc == 3) //Empate
    {
        system("cls");
        printf("\n\t***************************************************************************");
        printf("\n\t///////////////////////////////////////////////////////////////////////////");
        printf("\n\t**                                                                       **");
        printf("\n\t**     ____    __    __    ______       __       _________    ____       **");
        printf("\n\t**    |   _|| |  \\  /  || |   _  \\     /  \\\\    |___  ___|| |  __||      **");
        printf("\n\t**     ____    __    __    ______       __       _________    ____       **");
        printf("\n\t**    |   _|| |  \\  /  || |   _  \\     /  \\\\    |___  ___|| |  __||      **");
        printf("\n\t**     ____    __    __    ______       __       _________    ____       **");
        printf("\n\t**    |   _|| |  \\  /  || |   _  \\     /  \\\\    |___  ___|| |  __||      **");
        printf("\n\t**    |  |_   |   \\/   || |  |_|  ||  /    \\\\      |  ||    |  |_        **");
        printf("\n\t**    |   _|| |        || |   ___//  / /__\\ \\\\     |  ||    |  __||      **");
        printf("\n\t**    |  |_   |  |\\/|  || |  |      /   __   \\\\    |  ||    |  |_        **");
        printf("\n\t**    |____|| |__|  |__|| |__|     /___/  \\___\\\\   |__||    |____||      **");
        printf("\n\t**                                                                       **");
        printf("\n\t**                                                                       **");
        printf("\n\t///////////////////////////////////////////////////////////////////////////");
        printf("\n\t***************************************************************************\n\n\n");
        printf("\t\t\t Igualados. Nadie pudo vencer.\n\n");
    }

    if(opc == 4) //Ranking
    {
        system("cls");
        printf("\n\t*****************************************************************************************");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t**                                                                                     **");

        printf("\n\t**     _____          __        __     __     __   __     __   __     __    _______    **");
        printf("\n\t**    ||  _  \\       /  \\\\     |  \\   |  ||  |  | /  // |  || |  \\   |  || /   ____||  **");
        printf("\n\t**    || |_| ||     /    \\\\    |   \\  |  ||  |  |/  //  |  || |   \\  |  || |  | ____   **");
        printf("\n\t**    ||     //    / /__\\ \\\\   |  |\\\\ |  ||  |     \\\\   |  || |  |\\\\ |  || |  ||__  || **");
        printf("\n\t**    ||  |\\  \\   /   __   \\\\  |  |\\     ||  |      \\\\  |  || |  |\\     || |  |___| || **");
        printf("\n\t**    ||__| \\__\\ /___/  \\___\\\\ |__| \\____||  |__|\\___\\\\ |__|| |__| \\____|| \\_______//  **");
        printf("\n\t**                                                                                     **");
        printf("\n\t**                                                                                     **");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t*****************************************************************************************\n\n\n");
        printf("\t\t\t Cada punto cuenta, cada victoria te acerca a la cima.\n\n");
    }
}
