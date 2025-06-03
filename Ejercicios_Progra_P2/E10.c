#include <stdio.h>

//Escribir una funcion que reciba el tiempo como tres argumentos enteros: horas,
//  minutos y segundos, y regrese en el nombre de la funcion el numero de segundos 
// transcurridos desde la hora 00:00:00. Utilizar esta funcion para calcular la 
// cantidad de seguntos entre dos tiempos




int transformar_segundos(int h, int m, int s) {
    return h * 3600 + m * 60 + s;
}

int leer_entero_positivo(const char* mensaje) {
    int valor;
    char c;
    int entrada_valida = 0;

    while (entrada_valida == 0) {
        printf("%s", mensaje);
        if (scanf("%d%c", &valor, &c) != 2 || c != '\n' || valor < 0) {
            printf("ENTRADA INVALIDA DEBE SER UN NUMERO ENTERO POSITIVO\n");
            while (getchar() != '\n'); 
        } else {
            entrada_valida = 1;
        }
    }

    return valor;
}

int main() {
    int h1, m1, s1;
    int h2, m2, s2;

    printf("INGRESE LA PRIMERA HORA\n");
    h1 = leer_entero_positivo("HORAS: ");
    m1 = leer_entero_positivo("MINUTOS: ");
    s1 = leer_entero_positivo("SEGUNDOS: ");

    printf("INGRESE LA SEGUNDA HORA\n");
    h2 = leer_entero_positivo("HORAS: ");
    m2 = leer_entero_positivo("MINUTOS: ");
    s2 = leer_entero_positivo("SEGUNDOS: ");

    int t1 = transformar_segundos(h1, m1, s1);
    int t2 = transformar_segundos(h2, m2, s2);

    int diferencia = t2 - t1;

    printf("LA DIFERENCIA EN SEGUNDOS ENTRE LOS DOS TIEMPOS ES %d\n", diferencia);

    return 0;
}
