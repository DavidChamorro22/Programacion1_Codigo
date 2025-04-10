#include <stdio.h>
#include <stdlib.h>

int main() {
    char id[20];
    int cantidad, opcion, dias_de_retraso;
    int stock = -1;
    float precio, total_ganancias = 0, cargo_por_retraso;
    char titulo[50], autor[50];

    printf("\t--- BIENVENIDO A LA BIBLIOTECA ---\n");
    printf("INGRESE EL ID DEL LIBRO:\n>>");
    fgets(id, sizeof(id), stdin);

    printf("INGRESE EL TITULO DEL LIBRO:\n>>");
    fgets(titulo, sizeof(titulo), stdin);

    printf("INGRESE EL NOMBRE DEL AUTOR:\n>>");
    fgets(autor, sizeof(autor), stdin);

    printf("INGRESE LA CANTIDAD DE EJEMPLARES DISPONIBLES:\n>>");
    while (scanf("%d", &stock) != 1 || stock < 0) {
        printf("ERROR: LA CANTIDAD DEBE SER UN NUMERO NO NEGATIVO. INTENTE DE NUEVO\n>>");
        while(getchar() != '\n');
    }

    printf("INGRESE EL PRECIO POR DIA DE ALQUILER:\n>>");
    while (scanf("%f", &precio) != 1 || precio < 0) {
        printf("ERROR: EL PRECIO DEBE SER UN NUMERO NO NEGATIVO. INTENTE DE NUEVO\n>>");
        while(getchar() != '\n');
    }

    do {
        printf("\n\t--- MENU DE OPCIONES ---\n");
        printf("1. PRESTAR LIBRO\n");
        printf("2. DEVOLVER LIBRO\n");
        printf("3. CONSULTAR INFORMACION DEL LIBRO\n");
        printf("4. MOSTRAR GANANCIAS ACUMULADAS\n");
        printf("5. SALIR\n");
        printf("SELECCIONE UNA OPCION:\n>>");
        
        while (scanf("%d", &opcion) != 1) {
            printf("OPCION INVALIDA. INTENTE DE NUEVO.\n>>");
            while(getchar() != '\n');
        }
        
        switch (opcion) {
            case 1:
                printf("INGRESE LA CANTIDAD DE LIBROS A PRESTAR:\n>>");
                while (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                    printf("LA CANTIDAD A PRESTAR DEBE SER UN NUMERO POSITIVO. INTENTE DE NUEVO\n>>");
                    while(getchar() != '\n');
                }
                if (cantidad <= stock) {
                    stock -= cantidad;
                    total_ganancias += cantidad * precio;
                    printf("PRESTAMO REALIZADO CON EXITO. GANANCIA: $%.2f\n", cantidad * precio);
                } else {
                    printf("NO HAY SUFICIENTES EJEMPLARES PARA REALIZAR EL PRESTAMO.\n");
                }
                break;

            case 2:
                printf("INGRESE LA CANTIDAD DE LIBROS DEVUELTOS:\n>>");
                while (scanf("%d", &cantidad) != 1 || cantidad < 0) {
                    printf("LA CANTIDAD DE LIBROS DEVUELTOS NO PUEDE SER NEGATIVA. INTENTE DE NUEVO\n>>");
                    while(getchar() != '\n');
                }
                stock += cantidad;
                printf("LIBROS DEVUELTOS CON EXITO. NUEVO STOCK: %d\n", stock);
                
                printf("INGRESE EL NUMERO DE DIAS DE RETRASO (SI NO HAY, INGRESE 0):\n>>");
                while (scanf("%d", &dias_de_retraso) != 1 || dias_de_retraso < 0) {
                    printf("EL NUMERO DE DIAS DEBE SER UN NUMERO NO NEGATIVO. INTENTE DE NUEVO\n>>");
                    while(getchar() != '\n');
                }
                if (dias_de_retraso > 0) {
                    cargo_por_retraso = dias_de_retraso * 0.50;
                    total_ganancias += cargo_por_retraso;
                    printf("CARGO POR RETRASO: $%.2f\n", cargo_por_retraso);
                }
                break;

            case 3:
                printf("\nINFORMACION DEL LIBRO\n");
                printf("ID: %s", id);
                printf("TITULO: %s", titulo);
                printf("AUTOR: %s", autor);
                printf("CANTIDAD DISPONIBLE: %d\n", stock);
                printf("PRECIO POR DIA DE ALQUILER: %.2f\n", precio);
                break;

            case 4:
                printf("TOTAL DE GANANCIAS ACUMULADAS: $%.2f\n", total_ganancias);
                break;

            case 5:
                printf("SALIENDO DEL PROGRAMA...\n");
                printf("\t--- GRACIAS POR USAR EL PROGRAMA ---\n");
                break;

            default:
                printf("OPCION INVALIDA. INTENTE DE NUEVO.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}
