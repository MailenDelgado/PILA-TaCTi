#include "Juego.h"

int main()
{
    grafica();
    menu();
    return 0;
}


//#include <stdio.h>
//
//int obtenerEntradaBinaria() {
//    int num;
//    char c;
//
//    while (1) {
//        printf("Ingrese un numero (0 o 1): ");
//        if (scanf("%d", &num) == 1 && (num == 0 || num == 1)) {
//            return num;
//        }
//
//        // Limpia el buffer de entrada en caso de entrada inválida
//        while ((c = getchar()) != '\n' && c != EOF);
//        printf("Entrada invalida. Solo se permiten los numeros 0 y 1. Intente de nuevo.\n");
//    }
//}
//
//int main() {
//    int valor = obtenerEntradaBinaria();
//    printf("Valor ingresado: %d\n", valor);
//    return 0;
//}


//#include <stdio.h>
//
//void obtenerEntradasBinarias(int *num1, int *num2) {
//    char c;
//    int entradaValida = 0; // Variable de control
//
//    while (!entradaValida) {
//        printf("Ingrese dos numeros (0 o 1) separados por espacio: ");
//
//        // Intentar leer dos enteros
//        if (scanf("%d %d", num1, num2) == 2 &&
//            (*num1 == 0 || *num1 == 1) &&
//            (*num2 == 0 || *num2 == 1)) {
//            entradaValida = 1; // Marcar como válido para salir del bucle
//        } else {
//            // Limpiar el buffer de entrada
//            while ((c = getchar()) != '\n' && c != EOF);
//            printf("Entrada invalida. Solo se permiten los numeros 0 y 1. Intente de nuevo.\n");
//        }
//    }
//}
//
//int main() {
//    int valor1, valor2;
//
//    obtenerEntradasBinarias(&valor1, &valor2);
//
//    printf("Valores ingresados: %d y %d\n", valor1, valor2);
//
//    return 0;
//}
