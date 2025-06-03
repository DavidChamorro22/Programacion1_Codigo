#include <stdio.h>

// En un programa en C: Un "numero perfecto" es aquel cuyos factores suman igual que dicho numero, 
// incluyendo el 1 pero excluyendo ese numero entero como factor.Por ejemplo, 6 es un numero perfecto 
// porque 6=1+2+3. Tomando en cuenta esto escribir una funcion perfecto() que determine si su parametro es 
// un numero perfecto.Luego utilizar esta funcion en un programa que determine e imprima todos los numeros 
// perfectos entre 1 y 100, con sus factores, para confirmar que el numero de verdad sea perfecto

int perfecto(int n) {
    int suma = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            suma += i;
        }
    }
    return suma == n;
}

int main() {
    printf("NUMEROS PERFECTOS ENTRE 1 Y 100\n");

    for (int num = 1; num <= 100; num++) {
        if (perfecto(num)) {
            printf("%d ES PERFECTO Y SUS FACTORES SON: ", num);
            for (int i = 1; i < num; i++) {
                if (num % i == 0) {
                    printf("%d ", i);
                }
            }
            printf("\n");
        }
    }

    return 0;
}
