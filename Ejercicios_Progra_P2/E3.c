#include <stdio.h>

//Escribir una funcion Calidad_Puntos() que reciba una nota de 
// un alumno y regrese en el nombre de la funcion: 4 si el 
// promedio es entre 90 y 100, 3 si el promedio es entre 80 y 89, 
// 2 si el promedio es entre 70 y 79, 1 si el promedio es entre 60 
// y 69 y 0 si el promedio es menor de 60

int Calidad_Puntos(int nota) {
    if (nota < 0 || nota > 100) {
        return -1; 
    }
    if (nota >= 90) {
        return 4;
    }
    if (nota >= 80) {
        return 3;
    }
    if (nota >= 70) {
        return 2;
    }
    if (nota >= 60) {
        return 1;
    }
    return 0;
}

int main() {
    int nota, puntos;

    printf("INGRESE LA NOTA DEL ALUMNO\n");
    if (scanf("%d", &nota) != 1) {
        printf("ENTRADA INVALIDA\n");
        return 1;
    }

    puntos = Calidad_Puntos(nota);

    if (puntos == -1) {
        printf("NOTA FUERA DE RANGO\n");
    } else {
        printf("PUNTOS %d\n", puntos);
    }

    return 0;
}
