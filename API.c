#include "API.h"

// Funci�n de escritura para manejar la respuesta de cURL
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

int comparar_puntajes(const void *a, const void *b) {
    const cJSON *jsonA = *(const cJSON **)a;
    const cJSON *jsonB = *(const cJSON **)b;

    cJSON *scoreA = cJSON_GetObjectItemCaseSensitive(jsonA, "puntaje");
    cJSON *scoreB = cJSON_GetObjectItemCaseSensitive(jsonB, "puntaje");

    return (scoreB->valuedouble - scoreA->valuedouble);
}

void mostrarLista(const tLista *pl, void(*show)(const void *dato)){
    tJugador *jugador = (tJugador*)pl;
    printf("%s\t%d\n", jugador->nombre, jugador->puntos);
}

// Funci�n para recuperar los datos de la API
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
//        printf("Respuesta de la API:\n%s\n", chunk.response);

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

//                        if (nombre && puntos) {
//                            printf("Jugador: %s, Puntos: %d\n", nombre->valuestring, puntos->valueint);
//                        }
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

// Funci�n para enviar los datos a la API
void enviar_a_api(const char *codigoGrupo, const char *nombreJugador, int puntos) {

    // Crear el objeto JSON ra�z
    cJSON *json_raiz = cJSON_CreateObject();
    cJSON_AddStringToObject(json_raiz, "CodigoGrupo", codigoGrupo);

    // Crear el array "Jugadores"
    cJSON *array_jugadores = cJSON_CreateArray();
    cJSON *json_jugador = cJSON_CreateObject();

    cJSON_AddStringToObject(json_jugador, "nombre", nombreJugador);
    cJSON_AddNumberToObject(json_jugador, "puntos", puntos);

    // Agregar el jugador al array
    cJSON_AddItemToArray(array_jugadores, json_jugador);

    // Agregar el array al objeto ra�z
    cJSON_AddItemToObject(json_raiz, "Jugadores", array_jugadores);

    // Convertir a cadena JSON
    char *json_str = cJSON_PrintUnformatted(json_raiz);
    if (!json_str) {
        fprintf(stderr, "Error al generar JSON\n");
        cJSON_Delete(json_raiz);
        return;
    }
    printf("JSON enviado:\n%s\n", json_str);

    // Inicializar curl
    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;

        // Configurar URL
        curl_easy_setopt(curl, CURLOPT_URL, URL_API);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Configurar headers (indicamos que enviamos JSON)
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Configurar datos a enviar
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Ejecutar la petici�n
        res = curl_easy_perform(curl);

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        printf("Codigo de respuesta HTTP: %ld\n", response_code);

        if (res != CURLE_OK) {
            fprintf(stderr, "Error en la peticion: %s\n", curl_easy_strerror(res));
        } else {
            printf("Datos enviados con exito\n");
        }

        // Liberar recursos
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    // Liberar memoria JSON
    cJSON_Delete(json_raiz);
    free(json_str);
}
