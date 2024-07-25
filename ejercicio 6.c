#include <stdio.h>
#define F 3
#define C 5

void carga(float arre[F][C], int i, int j){
	if((i!=3)&&(j!=5)){
        if(i<F){
		if(j<C){
			printf("ingrese monto de categoria %d, y sector %d en millones \n", i+1, j+1);
			scanf("%f", &arre[i][j]);
			fflush(stdin);
			carga(arre, i, j+1);     //
	}
		carga(arre, i+1, 0);
}}else{return;}
}

float sumarmonto(float arre[F][C], int j, int xcat, float monto){
	if(xcat <= F){
		monto = monto + arre[xcat-1][j]; // acumulo el monto de la fila ingresada
		sumarmonto(arre, j+1, xcat,monto);
	}
	return(monto);
}

void servicios(float arre[F][C], int i){
	float acum;
	acum=0;
	if(i<F){
		acum= acum + arre[i][3];
		servicios(arre, i+1);
	}
	printf("El monto total para el sector de Servicios es: %f \n", acum);
	fflush(stdin);
}


void listado(float arre[F][C], int i, int j, float acum){
	if(i<F){
		if(j<C){
			acum= acum+ arre[i][j];
			listado(arre,i,j+1, acum);
		}
		listado(arre,i+1, j, acum);
	}
	printf("El monto total financiado es: %f \n", acum);
	fflush(stdin);
	return;
}


void comparar(float arre[F][C], int i, int j, float xxmonto){
	if(i<F){
		if(j<C){
			if(arre[i][j] > xxmonto){
				printf("MONTO SUPERIOR, Categoria: %i - Sector: %i \n", i+1, j+1);
				fflush(stdin);
				comparar(arre, i, j+1, xxmonto);
			}
			else if(arre[i][j] < xxmonto){
				printf("MONTO INFERIOR, Categoria: %i - Sector: %i \n", i+1, j+1);
				fflush(stdin);
				comparar(arre, i, j+1, xxmonto);
			}
			else{
				printf("MONTO IGUAL, Categoria: %i - Sector: %i \n", i+1, j+1);
				fflush(stdin);
				comparar(arre, i , j+1, xxmonto);
			}

		}
		comparar(arre, i+1, j, xxmonto);
	}
	return;
}
int main(){
	float arre[F][C], m, xxmonto;
	int cat;
	carga(arre, 0, 0);
	printf("Ingrese una categoria para mostar el monto total (1,2 o 3)\n");
	scanf("%i", &cat);
	fflush(stdin);
	m= sumarmonto(arre,  0 , cat, 0);
	printf("El monto total de la categoria: %d es: %f \n", cat, m);
	fflush(stdin);
	servicios(arre, 0);
	listado(arre, 0,0, 0);
	printf("Ingrese monto para comparar \n");
	scanf("%f", &xxmonto);
	fflush(stdin);
	comparar(arre, 0 , 0,xxmonto);
}
