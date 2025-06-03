#include <stdio.h>

//Un numero entero es "primo" si es divisible solo para 
// y para si mismo.Por ejemplo, los numeros, 2,3,5,7 son primos 
// pero 4,6,8 y 9 no lo son. Con este concepto escribir una funcion 
// que determine si un numero es primo, y utilizarla en un programa 
// que imprima todos los numeros primos entre el 1 al 10000

int es_primo(int n) {
    if (n <= 1) {
        return 0; 
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0; 
        }
    }

    return 1; 
}

int main() {
    printf("NUMEROS PRIMOS ENTRE 1 Y 100\n");

    for (int i = 1; i <= 100; i++) {
        if (es_primo(i)) {
            printf("%d ", i);
        }
    }

    printf("\n");
    return 0;
}
