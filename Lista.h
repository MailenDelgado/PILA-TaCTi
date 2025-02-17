#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#define BIEN 1
#define SIN_MEMORIA -2
#define MEMORIA_VACIA -3
#define MINIMO(X, Y) ((X)<(Y)?(X):(Y))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista *pl);
int listaVacia(const tLista *pl);
int listaLlena(const tLista *pl, unsigned cantbyte);
int vaciarLista(tLista *pl);
int ponerEnLista(tLista *pl, const void *dato, unsigned cantbyte);
int actualizaEnPosLista(tLista *pl, const void *dato, unsigned cantbyte, int pos, void (*actualizardato)(void *dest, const void *org));
int sacarDeLista(tLista *pl, void *dato, unsigned cantbyte);
void ordenarLista(tLista *pl, int (*cmp)(const void *, const void*));
void recorroLista(tLista *pl, void *pd, unsigned tam, int (*accion)(const void *, const void *));
void *buscarporPos(const tLista *pl, int pos);

#endif // LISTA_H_INCLUDED
