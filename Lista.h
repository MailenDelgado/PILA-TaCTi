#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))

typedef struct sNodo{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista *pl);
int ponerEnLista(tLista *pl, const void *pd, unsigned tam);
int sacarPrimeroDeLista(tLista *pl, void *pd, unsigned tam);
int verPrimeroDeLista(tLista *pl, void *pd, unsigned tam);
void recorroLista(tLista *pl, void *pd, unsigned tam, int (*accion)(const void *, const void *));
int modificoOrdenLista(const void *pd1, const void *pd2);
void ordenarLista(tLista *pl, int (*cmp)(const void*, const void*));
int comparoPorOrden(const void *d1, const void *d2);
int imprimoOrden(const void*, const void*);

#endif // LISTA_H_INCLUDED
