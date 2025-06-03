#include <stdio.h>

//Elaborar una funcion que reciba un dato de tipo char, que 
// debe devolver un numero:   0 si es una entrada mayuscula, 1 si 
// es una letra minuscula, 2 si es un digito, 3 si es un acaracter especial. 
// En un programa leer una serie de caracteres hasta ingresar un "*", que seran
//  enviados a la funcion, luego utlizar el valor devuelto de la funcion para indicar 
// el tipo de caracter.


int tipo_caracter(char c) {
    if (c >= 'A' && c <= 'Z')
        return 0; 
    else if (c >= 'a' && c <= 'z')
        return 1; 
    else if (c >= '0' && c <= '9')
        return 2; 
    else
        return 3; 
}

int main() {
    char c;

    printf("INGRESE CARACTERES (termina con '*'):\n");

    while (1) {
        c = getchar();

        if (c == '*')
            break;

        
        if (c == '\n' || c == ' ')
            continue;

        int tipo = tipo_caracter(c);

        switch (tipo) {
            case 0:
                printf("EL CARACTER '%c' ES UNA LETRA MAYUSCULA (0)\n", c);
                break;
            case 1:
                printf("EL CARACTER '%c' ES UNA LETRA MINUSCULA (1) \n", c);
                break;
            case 2:
                printf("EL CARACTER '%c' ES UN DIGITO (2) \n", c);
                break;
            case 3:
                printf("EL CARACTER '%c' ES UN CARACTER ESPECIAL (3) \n", c);
                break;
        }
    }

    printf("FIN DEL PROGRAMA\n");
    return 0;
}
