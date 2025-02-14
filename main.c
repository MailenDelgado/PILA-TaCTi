#include "Juego.h"
#include "config/config.h"
#define NOMBRE_ARCH_CONFIG "config/config.txt"

void menu(void);

int main()
{
    menu();
    return 0;
}

void menu(void){
    char op;
    tConfig confi;

    cargarConfig(NOMBRE_ARCH_CONFIG, &confi);
    printf("\n\t===================================================\n");
    printf("\n\t\t\tJuego Tateti (Ta-C-ti)\n\n");
    printf("\tEliga una opcion:\n\t[A]Jugar\n\t[B]Ver ranking equipo\n\t[C]Salir\n");
    printf("\n\t===================================================\n");
    scanf("%s", &op);
    if(op == 'A' || op == 'a')
    {
        printf("Jugar\n");
        jugar2(confi.cantPartidas);
        menu();
    }
    else if((op == 'B') || (op == 'b'))
    {
        printf("Ver ranking equipo\n");
        menu();
    }
    else if((op == 'C') || (op == 'c'))
        printf("Salir");
    else
    {
        printf("Opcion incorrecta\n");
        menu();
    }
}
