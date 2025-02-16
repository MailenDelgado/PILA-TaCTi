# PILA-TaCTi

Este proyecto implementa un minijuego de Tateti (Ta-C-Ti) desarrollado en C, diseñado para ser utilizado en un tótem interactivo en supermercados. Los jugadores pueden enfrentarse a una inteligencia artificial básica, y los resultados de cada partida se registran en un servidor remoto mediante una API.

## Instrucciones del juego
Al iniciar, se presenta un menú interactivo. Las opciones disponibles son:

- **[A] Jugar:** Se le pedirá que cargue los nombres de las personas que van a jugar. Puede ingresar la cantidad de nombres que desee. Una vez que termine de ingresarlos, aparecerá por pantalla el orden en el que jugarán los jugadores, y se le preguntará al primer jugador si está listo. En caso de que sí, inicia el juego.
- **[B] Ver ranking equipo:** Se mostrara por pantalla todos los puntos que cada jugador fue acumulando a lo largo de todos los juegos. 
- **[C] Salir:** Termina el juego.

## Reglas del juego
- **Turnos alternados:** Al usuario y a la máquina se le asignaran un simbolo aleatoriamente ("X" o "O") y jugaran por turnos en un tablero de 3x3, en el que simpre iniciara al que le haya tocado el simbolo "X".
- **Condiciones de victoria:**
    - Un jugador gana si coloca tres de sus símbolos en una línea horizontal, vertical o diagonal.
    - Si el tablero se llena sin que haya un ganador, la partida se considera un empate.
- **Sistema de puntuación:** Por cada partida que se termine, se sumaran +3 puntos si gana el jugador, +2 puntos si empata con la maquina y -1 punto si pierde.

## Configuraciones
### Configuraciones del juego
Si deseás modificar algunas configuraciones del juego, podes hacerlo editando manualmente el archivo "config.txt", respetando el siguiente formato:
```
UrlApi|CodigoDeGrupo
CantDePartidas
```
### Configuraciones de libcurl y Codeblocks
Este proyecto necesita de la instalacion de curl para conectarse con la api, si no lo tiene instalado siga las sigueintes instrucciones:
1. Descargar la última versión de curl desde la pagina oficial de [curl](https://curl.se/windows/).
2. Descomprimir e zip y pasar esa carpeta a una ubicación que no la vayan a borrar.
3. Agregar dentro de PATH (como variable de entorno) la ubicación a la carpeta “bin”.
4. En Codeblocks: Settings > Compiler > Linker Settings: agregar ubicación a “lib\libcurl.dll.a”.
5. En Codeblocks: Settings > Compiler > Search directories > Compiler y Resource compiler: agregar ubicación a “include”.
6. En Codeblocks: Settings > Compiler > Search directories > Linker: agregar ubicación a “lib”.

