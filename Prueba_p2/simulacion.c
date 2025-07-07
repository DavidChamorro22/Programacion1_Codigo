#include <stdio.h>
#include <string.h>

#define ZONAS 5
#define DIAS 30
#define LIMITE_PM25_OMS 25.0  // µg/m3, límite para PM2.5 según OMS

typedef struct {
    char nombre[20];
    float historico[DIAS];  // Últimos 30 días
    float actual;           // Dato actual del día
    float promedio;         // Promedio histórico (solo históricos)
    float prediccion;       // Predicción para próximas 24h
    int alerta_actual;      // 1 si actual supera límite, 0 si no
    int alerta_prediccion;  // 1 si predicción supera límite, 0 si no
} Zona;

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para validar entrada float dentro de un rango
float leerFloatRango(const char* mensaje, float min, float max) {
    float valor;
    int res;
    do {
        printf("%s", mensaje);
        res = scanf("%f", &valor);
        limpiarBuffer();
        if (res != 1) {
            printf("Entrada invalida, ingrese un numero valido.\n");
        } else if (valor < min || valor > max) {
            printf("Valor fuera de rango [%.2f - %.2f]. Intente nuevamente.\n", min, max);
        } else {
            break;
        }
    } while(1);
    return valor;
}

void inicializarZonas(Zona zonas[]) {
    strcpy(zonas[0].nombre, "Centro");
    strcpy(zonas[1].nombre, "Norte");
    strcpy(zonas[2].nombre, "Sur");
    strcpy(zonas[3].nombre, "Este");
    strcpy(zonas[4].nombre, "Oeste");

    float datos_hist[ZONAS][DIAS] = {
        {22, 24, 23, 25, 26, 24, 23, 22, 24, 23, 25, 26, 24, 23, 22, 24, 23, 25, 26, 24, 23, 22, 24, 23, 25, 26, 24, 23, 22, 24},
        {20, 21, 19, 22, 21, 20, 19, 20, 21, 19, 22, 21, 20, 19, 20, 21, 19, 22, 21, 20, 19, 20, 21, 19, 22, 21, 20, 19, 20, 21},
        {30, 29, 31, 28, 30, 29, 31, 28, 30, 29, 31, 28, 30, 29, 31, 28, 30, 29, 31, 28, 30, 29, 31, 28, 30, 29, 31, 28, 30, 29},
        {15, 16, 14, 17, 15, 16, 14, 17, 15, 16, 14, 17, 15, 16, 14, 17, 15, 16, 14, 17, 15, 16, 14, 17, 15, 16, 14, 17, 15, 16},
        {27, 28, 26, 29, 27, 28, 26, 29, 27, 28, 26, 29, 27, 28, 26, 29, 27, 28, 26, 29, 27, 28, 26, 29, 27, 28, 26, 29, 27, 28}
    };

    for(int i = 0; i < ZONAS; i++) {
        for(int j = 0; j < DIAS; j++) {
            zonas[i].historico[j] = datos_hist[i][j];
        }
    }

    zonas[0].actual = 27.5;
    zonas[1].actual = 20.5;
    zonas[2].actual = 32.0;
    zonas[3].actual = 16.0;
    zonas[4].actual = 28.5;
}

float calcularPromedioHistorico(Zona z) {
    float suma = 0;
    for(int i = 0; i < DIAS; i++) {
        suma += z.historico[i];
    }
    return suma / DIAS;
}

float calcularPromedioHistoricoActual(Zona z) {
    float suma = 0;
    for(int i = 0; i < DIAS; i++) {
        suma += z.historico[i];
    }
    suma += z.actual;
    return suma / (DIAS + 1);
}

void calcularPromediosHistoricos(Zona zonas[]) {
    for(int i = 0; i < ZONAS; i++) {
        zonas[i].promedio = calcularPromedioHistorico(zonas[i]);
    }
}

void mostrarPromedios(Zona zonas[]) {
    printf("\nLIMITE PERMITIDO POR LA OMS PARA PM2.5: %.2f UG/M3\n", LIMITE_PM25_OMS);
    printf("PROMEDIO DE CONTAMINACION POR ZONA (ULTIMOS 30 DIAS MAS DATO ACTUAL):\n");
    printf("-------------------------------------------------------------------\n");
    printf("%-10s | %-20s | %-10s | %-10s\n", "ZONA", "PROMEDIO HIST+ACTUAL", "ACTUAL", "ESTADO");
    for(int i = 0; i < ZONAS; i++) {
        float promedioExtendido = calcularPromedioHistoricoActual(zonas[i]);
        printf("%-10s | %-20.2f | %-10.2f | %-10s\n",
            zonas[i].nombre,
            promedioExtendido,
            zonas[i].actual,
            (promedioExtendido > LIMITE_PM25_OMS) ? "FUERA LIMITE" : "DENTRO");
    }
}

void monitoreoActual(Zona zonas[]) {
    printf("\nMONITOREO DE CONTAMINACION ACTUAL:\n");
    printf("---------------------------------\n");
    printf("%-10s | %-10s | %-10s\n", "ZONA", "ACTUAL", "ESTADO");
    for(int i = 0; i < ZONAS; i++) {
        zonas[i].alerta_actual = (zonas[i].actual > LIMITE_PM25_OMS) ? 1 : 0;
        printf("%-10s | %-10.2f | %-10s\n", zonas[i].nombre, zonas[i].actual,
               zonas[i].alerta_actual ? "FUERA LIMITE" : "DENTRO LIMITE");
    }
}

void prediccion(Zona zonas[]) {
    float temperatura = leerFloatRango("TEMPERATURA (°C) [-50 a 60]: ", -50, 60);
    float viento = leerFloatRango("VELOCIDAD DEL VIENTO (km/h) [0 a 150]: ", 0, 150);
    float humedad = leerFloatRango("NIVEL DE HUMEDAD (%) [0 a 100]: ", 0, 100);

    printf("\nPREDICCION DE NIVELES FUTUROS PARA LAS 5 ZONAS:\n");
    printf("----------------------------------------------\n");
    printf("%-10s | %-12s | %-50s\n", "ZONA", "PREDICCION", "EXPLICACION");

    for(int i = 0; i < ZONAS; i++) {
        float peso_actual = 0.5;
        float peso_historico = 0.5;
        float promedio_historico = calcularPromedioHistorico(zonas[i]);

        float factor_clima = 1.0;
        if(temperatura > 30) factor_clima += 0.1;
        if(viento < 5) factor_clima += 0.15;
        if(humedad > 70) factor_clima += 0.05;

        zonas[i].prediccion = (peso_actual * zonas[i].actual + peso_historico * promedio_historico) * factor_clima;
        zonas[i].alerta_prediccion = (zonas[i].prediccion > LIMITE_PM25_OMS) ? 1 : 0;

        printf("%-10s | %-12.2f | ", zonas[i].nombre, zonas[i].prediccion);
        if(zonas[i].alerta_prediccion) {
            printf("PREDICCION FUERA DE LIMITE OMS\n");
        } else {
            printf("PREDICCION DENTRO DE LIMITE OMS\n");
        }
    }
}

void alertasPreventivas(Zona zonas[]) {
    printf("\nALERTAS PREVENTIVAS:\n");
    printf("-------------------\n");
    for(int i = 0; i < ZONAS; i++) {
        if(zonas[i].alerta_actual && zonas[i].alerta_prediccion) {
            printf("ZONA %s: ALERTA MUY ALTA (ACTUAL Y PREDICCION FUERA LIMITE OMS)\n", zonas[i].nombre);
        } else if(zonas[i].alerta_actual) {
            printf("ZONA %s: ALERTA ACTUAL (NIVEL ACTUAL FUERA LIMITE OMS)\n", zonas[i].nombre);
        } else if(zonas[i].alerta_prediccion) {
            printf("ZONA %s: ALERTA PREDICCION (NIVEL PREDICHO FUERA LIMITE OMS)\n", zonas[i].nombre);
        } else {
            printf("ZONA %s: SIN ALERTAS\n", zonas[i].nombre);
        }
    }
}

void calcularYMostrarPromediosHistoricos(Zona zonas[]) {
    calcularPromediosHistoricos(zonas);
    printf("\nPROMEDIO HISTORICO ULTIMOS 30 DIAS POR ZONA:\n");
    printf("--------------------------------------------\n");
    printf("%-10s | %-15s | %-10s\n", "ZONA", "PROMEDIO HIST", "ESTADO");
    for(int i = 0; i < ZONAS; i++) {
        printf("%-10s | %-15.2f | %-10s\n", zonas[i].nombre, zonas[i].promedio,
               zonas[i].promedio > LIMITE_PM25_OMS ? "FUERA LIMITE" : "DENTRO LIMITE");
    }
}

void generacionRecomendaciones(Zona zonas[]) {
    printf("\nRECOMENDACIONES PARA MITIGAR CONTAMINACION:\n");
    printf("-------------------------------------------\n");
    for(int i = 0; i < ZONAS; i++) {
        int superar_limite = (zonas[i].alerta_actual || zonas[i].alerta_prediccion);
        if(superar_limite) {
            printf("ZONA %s:\n", zonas[i].nombre);
            printf(" - Reducir uso de vehículos particulares.\n");
            printf(" - Fomentar uso de transporte público y bicicletas.\n");
            printf(" - Controlar emisiones industriales.\n");
            printf(" - Monitorear regularmente la calidad del aire.\n");
        } else {
            printf("ZONA %s: Niveles dentro del límite, mantener medidas preventivas.\n", zonas[i].nombre);
        }
    }
}

int main() {
    Zona zonas[ZONAS];
    int opcion;
    inicializarZonas(zonas);

    do {
        printf("\n--- MENU DE MONITOREO DE CONTAMINACION ---\n");
        printf("1. Promedios de contaminacion por zona\n");
        printf("2. Monitoreo actual\n");
        printf("3. Prediccion\n");
        printf("4. Alertas preventivas\n");
        printf("5. Calculo de promedios historicos\n");
        printf("6. Generacion de recomendaciones\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion (1-7): ");

        while (scanf("%d", &opcion) != 1 || opcion < 1 || opcion > 7) {
            printf("Opcion invalida. Intente nuevamente: ");
            limpiarBuffer();
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
                generacionRecomendaciones(zonas);
                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
        }

    } while(opcion != 7);

    return 0;
}
