#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#include <malloc.h>
#define N 7

typedef char cadena[30];

typedef struct info{
    int nroPlanta;
    cadena nombre;
    int CantProd;
};

typedef struct emp{
    cadena nombre;
    int CantProd;
    int dni;
    cadena nomEmp;
    cadena EstadoS;
    int hijos;
    int plantaNum;
    int NumCat;
};

typedef struct cat{
    int NumCat;
    cadena NomCat;
    float sueldo;
};

struct lista {
    emp punto1;
    struct lista *sig;
};

typedef struct lista *puntero;

typedef struct puntoA{
    cadena nombre;   //nombre planta//
    int CantProducto;
   puntero cabexa;  
};

int menu(){
    int opcion;
    printf("[1]Generar un arreglo de 7 componentes\n");
    printf("[2]Listado con los datos almacenados\n");
    printf("[3]Ingresa dni y modifica info. de un empleado○\n");
    printf("[4]Ingresa dni y elimina info. de un empleado\n");
    printf("[5]Crear lista para empleados con sueldo adicional con hijos\n");
    printf("[6]Listado ordenado alfabeticamente\n");
    printf("[7]Generar un archivo con la informacion de la lista\n");
    printf("[0] Salir del Programa\n");
    printf ("--->  ");
    scanf ("%d", &opcion);
    return opcion;
}

void insertarLista (puntero &cab, FILE *empleados) {
    emp E;
    puntero nuevo;
    while (fread (&E, sizeof(E), 1, empleados) != 0) {
        nuevo = (puntero) malloc (sizeof (struct lista));
        strcpy (nuevo->punto1.nombre, E.nombre);
        strcpy (nuevo->punto1.nomEmp, E.nomEmp);        
        strcpy (nuevo->punto1.EstadoS, E.EstadoS);
        nuevo->punto1.CantProd = E.CantProd;   
        nuevo->punto1.dni = E.dni;
        nuevo->punto1.hijos = E.hijos;
        nuevo->punto1.plantaNum = E.plantaNum;
        nuevo->punto1.NumCat = E.NumCat;
        nuevo->sig = cab;
        cab = nuevo;    
    }
return;
}

void cargaPunto1 (PuntoA registro[N], FILE *planta, FILE *empleados) {
    int i;
    info p;
    for (i = 0; i < N; i++) {
        while ((fread (&p, sizeof(p), 1, planta) != 0 )) {
            
            if (strcmp (registro[i].nombre, p.nombre) != 0) {
                strcpy (registro[i].nombre, p.nombre);
                registro[i].CantProducto= p.CantProd; 
            }
        }
        registro[i].cabexa = NULL;
        insertarLista (registro[i].cabexa, empleados);
    }
    return;
}

void mostrarLista(puntero cabeza){
    int longitud;
    while(cabza!=NULL){
        printf("%s               %3d             %s                %3d",cabeza->punto1.nomEmp,cabeza->punto1.NumCat,cabeza->punto1.EstadoS,cabeza->punto1.hijos);
        longitud += 1;
        cabeza = cabeza->sig;
    }
    printf("\nTotal de empleados: %d", longitud);
    return;
}

void listado(PuntoA registro[N]){
    int i;
    for (i=0;i<N;i++){
        printf("NUMERO DE PLANTA: %d               NOMBRE DE PLANTA: %s", i+1, registro[i].nombre);
        printf("PRODUCTOS QUE ELABORA: %d\n",registro[i].CantProducto);
        printf ("\nNombre de empleado     Categoría   Estado civil 	   Cantidad de Hijos");
        mostrarLista (registro[i].cabexa);
        printf ("\n");      //Para la siguiente planta
    }
    return;
}

int main (){
FILE *planta,*empleados,*categoria;
PuntoA registro[N];
int op;
planta = fopen ("PLANTAS.DAT", "rb");
empleados = fopen("EMPLEADOS.DAT", "rb");
categoria = fopen ("CATEGORIA.DAT", "rb");

if ((planta != NULL) && (empleados != NULL) && (categoria != NULL)) {
    do {
        op = menu ();
        switch (op)
        {
        case 1: cargaPunto1 (registro, planta, empleados); 
            break;
        case 2: listado(registro);
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
        default: printf ("\nIngreso opcion INCORRECTA, intentelo de nuevo\n");
            break;
        case 0: printf("\nIngreso SALIR, termina el programa\n");
            break;
        }
    } while (op != 0);
    
    } else {
        printf("La apertura no se realizo\n")
        printf("\nEl archivo no ha sido creado correctamente\n");
    }

return 0;
}