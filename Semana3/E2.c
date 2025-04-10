#include <stdio.h>

int main() {
    int vec[10], i, max, min;

    for (i = 0; i < 10; i++) {
        printf("Ingrese el numero %d\n ", i + 1);
        printf(">>");
        while (scanf("%d", &vec[i]) != 1) {
            printf("Entrada invalida. Intente de nuevo\n ");
            printf(">>");
            while (getchar() != '\n'); // Limpia el buffer
        }
    }

    max = vec[0];
    min = vec[0];

    for (i = 1; i < 10; i++) {
        if (vec[i] > max) max = vec[i];
        if (vec[i] < min) min = vec[i];
    }

    printf("\nMaximo es: %d\n", max);
    printf("Minimo es: %d\n", min);

    return 0;
}
