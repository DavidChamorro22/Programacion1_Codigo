#include <stdio.h>

//Escribir una funcion multiplo() que determine en un par de
//  enteros si el segundo de ellos es multiplo del primero. 
// La funcion debe tomar dos argumentos enteros y regresar 1 
// (verdadero) si el segundo es multiplo del primero, y 0 
// (falso) de no ser asi. Utilizar esta funcion en un 
// programa que introduzca serie de pares enteros y liste el 
// resultado de esa funcion

int multiplo(int a, int b) {
    if (a == 0) {
        return 0; 
    }
    if (b % a == 0) {
        return 1;
    } else {
        return 0;
    }
}

int pedirEntero(const char* mensaje) {
    int num;
    int resultado;
    char c;
    do {
        printf("%s", mensaje);
        resultado = scanf("%d", &num);
        // limpiar buffer si hay entrada inválida
        while ((c = getchar()) != '\n' && c != EOF);
        if (resultado != 1) {
            printf("ERROR INGRESE UN NUMERO ENTERO VALIDO\n");
        }
    } while (resultado != 1);
    return num;
}

int main() {
    int num1, num2;
    char respuesta;
    char c; 

    do {
        num1 = pedirEntero("INGRESE EL PRIMER NUMERO ENTERO: ");
        num2 = pedirEntero("INGRESE EL SEGUNDO NUMERO ENTERO: ");

        if (multiplo(num1, num2)) {
            printf("EL NUMERO %d ES MULTIPLO DEL NUMERO %d\n", num2, num1);
        } else if (multiplo(num2, num1)) {
            printf("EL NUMERO %d ES MULTIPLO DEL NUMERO %d\n", num1, num2);
        } else {
            printf("EL NUMERO %d NO ES MULTIPLO DEL NUMERO %d Y EL NUMERO %d NO ES MULTIPLO DEL NUMERO %d\n",
                   num2, num1, num1, num2);
        }

        printf("DESEA INGRESAR OTRO PAR DE NUMEROS S/N: ");
        scanf(" %c", &respuesta);
        // limpiar buffer después de leer respuesta
        while ((c = getchar()) != '\n' && c != EOF);
    } while (respuesta == 'S' || respuesta == 's');

    return 0;
}
