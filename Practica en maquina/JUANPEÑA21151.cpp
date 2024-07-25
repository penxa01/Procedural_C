#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
//JUAN PEÑA //
//DNI: 43764220 //
//CARRERA: LCC //
//NRO REGISTRO: 21151//


struct inqui{
float importe;
char nom[40],cel[12];
int nrod, pago; /*(1 - pagÃ³, 2 - No pagÃ³)*/
};

struct nodo{
    float imp;
   char nombre[40],celular[12] ;
    int NumDepto;
    struct nodo *sig;
};

typedef struct nodo *puntero;


int menu(){
int op;
printf("INGRESE OPCION DESEADA\n");
printf("[1]Listado de inquilinos\n");
printf("[2]Inquilinos que pagaron\n");
printf("[3]Genera lista de inquilinos que no pagaron\n");
printf("[4]Cantidad de inquilinos que deben el mes y total a cobrar\n");
printf("[0] Finaliza el programa\n");
 scanf("%d",&op);
 return (op);
}

void mostrar(FILE *inquilinos){
   struct inqui A;
	rewind(inquilinos);
	printf("INQUILINOS\n");
  while(fread(&A, sizeof(A), 1, inquilinos)){
      printf("NOMBRE: %s",A.nom);
      printf("      CELULAR: %s\n",A.cel);
      printf("NUMERO DE DEPARTAMENTO: %d\n",A.nrod);
      printf("IMPORTE: %f      ",A.importe);
      printf("PAGO: %d\n",A.pago);
      printf("\n--------------------------\n");
  }
  return;
}

void Pago(inqui A, FILE *inquilinos){
	rewind(inquilinos);
	 printf("INQUILINOS QUE SI PAGARON EL ALQUILER\n");
    while(fread(&A,sizeof(A),1,inquilinos)!=0){
        if(A.pago == 1){
      printf("NOMBRE: %s",A.nom);
      printf("      CELULAR: %s\n",A.cel);
      printf("NUMERO DE DEPARTAMENTO: %d\n",A.nrod);
      printf("IMPORTE: %f  ",A.importe);
      printf("\n--------------------------\n");
        }
    }
    return;
}

void lista(FILE *inquilinos,puntero &cabeza){
    rewind(inquilinos);
	struct inqui A;
    puntero nuevo;
     cabeza =NULL;
     while(fread(&A,sizeof(A),1,inquilinos)){
         if(A.pago==2){
             nuevo=(puntero) malloc(sizeof(struct nodo));
             strcpy(nuevo->nombre,A.nom);
             strcpy(nuevo->celular,A.cel);
             nuevo->NumDepto=A.nrod;
             nuevo->imp=A.importe;
             nuevo->sig=cabeza;
             cabeza=nuevo;
         }
     }
    return;
}

/*void generarL(FILE *archivo, puntero &cabeza){
	struct inqui A;
	puntero nuevo;
	cabeza= NULL;
	rewind(archivo);
	fseek(archivo, 0, SEEK_SET);
	while(fread(&A, sizeof(A), 1, archivo) != 0){
	if(A.pago == 2){
        nuevo= (puntero)malloc(sizeof(struct nodo));
        strcpy(nuevo->nombre , A.nom);
        strcpy(nuevo->celular , A.cel);
        nuevo->imp = A.importe;
        nuevo->NumDepto = A.nrod;
        nuevo->sig = cabeza;
        cabeza= nuevo;
	   }
	}
 return;
}*/

void muestra_lista(puntero cabeza){
      printf("\nINQUILINOS QUE NO PAGARON ALQUILER\n");
    while(cabeza!=NULL){
        printf("Nombre: %s          Celular: %s\n",cabeza->nombre,cabeza->celular);
        printf("Numero de departamento: %d\n", cabeza->NumDepto);
        printf("Importe: %f",cabeza->imp);
        printf("\n---------------------------\n");
        cabeza=cabeza->sig;
    }
    return;
}

int recursiva(puntero cabeza,float &acum){
    if(cabeza!=NULL){
      acum+=cabeza->imp;
      return(1+recursiva(cabeza->sig,acum));
    }
     return (0);

}

int main(){
    inqui A;
    float total=0;
    int opcion;
    FILE *inquilinos;
    puntero cabeza;
    printf("JUAN PEÑA  DNI: 43654220\n\n");
	if((inquilinos=fopen("Inquilino.dat", "rb")) == NULL)
				printf("Hay error \n");
do{
    opcion=menu();
    switch(opcion){
        case 1:{
            mostrar(inquilinos);
            system("pause");
            system("cls");
    }
        break;
        case 2: {Pago(A,inquilinos);
            system("pause");
            system("cls");
    }
        break;
        case 3:{
            lista(inquilinos,cabeza);
            muestra_lista(cabeza);
            system("pause");
            system("cls");
    }
        break;
        case 4:{
            printf("\n---------------------------------\n");
            printf("Cantidad de inquilinos que deben: %d\n", recursiva(cabeza,total));
            printf("Importe total a cobrar de alquileres: %f", total);
            printf("\n---------------------------------\n");}
    }
} while(opcion !=0);

fclose(inquilinos);
}
