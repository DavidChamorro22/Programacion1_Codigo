#include <stdio.h>

int main() {
    int calificaciones[100], cantidad = 0, opcion, i;
    int A, B, C, D, E, max, min;

    do {
        printf("1. Ingresar calificaciones\n");
        printf("2. Mostrar calificaciones\n");
        printf("3. Calcular estadisticas\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion\n ");
        printf(">>");
        while (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Intente de nuevo\n");
            printf(">>");
            while (getchar() != '\n');
        }

        if (opcion == 1) {
            printf("Ingrese la cantidad de alumnos\n ");
            printf(">>");
            while (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                printf("Entrada inválida. Intente de nuevo\n");
                printf(">>");
                while (getchar() != '\n');
            }

            for (i = 0; i < cantidad; i++) {
                printf("Calificacion del alumno %d\n ", i + 1);
                printf(">>");
                while (scanf("%d", &calificaciones[i]) != 1) {
                    printf("Entrada invalida. Intente de nuevo\n ");
                    printf(">>");
                    while (getchar() != '\n');
                }
            }

        } else if (opcion == 2) {
            for (i = 0; i < cantidad; i++) {
                printf("Alumno %d: %d\n", i + 1, calificaciones[i]);
            }

        } else if (opcion == 3) {
            if (cantidad == 0) {
                printf("Primero debe ingresar las calificaciones.\n");
                continue;
            }

            A = B = C = D = E = 0;
            max = min = calificaciones[0];

            for (i = 0; i < cantidad; i++) {
                int nota = calificaciones[i];

                if (nota < 4) E++;
                else if (nota < 6) D++;
                else if (nota < 8) C++;
                else if (nota < 9) B++;
                else A++;

                if (nota > max) max = nota;
                if (nota < min) min = nota;
            }

            printf("Cantidad de A: %d\n", A);
            printf("Cantidad de B: %d\n", B);
            printf("Cantidad de C: %d\n", C);
            printf("Cantidad de D: %d\n", D);
            printf("Cantidad de E: %d\n", E);
            printf("Nota más alta: %d\n", max);
            printf("Nota más baja: %d\n", min);
        }

    } while (opcion != 4);

    return 0;
}
