#include <stdio.h>

//Realizar un programa que lea dos fechas cualquiera con el formato 
// año/mes/dia, para calcular en una funcion el numero de dias que existe 
// entre dos fechas leidas y por ultimo imprimir los datos leidos y calculado

int es_bisiesto(int anio) {
    if ((anio % 400) == 0)
        return 1;
    else if ((anio % 4) == 0 && (anio % 100) != 0)
        return 1;
    else
        return 0;
}


long fecha_a_dias(int anio, int mes, int dia) {
    int dias_mes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    long total = 0;

    for (int a = 1; a < anio; a++) {
        if (es_bisiesto(a) == 1)
            total += 366;
        else
            total += 365;
    }

    if (es_bisiesto(anio) == 1)
        dias_mes[1] = 29;

    for (int m = 1; m < mes; m++) {
        total += dias_mes[m - 1];
    }

    total += dia;

    return total;
}

int main() {
    int anio1, mes1, dia1, anio2, mes2, dia2;
    char sep1, sep2;

    while (1) {
        printf("INGRESE LA PRIMERA FECHA EN FORMATO ANIO/MES/DIA: ");
        if (scanf("%d%c%d%c%d", &anio1, &sep1, &mes1, &sep2, &dia1) == 5 &&
            sep1 == '/' && sep2 == '/' &&
            anio1 > 0 && mes1 >= 1 && mes1 <= 12 && dia1 >= 1 && dia1 <= 31) {
            break;
        } else {
            printf("FECHA INVALIDA, INTENTE DE NUEVO\n");
            while(getchar() != '\n'); 
        }
    }

    while (1) {
        printf("INGRESE LA SEGUNDA FECHA EN FORMATO ANIO/MES/DIA: ");
        if (scanf("%d%c%d%c%d", &anio2, &sep1, &mes2, &sep2, &dia2) == 5 &&
            sep1 == '/' && sep2 == '/' &&
            anio2 > 0 && mes2 >= 1 && mes2 <= 12 && dia2 >= 1 && dia2 <= 31) {
            break;
        } else {
            printf("FECHA INVALIDA, INTENTE DE NUEVO\n");
            while(getchar() != '\n'); 
        }
    }

    long d1 = fecha_a_dias(anio1, mes1, dia1);
    long d2 = fecha_a_dias(anio2, mes2, dia2);
    long diff;

    if (d1 > d2)
        diff = d1 - d2;
    else
        diff = d2 - d1;

    printf("\nFECHA 1: %04d/%02d/%02d\n", anio1, mes1, dia1);
    printf("FECHA 2: %04d/%02d/%02d\n", anio2, mes2, dia2);
    printf("DIAS ENTRE LAS FECHAS: %ld\n", diff);

    return 0;
}
