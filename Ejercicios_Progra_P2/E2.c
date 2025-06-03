#include <stdio.h>

// Realizar una funcion que reciba un dato tipo char y devuelva el 0 si no es una letra. En caso de que el 
// caracter sea una letra minuscula debe devolver la letra mayuscula, caso contrario si el caracter es una 
// letra mayuscula devuelve el mismo caracter.

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
    int leido;

    printf("INGRESE UN SOLO CARACTER\n");
    leido = scanf(" %c", &entrada);

    if (leido != 1) {
        printf("ENTRADA INVALIDA\n");
        return 1;
    }

    char resultado = convertirLetra(entrada);

    if (resultado == 0) {
        printf(" 0 NO ES UNA LETRA\n");
    } else {
        printf("RESULTADO %c\n", resultado);
    }

    return 0;
}
