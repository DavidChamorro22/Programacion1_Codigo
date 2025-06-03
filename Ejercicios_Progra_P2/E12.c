#include <stdio.h>
#include <math.h>

//Elaborar un programa que calcule la altura maxima de un proyectil, la formula  
// que determina la altura h es:  h = v elevado al cuadrado * seno elvado al cuadrado (a) / 2 g


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


double leer_angulo(const char* mensaje) {
    double valor;
    char c;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%lf%c", &valor, &c) != 2 || c != '\n' || valor < 0 || valor > 90) {
            printf("ENTRADA INVALIDA EL ANGULO DEBE ESTAR ENTRE 0 Y 90 GRADOS\n");
            while (getchar() != '\n'); 
        } else {
            return valor;
        }
    }
}

int main() {
    double v = leer_positivo("INGRESE LA VELOCIDAD INICIAL EN M/S: ");
    double a = leer_angulo("INGRESE EL ANGULO DE LANZAMIENTO EN GRADOS: ");
    double g = leer_positivo("INGRESE LA ACELERACION GRAVITACIONAL EN M/S^2: ");

    
    double rad = a * M_PI / 180.0;

    
    double h = (v * v * pow(sin(rad), 2)) / (2 * g);

    printf("LA ALTURA MAXIMA DEL PROYECTIL ES %.4f METROS\n", h);

    return 0;
}
