#include "lista.h"

void crearLista(tLista* pl)
{
    *pl = NULL;
}

int listaVacia(const tLista* pl)
{
    return *pl == NULL;
}

int listaLlena(const tLista* pl, size_t cantbyte)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    void *dato = malloc(cantbyte);
    free(dato);
    free(aux);
    return aux == NULL || dato == NULL;
}

int vaciarLista(tLista* pl)
{
    tNodo *elim;
    while (*pl)
    {
        elim = *pl;
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
    return BIEN;
}

int ponerEnLista(tLista* pl, const void* dato, size_t cantbyte)
{
    while(*pl){
        pl=&(*pl)->sig;
    }

    tNodo *nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
    {
        printf("no se pudo reservar memoria1");
        return SIN_MEMORIA;
    }
    nue->info= malloc(cantbyte);
    if(!nue->info)
    {
        printf("no se puedo reservar memoria2");
        free(nue);
        return SIN_MEMORIA;
    }
    memcpy(nue->info, dato, cantbyte);
    nue->tamInfo = cantbyte;
    nue->sig = *pl;
    *pl = nue;

    return BIEN;
}

int sacarDeLista(tLista* pl, void* dato, size_t cantbyte)
{
    tNodo *elim = *pl;

    if(elim == NULL)
        return MEMORIA_VACIA;
    *pl = elim->sig;
    memcpy(dato, elim->info, MINIMO(cantbyte, elim->tamInfo));
    free(elim->info);
    free(elim);

    return BIEN;
}


void mostrarLista(const tLista *pl, void(*show)(const void *dato))
{
    while (*pl)
    {
        show((*pl)->info);
        pl = &(*pl)->sig;
    }
}

void ver (const void *dato)
{
    printf("%s\n", (char*)dato);
}
