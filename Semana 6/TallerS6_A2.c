#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nombre: David Chamorro
// NRC: 5514
// Actividad: Taller S6
// Profesora: Bernarda Sandoval

#define MAX 10
#define NOMBRE 50

int leerEnteroEnRango() {
    char linea[20];
    int n;
    while (1) {
        printf("\t---GESTOR DE INVENTARIO DE PRODUCTOS---\n");
        printf("INGRESE CANTIDAD DE PRODUCTOS ENTRE 1 Y 10\n");
        printf(">> ");
        fgets(linea, sizeof(linea), stdin);
        if (sscanf(linea, "%d", &n) != 1 || n < 1 || n > MAX) {
            printf("ENTRADA INVALIDA INGRESE UN NUMERO VALIDO ENTRE 1 Y 10\n");
        } else {
            return n;
        }
    }
}

float leerFlotantePositivo() {
    char linea[30];
    float valor;
    while (1) {
        printf(">> ");
        fgets(linea, sizeof(linea), stdin);
        if (sscanf(linea, "%f", &valor) != 1 || valor <= 0) {
            printf("ENTRADA INVALIDA INGRESE UN NUMERO POSITIVO\n");
        } else {
            return valor;
        }
    }
}

void leerNombreProducto(char nombre[]) {
    while (1) {
        printf(">> ");
        fgets(nombre, NOMBRE, stdin);
        nombre[strcspn(nombre, "\n")] = '\0';  // eliminar salto de línea

        int vacio = 1;
        for (int i = 0; nombre[i] != '\0'; i++) {
            if (nombre[i] != ' ') {
                vacio = 0;
                break;
            }
        }

        if (strlen(nombre) == 0 || vacio) {
            printf("ENTRADA INVALIDA INGRESE UN NOMBRE VALIDO\n");
        } else {
            break;
        }
    }
}

int leerOpcionMenu() {
    char linea[10];
    int opcion;
    while (1) {
        printf(">> ");
        fgets(linea, sizeof(linea), stdin);
        if (sscanf(linea, "%d", &opcion) != 1 || opcion < 1 || opcion > 5) {
            printf("OPCION INVALIDA INGRESE UN NUMERO DEL MENU\n");
        } else {
            return opcion;
        }
    }
}

int main() {
    char nombres[MAX][NOMBRE], buscado[NOMBRE];
    float precios[MAX];
    int n, opcion;

    n = leerEnteroEnRango();

    for (int i = 0; i < n; i++) {
        printf("NOMBRE DEL PRODUCTO %d\n", i + 1);
        leerNombreProducto(nombres[i]);

        printf("PRECIO DEL PRODUCTO %d\n", i + 1);
        precios[i] = leerFlotantePositivo();
    }

    do {
        printf("\t---MENU DE OPERACIONES---\n");
        printf("1 MOSTRAR TOTAL DEL INVENTARIO\n");
        printf("2 MOSTRAR PRODUCTO MAS CARO Y MAS BARATO\n");
        printf("3 MOSTRAR PRECIO PROMEDIO\n");
        printf("4 BUSCAR PRODUCTO POR NOMBRE\n");
        printf("5 SALIR\n");
        printf("SELECCIONE UNA OPCION\n");
        opcion = leerOpcionMenu();

        if (opcion == 1) {
            float total = 0;
            for (int i = 0; i < n; i++) total += precios[i];
            printf("TOTAL DEL INVENTARIO %.2f\n", total);
        } else if (opcion == 2) {
            int max = 0, min = 0;
            for (int i = 1; i < n; i++) {
                if (precios[i] > precios[max]) max = i;
                if (precios[i] < precios[min]) min = i;
            }
            printf("PRODUCTO MAS CARO %s CON PRECIO %.2f\n", nombres[max], precios[max]);
            printf("PRODUCTO MAS BARATO %s CON PRECIO %.2f\n", nombres[min], precios[min]);
        } else if (opcion == 3) {
            float suma = 0;
            for (int i = 0; i < n; i++) suma += precios[i];
            printf("PRECIO PROMEDIO %.2f\n", suma / n);
        } else if (opcion == 4) {
            printf("INGRESE NOMBRE DEL PRODUCTO A BUSCAR\n");
            leerNombreProducto(buscado);
            int encontrado = -1;
            for (int i = 0; i < n; i++) {
                if (strcmp(nombres[i], buscado) == 0) {
                    encontrado = i;
                    break;
                }
            }
            if (encontrado != -1)
                printf("EL PRECIO DE %s ES %.2f\n", nombres[encontrado], precios[encontrado]);
            else
                printf("PRODUCTO NO ENCONTRADO\n");
        }

    } while (opcion != 5);

    printf("SALIENDO DEL PROGRAMA\n");
    return 0;
}
