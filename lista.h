#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIEN 1
#define SIN_MEMORIA -2
#define MEMORIA_VACIA -3
#define MINIMO(X, Y) ((X)<(Y)?(X):(Y))

#define TAMNOMBRE 100

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;
void crearLista(tLista *pl);
int listaVacia(const tLista *pl);
int listaLlena(const tLista *pl, size_t cantbyte);
int vaciarLista(tLista *pl);
int ponerEnLista(tLista *pl, const void *dato, size_t cantbyte);
int sacarDeLista(tLista *pl, void *dato, size_t cantbyte);
void mostrarLista(const tLista *pl, void(*show)(const void *dato));





void ver (const void *dato);
#endif // LISTA_H_INCLUDED
