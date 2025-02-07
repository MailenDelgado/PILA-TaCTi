#include "funciones.h"
#include "lista.h"

typedef struct{
    char nombre[TAMNOMBRE];
    int puntaje;
}tJugador;

void Jugar()
{
    ///cambiar todas las variables globales por macros
    tLista list_jugadores;
    tJugador jugador;
    crearLista(&list_jugadores);
    ///char cad[TAMNOMBRE]; ///despues se puede cambiar por una macro
    do
    {
    system("cls");
    printf("\t\t\t----------------\n");
    printf("ingrese los nombres de los jugadores o para terminar ingrese 0: \n");
//    scanf("%s", cad);
//    if(!listaLlena(&jugadores, sizeof(cad)) && strcmp(cad,"0"))
//        ponerEnLista(&jugadores, cad, sizeof(cad));
//
//    }while(strcmp(cad, "0"));
     scanf("%s", jugador.nombre);
    if(!listaLlena(&list_jugadores, sizeof(tJugador)) && strcmp(jugador.nombre,"0"))
        ponerEnLista(&list_jugadores, jugador.nombre, sizeof(tJugador));

    }while(strcmp(jugador.nombre, "0"));

    mostrarLista(&list_jugadores, ver);
    system("pause");

}

void VerRankingEquipo()
{

}
