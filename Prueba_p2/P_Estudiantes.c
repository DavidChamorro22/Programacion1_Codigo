#include <stdio.h>
#include <string.h>

#define MAX_ESTUDIANTES 10
#define MAX_NOMBRE 50
#define NUM_NOTAS 3

// Prototipos de funciones
int ingresarDatos(int codigos[], char nombres[][MAX_NOMBRE], float notas[][NUM_NOTAS]);
int esCodigoRepetido(int codigos[], int cantidad, int nuevoCodigo);
float calcularPromedioEstudiante(float notas[NUM_NOTAS]);
float calcularPromedioGrupo(float notas[][NUM_NOTAS], int cantidad);
int buscarPorCodigo(int codigos[], int cantidad, int codigo);
int indiceMayorPromedio(float promedios[], int cantidad);
int indiceMenorPromedio(float promedios[], int cantidad);
void imprimirListado(int codigos[], char nombres[][MAX_NOMBRE], float notas[][NUM_NOTAS], float promedios[], int cantidad);

int main() {
    int codigos[MAX_ESTUDIANTES];
    char nombres[MAX_ESTUDIANTES][MAX_NOMBRE];
    float notas[MAX_ESTUDIANTES][NUM_NOTAS];
    float promedios[MAX_ESTUDIANTES];
    int cantidad, i;

    cantidad = ingresarDatos(codigos, nombres, notas);

    for (i = 0; i < cantidad; i++) {
        promedios[i] = calcularPromedioEstudiante(notas[i]);
    }

    printf("\nPROMEDIO GENERAL DEL GRUPO: %.2f\n", calcularPromedioGrupo(notas, cantidad));

    int codigoBuscar;
    printf("\nINGRESE UN CODIGO PARA BUSCAR: ");
    scanf("%d", &codigoBuscar);
    int indice = buscarPorCodigo(codigos, cantidad, codigoBuscar);

    if (indice != -1) {
        printf("NOMBRE: %s\n", nombres[indice]);
        for (i = 0; i < NUM_NOTAS; i++) {
            printf("NOTA %d: %.2f\n", i + 1, notas[indice][i]);
        }
        printf("PROMEDIO: %.2f\n", promedios[indice]);
    } else {
        printf("ESTUDIANTE NO ENCONTRADO\n");
    }

    int mejor = indiceMayorPromedio(promedios, cantidad);
    int peor = indiceMenorPromedio(promedios, cantidad);

    printf("\nESTUDIANTE CON MEJOR PROMEDIO:\n");
    printf("CODIGO: %d\nNOMBRE: %s\nPROMEDIO: %.2f\n", codigos[mejor], nombres[mejor], promedios[mejor]);

    printf("\nESTUDIANTE CON PEOR PROMEDIO:\n");
    printf("CODIGO: %d\nNOMBRE: %s\nPROMEDIO: %.2f\n", codigos[peor], nombres[peor], promedios[peor]);

    printf("\nLISTADO COMPLETO DE ESTUDIANTES:\n");
    imprimirListado(codigos, nombres, notas, promedios, cantidad);

    return 0;
}

// INGRESO DE DATOS
int ingresarDatos(int codigos[], char nombres[][MAX_NOMBRE], float notas[][NUM_NOTAS]) {
    int n, i, j;

    do {
        printf("CUANTOS ESTUDIANTES DESEA INGRESAR (MAXIMO 10): ");
        scanf("%d", &n);
    } while (n < 1 || n > MAX_ESTUDIANTES);

    for (i = 0; i < n; i++) {
        int codigoValido = 0;

        while (!codigoValido) {
            printf("\nINGRESE CODIGO DEL ESTUDIANTE %d: ", i + 1);
            scanf("%d", &codigos[i]);
            if (esCodigoRepetido(codigos, i, codigos[i])) {
                printf("CODIGO REPETIDO. INGRESE OTRO\n");
            } else {
                codigoValido = 1;
            }
        }

        printf("INGRESE NOMBRE DEL ESTUDIANTE %d: ", i + 1);
        scanf(" %[^\n]", nombres[i]);

        for (j = 0; j < NUM_NOTAS; j++) {
            do {
                printf("INGRESE NOTA %d (0 A 10): ", j + 1);
                scanf("%f", &notas[i][j]);
                if (notas[i][j] < 0 || notas[i][j] > 10) {
                    printf("NOTA INVALIDA. DEBE ESTAR ENTRE 0 Y 10\n");
                }
            } while (notas[i][j] < 0 || notas[i][j] > 10);
        }
    }

    return n;
}

// VALIDAR CODIGO UNICO
int esCodigoRepetido(int codigos[], int cantidad, int nuevoCodigo) {
    for (int i = 0; i < cantidad; i++) {
        if (codigos[i] == nuevoCodigo) {
            return 1;
        }
    }
    return 0;
}

// CALCULAR PROMEDIO DE UN ESTUDIANTE
float calcularPromedioEstudiante(float notas[NUM_NOTAS]) {
    float suma = 0;
    for (int i = 0; i < NUM_NOTAS; i++) {
        suma += notas[i];
    }
    return suma / NUM_NOTAS;
}

// PROMEDIO DEL GRUPO
float calcularPromedioGrupo(float notas[][NUM_NOTAS], int cantidad) {
    float total = 0;
    for (int i = 0; i < cantidad; i++) {
        total += calcularPromedioEstudiante(notas[i]);
    }
    return total / cantidad;
}

// BUSCAR POR CODIGO
int buscarPorCodigo(int codigos[], int cantidad, int codigo) {
    for (int i = 0; i < cantidad; i++) {
        if (codigos[i] == codigo) {
            return i;
        }
    }
    return -1;
}

// MEJOR PROMEDIO
int indiceMayorPromedio(float promedios[], int cantidad) {
    int mayor = 0;
    for (int i = 1; i < cantidad; i++) {
        if (promedios[i] > promedios[mayor]) {
            mayor = i;
        }
    }
    return mayor;
}

// PEOR PROMEDIO
int indiceMenorPromedio(float promedios[], int cantidad) {
    int menor = 0;
    for (int i = 1; i < cantidad; i++) {
        if (promedios[i] < promedios[menor]) {
            menor = i;
        }
    }
    return menor;
}

// IMPRIMIR LISTADO
void imprimirListado(int codigos[], char nombres[][MAX_NOMBRE], float notas[][NUM_NOTAS], float promedios[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("\nCODIGO: %d\n", codigos[i]);
        printf("NOMBRE: %s\n", nombres[i]);
        for (int j = 0; j < NUM_NOTAS; j++) {
            printf("NOTA %d: %.2f\n", j + 1, notas[i][j]);
        }
        printf("PROMEDIO: %.2f\n", promedios[i]);
    }
}
