#include <stdio.h>

//Elaborar una funcion producto() que reciba dos numeros de tipo 
// int A y B, y devuelve en el nombre de la funcion un dato de tipo int, 
// que contenga el resultado de multiplicar A por B por el metodo de sumas sucesivas, asi: A       B     PRODUCTO 

int producto(int a, int b) {
    int resultado = 0;
    int negativo = 0;

    if (b < 0) {
        b = -b;
        negativo = 1;
    }

    for (int i = 0; i < b; i++) {
        resultado += a;
    }

    if (negativo) {
        resultado = -resultado;
    }

    return resultado;
}

int leerEntero(char nombre) {
    int n, ok;

    do {
        printf("INGRESE UN NUMERO ENTERO PARA: %c\n", nombre);
        ok = scanf("%d", &n);
        while (getchar() != '\n'); // Limpiar el buffer
    } while (ok != 1);

    return n;
}

int main() {
    int a = leerEntero('A');
    int b = leerEntero('B');

    int resultado = producto(a, b);
    printf("EL PRODUCTO DE %d POR %d ES %d\n", a, b, resultado);

    return 0;
}
