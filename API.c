#include "API.h"

// Funcion de escritura para manejar la respuesta de cURL
size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->response, mem->size + total_size + 1);
    if (ptr == NULL) {
        return 0;
    }

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, total_size);
    mem->size += total_size;
    mem->response[mem->size] = '\0';

    return total_size;
}

// Funcion para recuperar los datos de la API
void recuperar_de_api(void) {
    system("cls");/// limpiamos la pantalla
    tLista listaJug;
    tJugador jug;
    crearLista(&listaJug);
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error al inicializar cURL\n");
        return;
    }

    struct Memory chunk = { .response = malloc(1), .size = 0 };
    if (chunk.response == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        curl_easy_cleanup(curl);
        return;
    }
    chunk.response[0] = '\0';

    curl_easy_setopt(curl, CURLOPT_URL, URL_API2);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error en la peticion GET: %s\n", curl_easy_strerror(res));
    } else {

        // Validar si la respuesta est� vac�a o solo contiene "[]"
        if (chunk.response == NULL || strlen(chunk.response) == 0 || strcmp(chunk.response, "[]") == 0) {
            printf("No hay datos disponibles en la API.\n");
        } else {
            // Parsear JSON
            cJSON *json_respuesta = cJSON_Parse(chunk.response);

            if (!json_respuesta) {
                printf("Error al parsear JSON: %s\n", cJSON_GetErrorPtr());
            } else {
                // La API devuelve un array, no un objeto
                if (!cJSON_IsArray(json_respuesta)) {
                    printf("El JSON no es un array como se esperaba.\n");
                } else {
                    int num_jugadores = cJSON_GetArraySize(json_respuesta);
                    for (int i = 0; i < num_jugadores; i++) {
                        cJSON *jugador = cJSON_GetArrayItem(json_respuesta, i);
                        cJSON *nombre = cJSON_GetObjectItem(jugador, "nombreJugador");
                        cJSON *puntos = cJSON_GetObjectItem(jugador, "puntaje");

                        memcpy(jug.nombre, nombre->valuestring, sizeof(jug.nombre));
                        jug.puntos = puntos->valueint;
                        ponerEnLista(&listaJug, &jug, sizeof(tJugador));
                    }
                }
                cJSON_Delete(json_respuesta);
            }
        }
    }
    ordenarLista(&listaJug, comparoPorPuntaje);
    grafica(4);
    printf("\n\t\t\t\tNombre:\tPuntos:\n");
    recorroLista(&listaJug, NULL, 0, imprimoRanking);
    // Liberar memoria
    curl_easy_cleanup(curl);
    free(chunk.response);
}
