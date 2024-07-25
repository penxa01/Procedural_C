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
      rewind(inquilinos);
     while(fread(&A,sizeof(A),1,inquilinos)){
         if(A.pago==2){
             nuevo=(puntero) malloc(sizeof(struct nodo));
             strcpy(nuevo->nombre,A.nom);
             strcpy(nuevo->celular,A.cel); //Primero colocar variable de destino depues variable de la cual se copia el contenido
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
    system("COLOR 02");
    inqui A;
    float total=0;
    FILE *inquilinos;
    puntero cabeza;
printf("JUAN PEÑA  DNI: 43654220\n");
	if((inquilinos=fopen("Inquilino.dat", "rb")) == NULL)
				printf("Hay error \n");

	mostrar(inquilinos);
	system("pause");
    system("cls");

    Pago(A,inquilinos);
    system("pause");
   lista(inquilinos,cabeza);
   /*al hacer la caga normal el primer elemento que se ingresa a la lista,
    pasa a ser la cabeza, osea que toma null,
    y los proximos nodos van a tomar otras direcciones distintas
    donde siempre el ultimo que ingreso va a ser la cabeza*/
    muestra_lista(cabeza);

	printf("\n---------------------------------\n");
    printf("Cantidad de inquilinos que deben: %d\n", recursiva(cabeza,total));
    printf("Importe total a cobrar de alquileres: %f", total);
    fclose(inquilinos);
}
