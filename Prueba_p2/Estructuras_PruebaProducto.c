#include <stdio.h>
#define MAXPRODUCTOS 10
#define MAXLONGITUD 10
#define SUCURSALES 3
 
void leerDatos(char productos[MAXPRODUCTOS][MAXLONGITUD], int cod[MAXPRODUCTOS], int stock[MAXPRODUCTOS][SUCURSALES], int *cantidad);
int leerEntero(char *mensaje);
int leerEnteroRango(char *mensaje, int min, int max);
// Sin punteros int buscarCodigo(int cod[MAXPRODUCTOS], int busca, int cantidad);
// Con punteros
void buscarCodigo(int cod[MAXPRODUCTOS], int *indice, int cantidad, int busca);
void mostrarDatos(const char productos[MAXPRODUCTOS][MAXLONGITUD], const int cod[MAXPRODUCTOS], const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad);
void sumaStockProducto(const int stock[MAXPRODUCTOS][SUCURSALES],const char productos[MAXPRODUCTOS][MAXLONGITUD] ,int cantidad, int sumaProductos[MAXPRODUCTOS]);
void sumaTotalStock(const int stock[MAXPRODUCTOS][SUCURSALES],const char productos[MAXPRODUCTOS][MAXLONGITUD] ,int cantidad, int sumaProductos[MAXPRODUCTOS], int stockTotal );
 
int main(int argc, char *argv[])
{
    int cantidad = 0, indice;
    char productos[MAXPRODUCTOS][MAXLONGITUD];
    int cod[MAXPRODUCTOS];
    int stock[MAXPRODUCTOS][SUCURSALES];
    int sumaProductos[MAXPRODUCTOS];
    int stockTotal=0;
 
    leerDatos(productos, cod, stock, &cantidad);
    mostrarDatos(productos, cod, stock, cantidad);
    sumaStockProducto(stock, productos, cantidad, sumaProductos);
    sumaTotalStock(stock, productos, cantidad, sumaProductos,stockTotal);
 
 
 
    return 0;
}
 
int leerEntero(char *mensaje)
{
    int valor;
    printf("%s : ", mensaje);
    while (scanf("%d", &valor) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Dato incorrecto, vuelva a ingresar");
    }
    return valor;
}
int leerEnteroRango(char *mensaje, int min, int max)
{
    int valor;
    printf("%s entre %d y %d: ", mensaje, min, max);
    while (scanf("%d", &valor) != 1 || valor < min || valor > max)
    {
        while (getchar() != '\n')
            ;
        printf("Dato incorrecto, vuelva a ingresar: ");
    }
    return valor;
}
 
void leerDatos(char productos[MAXPRODUCTOS][MAXLONGITUD], int cod[MAXPRODUCTOS], int stock[MAXPRODUCTOS][SUCURSALES], int *cantidad)
{
    int indice;
    int resp;
    do
    {
        int codigo = leerEntero("INGRESE EL CODIGO: ");
        buscarCodigo(cod, &indice, *cantidad, codigo);
        if (indice == -1)
        {
            cod[*cantidad] = codigo;
            printf("INGRESE EL NOMBRE: ");
            scanf("%s", productos[*cantidad]);
 
            for (int i = 0; i < SUCURSALES; i++)
            {
                printf("INGRESE EL STOCK DE LA SURCUSAL %d: ", i + 1);
                scanf("%d", &stock[*cantidad][i]);
            }
 
            *cantidad += 1;
        }
        else
            printf("EL CODIGO YA EXISTE ");
 
        printf("1 PARA CONTINUAR INGRESANDO, OTRO VALOR PARA SALIR");
        resp = leerEnteroRango("0 PARA SALIR, CUALQUIER DIGITO PARA SALIR", 0, 9);
 
    } while (*cantidad < MAXPRODUCTOS && resp != 0);
}
 
void buscarCodigo(int cod[MAXPRODUCTOS], int *indice, int cantidad, int busca)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (cod[i] == busca)
        {
            *indice = i;
            return;
        }
    }
    *indice = -1;
}
 
void mostrarDatos(const char productos[MAXPRODUCTOS][MAXLONGITUD], const int cod[MAXPRODUCTOS], const int stock[MAXPRODUCTOS][SUCURSALES], int cantidad){
    for (int i = 0; i < cantidad; i++) {
        printf("codigo: %d \n", cod[i]);
        printf("nombre: %s \n", productos[i]);
 
        for (int j = 0; j < SUCURSALES; j++) {
            printf("stock sucursal %d : %d\n ", j+1, stock[i][j]);
        }
 
        printf("\n");
    }
 
}
 
void sumaStockProducto(const int stock[MAXPRODUCTOS][SUCURSALES],const char productos[MAXPRODUCTOS][MAXLONGITUD],int cantidad, int sumaProductos[MAXPRODUCTOS]){
 
   
    for (int i = 0; i < cantidad; i++)
    {
      int suma=0;
      for (int j = 0; j < SUCURSALES; j++)
      {
        suma+= stock[i][j];
      }
     
      sumaProductos[i]+=suma;
      printf("EL PRODUCTO %s TIENE %d TOTAL \n",productos[i],sumaProductos[i]);
 
    }
}
 
void sumaTotalStock(const int stock[MAXPRODUCTOS][SUCURSALES],const char productos[MAXPRODUCTOS][MAXLONGITUD] ,int cantidad, int sumaProductos[MAXPRODUCTOS], int stockTotal ){
    for (int i = 0; i < cantidad; i++)
    {
        stockTotal=+sumaProductos[i];
        printf("EL TOTAL DEL STOCK DE TODOS LOS PRODUCTOS ES: %d", stockTotal);
    }
   
}
 