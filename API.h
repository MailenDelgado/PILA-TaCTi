#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON/cJSON.h"
#include "Juego.h"

#define URL_API "https://algoritmos-api.azurewebsites.net/api/TaCTi"
#define URL_API2 "https://algoritmos-api.azurewebsites.net/api/TaCTi/PILAR"

// Estructura para almacenar la respuesta de la API
struct Memory {
    char *response;
    size_t size;
};

size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);

void recuperar_de_api(void);
void enviar_a_api(const char *codigoGrupo, const char *nombreJugador, int puntos);

#endif // API_H_INCLUDED
