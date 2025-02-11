#include "cabeceraLista.h"


void crearLista(tLista* pl)
{
    *pl = NULL;
}

int listaVacia(const tLista* pl)
{
    return *pl == NULL;
}

int listaLlena(const tLista* pl, unsigned cantbyte)
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

int ponerEnLista(tLista* pl, const void* dato, unsigned cantbyte)
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
        printf("no se pudo reservar memoria2");
        free(nue);
        return SIN_MEMORIA;
    }
    memcpy(nue->info, dato, cantbyte);
    nue->tamInfo = cantbyte;
    nue->sig = *pl;
    *pl = nue;

    return BIEN;
}

int sacarDeLista(tLista* pl, void* dato, unsigned cantbyte)
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

void *buscarporPos(const tLista *pl, int pos){
        int i=0;

        while(*pl && i<pos){
            pl = &(*pl)->sig;
            i++;
        }

        return (*pl)->info;

}

int actualizaEnPosLista(tLista *pl, const void *dato, unsigned cantbyte, int pos, void (*actualizardato)(void *dest, const void *org)){
    int i=0;

    while(*pl && i<pos){
        pl=&(*pl)->sig;
        i++;
    }
    if(i==pos && *pl){
    actualizardato((*pl)->info, dato);
    return BIEN;
    }
    return 0; //no encontró la posicion

}


