#include "menu.h"
#include "funciones.h"
void menu_principal()
{
    char opcion;
    char repetir = TRUE;
    do
    {
        system("cls");
        printf("\n\n\t\t\tTateti (Ta-C-ti)\n");
        printf("\t\t\t----------------\n");
        printf("\n\t[A] Jugar\n");
        printf("\t[B] Ver ranking equipo\n");
        printf("\t[C] Salir\n");

        printf("\n\tIngrese una opcion: ");
        scanf("%c", &opcion);

        switch(opcion)
        {
        case 'A':
            Jugar();
            break;
        case 'B':
            VerRankingEquipo();
            break;
        case 'C':
            repetir = FALSE;
            break;
        }
    }while(repetir);
}
