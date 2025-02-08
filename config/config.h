#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdio.h>

#define MAX_URL 259
#define MAX_COD 50

typedef struct
{
    char url[MAX_URL];
    char codGrupo[MAX_COD];
    unsigned cantPartidas;
} tConfig;

int cargarConfig(const char *nombreArchivo, tConfig *confi);
#endif // CONFIG_H_INCLUDED
