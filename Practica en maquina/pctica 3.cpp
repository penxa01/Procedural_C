#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>

struct peliculas{
	int codigo;
	char titulo[40];
	int fecha; 
	int puntuacion;
};


struct lista{
	int codigo;
	char titulo[40];
	int fecha;
	int puntuacion;
	struct lista *sig;
};
typedef struct lista *puntero;

struct arreglo{
    int cod;
    char titu[30];
    int fech;
};


void mostrar(FILE *archivo){
	struct peliculas I ;
	rewind(archivo);
	while(fread(&I, sizeof(I), 1, archivo)!=0){
		printf("Titulo: %s \n",I.titulo);
		printf("Codigo: %d \n", I.codigo);
		printf("Fecha de la pelicula: %d \n", I.fecha);
		printf("Puntuacion de la pelicula: %d \n", I.puntuacion);
		
	}
	return; 
}


int menu(){
	int i;
	printf("Elija la opcion que desee \n");
	printf("[1] - Modificar puntuacion \n");
	printf("[2]- Generar Lista \n");
	printf("[3]- Total de peliculas y Total de peliculas con puntuacion 10 \n");
	printf("[4]-  Arreglo Dinamico \n");
	printf("Ingrese 0 para finalizar  \n");
	scanf("%d", &i);
	return(i);
}

	
	
void modifica (FILE *archivo, int cod){
	struct peliculas p;
		fseek(archivo, (cod-1)*sizeof(p),SEEK_SET);
		fread(&p, sizeof(p), 1, archivo);
		printf("Ingrese nueva puntuacion \n");
		scanf("%d", &p.puntuacion);
		printf("El puntaje a sido modificado y es de: %d \n", p.puntuacion);
		fseek(archivo,(cod-1)*sizeof(p), SEEK_SET);
		fwrite(&p, sizeof(p), 1, archivo);
		
		return;
}
		
    void lista(FILE *archivo, puntero &cab){
	struct peliculas p ;
	puntero nuevo;
	cab= NULL;
	rewind(archivo);
	fseek(archivo, 0, SEEK_SET);
	while(fread(&p, sizeof(p), 1, archivo) != 0){
	if((p.puntuacion <= 6) && (p.puntuacion >= 10)){
	nuevo= (puntero)malloc(sizeof(struct lista));
	strcpy(nuevo->titulo , p.titulo);
	nuevo->fecha = p.fecha;
	nuevo->puntuacion = p.puntuacion;
	nuevo->codigo = p.codigo;
	nuevo->sig = cab;
	cab= nuevo;
	}
	}
	return;
}
	
	
   void mostrarlista(puntero cab){
	while( cab != NULL){
	printf(" Titulo: %s \n", cab->titulo);
	printf("Codigo: %d \n", cab->codigo);
	printf("Fecha: %d \n", cab->fecha);
	printf("Puntuacion: %d \n", cab->puntuacion);
	cab = cab->sig;
	}
	return;
	}
	
	
	
int totalCoso(puntero cab,int total, int &total10){
    if(cab != NULL){
        total+=1;
        if(cab->puntuacion == 10){
            total10+=1;
        }
        totalCoso(cab->sig,total,total10);
    }
    return total;
}
	
void arre(puntero cab,int total10,arreglo *A){
    int i=0,j;
    while((cab != NULL) && (i<total10)){
        if(cab->puntuacion == 10){
           A[i].cod= cab->codigo;
           strcpy(A[i].titu,cab->titulo);
           A[i].fech= cab->fecha;
        }
        cab=cab->sig;
        i++;
    }
    for(j=0;j<total10;j++){
        printf("Peliculas con puntuacion 10\n");
        printf("TITULO: %s\n",A[i].titu);
        printf("Codigo: %d\n", A[i].cod);
        printf("Fecha: %d \n",A[i].fech);
        printf("----------------\n");
    }
return;
}


int main(){
     arreglo *A;
	int op, cod;
    int total=0,total10=0;
	FILE *archivo; 
	puntero cab;
	cab= NULL; 
	
	if((archivo=fopen("Peliculas.dat", "r+")) == NULL){
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
			if((archivo=fopen("Peliculas.dat", "r+")) == NULL){
				printf("Hay error \n");
			}
			else{
				printf("Ingrese codigo de la pelicula a la que desea modificar su puntuacion \n");
				scanf("%d", &cod);
				modifica(archivo, cod);
				fclose(archivo);
			}
			
		}
		break;
		case 2:{
			if((archivo=fopen("Peliculas.dat", "r+")) == NULL){
				printf("Hay error \n");
			}
			else{
				printf("Generamos lista \n");
				lista(archivo, cab);
				mostrarlista(cab);
				fclose(archivo);
			}
		}
		break;
		case 3:{
			if((archivo=fopen("Peliculas.dat", "r+")) == NULL){
				printf("Hay error \n");
			}
			else{
				printf("Total de peliculas: %d \n",totalCoso(cab,total,total10));
                printf("-----------------------------------\n");
                printf("Peliculas con puntuacion de 10: %d \n",total10);
				fclose(archivo);
			}
		}
		break;
		case 4:{
			if((archivo=fopen("Peliculas.dat", "r+")) == NULL){
				printf("Hay error \n");
			}
			else{
				 A=(arreglo *) malloc (sizeof(arreglo)*total10);
				arre(cab,total10,A);
				fclose(archivo);
			}
		}
		break;
		}
	} while(op != 0);
}
