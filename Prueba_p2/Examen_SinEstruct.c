#include <stdio.h>
#define MAXPRODUCTOS 10
#define MAXLONGITUD 50
#define SUCURSALES 3

// Prototipos
int leerEntero(char *mensaje);
int leerEnteroRango(char *mensaje, int min, int max);
void leerDatos(char productos[MAXPRODUCTOS][MAXLONGITUD], int cod[MAXPRODUCTOS], int stock[MAXPRODUCTOS][SUCURSALES], int *cantidad);
int buscarCodigo(const int cod[MAXPRODUCTOS], int cantidad, int codigoBuscado);
void calcularTotalesPorProducto(const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad, int totalPorProducto[MAXPRODUCTOS]);
int calcularTotalGeneral(const int totalPorProducto[MAXPRODUCTOS], int cantidad);
void buscarYMostrarProducto(const int cod[MAXPRODUCTOS], const char productos[MAXPRODUCTOS][MAXLONGITUD], const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad, int codigoBuscado);
void sucursalMayorYMenor(const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad);
void mostrarInventarioCompleto(const int cod[MAXPRODUCTOS], const char productos[MAXPRODUCTOS][MAXLONGITUD], const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad);

int main() {
    int cantidad = 0;
    char productos[MAXPRODUCTOS][MAXLONGITUD];
    int cod[MAXPRODUCTOS];
    int stock[MAXPRODUCTOS][SUCURSALES];
    int totalPorProducto[MAXPRODUCTOS] = {0};

    int opcion;

    do {
        printf("\n--- MENU INVENTARIO TIENDA ELECTRONICA ---\n");
        printf("1. Ingresar datos de productos\n");
        printf("2. Mostrar inventario completo\n");
        printf("3. Buscar producto por codigo\n");
        printf("4. Mostrar sucursal con mayor y menor stock\n");
        printf("5. Mostrar total general de stock\n");
        printf("0. Salir\n");
        opcion = leerEnteroRango("Seleccione opcion", 0, 5);

        switch(opcion) {
            case 1:
                leerDatos(productos, cod, stock, &cantidad);
                // Al actualizar datos, recalculamos totales
                calcularTotalesPorProducto(stock, cantidad, totalPorProducto);
                printf("Datos ingresados correctamente.\n");
                break;
            case 2:
                if (cantidad == 0) {
                    printf("No hay productos registrados.\n");
                } else {
                    mostrarInventarioCompleto(cod, productos, stock, cantidad);
                }
                break;
            case 3:
                if (cantidad == 0) {
                    printf("No hay productos registrados para buscar.\n");
                } else {
                    int codigoBusqueda = leerEntero("Ingrese codigo a buscar");
                    buscarYMostrarProducto(cod, productos, stock, cantidad, codigoBusqueda);
                }
                break;
            case 4:
                if (cantidad == 0) {
                    printf("No hay productos registrados.\n");
                } else {
                    sucursalMayorYMenor(stock, cantidad);
                }
                break;
            case 5:
                if (cantidad == 0) {
                    printf("No hay productos registrados.\n");
                } else {
                    int totalGeneral = calcularTotalGeneral(totalPorProducto, cantidad);
                    printf("Total general de stock de todos los productos: %d\n", totalGeneral);
                }
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida, intente de nuevo.\n");
        }

    } while (opcion != 0);

    return 0;
}

int leerEntero(char *mensaje) {
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor) != 1) {
        while (getchar() != '\n'); 
        printf("Dato incorrecto, vuelva a ingresar: ");
    }
    return valor;
}

int leerEnteroRango(char *mensaje, int min, int max) {
    int valor;
    printf("%s (%d-%d): ", mensaje, min, max);
    while (scanf("%d", &valor) != 1 || valor < min || valor > max) {
        while (getchar() != '\n');
        printf("Dato incorrecto, vuelva a ingresar: ");
    }
    return valor;
}

void leerDatos(char productos[MAXPRODUCTOS][MAXLONGITUD], int cod[MAXPRODUCTOS], int stock[MAXPRODUCTOS][SUCURSALES], int *cantidad) {
    while (*cantidad < MAXPRODUCTOS) {
        int codigo = leerEntero("Ingrese codigo unico");
        if (buscarCodigo(cod, *cantidad, codigo) == -1) {
            cod[*cantidad] = codigo;

            printf("Ingrese nombre del producto: ");
            scanf("%s", productos[*cantidad]);

            for (int i = 0; i < SUCURSALES; i++) {
                stock[*cantidad][i] = leerEnteroRango("Ingrese stock sucursal", 0, 10000);
            }
            (*cantidad)++;

            printf("Producto ingresado correctamente.\n");

            int continuar = leerEnteroRango("Desea ingresar otro producto? 1=Si 0=No", 0, 1);
            if (continuar == 0) break;
        } else {
            printf("ERROR: Codigo ya existe, ingrese otro codigo.\n");
        }
    }
}

int buscarCodigo(const int cod[MAXPRODUCTOS], int cantidad, int codigoBuscado) {
    for (int i = 0; i < cantidad; i++) {
        if (cod[i] == codigoBuscado) return i;
    }
    return -1;
}

void calcularTotalesPorProducto(const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad, int totalPorProducto[MAXPRODUCTOS]) {
    for (int i = 0; i < cantidad; i++) {
        int suma = 0;
        for (int j = 0; j < SUCURSALES; j++) {
            suma += stock[i][j];
        }
        totalPorProducto[i] = suma;
    }
}

int calcularTotalGeneral(const int totalPorProducto[MAXPRODUCTOS], int cantidad) {
    int total = 0;
    for (int i = 0; i < cantidad; i++) {
        total += totalPorProducto[i];
    }
    return total;
}

void buscarYMostrarProducto(const int cod[MAXPRODUCTOS], const char productos[MAXPRODUCTOS][MAXLONGITUD], const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad, int codigoBuscado) {
    int indice = buscarCodigo(cod, cantidad, codigoBuscado);
    if (indice == -1) {
        printf("Producto con codigo %d no encontrado.\n", codigoBuscado);
        return;
    }
    printf("Producto encontrado:\n");
    printf("Codigo: %d\n", cod[indice]);
    printf("Nombre: %s\n", productos[indice]);
    int suma = 0;
    for (int i = 0; i < SUCURSALES; i++) {
        printf("Stock sucursal %d: %d\n", i + 1, stock[indice][i]);
        suma += stock[indice][i];
    }
    printf("Stock total del producto: %d\n", suma);
}

void sucursalMayorYMenor(const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad) {
    int sumaSucursales[SUCURSALES] = {0};

    for (int j = 0; j < SUCURSALES; j++) {
        for (int i = 0; i < cantidad; i++) {
            sumaSucursales[j] += stock[i][j];
        }
    }

    int mayor = 0, menor = 0;
    for (int i = 1; i < SUCURSALES; i++) {
        if (sumaSucursales[i] > sumaSucursales[mayor]) mayor = i;
        if (sumaSucursales[i] < sumaSucursales[menor]) menor = i;
    }

    printf("Sucursal con mayor stock total: %d (Stock total: %d)\n", mayor + 1, sumaSucursales[mayor]);
    printf("Sucursal con menor stock total: %d (Stock total: %d)\n", menor + 1, sumaSucursales[menor]);
}

void mostrarInventarioCompleto(const int cod[MAXPRODUCTOS], const char productos[MAXPRODUCTOS][MAXLONGITUD], const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad) {
    printf("CODIGO\tNOMBRE\t\tSUCURSAL1\tSUCURSAL2\tSUCURSAL3\tTOTAL\n");
    for (int i = 0; i < cantidad; i++) {
        int suma = 0;
        printf("%d\t%s\t\t", cod[i], productos[i]);
        for (int j = 0; j < SUCURSALES; j++) {
            printf("%d\t\t", stock[i][j]);
            suma += stock[i][j];
        }
        printf("%d\n", suma);
    }
}
