#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_IN "promedios.txt"
#define FILE_OUT "valores.txt"
#define MAX 15

// Definicion de constantes
float PM10_OMS = 45.0;
float PM25_OMS = 15.0;
float CO_OMS = 4.0;
float NO2_OMS = 25.0;
float SO2_OMS = 40.0;

// Variables globales para exportar datos
int yaExportoContaminacionActual = 0;
int yaExportoPrediccionFuturo = 0;
int yaExportoPromediosHistoricos = 0;

// Declaración de funciones
void ingresarDatos();
void contaminacionActual();
void sugerirMedida(int contaminante, float valor, int exportado);
void prediccionfuturo(float temperatura, float viento, float humedad);
void promediosHistoricos();
void exportarDatos(int opcion, char *ciudad, int anio, float pm25, float co, float no2, float so2, float pm10, char *origen);

typedef struct {
    char ciudad[20];
    int anio;
    float N02;
    float C0;
    float S02;
    float PM25;
    float PM10;
} valores;

int main() {
    int opc;
    printf("Ingresando datos...\n");
    ingresarDatos();
    do {
        printf("Bienvenido al sistema de monitoreo de calidad del aire.\n");
        printf("Este programa analiza los niveles de contaminacion PM2.5, PM10, CO, NO2 y SO2 en diferentes ciudades.\n");
        printf("Las zonas analizadas de Quito son: Tumbaco, Carapungo, Centro, Chillos y Cotocollao.\n");
        printf("Todos los datos se almacenan en el archivo 'resultados.txt'.\n\n");
        printf("Ingresa una opcion:\n");
        printf("1. Ver contaminacion actual\n");
        printf("2. Prediccion de contaminacion futura\n");
        printf("3. Promedios historicos de contaminacion\n");
        printf("4. Salir\n");
        
        // Validación de entrada
        while (scanf("%d", &opc) != 1 || opc < 1 || opc > 4) {
            printf("Entrada invalida. Por favor, ingrese un numero.\n");
            while (getchar() != '\n'); // Limpiar el buffer
        }
        
        // Manejo de opciones
        switch (opc) {
            case 1:
                contaminacionActual();
                break;
            case 2: {
                float temperatura, viento, humedad;
                printf("Ingrese la temperatura actual (Celsius): ");
                while (scanf("%f", &temperatura) != 1 || temperatura < -50 || temperatura > 50) {
                    printf("Entrada invalida. Por favor, ingrese un numero.\n");
                    while (getchar() != '\n');
                }
                printf("Ingrese la velocidad del viento (km/h): ");
                while (scanf("%f", &viento) != 1 || viento < 0) {
                    printf("Entrada invalida. Por favor, ingrese un numero.\n");
                    while (getchar() != '\n');
                }
                printf("Ingrese la humedad relativa: ");
                while (scanf("%f", &humedad) != 1 || humedad < 0 || humedad > 100) {
                    printf("Entrada invalida. Por favor, ingrese un numero entre 0 y 100.\n");
                    while (getchar() != '\n');
                }
                prediccionfuturo(temperatura, viento, humedad);
                break;
            }
            case 3:
                promediosHistoricos();
                break;
            default:
                printf("Saliendo del programa\n");
        }
    } while (opc != 4);
    return 0;
}

void exportarDatos(int opcion, char *ciudad, int anio, float pm25, float co, float no2, float so2, float pm10, char *origen) {
    FILE *archivo = fopen("valores.txt", "a"); // Modo anadir (append)
    if (!archivo) {
        printf("No se pudo abrir 'valores.txt' para exportar datos.\n");
        return;
    }
    
    // Exportar datos según la opción
    switch (opcion) {
        case 1: // Contaminación actual
            fprintf(archivo, "-------------------------------\n");
            fprintf(archivo, "\n# CONTAMINACION ACTUAL - Ciudad: %s, Año: %d\n", ciudad, anio);
            fprintf(archivo, "PM10: %.2f\t(OMS: %.2f)\n", pm10, PM10_OMS);
            fprintf(archivo, "PM2.5: %.2f\t(OMS: %.2f)\n", pm25, PM25_OMS);
            fprintf(archivo, "CO: %.2f\t(OMS: %.2f)\n", co, CO_OMS);
            fprintf(archivo, "NO2: %.2f\t(OMS: %.2f)\n", no2, NO2_OMS);
            fprintf(archivo, "SO2: %.2f\t(OMS: %.2f)\n", so2, SO2_OMS);
            break;

        case 2: // Predicción futura
            fprintf(archivo, "-------------------------------\n");
            fprintf(archivo, "\n# PREDICCION FUTURA - Ciudad: %s (Aprox. proximas 24h)\n", ciudad);
            fprintf(archivo, "PM10 estimado: %.2f\n", pm10);
            fprintf(archivo, "PM2.5 estimado: %.2f\n", pm25);
            fprintf(archivo, "CO estimado: %.2f\n", co);
            fprintf(archivo, "NO2 estimado: %.2f\n", no2);
            fprintf(archivo, "SO2 estimado: %.2f\n", so2);
            break;

        case 3: // Promedios históricos
            fprintf(archivo, "-------------------------------\n");
            fprintf(archivo, "\n# PROMEDIOS HISTORICOS - Ciudad: %s (2023-2025)\n", ciudad);
            fprintf(archivo, "PM10 promedio: %.2f\t(OMS: %.2f)\n", pm10, PM10_OMS);
            fprintf(archivo, "PM2.5 promedio: %.2f\t(OMS: %.2f)\n", pm25, PM25_OMS);
            fprintf(archivo, "CO promedio: %.2f\t(OMS: %.2f)\n", co, CO_OMS);
            fprintf(archivo, "NO2 promedio: %.2f\t(OMS: %.2f)\n", no2, NO2_OMS);
            fprintf(archivo, "SO2 promedio: %.2f\t(OMS: %.2f)\n", so2, SO2_OMS);
            break;

        case 4: // sugerir medidas
            fprintf(archivo, "ALERTA Y SUGERENCIA DE MEDIDA\n");
            fprintf(archivo, "Contaminante con alerta: %s\texcede el limite (%.2f > %.2f)\n", ciudad, pm25, co);
            fprintf(archivo, " %s\n", origen);  // Aquí 'origen' se usa como texto de sugerencia y ciudad como el nombre del contaminante
            fprintf(archivo, "-------------------------------\n");
            break;

        default:
            fprintf(archivo, "EXPORTACION SIN CATEGORIA - Ciudad: %s, Anio: %d\n", ciudad, anio);
            fprintf(archivo, "PM2.5: %.2f, CO: %.2f, NO2: %.2f, SO2: %.2f, PM10: %.2f\n", pm25, co, no2, so2, pm10);
            fprintf(archivo, "Origen: %s\n", origen);
            fprintf(archivo, "-------------------------------\n");
            break;
    }

    fclose(archivo);
}

void ingresarDatos() {
    FILE *entrada, *salida;
    valores datos[MAX];
    int count = 0;

    // Abrir archivo de entrada
    entrada = fopen("promedios.txt", "r");
    if (entrada == NULL) {
        printf("Error al abrir el archivo de entrada.\n");
        return;
    }

    char linea[200];

    // Leer y descartar la primera línea (encabezados)
    fgets(linea, sizeof(linea), entrada);

    // Leer línea por línea y guardar en estructura
    while (fscanf(entrada, "%s %d %f %f %f %f %f",
                  datos[count].ciudad,
                  &datos[count].anio,
                  &datos[count].PM25,
                  &datos[count].C0,
                  &datos[count].N02,
                  &datos[count].S02,
                  &datos[count].PM10) == 7) {
        count++;
    }
    fclose(entrada);

    // Abrir archivo de salida
    salida = fopen("valores.txt", "w");
    if (salida == NULL) {
        printf("Error al crear el archivo de salida.\n");
        return;
    }

    // Escribir datos en el nuevo archivo
    fprintf(salida, "Ciudad\tAño\tPM2.5\tCO\tNO2\tSO2\tPM10\n");
    for (int i = 0; i < count; i++) {
        fprintf(salida, "%s\t%d\t%.2f\t%.2f\t%.3f\t%.3f\t%.3f\n",
                datos[i].ciudad,
                datos[i].anio,
                datos[i].PM25,
                datos[i].C0,
                datos[i].N02,
                datos[i].S02,
                datos[i].PM10);
    }
    fclose(salida);
    printf("Datos guardados exitosamente en 'valores.txt'\n\n");
    return;
}

void contaminacionActual() {
    FILE *archivo = fopen("valores.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    
    char linea[200];
    fgets(linea, sizeof(linea), archivo); // encabezado

    printf("Contaminacion Actual:\n\n");

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char ciudad[50];
        int anio;
        float pm25, co, no2, so2, pm10;

        if (sscanf(linea, "%s %d %f %f %f %f %f", ciudad, &anio, &pm25, &co, &no2, &so2, &pm10) == 7) {
            if (anio == 2025) {
                printf("Ciudad: %s, Anio: %d\n\n", ciudad, anio);

                char *nombres[] = {"PM2.5", "CO", "NO2", "SO2", "PM10"};
                float valoresActuales[] = {pm25, co, no2, so2, pm10};
                float valoresOMS[] = {PM25_OMS, CO_OMS, NO2_OMS, SO2_OMS, PM10_OMS};
                
                // Exportar datos si no se ha hecho más de 5 veces
                if (yaExportoContaminacionActual < 5) {
                    exportarDatos(1, ciudad, anio, pm25, co, no2, so2, pm10, "ContaminacionActual");
                    yaExportoContaminacionActual += 1;
                }
                
                // Mostrar resultados
                for (int i = 0; i < 5; i++) {
                    printf("  %s: %.2f (OMS: %.2f):\n", nombres[i], valoresActuales[i], valoresOMS[i]);
                    if (valoresActuales[i] > valoresOMS[i]) {
                        printf("FUERA DEL LIMITE\n");
                        sugerirMedida(i + 1, valoresActuales[i], yaExportoContaminacionActual);
                    } else {
                        printf("DENTRO DEL LIMITE\n");
                    }
                }
                yaExportoContaminacionActual += 1;
                printf("\n");
            }
        }
    }
    fclose(archivo);
}

void sugerirMedida(int contaminante, float valor, int exportado) {
    switch (contaminante) {
        case 1:
            printf("Alerta: PM2.5 excede el limite (%.2f > %.2f)\n", valor, PM25_OMS);
            printf("Sugerencia: Reducir trafico vehicular y suspender actividades al aire libre.\n");
            if (exportado <= 5) {
                exportarDatos(4, "PM2.5", 0, valor, PM25_OMS, 0, 0, 0, "Sugerencia: Reducir trafico vehicular y suspender actividades al aire libre");
            }
            break;
        case 2:
            printf("Alerta: CO excede el limite (%.2f > %.2f)\n", valor, CO_OMS);
            printf("Sugerencia: Control estricto de emisiones industriales.\n");
            if (exportado <= 5) {
                exportarDatos(4, "CO", 0, valor, CO_OMS, 0, 0, 0, "Sugerencia: Control estricto de emisiones industriales.");
            }
            break;
        case 3:
            printf("Alerta: NO2 excede el limite (%.2f > %.2f)\n", valor, NO2_OMS);
            printf("Sugerencia: Fomentar transporte publico y energias limpias.\n");
            if (exportado <= 5) {
                exportarDatos(4, "NO2", 0, valor, NO2_OMS, 0, 0, 0, "Sugerencia: Fomentar transporte publico y energias limpias");
            }
            break;
        case 4:
            printf("Alerta: SO2 excede el limite (%.2f > %.2f)\n", valor, SO2_OMS);
            printf("Sugerencia: Restringir temporalmente industrias contaminantes.\n");
            if (exportado <= 5) {
                exportarDatos(4, "SO2", 0, valor, SO2_OMS, 0, 0, 0, "Sugerencia: Restringir temporalmente industrias contaminantes");
            }
            break;
        case 5:
            printf("Alerta: PM10 excede el limite (%.2f > %.2f)\n", valor, PM10_OMS);
            printf("Sugerencia: Limitar actividades al aire libre y reforzar medidas de control del polvo.\n");
            if (exportado <= 5) {
                exportarDatos(4, "PM10", 0, valor, PM10_OMS, 0, 0, 0, "Sugerencia: Limitar actividades al aire libre y reforzar medidas de control del polvo");
            }
            break;
        default:
            printf("Contaminante no reconocido. Consulta a las autoridades ambientales.\n");
    }
}

void prediccionfuturo(float temperatura, float viento, float humedad) {
    /* Inicio de función de predicción futura de contaminación */
    FILE *archivo_que_contiene_datos = NULL;
    archivo_que_contiene_datos = fopen(FILE_OUT, "r"); // Abrir el archivo que contiene los datos
    
    if (archivo_que_contiene_datos == NULL) {
        printf("Error al intentar abrir el archivo que contiene los valores\n");
        return; // Salir si no se pudo abrir
    } else {
        /* Si se abrió correctamente, continuar */
        char linea_del_archivo[200]; // Buffer para leer líneas
        valores datos_lectura[MAX]; // Estructura para almacenar datos
        int contador_de_datos = 0; // Contador para llevar registro
        
        // Primero leer la línea de encabezado y descartarla
        fgets(linea_del_archivo, sizeof(linea_del_archivo), archivo_que_contiene_datos);
        
        /* Leer cada línea del archivo */
        while (fgets(linea_del_archivo, sizeof(linea_del_archivo), archivo_que_contiene_datos) != NULL 
               && contador_de_datos < MAX) {
            int resultado_escaneo = sscanf(linea_del_archivo, 
                                          "%s %d %f %f %f %f %f",
                                          datos_lectura[contador_de_datos].ciudad,
                                          &datos_lectura[contador_de_datos].anio,
                                          &datos_lectura[contador_de_datos].PM25,
                                          &datos_lectura[contador_de_datos].C0,
                                          &datos_lectura[contador_de_datos].N02,
                                          &datos_lectura[contador_de_datos].S02,
                                          &datos_lectura[contador_de_datos].PM10);
            if (resultado_escaneo != 7) {
                /* Si no se leyeron todos los valores, ignorar línea */
                continue;
            }
            contador_de_datos = contador_de_datos + 1;
        }
        
        fclose(archivo_que_contiene_datos); // No olvidar cerrar el archivo
        
        /* Cálculo del factor climático */
        float factor_de_clima_calculado = 1.0;
        factor_de_clima_calculado = factor_de_clima_calculado + (temperatura - 20.0) * 0.01;
        factor_de_clima_calculado = factor_de_clima_calculado + (60.0 - humedad) * 0.005;
        factor_de_clima_calculado = factor_de_clima_calculado - (viento * 0.02);
        
        printf("\n--- Prediccion de contaminación para las próximas 24 horas ---\n");
        
        /* Procesar por ciudad */
        for (int indice_principal = 0; indice_principal < contador_de_datos; indice_principal++) {
            char nombre_ciudad_actual[20];
            strcpy(nombre_ciudad_actual, datos_lectura[indice_principal].ciudad);
            
            /* Verificar si ya se procesó esta ciudad */
            int ciudad_ya_procesada = 0;
            for (int indice_secundario = 0; indice_secundario < indice_principal; indice_secundario++) {
                if (strcmp(nombre_ciudad_actual, datos_lectura[indice_secundario].ciudad) == 0) {
                    ciudad_ya_procesada = 1;
                    break;
                }
            }
            
            if (ciudad_ya_procesada == 0) {
                /* Calcular promedio ponderado */
                int total_elementos = 0;
                float suma_PM10 = 0.0, suma_PM25 = 0.0, suma_CO = 0.0, suma_NO2 = 0.0, suma_SO2 = 0.0;
                
                for (int indice_terciario = 0; indice_terciario < contador_de_datos; indice_terciario++) {
                    if (strcmp(datos_lectura[indice_terciario].ciudad, nombre_ciudad_actual) == 0) {
                        float peso_ponderado = indice_terciario + 1; // El peso aumenta con la posición
                        suma_PM10 = suma_PM10 + (datos_lectura[indice_terciario].PM10 * peso_ponderado);
                        suma_PM25 = suma_PM25 + (datos_lectura[indice_terciario].PM25 * peso_ponderado);
                        suma_CO = suma_CO + (datos_lectura[indice_terciario].C0 * peso_ponderado);
                        suma_NO2 = suma_NO2 + (datos_lectura[indice_terciario].N02 * peso_ponderado);
                        suma_SO2 = suma_SO2 + (datos_lectura[indice_terciario].S02 * peso_ponderado);
                        total_elementos = total_elementos + peso_ponderado;
                    }
                }
                
                if (total_elementos > 0) {
                    /* Calcular predicciones */
                    float prediccion_PM10 = (suma_PM10 / total_elementos) * factor_de_clima_calculado;
                    float prediccion_PM25 = (suma_PM25 / total_elementos) * factor_de_clima_calculado;
                    float prediccion_CO = (suma_CO / total_elementos) * factor_de_clima_calculado;
                    float prediccion_NO2 = (suma_NO2 / total_elementos) * factor_de_clima_calculado;
                    float prediccion_SO2 = (suma_SO2 / total_elementos) * factor_de_clima_calculado;
                    
                    /* Mostrar resultados */
                    printf("Ciudad: %s\n\n", nombre_ciudad_actual);
                    
                    char* nombres_contaminantes[] = {"PM10", "PM2.5", "CO", "NO2", "SO2"};
                    float valores_predichos[] = {prediccion_PM10, prediccion_PM25, prediccion_CO, prediccion_NO2, prediccion_SO2};
                    float limites_OMS[] = {PM10_OMS, PM25_OMS, CO_OMS, NO2_OMS, SO2_OMS};
                    
                    for (int indice_contaminante = 0; indice_contaminante < 5; indice_contaminante++) {
                        printf("  %s: %.2f (OMS: %.2f): ", 
                               nombres_contaminantes[indice_contaminante],
                               valores_predichos[indice_contaminante],
                               limites_OMS[indice_contaminante]);
                        
                        if (valores_predichos[indice_contaminante] > limites_OMS[indice_contaminante]) {
                            printf("FUERA DEL LIMITE\n");
                            sugerirMedida(indice_contaminante + 1, valores_predichos[indice_contaminante], yaExportoPrediccionFuturo);
                        } else {
                            printf("DENTRO DEL LIMITE\n");
                        }
                    }
                    
                    /* Exportar datos si no se ha alcanzado el límite */
                    if (yaExportoPrediccionFuturo < 5) {
                        char* texto_origen = "Prediccion_24_horas";
                        exportarDatos(2, 
                                    nombre_ciudad_actual, 
                                    2025, 
                                    prediccion_PM25, 
                                    prediccion_CO, 
                                    prediccion_NO2, 
                                    prediccion_SO2, 
                                    prediccion_PM10, 
                                    texto_origen);
                        yaExportoPrediccionFuturo = yaExportoPrediccionFuturo + 1;
                    }
                    
                    printf("\n");
                }
            }
        }
    }
}

void promediosHistoricos() {
    /* Función para calcular y mostrar promedios históricos */
    FILE* puntero_archivo = fopen(FILE_OUT, "r");
    
    if (puntero_archivo == NULL) {
        printf("Error de apertura de archivo\n");
        return;
    }
    
    /* Variables para almacenar datos */
    valores datos_almacenados[MAX];
    int cantidad_datos = 0;
    char buffer_linea[200];
    
    /* Leer y descartar encabezado */
    fgets(buffer_linea, sizeof(buffer_linea), puntero_archivo);
    
    /* Leer datos del archivo */
    while (fgets(buffer_linea, sizeof(buffer_linea), puntero_archivo) != NULL 
           && cantidad_datos < MAX) {
        sscanf(buffer_linea, 
               "%s %d %f %f %f %f %f",
               datos_almacenados[cantidad_datos].ciudad,
               &datos_almacenados[cantidad_datos].anio,
               &datos_almacenados[cantidad_datos].PM25,
               &datos_almacenados[cantidad_datos].C0,
               &datos_almacenados[cantidad_datos].N02,
               &datos_almacenados[cantidad_datos].S02,
               &datos_almacenados[cantidad_datos].PM10);
        cantidad_datos = cantidad_datos + 1;
    }
    
    fclose(puntero_archivo);
    
    printf("\n--- Promedios Históricos (últimos 3 años) ---\n");
    
    /* Procesar por ciudad */
    for (int indice_ciudad = 0; indice_ciudad < cantidad_datos; indice_ciudad++) {
        /* Verificar si ya se procesó esta ciudad */
        int ciudad_repetida = 0;
        
        for (int indice_comparacion = 0; indice_comparacion < indice_ciudad; indice_comparacion++) {
            if (strcmp(datos_almacenados[indice_ciudad].ciudad, 
                       datos_almacenados[indice_comparacion].ciudad) == 0) {
                ciudad_repetida = 1;
                break;
            }
        }
        
        if (ciudad_repetida == 0) {
            /* Variables para cálculos */
            float acumulador_PM10 = 0.0;
            float acumulador_PM25 = 0.0;
            float acumulador_CO = 0.0;
            float acumulador_NO2 = 0.0;
            float acumulador_SO2 = 0.0;
            int contador_registros = 0;
            
            /* Sumar valores para esta ciudad */
            for (int indice_busqueda = 0; indice_busqueda < cantidad_datos; indice_busqueda++) {
                if (strcmp(datos_almacenados[indice_ciudad].ciudad, 
                           datos_almacenados[indice_busqueda].ciudad) == 0 
                    && datos_almacenados[indice_busqueda].anio >= 2023 
                    && datos_almacenados[indice_busqueda].anio <= 2025) {
                    /* Acumular valores */
                    acumulador_PM10 = acumulador_PM10 + datos_almacenados[indice_busqueda].PM10;
                    acumulador_PM25 = acumulador_PM25 + datos_almacenados[indice_busqueda].PM25;
                    acumulador_CO = acumulador_CO + datos_almacenados[indice_busqueda].C0;
                    acumulador_NO2 = acumulador_NO2 + datos_almacenados[indice_busqueda].N02;
                    acumulador_SO2 = acumulador_SO2 + datos_almacenados[indice_busqueda].S02;
                    contador_registros = contador_registros + 1;
                }
            }
            
            if (contador_registros > 0) {
                /* Calcular promedios */
                float promedio_PM10 = acumulador_PM10 / contador_registros;
                float promedio_PM25 = acumulador_PM25 / contador_registros;
                float promedio_CO = acumulador_CO / contador_registros;
                float promedio_NO2 = acumulador_NO2 / contador_registros;
                float promedio_SO2 = acumulador_SO2 / contador_registros;
                
                /* Mostrar resultados */
                printf("\nCiudad: %s\n", datos_almacenados[indice_ciudad].ciudad);
                printf("  Promedio PM10: %.2f (OMS: %.2f) %s\n", 
                       promedio_PM10, 
                       PM10_OMS,
                       (promedio_PM10 > PM10_OMS) ? "FUERA DEL LIMITE" : "DENTRO DEL LIMITE");
                printf("  Promedio PM2.5: %.2f (OMS: %.2f) %s\n", 
                       promedio_PM25, 
                       PM25_OMS,
                       (promedio_PM25 > PM25_OMS) ? "FUERA DEL LIMITE" : "DENTRO DEL LIMITE");
                printf("  Promedio CO: %.2f (OMS: %.2f) %s\n", 
                       promedio_CO,
                       CO_OMS,
                       (promedio_CO > CO_OMS) ? "FUERA DEL LIMITE" : "DENTRO DEL LIMITE");
                printf("  Promedio NO2: %.2f (OMS: %.2f) %s\n", 
                       promedio_NO2,
                       NO2_OMS,
                       (promedio_NO2 > NO2_OMS) ? "FUERA DEL LIMITE" : "DENTRO DEL LIMITE");
                printf("  Promedio SO2: %.2f (OMS: %.2f) %s\n", 
                       promedio_SO2,
                       SO2_OMS,
                       (promedio_SO2 > SO2_OMS) ? "FUERA DEL LIMITE" : "DENTRO DEL LIMITE");
                
                /* Exportar datos si no se ha alcanzado el límite */
                if (yaExportoPromediosHistoricos < 5) {
                    exportarDatos(3,
                                datos_almacenados[indice_ciudad].ciudad,
                                0, // No hay año específico para promedios
                                promedio_PM25,
                                promedio_CO,
                                promedio_NO2,
                                promedio_SO2,
                                promedio_PM10,
                                "Promedios_Historicos");
                    yaExportoPromediosHistoricos = yaExportoPromediosHistoricos + 1;
                }
            }
        }
    }
}
