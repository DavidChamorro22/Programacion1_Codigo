#include <stdio.h>
#include <math.h>

// Escribir la funcion distancia() que calcule la distancia la 
// distancia entre dos puntos (x1,y1) y (x2, y2). Todos los valores 
// de los puntos y el valor de resgreso deberan ser tipo float

float distancia(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
}

int leer_float(char nombre[]) {
    float valor;
    int valido;
    do {
        printf("INGRESE: %s\n", nombre);
        valido = scanf("%f", &valor);
        if (valido != 1) {
            printf("ENTRADA INVALIDA\n");
            while (getchar() != '\n'); // Limpiar el buffer
        }
    } while (valido != 1);
    return valor;
}

int main() {
    float x1, y1, x2, y2, dist;

    x1 = leer_float("X1");
    y1 = leer_float("Y1");
    x2 = leer_float("X2");
    y2 = leer_float("Y2");

    dist = distancia(x1, y1, x2, y2);

    printf("DISTANCIA %.4f\n", dist);

    return 0;
}
