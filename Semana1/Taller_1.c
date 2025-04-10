#include <stdio.h>

// PARALELO 5514
//INTEGRANTES: CHAMORRO DAVID Y MALDONADO ISAAC
//TAREA: S1 TALLER

int main() {
    int id, stock, cantidad, opcion;
    float precio, total_ganancias = 0;
    char nombre[30];

    printf(" \t--- BIENVENIDO ---\n ");

    printf("INGRESE EL ID DEL PRODUCTO:\n ");
    printf(">>");
    scanf("%d", &id);
    
    while(getchar() != '\n'); 
    
    printf("INGRESE EL NOMBRE DEL PRODUCTO:\n ");
    printf(">>");
    fgets(nombre, 30, stdin);
    
    do {
        printf("INGRESE LA CANTIDAD INICIAL EN STOCK:\n ");
        printf(">>");
        scanf("%d", &stock);
        if (stock < 0) {
            printf("ERROR: LA CANTIDAD INICIAL NO PUEDE SER NEGATIVA, INTENTE DE NUEVO\n");
        }
    } while (stock < 0);
    
    do {
        printf("INGRESE EL PRECIO UNITARIO DEL PRODUCTO:\n ");
        printf(">>");
        scanf("%f", &precio);
        if (precio < 0) {
            printf("ERROR: EL PRECIO UNITARIO NO PUEDE SER NEGATIVO, INTENTE DE NUEVO\n");
        }
    } while (precio < 0);

    do {
        printf("\t--- MENU DE OPCIONES---\n");
        printf("1. VENDER PRODUCTO\n");
        printf("2. REABASTECER STOCK DEL PRODUCTO\n");
        printf("3. MOSTRAR INFORMACION DEL PRODUCTO\n");
        printf("4. MOSTRAR TOTAL DE GANANCIAS\n");
        printf("5. SALIR\n");
        printf("SELECCIONE UNA OPCION:\n ");
        printf(">>");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("INGRESE LA CANTIDAD A VENDER:\n ");
                printf(">>");
                scanf("%d", &cantidad);

                
                if (cantidad < 0) {
                    printf("LA CANTIDAD A VENDER NO PUEDE SER NEGATIVA\n");
                } else if (cantidad <= stock) {
                    stock -= cantidad; 
                    total_ganancias += cantidad * precio; 
                    printf("VENTA REALIZADA CON EXITO. GANANCIA: $%.2f\n", cantidad * precio);
                } else {
                    printf("NO HAY SUFICIENTE STOCK PARA REALIZAR LA VENTA\n");
                }
                break;

            case 2:
                printf("INGRESE LA CANTIDAD A AGREGAR AL STOCK:\n ");
                printf(">>");
                scanf("%d", &cantidad);

                
                if (cantidad < 0) {
                    printf("LA CANTIDAD A AGREGAR NO PUEDE SER NEGATIVA\n");
                } else {
                    stock += cantidad; 
                    printf("STOCK ACTUALIZADO. NUEVO STOCK: %d\n", stock);
                }
                break;

            case 3:
                printf("\nINFORMACION DEL PRODUCTO\n");
                printf("ID: %d\n", id);
                printf("NOMBRE: %s", nombre);
                printf("STOCK DISPONIBLE: %d\n", stock);
                printf("PRECIO UNITARIO: %.2f\n", precio);
                break;

            case 4:
                printf("TOTAL DE GANANCIAS: $%.2f\n", total_ganancias);
                break;

            case 5:
                printf("SALIENDO DEL PROGRAMA... \n");
                printf("\t--- GRACIAS POR USAR EL PROGRAMA ---\n");
                break;

            default:
                printf("OPCION INVALIDA. INTENTE DE NUEVO\n");
        }
    } while (opcion != 5);

    return 0;
}
