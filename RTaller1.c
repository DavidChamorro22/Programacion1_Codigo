#include <stdio.h>
#include <stdlib.h>

int main() {
    int id, cantidad, opcion, dias_de_retraso;
    int stock = 0;
    float precio, total_ganancias = 0, cargo_por_retraso;
    char titulo[50], autor[50];
    char buffer[10];  // Para almacenar la entrada y validar si es un número

    printf(" \t--- BIENVENIDO A LA BIBLIOTECA ---\n");

    printf("INGRESE EL ID DEL LIBRO:\n ");
    printf(">>");
    scanf("%d", &id);

    while (getchar() != '\n'); // Limpiar el buffer de entrada

    printf("INGRESE EL TITULO DEL LIBRO:\n ");
    printf(">>");
    fgets(titulo, 50, stdin);

    printf("INGRESE EL NOMBRE DEL AUTOR:\n ");
    printf(">>");
    fgets(autor, 50, stdin);

    // Validación de cantidad de ejemplares disponibles
    do {
        printf("INGRESE LA CANTIDAD DE EJEMPLARES DISPONIBLES:\n ");
        printf(">>");
        if (scanf("%d", &stock) != 1 || stock < 0) {
            printf("ERROR: LA CANTIDAD NO PUEDE SER NEGATIVA O NO NUMERICA. INTENTE DE NUEVO\n");
            while (getchar() != '\n'); // Limpiar el buffer si no es un número
        }
    } while (stock < 0);

    // Validación de precio
    do {
        printf("INGRESE EL PRECIO POR DIA DE ALQUILER:\n ");
        printf(">>");
        if (scanf("%f", &precio) != 1 || precio < 0) {
            printf("ERROR: EL PRECIO NO PUEDE SER NEGATIVO O NO NUMERICO. INTENTE DE NUEVO\n");
            while (getchar() != '\n'); // Limpiar el buffer si no es un número
        }
    } while (precio < 0);

    // Menú de opciones
    do {
        printf("\t--- MENU DE OPCIONES ---\n");
        printf("1. PRESTAR LIBRO\n");
        printf("2. DEVOLVER LIBRO\n");
        printf("3. CONSULTAR INFORMACION DEL LIBRO\n");
        printf("4. MOSTRAR GANANCIAS ACUMULADAS\n");
        printf("5. SALIR\n");
        printf("SELECCIONE UNA OPCION:\n ");
        printf(">>");
        if (scanf("%d", &opcion) != 1) {
            printf("OPCION INVALIDA. INTENTE DE NUEVO\n");
            while (getchar() != '\n'); // Limpiar el buffer si no es un número
        }

        switch (opcion) {
            case 1:
                // Validación de cantidad a prestar
                do {
                    printf("INGRESE LA CANTIDAD DE LIBROS A PRESTAR:\n ");
                    printf(">>");
                    if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                        printf("LA CANTIDAD A PRESTAR DEBE SER UN NUMERO POSITIVO. INTENTE DE NUEVO\n");
                        while (getchar() != '\n'); // Limpiar el buffer si no es un número
                    }
                } while (cantidad <= 0);

                if (cantidad <= stock) {
                    stock -= cantidad; // Reducir el stock
                    total_ganancias += cantidad * precio; // Calcular ganancias
                    printf("PRESTAMO REALIZADO CON EXITO. GANANCIA: $%.2f\n", cantidad * precio);
                } else {
                    printf("NO HAY SUFICIENTES EJEMPLARES PARA REALIZAR EL PRESTAMO\n");
                }
                break;

            case 2:
                // Validación de cantidad de libros devueltos
                do {
                    printf("INGRESE LA CANTIDAD DE LIBROS DEVUELTOS:\n ");
                    printf(">>");
                    if (scanf("%d", &cantidad) != 1 || cantidad < 0) {
                        printf("LA CANTIDAD DE LIBROS DEVUELTOS NO PUEDE SER NEGATIVA. INTENTE DE NUEVO\n");
                        while (getchar() != '\n'); // Limpiar el buffer si no es un número
                    }
                } while (cantidad < 0);

                stock += cantidad; // Aumentar el stock con los libros devueltos
                printf("LIBROS DEVUELTOS CON EXITO. NUEVO STOCK: %d\n", stock);

                // Preguntar por el retraso en la devolución
                printf("INGRESE EL NUMERO DE DIAS DE RETRASO (SI NO HAY, INGRESE 0):\n ");
                printf(">>");
                if (scanf("%d", &dias_de_retraso) != 1 || dias_de_retraso < 0) {
                    printf("EL NUMERO DE DIAS DE RETRASO DEBE SER UN NUMERO NO NEGATIVO. INTENTE DE NUEVO\n");
                    while (getchar() != '\n'); // Limpiar el buffer si no es un número
                }

                if (dias_de_retraso > 0) {
                    cargo_por_retraso = dias_de_retraso * 0.50; // 0.50 es la tarifa diaria por retraso
                    total_ganancias += cargo_por_retraso;
                    printf("CARGO POR RETRASO: $%.2f\n", cargo_por_retraso);
                }
                break;

            case 3:
                printf("\nINFORMACION DEL LIBRO\n");
                printf("ID: %d\n", id);
                printf("TITULO: %s", titulo);
                printf("AUTOR: %s", autor);
                printf("CANTIDAD DISPONIBLE: %d\n", stock);
                printf("PRECIO POR DIA DE ALQUILER: %.2f\n", precio);
                break;

            case 4:
                printf("TOTAL DE GANANCIAS ACUMULADAS: $%.2f\n", total_ganancias);
                break;

            case 5:
                printf("SALIENDO DEL PROGRAMA... \n");
                printf("\t--- GRACIAS POR USAR EL PROGRAMA ---\n");
                break;

            default:
                printf("OPCION INVALIDA. INTENTE DE NUEVO\n");
        }
    } while (opcion != 5);

    return 0;
}
