#include <stdio.h>
#include <math.h>

//Elaborar una funcion que reciba como argumentos la longitud de un pendulo l y 
// la aceleracion gravitacional g, para calcular el tiempo de oscilacion t, mediante 
// la siguiente formula:   t = pi raiz cuadrad de l/g


double tiempo_oscilacion(double l, double g) {
    return 3.14 * sqrt(l / g);
}


double leer_positivo(const char* mensaje) {
    double valor;
    char c;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%lf%c", &valor, &c) != 2 || c != '\n' || valor <= 0) {
            printf("ENTRADA INVALIDA DEBE SER UN NUMERO POSITIVO\n");
            while (getchar() != '\n'); 
        } else {
            return valor;
        }
    }
}

int main() {
    double l = leer_positivo("INGRESE LA LONGITUD DEL PENDULO EN METROS: ");
    double g = leer_positivo("INGRESE LA ACELERACION GRAVITACIONAL EN M/S^2: ");

    double t = tiempo_oscilacion(l, g);

    printf("EL TIEMPO DE OSCILACION ES %.4f SEGUNDOS\n", t);

    return 0;
}
