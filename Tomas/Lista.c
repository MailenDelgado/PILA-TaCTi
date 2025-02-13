#include "TACTI\Lista.h"

void crearLista(tLista *pl){
    *pl = NULL;
}

int ponerEnLista(tLista *pl, const void *pd, unsigned tam){
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));
    if(!nue || !(nue->info = malloc(tam)))
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;
    nue->sig = *pl;
    *pl = nue;
    return 1;
}

int sacarPrimeroDeLista(tLista *pl, void *pd, unsigned tam){
    if(!(*pl))
        return 0;//PILA_VACIA
    tNodo *aux = *pl;
    *pl = aux->sig;
    memcpy(pd, aux->info, MINIMO(tam, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}

int verPrimeroDeLista(tLista *pl, void *pd, unsigned tam){
    if(!(*pl))
        return 0;//PILA_VACIA
    memcpy(pd, (*pl)->info, MINIMO(tam, (*pl)->tamInfo));
    return 1;
}


void recorroLista(tLista *pl, void *pd, unsigned tam, int (*accion)(const void *, const void *)){
    int i = 0;
    while(*pl)
    {
        accion((*pl)->info, pd + i);
        i += sizeof(int);
        pl = &(*pl)->sig;
    }
}

void ordenarLista(tLista *pl, int (*cmp)(const void *, const void*)){
    tLista *pri = pl;
    if(!(*pl))
        return;
    while((*pl)->sig)
    {
        if(cmp((*pl)->info, (*pl)->sig->info) > 0)
        {
            tLista *q = pri;
            tNodo *aux = (*pl)->sig;
            (*pl)->sig = aux->sig;
            while(cmp((*q)->info, aux->info) < 0)
                q = &(*q)->sig;
            aux->sig = *q;
            *q = aux;
        }
        else
            pl = &(*pl)->sig;
    }
}

