#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>




struct inqui{
	float importe;
	char nom[40];
	char cel[12];
	int nrod;
	int pago;

};


struct lista{
	float importe;
	char nom[40];
	char cel[12];
	int nrod;
	struct lista *sig;
};
typedef struct lista *puntero ;


void mostrar(FILE *archivo){
	struct inqui I;
	rewind(archivo);
	while(fread(&I, sizeof(I), 1, archivo)){
		printf(" Nombre del inquilino: %s \n", I.nom);
		printf("Numero de departamento : %d \n", I.nrod);
		printf(" Importe: %f \n", I.importe);
		printf("Numero de celular: %s \n", I.cel);
		printf("Pago: %d \n", I.pago);
		
	}
	return; 
}




int menu(){
	int i;
	printf("Elija la opcion que desee \n");
	printf("[1] - Listado de  inquilinos que pagaron \n");
	printf("[2]- Generar lista \n");
	printf("[3]- Importe total de alquileres y cantidad de inquilinos que deben el mes \n");
	printf("Ingrese 0 para finalizar  \n");
	scanf("%d", &i);
	return(i);
}


	
void mostrarpagados	(FILE *archivo){
	struct inqui I;
	rewind(archivo);
	while(fread(&I, sizeof(I), 1, archivo)){
		if(I.pago == 1){
			printf("Nombre del inquilino: %s \n", I.nom);
			printf("Numero de celular: %s \n", I.cel);
			printf("Numero de departamento: %d \n", I.nrod);
			printf("Importe: %f \n", I.importe);
		}
	}
	return;
}
	
	
void generarL(FILE *archivo, puntero &p){
	struct inqui I;
	puntero nuevo;
	p= NULL;
	rewind(archivo);
	fseek(archivo, 0, SEEK_SET);
	while(fread(&I, sizeof(I), 1, archivo) != 0){
	if(I.pago == 2){
	nuevo= (puntero)malloc(sizeof(struct lista));
	strcpy(nuevo->nom , I.nom);
	strcpy(nuevo->cel , I.cel);
	nuevo->importe = I.importe;
	nuevo->nrod = I.nrod;
	nuevo->sig = p;
	p= nuevo;
	}
	}
	return;
	}
	
	
	
void mostrarlista(puntero p){
	while( p != NULL){
	printf("Nombre del inquilino %s \n", p->nom);
	printf("Numero de celular %s \n", p->cel);
	printf("Importe %f \n", p->importe);
	printf("Numero de departamento %d \n", p->nrod);
	p = p->sig;
	}
	return;
}
	
	
int calcular(puntero p, float &acum){
	
		if(p != NULL){
			acum= acum + p->importe;
			//if(p->pago == 2){
				//contd+= 1 ;
			
			//p = p->sig; 
			return (1+ calcular(p->sig ,acum));
		}
		return(0);
	}
	
	

int main(){
	int op, x;
	float acum;
	FILE *archivo; 
	puntero p;
	p= NULL; 
	acum=0;
	
	if((archivo=fopen("Inquilino.dat", "r")) == NULL){
		printf("Hay error \n");
	}
	else{
		mostrar(archivo);
		fclose(archivo);
	}
	
	do{
		op= menu();
		switch(op){
		case 1:{
			if((archivo=fopen("Inquilino.dat", "r")) == NULL){
				printf("Hay error \n");
			}
			else{
				mostrarpagados(archivo);
				fclose(archivo);
			}
			
		}
		break;
		case 2:{
			if((archivo=fopen("Inquilino.dat", "r")) == NULL){
				printf("Hay error \n");
			}
			else{
				generarL(archivo, p);
				mostrarlista(p);
				fclose(archivo);
			}
		}
		break;
		case 3:{
			x= calcular(p, acum);
			printf("Cantidad de inquilinos que deben el mes: %d \n", x );
			printf("Importe total que se debe cobrar en alquileres: %f \n", acum);
		
		}
		break;
		}
	} while(op != 0);
}
