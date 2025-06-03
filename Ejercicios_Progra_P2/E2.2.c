#include <stdio.h>

// Realizar una funcion que reciba un dato tipo char y devuelva el 0 si no es una letra. En caso de que el 
// caracter sea una letra minuscula debe devolver la letra mayuscula, caso contrario si el caracter es una 
// letra mayuscula devuelve el mismo caracter.
// Luego utlizar esta funcion en un programa que permita ingresar una serie de caracteres hasta dirigir un 
// caracter "*", e indicar el resultado  correspondiente.

char convertirLetra(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    if (c >= 'A' && c <= 'Z') {
        return c;
    }
    return 0;
}

int main() {
    char entrada;
    char resultado;

    printf("INGRESE CARACTERES UNO POR UNO (INGRESE * PARA TERMINAR)\n");

    while (1) {
        printf("CARACTER: ");
        if (scanf(" %c", &entrada) != 1) {
            printf("ENTRADA INVALIDA\n");
            break;
        }

        if (entrada == '*') {
            break;
        }

        resultado = convertirLetra(entrada);

        if (resultado == 0) {
            printf("NO ES UNA LETRA\n");
        } else {
            printf("RESULTADO %c\n", resultado);
        }
    }

    return 0;
}
