#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"

typedef char cadena[30];

typedef struct ofertas{
    int id_oferta;
   cadena tiempo;
    cadena nombre;
	};

typedef struct nuevo{
    cadena dedicacion;
    int identificador;
};

void arreglo_ofertas(ofertas *A,int i){
   int cont;
    for(cont=0;cont<i;cont++){
        printf("Ingrese el ID de la oferta nro: %d\n",cont+1);
        scanf("%d",&A[cont].id_oferta);
        printf("Ingree nombre del puesto de trabajo\n");
        getchar();
        fgets(A[cont].nombre,20,stdin);
        strtok(A[cont].nombre,"\n");
        printf("Ingrese horas de trabajo\n");
        fgets(A[cont].tiempo,20,stdin);
        strtok(A[cont].tiempo,"\n");
        system("cls");
    }
return;
}

void mostrar(ofertas *A,int N){
    int i;
    for (i=0;i<N;i++){
        printf("ID: %d          Nombre del puesto: %s\n",A[i].id_oferta,A[i].nombre);
        printf("--------------------------------------\n");
        printf("Dedicacion: %s\n",A[i].tiempo);
    }
return;
}

int recursiva(ofertas *A,int i,int &full,int N,int analista){

    if(i<N){
        if(strcmp(A[i].nombre,"Analista")==0){
            analista+=1;
        }
        if(strcmp(A[i].tiempo,"Full time")==0){
            full+=1;
        }    
    return recursiva(A,i+1,full,N,analista); 
    }
    else{
        return analista;
    }
}

void carga_archivo(FILE *archivo,ofertas *A,int N,nuevo X){
   int i;
   for(i=0;i<N;i++){
       strcpy(X.dedicacion,A[i].tiempo);
       X.identificador=A[i].id_oferta;
       if(strcmp(A[i].nombre,"Testeo de software"==0)){
         fwrite(&X,sizeof(X),1,archivo);
       }
   }
   return;
}

int main(){
    ofertas *trabajo;
    nuevo X;
    int diarias;
    int full_time=0,contador=0;
    int anal;
    int analista=0;
    FILE *archivo; 
 archivo=fopen("archivo.dat","wb");
    printf("Ingrese cuantas ofertas hubo en el dia\n");
    scanf("%d",&diarias);
    trabajo=(ofertas*)malloc (diarias *sizeof(ofertas));
    arreglo_ofertas(trabajo,diarias);
    mostrar(trabajo,diarias);   
    anal=recursiva(trabajo,contador,full_time,diarias,analista);
    printf("-----------------------------\n");
    printf("Hay %d ofertas de analistas\n",anal);
    printf("Hay %d ofertas full time\n",full_time);
    carga_archivo(archivo,trabajo,diarias,X);
    free(trabajo);
}

