#include "Juego.h"
#include "config/config.h"
#define NOMBRE_ARCH_CONFIG "config.txt"
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
    printf("Eliga una opcion: \n[A]Jugar\n[B]Ver ranking equipo\n[C]Salir\n");
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
