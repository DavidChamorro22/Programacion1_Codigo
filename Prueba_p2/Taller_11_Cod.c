#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIBROS 10


struct Libro {
    int id;
    char titulo[101];
    char autor[51];
    int anio;
    char estado[11];
};

// ARREGLO GLOBAL
struct Libro libros[MAX_LIBROS];
int cantidad = 0;

int leerEntero(char *mensaje, int min, int max) {
    int valor, resultado;
    do {
        printf("%s", mensaje);
        resultado = scanf("%d", &valor);
        while (getchar() != '\n');
        if (resultado != 1 || valor < min || valor > max) {
            printf("ENTRADA INVALIDA. INGRESE UN NUMERO ENTRE %d Y %d\n", min, max);
        }
    } while (resultado != 1 || valor < min || valor > max);
    return valor;
}

void leerCadena(char *mensaje, char *cadena, int tamano) {
    do {
        printf("%s", mensaje);
        fgets(cadena, tamano, stdin);
        cadena[strcspn(cadena, "\n")] = 0;
        if (strlen(cadena) == 0) {
            printf("      NO SE PERMITEN CADENAS VACIAS\n");
        }
    } while (strlen(cadena) == 0);
}

int buscarLibroPorID(int id) {
    for (int i = 0; i < cantidad; i++) {
        if (libros[i].id == id) return i;
    }
    return -1;
}

int menu() {
    return leerEntero(
        "\nMENU\n1. REGISTRAR LIBRO\n2. MOSTRAR TODOS LOS LIBROS\n3. BUSCAR LIBRO\n4. ACTUALIZAR ESTADO\n5. ELIMINAR LIBRO\n6. SALIR\nINGRESE OPCION: ",
        1, 6);
}

void registrarLibro() {
    if (cantidad >= MAX_LIBROS) {
        printf("NO SE PUEDEN REGISTRAR MAS LIBROS\n");
        return;
    }

    int id = leerEntero("INGRESE ID UNICO DEL LIBRO: ", 1, 10000);
    if (buscarLibroPorID(id) != -1) {
        printf("ERROR: EL ID YA EXISTE\n");
        return;
    }

    struct Libro nuevo;
    nuevo.id = id;
    leerCadena("INGRESE TITULO: ", nuevo.titulo, 101);
    leerCadena("INGRESE AUTOR: ", nuevo.autor, 51);
    nuevo.anio = leerEntero("INGRESE ANIO DE PUBLICACION (1900 A 2100): ", 1900, 2100);
    strcpy(nuevo.estado, "Disponible");

    libros[cantidad] = nuevo;
    cantidad++;
    printf("LIBRO REGISTRADO CON EXITO\n");
}

void mostrarLibros() {
    if (cantidad == 0) {
        printf("NO HAY LIBROS REGISTRADOS\n");
        return;
    }

    printf("\n%-5s %-30s %-20s %-6s %-10s\n", "ID", "TITULO", "AUTOR", "ANIO", "ESTADO");
    for (int i = 0; i < cantidad; i++) {
        printf("%-5d %-30s %-20s %-6d %-10s\n",
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].anio,
               libros[i].estado);
    }
}

void buscarLibro() {
    int opcion = leerEntero("BUSCAR POR:\n1. ID\n2. TITULO\nOPCION: ", 1, 2);

    if (opcion == 1) {
        int id = leerEntero("INGRESE ID: ", 1, 10000);
        int pos = buscarLibroPorID(id);
        if (pos == -1) {
            printf("LIBRO NO ENCONTRADO\n");
        } else {
            printf("ID: %d\nTITULO: %s\nAUTOR: %s\nANIO: %d\nESTADO: %s\n",
                   libros[pos].id, libros[pos].titulo, libros[pos].autor,
                   libros[pos].anio, libros[pos].estado);
        }
    } else {
        char titulo[101];
        leerCadena("INGRESE TITULO: ", titulo, 101);
        int encontrado = 0;
        for (int i = 0; i < cantidad; i++) {
            if (strcmp(libros[i].titulo, titulo) == 0) {
                printf("ID: %d\nTITULO: %s\nAUTOR: %s\nANIO: %d\nESTADO: %s\n",
                       libros[i].id, libros[i].titulo, libros[i].autor,
                       libros[i].anio, libros[i].estado);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("LIBRO NO ENCONTRADO\n");
        }
    }
}

void actualizarEstado() {
    int id = leerEntero("INGRESE ID DEL LIBRO A ACTUALIZAR: ", 1, 10000);
    int pos = buscarLibroPorID(id);
    if (pos == -1) {
        printf("LIBRO NO ENCONTRADO\n");
        return;
    }

    if (strcmp(libros[pos].estado, "Disponible") == 0) {
        strcpy(libros[pos].estado, "Prestado");
    } else {
        strcpy(libros[pos].estado, "Disponible");
    }
    printf("ESTADO ACTUALIZADO A %s\n", libros[pos].estado);
}

void eliminarLibro() {
    int id = leerEntero("INGRESE ID DEL LIBRO A ELIMINAR: ", 1, 10000);
    int pos = buscarLibroPorID(id);
    if (pos == -1) {
        printf("LIBRO NO ENCONTRADO\n");
        return;
    }

    if (strcmp(libros[pos].estado, "Prestado") == 0) {
        printf("NO SE PUEDE ELIMINAR UN LIBRO PRESTADO\n");
        return;
    }

    for (int i = pos; i < cantidad - 1; i++) {
        libros[i] = libros[i + 1];
    }
    cantidad--;
    printf("LIBRO ELIMINADO CON EXITO\n");
}

int main() {
    int opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case 1: registrarLibro(); break;
            case 2: mostrarLibros(); break;
            case 3: buscarLibro(); break;
            case 4: actualizarEstado(); break;
            case 5: eliminarLibro(); break;
            case 6: printf("SALIENDO DEL PROGRAMA...\n"); break;
        }
    } while (opcion != 6);
    return 0;
}

