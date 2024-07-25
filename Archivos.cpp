#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#include <malloc.h>
#define P 7
#define C 5

typedef char cadena[30];

typedef struct info{
    int nroPlanta;
    cadena nombre;
    int CantProd;
};

typedef struct emp{
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

void cargaPlantas (FILE *planta,info plt){
    int i;
    for(i=0;i < P;i++){

        plt.nroPlanta = i+1;
        printf("Ingrese el nombre de planta %d\n",i+1);
        fgets(plt.nombre,30,stdin);
        strtok (plt.nombre, "\n");
        printf("Ingrese cantidad de productos que elabora\n");
        scanf("%d",&plt.CantProd);
        fwrite (&plt, sizeof(plt), 1, planta);
        printf ("\n-----------------------------------------------");
    }

}

int cargaEmpleados(FILE *empleados, emp EMP[100]){
int cont=0;
printf("Ingrese nombre del empleado\n");
fgets(EMP[cont].nomEmp,30,stdin);
strtok(EMP[cont].nomEmp, "\n");
while(strcmp(EMP[cont].nomEmp,"fin")!=0){

    printf("Ingrese numero de planta\n");
    scanf("%d",&EMP[cont].plantaNum);
    printf("Ingrese DNI del empleado\n");
    scanf("%d",&EMP[cont].dni);
    fflush(stdin);
    printf("A que categoria pertenece el empleado?\n");
    scanf("%d",&EMP[cont].NumCat);
    printf("Que estado civil posee?\n");
    fgets(EMP[cont].EstadoS,30,stdin);
    strtok(EMP[cont].EstadoS, "\n");
    printf("Cuantos hijos posee el empleado\n");
    scanf("%d",&EMP[cont].hijos);
    cont++;
    printf ("\n-----------------------------------------------");
    printf("Ingrese nombre del empleado\n");
    fgets(EMP[cont].nomEmp,30,stdin);
    strtok(EMP[cont].nomEmp, "\n");
   
}
 return cont;
}

//Ordenamos arr de empleados de acuerdo al nro de Planta, despues grabamos en archivo ya ordenado
void ordenaEmp (FILE *empleados, emp EMP[100], int c) {
    emp aux;
    int i, cota, k=1;
    while (k != -1) {
        k = -1;
        for (i=0; i < cota; i++) {
            if (EMP[i].plantaNum > EMP[i+1].plantaNum) {
                aux = EMP[i];
                EMP[i] = EMP[i+1];
                EMP[i+1] = aux;
                k = i;
            }
            cota = k;
        }
    }
    for (int j=0; j < c; j++)
        fwrite (&EMP[j], sizeof(EMP), 1, empleados);
    return;
}


void cargaCateg (FILE *categoria, cat CAT) {
    int i;
    for (i = 0; i < C; i++) {
        CAT.NumCat = i+1;
        printf ("\nIngrese nombre de la Categoria: ");
        fgets (CAT.NomCat, 30, stdin);
        strtok (CAT.NomCat, "\n");
        printf ("\nIngrese importe de sueldo: ");
        scanf ("%f", &CAT.sueldo);
        fwrite (&CAT, sizeof (CAT), 1, categoria);
        printf ("\n-----------------------------------------------");
    }
}

int main (void) {
    FILE *planta,*empleados,*categoria;
    info PLNT;
    emp EMP[100];
    cat CAT;
    int tam;
    planta= fopen ("PLANTAS.DAT","wb");
    empleados = fopen ("EMPLEADOS.DAT", "wb");
    categoria = fopen ("CATEGORIA.DAT", "wb");

    if ((planta != NULL) && (empleados != NULL) && (categoria != NULL)) {
        cargaPlantas (planta,PLNT);
        tam = cargaEmpleados (empleados, EMP);
        ordenaEmp (empleados, EMP, tam);
        cargaCateg (categoria,CAT );
    } else {
        printf("La apertura no se realizo\n");
        printf("\nEl archivo no ha sido creado correctamente\n");
    }
    fclose (categoria);
    fclose (empleados);
    fclose (planta);
    return 0;
}
