#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#include <malloc.h>
#define P 7

typedef char cadena[30];

typedef struct info{
    int nroPlanta;
    cadena nombre;
    int CantProd;
};

void carga(FILE *planta,info plt){
    int i;
    for(i=0;i < P;i++){
        plt.nro = i+1;
    
        printf("Ingrese el nombre de planta %d\n",i);
        fgets(plt.nombre,30,stdin);
        strtok (plt.nombre, "\n");
        printf("ingrese cantidad de productos que elabora\n");
        scanf("%d",&plt.CantProd);
        fwrite (&plt, sizeof(plt),1, );
    }
       
}

int main (void) {
    FILE *planta;
    info plt;
    planta= fopen ("PLANTAS.DAT","wb");
    if (planta != NULL) {
        carga (planta,plt);
    } else {
        printf("La apertura no se realizo\n")
        printf("\nEl archivo no ha sido creado correctamente\n");;
    }

    return 0;
}