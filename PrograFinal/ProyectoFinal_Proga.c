#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZONAS 5
#define DIAS 30
#define LIMITE_PM25_OMS 25.0

typedef struct {
    char nombre[20];
    float historico[DIAS];
    float actual;
    float prediccion;
    float promedio;
    int alerta_actual;
    int alerta_prediccion;
} Zona;

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializarZonas(Zona zonas[]) {
    char* nombres[ZONAS] = {"CENTRO", "NORTE", "SUR", "ESTE", "OESTE"};
    float datos_historicos[ZONAS][DIAS] = {
        {20,22,24,23,25,26,28,24,22,20,21,23,24,22,25,26,28,29,27,25,24,23,22,21,20,19,18,22,24,25},
        {18,19,21,22,20,23,24,25,26,27,28,29,30,31,28,27,26,25,24,23,22,21,20,19,18,20,21,22,23,24},
        {26,27,28,29,30,31,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,20,21,22,23,24,25,26,27},
        {15,16,17,18,19,20,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,6,7,8,9,10},
        {23,24,25,26,27,28,29,30,31,32,33,34,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18}
    };

    for (int i = 0; i < ZONAS; i++) {
        strcpy(zonas[i].nombre, nombres[i]);
        for (int j = 0; j < DIAS; j++) {
            zonas[i].historico[j] = datos_historicos[i][j];
        }
        zonas[i].actual = 0;
        zonas[i].prediccion = 0;
        zonas[i].promedio = 0;
        zonas[i].alerta_actual = 0;
        zonas[i].alerta_prediccion = 0;
    }
}

float calcularPromedioHistorico(Zona *zona) {
    float suma = 0;
    for (int i = 0; i < DIAS; i++) {
        suma += zona->historico[i];
    }
    return suma / DIAS;
}

void mostrarPromedios(Zona zonas[]) {
    printf("\nPROMEDIO HISTORICO PM2.5 POR ZONA (ULTIMOS 30 DIAS)\n");
    printf("Zona      | Promedio (ug/m3)\n");
    printf("----------------------------\n");
    for (int i = 0; i < ZONAS; i++) {
        zonas[i].promedio = calcularPromedioHistorico(&zonas[i]);
        printf("%-9s| %.2f\n", zonas[i].nombre, zonas[i].promedio);
    }
    printf("\nOperacion: Se calcula el promedio de contaminacion para cada zona usando datos historicos.\n");
}

void monitoreoActual(Zona zonas[]) {
    printf("\nMONITOREO ACTUAL PM2.5\n");
    printf("Zona      | Nivel Actual (ug/m3) | Limite OMS (25 ug/m3) | Estado\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < ZONAS; i++) {
        // Simular nivel actual basado en promedio + variacion aleatoria
        zonas[i].actual = zonas[i].promedio + (rand() % 10 - 5) * 0.5;
        if (zonas[i].actual > LIMITE_PM25_OMS) {
            zonas[i].alerta_actual = 1;
            printf("%-9s| %.2f                | 25.00               | EXCEDE LIMITE\n", zonas[i].nombre, zonas[i].actual);
        } else {
            zonas[i].alerta_actual = 0;
            printf("%-9s| %.2f                | 25.00               | DENTRO DEL LIMITE\n", zonas[i].nombre, zonas[i].actual);
        }
    }
    printf("\nOperacion: Se compara el nivel actual con el limite OMS para detectar riesgos.\n");
}

void ingresarFactoresClimaticos(float *temp, float *viento, float *humedad, int zonaIdx, char nombreZona[]) {
    printf("\nINGRESE LOS FACTORES CLIMATICOS PARA LA ZONA %s\n", nombreZona);

    do {
        printf("Temperatura (°C) [ -10 a 50 ]: ");
        if (scanf("%f", temp) != 1 || *temp < -10 || *temp > 50) {
            printf("Valor invalido. Intente de nuevo.\n");
            limpiarBuffer();
            continue;
        }
        break;
    } while(1);

    limpiarBuffer();

    do {
        printf("Velocidad del viento (km/h) [ 0 a 150 ]: ");
        if (scanf("%f", viento) != 1 || *viento < 0 || *viento > 150) {
            printf("Valor invalido. Intente de nuevo.\n");
            limpiarBuffer();
            continue;
        }
        break;
    } while(1);

    limpiarBuffer();

    do {
        printf("Nivel de humedad (%%) [ 0 a 100 ]: ");
        if (scanf("%f", humedad) != 1 || *humedad < 0 || *humedad > 100) {
            printf("Valor invalido. Intente de nuevo.\n");
            limpiarBuffer();
            continue;
        }
        break;
    } while(1);

    limpiarBuffer();
}

void prediccion(Zona zonas[]) {
    printf("\nPREDICCION DE NIVELES DE CONTAMINACION PM2.5 PARA LAS PROXIMAS 24 HORAS\n");
    printf("Basado en datos historicos, niveles actuales y factores climaticos.\n");

    for (int i = 0; i < ZONAS; i++) {
        float temp, viento, humedad;
        ingresarFactoresClimaticos(&temp, &viento, &humedad, i, zonas[i].nombre);

        float base = 0.7 * zonas[i].promedio + 0.3 * zonas[i].actual;
        float ajuste = 0;

        if (temp > 30) ajuste += 2.0;
        if (viento > 20) ajuste -= 3.0;
        if (humedad > 70) ajuste += 1.5;

        zonas[i].prediccion = base + ajuste;
        if (zonas[i].prediccion < 0) zonas[i].prediccion = 0;

        if (zonas[i].prediccion > LIMITE_PM25_OMS) {
            zonas[i].alerta_prediccion = 1;
            printf("Zona %-7s| Prediccion: %.2f ug/m3 | EXCEDE LIMITE\n", zonas[i].nombre, zonas[i].prediccion);
        } else {
            zonas[i].alerta_prediccion = 0;
            printf("Zona %-7s| Prediccion: %.2f ug/m3 | DENTRO DEL LIMITE\n", zonas[i].nombre, zonas[i].prediccion);
        }
    }
    printf("\nOperacion: Se combina el promedio historico y nivel actual con factores climaticos para predecir.\n");
}

void alertasPreventivas(Zona zonas[]) {
    printf("\nALERTAS PREVENTIVAS POR NIVELES DE CONTAMINACION\n");
    for (int i = 0; i < ZONAS; i++) {
        if (zonas[i].alerta_actual || zonas[i].alerta_prediccion) {
            printf("Zona %s: ALERTA! ", zonas[i].nombre);
            if (zonas[i].alerta_actual && zonas[i].alerta_prediccion) {
                printf("Supera limite actual y prediccion.\n");
            } else if (zonas[i].alerta_actual) {
                printf("Supera limite actual.\n");
            } else {
                printf("Supera limite en prediccion.\n");
            }
        } else {
            printf("Zona %s: Niveles dentro del limite.\n", zonas[i].nombre);
        }
    }
    printf("\nOperacion: Se emiten alertas para zonas que superan limites actuales o previstos.\n");
}

void calcularYMostrarPromediosHistoricos(Zona zonas[]) {
    printf("\nCOMPARACION DE PROMEDIOS HISTORICOS CON LIMITE OMS\n");
    printf("Zona      | Promedio (ug/m3) | Limite OMS | Estado\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < ZONAS; i++) {
        zonas[i].promedio = calcularPromedioHistorico(&zonas[i]);
        if (zonas[i].promedio > LIMITE_PM25_OMS) {
            printf("%-9s| %.2f           | 25.00      | EXCEDE LIMITE\n", zonas[i].nombre, zonas[i].promedio);
        } else {
            printf("%-9s| %.2f           | 25.00      | DENTRO DEL LIMITE\n", zonas[i].nombre, zonas[i].promedio);
        }
    }
    printf("\nOperacion: Se calcula y compara el promedio historico con limite OMS.\n");
}

void recomendaciones(Zona zonas[]) {
    printf("\nRECOMENDACIONES DE MITIGACION SEGUN NIVELES ACTUALES Y PREDICCIONES\n");
    int hubo_recomendacion = 0;
    for (int i = 0; i < ZONAS; i++) {
        if (zonas[i].alerta_actual || zonas[i].alerta_prediccion) {
            printf("\nZona %s:\n", zonas[i].nombre);
            printf(" - Reduccion del trafico vehicular.\n");
            printf(" - Cierre temporal de industrias contaminantes.\n");
            printf(" - Suspension de actividades al aire libre.\n");
            hubo_recomendacion = 1;
        }
    }
    if (!hubo_recomendacion) {
        printf("No hay zonas con niveles elevados, no se requieren recomendaciones especiales.\n");
    }
    printf("\nOperacion: Se sugieren medidas si niveles actuales o previstos superan limites.\n");
}

void exportarDatos(Zona zonas[]) {
    FILE *archivo = fopen("reporte_contaminacion.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir archivo para exportacion.\n");
        return;
    }

    fprintf(archivo, "REPORTE DE CONTAMINACION POR ZONA\n\n");
    fprintf(archivo, "Zona      | Promedio Historico | Nivel Actual | Prediccion\n");
    fprintf(archivo, "-----------------------------------------------------------\n");
    for (int i = 0; i < ZONAS; i++) {
        fprintf(archivo, "%-9s| %.2f               | %.2f         | %.2f\n",
                zonas[i].nombre, zonas[i].promedio, zonas[i].actual, zonas[i].prediccion);
    }
    fclose(archivo);
    printf("\nDatos exportados exitosamente a reporte_contaminacion.txt\n");
    printf("Operacion: Se guardan datos relevantes para analisis posterior.\n");
}

int main() {
    Zona zonas[ZONAS];
    int opcion;

    inicializarZonas(zonas);

    do {
        printf("\n==== MENU SISTEMA DE GESTION Y PREDICCION DE CONTAMINACION ====\n");
        printf("1. Mostrar promedio historico por zona\n");
        printf("2. Monitoreo actual de contaminacion\n");
        printf("3. Prediccion de niveles futuros (24h)\n");
        printf("4. Alertas preventivas\n");
        printf("5. Calculo y comparacion de promedios historicos con limite OMS\n");
        printf("6. Generacion de recomendaciones\n");
        printf("7. Exportacion de datos a archivo\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Intente de nuevo.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        switch(opcion) {
            case 1:
                mostrarPromedios(zonas);
                break;
            case 2:
                monitoreoActual(zonas);
                break;
            case 3:
                prediccion(zonas);
                break;
            case 4:
                alertasPreventivas(zonas);
                break;
            case 5:
                calcularYMostrarPromediosHistoricos(zonas);
                break;
            case 6:
                recomendaciones(zonas);
                break;
            case 7:
                exportarDatos(zonas);
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 0);

    return 0;
}