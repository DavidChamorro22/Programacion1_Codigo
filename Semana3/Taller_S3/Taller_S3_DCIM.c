#include <stdio.h>
// PARALELO 5514
//INTEGRANTES: CHAMORRO DAVID Y MALDONADO ISAAC
//TAREA: S1 TALLER


#define ESTUDIANTES 5
#define ASIGNATURAS 3

int main() {
    float calificaciones[ESTUDIANTES][ASIGNATURAS];
    float promedio_estudiantes[ESTUDIANTES], promedio_asignaturas[ASIGNATURAS];
    float max_calificacion[ESTUDIANTES], min_calificacion[ESTUDIANTES];
    float max_asignatura[ASIGNATURAS], min_asignatura[ASIGNATURAS];
    int aprobados[ASIGNATURAS], reprobados[ASIGNATURAS];

    printf("\t---SISTEMA DE INGRESO DE NOTAS---");

    for (int i = 0; i < ESTUDIANTES; i++) {
        printf("\nINGRESO DE CALIFICACIONES DEL ESTUDIANTE %d:\n", i + 1);
        for (int j = 0; j < ASIGNATURAS; j++) {
            float calificacion;
            while (1) {
                printf("INGRESE LA CALIFICACION EN LA ASIGNATURA %d (0-10):\n ", j + 1);
                printf(">>");
                if (scanf("%f", &calificacion) != 1) {
                    printf("ENTRADA INVALIDA, POR FAVOR INGRESE UN NUMERO\n");
                    while (getchar() != '\n');
                } else if (calificacion < 0 || calificacion > 10) {
                    printf("CALIFICACION INVALIDA, DEBE ESTAR ENTRE 0 Y 10\n");
                } else {
                    calificaciones[i][j] = calificacion;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < ESTUDIANTES; i++) {
        float suma = 0;
        max_calificacion[i] = calificaciones[i][0];
        min_calificacion[i] = calificaciones[i][0];
        for (int j = 0; j < ASIGNATURAS; j++) {
            suma += calificaciones[i][j];
            if (calificaciones[i][j] > max_calificacion[i]) max_calificacion[i] = calificaciones[i][j];
            if (calificaciones[i][j] < min_calificacion[i]) min_calificacion[i] = calificaciones[i][j];
        }
        promedio_estudiantes[i] = suma / ASIGNATURAS;
    }

    for (int j = 0; j < ASIGNATURAS; j++) {
        float suma = 0;
        max_asignatura[j] = calificaciones[0][j];
        min_asignatura[j] = calificaciones[0][j];
        for (int i = 0; i < ESTUDIANTES; i++) {
            suma += calificaciones[i][j];
            if (calificaciones[i][j] > max_asignatura[j]) max_asignatura[j] = calificaciones[i][j];
            if (calificaciones[i][j] < min_asignatura[j]) min_asignatura[j] = calificaciones[i][j];
        }
        promedio_asignaturas[j] = suma / ESTUDIANTES;
    }

    for (int j = 0; j < ASIGNATURAS; j++) {
        aprobados[j] = 0;
        reprobados[j] = 0;
        for (int i = 0; i < ESTUDIANTES; i++) {
            if (calificaciones[i][j] >= 6) aprobados[j]++;
            else reprobados[j]++;
        }
    }

    printf("\n\t---PROMEDIO POR ESTUDIANTE---\n");
    for (int i = 0; i < ESTUDIANTES; i++) {
        printf("ESTUDIANTE %d: %.2f (CALIFICACION MAS ALTA: %.2f, CALIFICACION MAS BAJA: %.2f)\n", i + 1, promedio_estudiantes[i], max_calificacion[i], min_calificacion[i]);
    }
    printf("\n");

    printf("\t---PROMEDIO POR ASIGNATURA---\n");
    for (int j = 0; j < ASIGNATURAS; j++) {
        printf("ASIGNATURA %d: %.2f (CALIFICACION MAS ALTA: %.2f, CALIFICACION MAS BAJA: %.2f)\n", j + 1, promedio_asignaturas[j], max_asignatura[j], min_asignatura[j]);
    }
    printf("\n");

    printf("\t---APROBADOS Y REPROBADOS POR ASIGNATURA---\n");
    for (int j = 0; j < ASIGNATURAS; j++) {
        printf("ASIGNATURA %d - APROBADOS: %d, REPROBADOS: %d\n", j + 1, aprobados[j], reprobados[j]);
    }
    printf("\n");

    return 0;
}

