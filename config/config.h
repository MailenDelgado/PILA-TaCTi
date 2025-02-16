#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdio.h>
#define NOMBRE_ARCH_CONFIG "config/config.txt"
#define MAX_URL 259
#define MAX_COD 50

typedef struct
{
    char url[MAX_URL];
    char codGrupo[MAX_COD];
    int cantPartidas;
} tConfig;

int cargarConfig(const char *nombreArchivo, tConfig *confi);
void mostrarConfig(tConfig *confi);

#endif // CONFIG_H_INCLUDED
