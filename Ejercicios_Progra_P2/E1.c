#include <stdio.h>

//Escribir un programa que introduzca una serie de enteros 
//y que los pase uno a la vez a la funcion par() que determina si el entero es par,
// o 0 si no lo es.

int par(int n) {
    if (n % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int cantidad, numero, i;
    char c;

    
    printf("CUANTOS NUMEROS DESEA INGRESAR:\n");
    while (scanf("%d%c", &cantidad, &c) != 2 || c != '\n' || cantidad <= 0) {
        printf("ENTRADA INVALIDA INGRESE UN ENTERO POSITIVO\n");
        while (getchar() != '\n');
    }

    
    for (i = 1; i <= cantidad; i++) {
        printf("INGRESE EL NUMERO %d \n", i);
        while (scanf("%d%c", &numero, &c) != 2 || c != '\n') {
            printf("ENTRADA INVALIDA INGRESE UN NUMERO ENTERO\n");
            while (getchar() != '\n');
        }

        if (par(numero)) {
            printf("EL NUMERO ES PAR\n");
        } else {
            printf("EL NUMERO NO ES PAR\n");
        }
    }

    return 0;
}