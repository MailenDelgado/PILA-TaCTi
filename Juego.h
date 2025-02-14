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

int bloquearVictoria(int *f, int *c, char tablero[3][3], char *jugador);
void cambiarSorteo(int *sorteo);
void cambiarJugador(char *jugador);
int comparoPorOrden(const void *d1, const void *d2);
int imprimoOrden(const void *d1, const void *d2);
void imprimirTablero(char tablero[3][3]);
void imprimirTableroEnArchivo(FILE *, char tablero[3][3]);
void inicializarTablero(char tablero[3][3]);
int intentarGanar(int *f, int *c, char tablero[3][3], char *jugador);
void jugarTurno(int opc, char tablero[3][3], char *jugador);
int modificoOrdenLista(const void *pd1, const void *pd2);
int sorteoSimbolo(void);
void sorteoOrden(int n, int *vec);
int verificarGanador(char tablero[3][3]);
int verificarEmpate(char tablero[3][3]);

int jugar(void);

int jugar2(int cantPartidas);
int ingresarJugadores(tLista *pl, void *pd, unsigned tam, int *val);

#endif // JUEGO_H_INCLUDED
