#include <stdio.h>
#include <string.h>

#define MAX 10
#define SUCURSALES 3

// Declaración de funciones
int leerEnteroPositivo(const char mensaje[]);
int leerProductos(int codigos[], char nombres[][30], int cantidades[][SUCURSALES]);
int codigoRepetido(int codigos[], int n, int codigoNuevo);
void calcularTotalesPorProducto(int cantidades[][SUCURSALES], int totalPorProducto[], int n);
int calcularTotalGeneral(int totalPorProducto[], int n);
int buscarProducto(int codigos[], int n, int codigo);
void mostrarProducto(int codigos[], char nombres[][30], int cantidades[][SUCURSALES], int totalPorProducto[], int pos);
void sucursalMayorMenor(int cantidades[][SUCURSALES], int n);
void imprimirInventario(int codigos[], char nombres[][30], int cantidades[][SUCURSALES], int totalPorProducto[], int n);

// Función principal
int main() {
    int codigos[MAX];
    char nombres[MAX][30];
    int cantidades[MAX][SUCURSALES];
    int totalPorProducto[MAX];
    int n, totalGeneral, codigo, pos;

    n = leerProductos(codigos, nombres, cantidades);
    calcularTotalesPorProducto(cantidades, totalPorProducto, n);
    totalGeneral = calcularTotalGeneral(totalPorProducto, n);

    printf("\nTOTAL GENERAL EN STOCK: %d\n", totalGeneral);

    codigo = leerEnteroPositivo("\nINGRESE CODIGO DE PRODUCTO A BUSCAR: ");
    pos = buscarProducto(codigos, n, codigo);
    if (pos != -1)
        mostrarProducto(codigos, nombres, cantidades, totalPorProducto, pos);
    else
        printf("PRODUCTO NO ENCONTRADO\n");

    sucursalMayorMenor(cantidades, n);
    imprimirInventario(codigos, nombres, cantidades, totalPorProducto, n);

    return 0;
}

// Función para validar y leer solo enteros positivos
int leerEnteroPositivo(const char mensaje[]) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (valor <= 0) {
            printf("ERROR: DEBE SER UN NUMERO ENTERO POSITIVO\n");
        }
    } while (valor <= 0);
    return valor;
}

// Función para leer productos
int leerProductos(int codigos[], char nombres[][30], int cantidades[][SUCURSALES]) {
    int n, i, j, codigo;

    do {
        n = leerEnteroPositivo("CUANTOS PRODUCTOS DESEA INGRESAR (MAXIMO 10): ");
        if (n > MAX)
            printf("ERROR: EL LIMITE ES 10 PRODUCTOS\n");
    } while (n > MAX);

    for (i = 0; i < n; i++) {
        do {
            codigo = leerEnteroPositivo("INGRESE CODIGO DEL PRODUCTO: ");
        } while (codigoRepetido(codigos, i, codigo));
        codigos[i] = codigo;

        printf("INGRESE NOMBRE DEL PRODUCTO: ");
        scanf(" %[^\n]", nombres[i]);

        for (j = 0; j < SUCURSALES; j++) {
            char mensaje[50];
            sprintf(mensaje, "CANTIDAD EN SUCURSAL %d: ", j + 1);
            cantidades[i][j] = leerEnteroPositivo(mensaje);
        }
    }
    return n;
}

// Verifica si un código ya fue ingresado
int codigoRepetido(int codigos[], int n, int codigoNuevo) {
    for (int i = 0; i < n; i++) {
        if (codigos[i] == codigoNuevo) {
            printf("ERROR: CODIGO REPETIDO\n");
            return 1;
        }
    }
    return 0;
}

// Calcula el total por producto
void calcularTotalesPorProducto(int cantidades[][SUCURSALES], int totalPorProducto[], int n) {
    for (int i = 0; i < n; i++) {
        totalPorProducto[i] = 0;
        for (int j = 0; j < SUCURSALES; j++) {
            totalPorProducto[i] += cantidades[i][j];
        }
    }
}

// Calcula el total general del stock
int calcularTotalGeneral(int totalPorProducto[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += totalPorProducto[i];
    }
    return total;
}

// Busca un producto por código
int buscarProducto(int codigos[], int n, int codigo) {
    for (int i = 0; i < n; i++) {
        if (codigos[i] == codigo)
            return i;
    }
    return -1;
}

// Muestra la información detallada de un producto
void mostrarProducto(int codigos[], char nombres[][30], int cantidades[][SUCURSALES], int totalPorProducto[], int pos) {
    printf("\nPRODUCTO ENCONTRADO:\n");
    printf("CODIGO: %d\n", codigos[pos]);
    printf("NOMBRE: %s\n", nombres[pos]);
    for (int j = 0; j < SUCURSALES; j++) {
        printf("SUCURSAL %d: %d\n", j + 1, cantidades[pos][j]);
    }
    printf("TOTAL: %d\n", totalPorProducto[pos]);
}

// Determina y muestra la sucursal con mayor y menor cantidad
void sucursalMayorMenor(int cantidades[][SUCURSALES], int n) {
    int sumas[SUCURSALES] = {0};

    for (int j = 0; j < SUCURSALES; j++) {
        for (int i = 0; i < n; i++) {
            sumas[j] += cantidades[i][j];
        }
    }

    int mayor = 0, menor = 0;
    for (int j = 1; j < SUCURSALES; j++) {
        if (sumas[j] > sumas[mayor]) mayor = j;
        if (sumas[j] < sumas[menor]) menor = j;
    }

    printf("\nSUCURSAL CON MAYOR STOCK: SUCURSAL %d\n", mayor + 1);
    printf("SUCURSAL CON MENOR STOCK: SUCURSAL %d\n", menor + 1);
}

// Imprime todos los productos
void imprimirInventario(int codigos[], char nombres[][30], int cantidades[][SUCURSALES], int totalPorProducto[], int n) {
    printf("\nLISTA COMPLETA DEL INVENTARIO:\n");
    for (int i = 0; i < n; i++) {
        printf("CODIGO: %d | NOMBRE: %s | ", codigos[i], nombres[i]);
        for (int j = 0; j < SUCURSALES; j++) {
            printf("S%d: %d ", j + 1, cantidades[i][j]);
        }
        printf("| TOTAL: %d\n", totalPorProducto[i]);
    }
}
