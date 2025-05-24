//NOMBRE: DAVID CHAMORR
//TAREA: TALLER S8 RC1
//DOCENTE: BERNARDA SANDOVAL
//ASIGNATURA: PROGRAMACION I


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 50


void limpiarBuffer();
int leerEnteroPositivo(const char* mensaje);
void leerNombre(char* nombre);
int buscarProducto(const char* nombre);
void ingresarProducto();
void editarProducto();
void eliminarProducto();
void mostrarProductos();
void calcularProduccion();


char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
int cantidades[MAX_PRODUCTOS];
int tiempos[MAX_PRODUCTOS];
int recursos[MAX_PRODUCTOS];
int numProductos = 0;
int tiempoDisponible = 0, recursosDisponibles = 0;

void limpiarBuffer() {
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
}

int leerEnteroPositivo(const char* mensaje) {
    int val, valido;
    do {
        printf("%s", mensaje);
        valido = scanf("%d", &val);
        limpiarBuffer();
        if (valido != 1 || val <= 0) {
            printf("ENTRADA INVALIDA INTENTE DE NUEVO\n");
        }
    } while (val <= 0);
    return val;
}

void leerNombre(char* nombre) {
    char buffer[MAX_NOMBRE];
    while (1) {
        printf("INGRESE EL NOMBRE DEL PRODUCTO (SIN ESPACIOS): ");
        if (fgets(buffer, MAX_NOMBRE, stdin) == NULL) continue;
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        if (strlen(buffer) == 0) continue;

        int espacio = 0;
        for (size_t i = 0; i < strlen(buffer); i++)
            if (isspace((unsigned char)buffer[i])) espacio = 1;
        if (!espacio) {
            strcpy(nombre, buffer);
            break;
        }
        printf("NO DEBE CONTENER ESPACIOS\n");
    }
}

int buscarProducto(const char* nombre) {
    for (int i = 0; i < numProductos; i++)
        if (strcmp(nombres[i], nombre) == 0)
            return i;
    return -1;
}

void ingresarProducto() {
    if (numProductos >= MAX_PRODUCTOS) {
        printf("MAXIMO DE PRODUCTOS ALCANZADO\n");
        return;
    }
    leerNombre(nombres[numProductos]);
    cantidades[numProductos] = leerEnteroPositivo("INGRESE CANTIDAD DEMANDADA : ");
    tiempos[numProductos] = leerEnteroPositivo("INGRESE TIEMPO DE FABRICACION POR UNIDAD : ");
    recursos[numProductos] = leerEnteroPositivo("INGRESE RECURSOS POR UNIDAD : ");
    numProductos++;
    printf("PRODUCTO AGREGADO\n");
}

void editarProducto() {
    if (numProductos == 0) {
        printf("NO HAY PRODUCTOS PARA EDITAR\n");
        return;
    }
    char nombre[MAX_NOMBRE];
    printf("INGRESE EL NOMBRE DEL PRODUCTO A EDITAR: ");
    fgets(nombre, MAX_NOMBRE, stdin);
    size_t len = strlen(nombre);
    if (len > 0 && nombre[len - 1] == '\n') nombre[len - 1] = '\0';

    int idx = buscarProducto(nombre);
    if (idx == -1) {
        printf("PRODUCTO NO ENCONTRADO\n");
        return;
    }
    leerNombre(nombres[idx]);
    cantidades[idx] = leerEnteroPositivo("INGRESE NUEVA CANTIDAD DEMANDADA : ");
    tiempos[idx] = leerEnteroPositivo("INGRESE NUEVO TIEMPO DE FABRICACION POR UNIDAD : ");
    recursos[idx] = leerEnteroPositivo("INGRESE NUEVOS RECURSOS POR UNIDAD : ");
    printf("PRODUCTO EDITADO\n");
}

void eliminarProducto() {
    if (numProductos == 0) {
        printf("NO HAY PRODUCTOS PARA ELIMINAR\n");
        return;
    }
    char nombre[MAX_NOMBRE];
    printf("INGRESE EL NOMBRE DEL PRODUCTO A ELIMINAR: ");
    fgets(nombre, MAX_NOMBRE, stdin);
    size_t len = strlen(nombre);
    if (len > 0 && nombre[len - 1] == '\n') nombre[len - 1] = '\0';

    int idx = buscarProducto(nombre);
    if (idx == -1) {
        printf("PRODUCTO NO ENCONTRADO\n");
        return;
    }
    for (int i = idx; i < numProductos - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }
    numProductos--;
    printf("PRODUCTO ELIMINADO\n");
}

void mostrarProductos() {
    if (numProductos == 0) {
        printf("NO HAY PRODUCTOS REGISTRADOS\n");
        return;
    }
    printf("\nLISTA DE PRODUCTOS:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%d. %s | CANTIDAD: %d | TIEMPO: %d MINUTOS | RECURSOS: %d\n",
            i + 1, nombres[i], cantidades[i], tiempos[i], recursos[i]);
    }
}

void calcularProduccion() {
    if (numProductos == 0) {
        printf("NO HAY PRODUCTOS PARA CALCULAR\n");
        return;
    }
    int tiempoTotal = 0, recursosTotales = 0;
    for (int i = 0; i < numProductos; i++) {
        tiempoTotal += cantidades[i] * tiempos[i];
        recursosTotales += cantidades[i] * recursos[i];
    }
    printf("TIEMPO TOTAL REQUERIDO: %d MINUTOS\n", tiempoTotal);
    printf("RECURSOS TOTALES REQUERIDOS: %d UNIDADES\n", recursosTotales);

    if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles)
        printf("LA FABRICA PUEDE CUMPLIR CON LA DEMANDA\n");
    else
        printf("LA FABRICA NO PUEDE CUMPLIR CON LA DEMANDA\n");
}

int main() {
    int opcion;

    printf("\t--- SISTEMA DE OPTIMIZACION DE PRODUCCION ---\n");
    tiempoDisponible = leerEnteroPositivo("INGRESE TIEMPO DE PRODUCCION DISPONIBLE (MINUTOS): ");
    recursosDisponibles = leerEnteroPositivo("INGRESE RECURSOS DISPONIBLES : ");

    do {
        printf("\nMENU:\n1 - INGRESAR PRODUCTO\n2 - EDITAR PRODUCTO\n3 - ELIMINAR PRODUCTO\n4 - MOSTRAR PRODUCTOS\n5 - CALCULAR PRODUCCION\n0 - SALIR\n");
        printf("SELECCIONE UNA OPCION: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1: ingresarProducto(); break;
            case 2: editarProducto(); break;
            case 3: eliminarProducto(); break;
            case 4: mostrarProductos(); break;
            case 5: calcularProduccion(); break;
            case 0: printf("SALIENDO DEL SISTEMA\n"); break;
            default: printf("OPCION INVALIDA\n");
        }
    } while (opcion != 0);

    return 0;
}
