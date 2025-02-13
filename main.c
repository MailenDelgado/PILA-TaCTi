#include "Juego.h"

void menu(void);

int main()
{
    menu();
    return 0;
}

void menu(void){
    char op;
    printf("Eliga una opcion: \n[A]Jugar\n[B]Ver ranking equipo\n[C]Salir\n");
    scanf("%s", &op);
    if(op == 'A' || op == 'a')
    {
        printf("Jugar\n");
        jugar2();
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
