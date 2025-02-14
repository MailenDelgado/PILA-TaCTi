# PILA-TaCTi

Este proyecto implementa un minijuego de Tateti (Ta-C-Ti) desarrollado en C, diseñado para ser utilizado en un tótem interactivo en supermercados. Los jugadores pueden enfrentarse a una inteligencia artificial básica, y los resultados de cada partida se registran en un servidor remoto mediante una API.

## Instrucciones del juego
Al iniciar, se presenta un menú interactivo. Las opciones disponibles son:

- **[A] Jugar:**  Se le pedirá que cargue los nombres de las personas que van a jugar. Puede ingresar la cantidad de nombres que desee. Una vez que termine de ingresarlos, aparecerá por pantalla el orden en el que jugarán los jugadores, y se le preguntará al primer jugador si está listo. En caso de que sí, inicia el juego.
- **[B] Ver ranking equipo:**  
- **[C] Salir:** Termina el juego.

## Reglas del juego
- **Turnos alternados:** El usuario y la máquina juegan por turnos en un tablero de 3x3.
- **Condiciones de victoria:**
    - Un jugador gana si coloca tres de sus símbolos en una línea horizontal, vertical o diagonal.
    - Si el tablero se llena sin que haya un ganador, la partida se considera un empate.
- **Sistema de puntuación:** Por cada partida que se termine, se sumaran +3 puntos si gana el jugador, +2 puntos si empata con la maquina y -1 punto si pierde

## Configuraciones
### Configuraciones del juego
Si deseas modificar algunas configuraciones del juego, puedes hacerlo editando los siguientes parámetros en el código:
 
## Cómo contribuir

Si deseas mejorar el proyecto, puedes clonar este repositorio, hacer tus modificaciones y enviar un pull request.
