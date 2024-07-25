#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#define N 

typedef char cadena [40];

struct inqui{
    float importe;
    cadena nom;
	char celular[12];
    int nrod;
	int pago;
};

struct nodo{
cadena nombre,cel;
int nrodepto;
struct nodo *sig;
};

typedef struct nodo *puntero;

void mostrar(FILE *inquilinos) {
	inqui A;
	
    while ( fread (&A, sizeof(A), 1, inquilinos)!=0) {
        printf("\nNombre del inquilino %s", A.nom);
        printf("\nImporte del inquilino %.2f", A.importe);
        printf("\nCelular del inquilino %s", A.celular);
        printf("\nNumero de Departamento %d", A.nrod);
        printf("\n Alquiler(1-pago,2-no pago) %i", A.pago);
        printf("\n------------------------------------------------------");
    }
    return;
}


void actualiza(FILE *inquilinos, inqui A){
    int nro;
    rewind(inquilinos);
    long int K;
     printf("\nIngrese numero de departamento\n");
   scanf("%d",&nro);
    fread(&A,sizeof(A),1,inquilinos);
   while(!feof(inquilinos)&& (nro!=A.nrod)){
       fread(&A,sizeof(A),1,inquilinos);
   }
   if(!feof(inquilinos)){
       fseek(inquilinos,nro*sizeof(A),SEEK_SET);
       printf("El importe actual es de: %f\n",A.importe);
       printf("ingrese nuevo importe\n");
       K=ftell(inquilinos);
       scanf("%f",&A.importe);
       printf("el nuevo importe es de %f\n",A.importe);
       fseek(inquilinos,K-sizeof(A),SEEK_SET);
       fwrite(&A,sizeof(A),1,inquilinos);
   }
return;
}

void recaudo(FILE *inquilinos,inqui A){
	float acum=0;
    rewind(inquilinos);
	while(fread(&A,sizeof(A),1,inquilinos)!=0){
		if(A.pago==2){
			acum+=A.importe;
		}
	}
	printf("El recaudo hasta el momento es de: %f \n",acum);
    return;
	
	
}

void lista(FILE *inquilinos,puntero cabeza,inqui A){
    puntero nuevo;
    rewind(inquilinos);
    cabeza==NULL;
    while(fread(&A,sizeof(A),1,inquilinos)!=0){
        if(A.pago==2){
            nuevo=(puntero)malloc(sizeof(struct nodo));
            strcpy(nuevo->nombre,A.nom);
            strcpy(nuevo->cel,A.celular);
            nuevo->nrodepto=A.nrod;
            nuevo->sig=cabeza;
            cabeza=nuevo;
        }
    }
    return;
}

void eliminar (puntero anterior,puntero p,int depto) {
    if ((p!=NULL)&&(p->nrodepto!=depto)){
        anterior=p;
        p=p->sig;
        eliminar(anterior,p,depto);
    } else {
        if(p!=NULL) {
            free (p);
        } else {
            printf("\nNo se pudo eliminar inquilino\n");
        }
    }
    return;
}
int main(){
    FILE *inquilinos;
    inqui A;
    int n;
    puntero cabeza,p,anterior;
    inquilinos=fopen("Inquilino.dat","r+");
    rewind(inquilinos);
    mostrar(inquilinos);
    actualiza(inquilinos,A);
    recaudo(inquilinos,A);
    lista(inquilinos,cabeza,A);
    printf("ingrese numero de departamento que desea eliminar\n");
    scanf("%d",&n);
    eliminar(anterior,p,n);
    fclose(inquilinos);
}
