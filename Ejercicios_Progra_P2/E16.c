#include <stdio.h>
#include <math.h>

//Construir una funcion hipotenusa() que calcule la longitud de la hipotenusa de un triangulo rectangulo, 
// cuando son conocidos los otros dos lados. La funcion debe tomar dos argumentos de tipo double y regresar 
// la hipotenusa tambien como double. Utilizar esta funcion en  un programa para determinar la longitud de la 
// hipotenusa de varios triangulos en una tabla


double hipotenusa(double a, double b) {
    return sqrt(a * a + b * b);
}


double leer_positivo(char mensaje[]) {
    double valor;
    int ok;
    char c;
    do {
        printf("%s", mensaje);
        ok = scanf("%lf", &valor);
        while ((c = getchar()) != '\n'); 
        if (ok != 1 || valor <= 0) {
            printf("ENTRADA INVALIDA, DEBE SER UN NUMERO POSITIVO\n");
        }
    } while (ok != 1 || valor <= 0);
    return valor;
}

int main() {
    int n;
    double cateto1, cateto2, hipo;
    char c;

    
    do {
        printf("CUANTOS TRIANGULOS DESEA INGRESAR: ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("ENTRADA INVALIDA, DEBE SER UN ENTERO POSITIVO\n");
            while ((c = getchar()) != '\n');
        } else {
            while ((c = getchar()) != '\n');
            break;
        }
    } while (1);

    printf("\n%-10s %-10s %-15s\n", "CATETO A", "CATETO B", "HIPOTENUSA");
    printf("-------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("\nTRIANGULO %d:\n", i + 1);
        cateto1 = leer_positivo("INGRESE CATETO A: ");
        cateto2 = leer_positivo("INGRESE CATETO B: ");
        hipo = hipotenusa(cateto1, cateto2);
        printf("%-10.2lf %-10.2lf %-15.2lf\n", cateto1, cateto2, hipo);
    }

    return 0;
}
