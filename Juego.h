#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Lista.h"

#define VICTORIA 3
#define EMPATE 2
#define DERROTA -1
#define CANT_PARTIDAS 2
#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))
#define N 100//NRO_MAXIMO_DE_JUGADORES

typedef struct{
    char nombre[20];
    unsigned puntos;
    unsigned orden;
}tJugador;

int bloquearVictoria(int *f, int *c);
void cambiarSorteo(int *sorteo);
void cambiarJugador(void);
int comparoPorOrden(const void *d1, const void *d2);
int imprimoOrden(const void *d1, const void *d2);
void imprimirTablero(void);
void imprimirTableroEnArchivo(FILE *);
void inicializarTablero(void);
int intentarGanar(int *f, int *c);
void jugarTurno(int opc);
int modificoOrdenLista(const void *pd1, const void *pd2);
int sorteoSimbolo(void);
void sorteoOrden(int n, int *vec);
int verificarGanador(void);
int verificarEmpate(void);

int jugar(void);

int jugar2(int cantPartidas);
int ingresarJugadores(tLista *pl, void *pd, unsigned tam, int *val);

#endif // JUEGO_H_INCLUDED
