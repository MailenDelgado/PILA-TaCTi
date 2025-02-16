#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "Lista.h"
#include "config/config.h"
#include <time.h>
#define TAMNOMBRE 20
#define TAM 3

typedef struct{
    char nombre[TAMNOMBRE];
    int puntos;
}tJugador;

typedef struct{
    int numPartida;
    int numJugador;
    char jugador[TAMNOMBRE];
    char tablero[TAM][TAM];
    int puntaje;
    char ganador[TAMNOMBRE];
}tPartida;

void menu(void);

int iniciarJuego(void);

int jugar(char tablero[TAM][TAM]);

int ingresoJugadores(tLista *list_jugadores, int *cantidad);

void inicializarTablero(char tablero[TAM][TAM]);

void imprimirTablero( char tablero[TAM][TAM]);

int verificarGanador( char tablero[TAM][TAM]);

int verificarEmpate( char tablero[TAM][TAM]);

void jugarTurno( char tablero[TAM][TAM],char jugador, int opc);

int intentarGanar(int *f, int *c, char tablero[3][3], char *jugador);

int bloquearVictoria(int *f, int *c, char tablero[3][3], char *jugador);

int verificafilacol(int fila, int columna);

int sortearJugadores(tLista *list_jugadores, int cantidad, int *orden);

char sortearSimbolo(void);

void sorteo(int *indices, int n);

int generarInforme(tLista *list_partidas, tLista *list_jugadores);

void generarRanking(tLista *pl, FILE *pf);

int mostrarJugadores(const void *, const void *);

void guardarPartida(tLista *list_partidas, char tablero[TAM][TAM],int numPartida, int numJugador,const char *ganador, int puntaje, tJugador jugador);

void verJugador (const void *dato);

void actualizardato(void *dest, const void *org);

int comparoPorPuntaje(const void *d1, const void *d2);

void imprimirTableroEnArchivo(FILE *pf, char tablero[3][3]);

int imprimoRanking(const void *d1, const void *d2);

int imprimoRankingEnArchivo(const void *d1, const void *d2);

void lecturaDeConfiguracion(void);

void verRanking(void);

int finalizaJuego(char tablero[3][3], char *jugador, int *opc, int band);

void grafica(void);
#endif // JUEGO_H_INCLUDED
