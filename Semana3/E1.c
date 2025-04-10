#include <stdio.h>

int main() {
    float peso[5], suma = 0, promedio;
    int i, mayor = 0, menor = 0;

    for (i = 0; i < 5; i++) {
        printf("Ingrese el peso de la persona %d\n   ", i + 1);
        printf(">>");
        while (scanf("%f", &peso[i]) != 1) {
            printf("Entrada invalida. Intente de nuevo\n ");
            printf(">>");
            while (getchar() != '\n'); 
        }
        suma += peso[i];
    }

    promedio = suma / 5;

    for (i = 0; i < 5; i++) {
        if (peso[i] > promedio)
            mayor++;
        else
            menor++;
    }

    printf("Promedio: %.2f\n", promedio);
    printf("Pesan mas que el promedio: %d\n", mayor);
    printf("Pesan menos o igual al promedio: %d\n", menor);

    return 0;
}
