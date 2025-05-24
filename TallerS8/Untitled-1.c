#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 50

// Variables globales
char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
int cantidades[MAX_PRODUCTOS];
int tiempos[MAX_PRODUCTOS];
int recursos[MAX_PRODUCTOS];
int numProductos = 0;

// Funciones
void ingresarProducto() {
    if (numProductos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos.\n");
        return;
    }

    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombres[numProductos]);

    printf("Ingrese la cantidad demandada: ");
    scanf("%d", &cantidades[numProductos]);

    printf("Ingrese el tiempo de fabricación por unidad (minutos): ");
    scanf("%d", &tiempos[numProductos]);

    printf("Ingrese la cantidad de recursos por unidad: ");
    scanf("%d", &recursos[numProductos]);

    numProductos++;
    printf("Producto agregado exitosamente.\n");
}

int buscarProducto(char nombreBuscar[]) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombres[i], nombreBuscar) == 0) {
            return i;
        }
    }
    return -1;
}

void editarProducto() {
    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a editar: ");
    scanf("%s", nombreBuscar);
    
    int indice = buscarProducto(nombreBuscar);
    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Ingrese el nuevo nombre: ");
    scanf("%s", nombres[indice]);

    printf("Ingrese la nueva cantidad: ");
    scanf("%d", &cantidades[indice]);

    printf("Ingrese el nuevo tiempo de fabricación por unidad: ");
    scanf("%d", &tiempos[indice]);

    printf("Ingrese la nueva cantidad de recursos por unidad: ");
    scanf("%d", &recursos[indice]);

    printf("Producto editado exitosamente.\n");
}

void eliminarProducto() {
    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombreBuscar);

    int indice = buscarProducto(nombreBuscar);
    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    for (int i = indice; i < numProductos - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }
    numProductos--;
    printf("Producto eliminado exitosamente.\n");
}

void calcularProduccion(int tiempoDisponible, int recursosDisponibles) {
    int tiempoTotal = 0;
    int recursosTotales = 0;

    for (int i = 0; i < numProductos; i++) {
        tiempoTotal += cantidades[i] * tiempos[i];
        recursosTotales += cantidades[i] * recursos[i];
    }

    printf("Tiempo total requerido: %d minutos\n", tiempoTotal);
    printf("Recursos totales requeridos: %d unidades\n", recursosTotales);

    if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
        printf("✅ La fábrica puede cumplir con la demanda.\n");
    } else {
        printf("❌ La fábrica NO puede cumplir con la demanda.\n");
    }
}

void mostrarProductos() {
    printf("\nLista de productos:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%d. %s | Cantidad: %d | Tiempo: %d | Recursos: %d\n",
               i + 1, nombres[i], cantidades[i], tiempos[i], recursos[i]);
    }
    printf("\n");
}

int main() {
    int opcion;
    int tiempoDisponible, recursosDisponibles;

    printf("Ingrese el tiempo de producción disponible (minutos): ");
    scanf("%d", &tiempoDisponible);
    printf("Ingrese los recursos disponibles: ");
    scanf("%d", &recursosDisponibles);

    do {
        printf("\n=== MENÚ ===\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar productos\n");
        printf("5. Calcular producción\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarProducto();
                break;
            case 2:
                editarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                mostrarProductos();
                break;
            case 5:
                calcularProduccion(tiempoDisponible, recursosDisponibles);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }

    } while (opcion != 0);

    return 0;
}
