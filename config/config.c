#include "config.h"

int cargarConfig(const char *nombreArchivo, tConfig *confi)
{
    FILE *pf;

    pf = fopen(nombreArchivo, "rt");
    if(!pf)
    {
        puts("Error al abrir el archivo de configuración");
        return 0;//ERROR_ARCH
    }
    if(fscanf(pf,"%259[^|]|%50[^\n]", confi->url, confi->codGrupo) != 2)
    {
        fclose(pf);
        puts("Error al leer la configuración (URL y Código).");
        return 0; // ERROR_ARCH
    }
    if(fscanf(pf, "%u", &confi->cantPartidas) != 1)
    {
        fclose(pf);
        puts("Error al leer la cantidad de partidas.");
        return 0; // ERROR_ARCH
    }

    fclose(pf);

    return 1;//TODO_OK
}

void mostrarConfig(tConfig *confi)
{
    printf("===============Configuraciones===============\n");
    printf("UrlApi: %s\n", confi->url);
    printf("Codigo del grupo: %s\n", confi->codGrupo);
    printf("Cantidad de partidas: %u\n", confi->cantPartidas);
    //printf("URL completa: %s/%s", confi->url, confi->codGrupo);
}
