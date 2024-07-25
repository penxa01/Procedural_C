#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"

struct nodo{
    int positivo;
    struct nodo *sig;
};

typedef struct nodo *puntero;

void crear(puntero &cabeza){
    cabeza=NULL;
    return;
}

void insertar(puntero &cabeza){
puntero nuevo;
int valor;
printf("Ingrese el un valor positivo\n");
scanf("%d",&valor);
while(valor>0){
    nuevo=(puntero)malloc(sizeof (struct nodo));
    nuevo->positivo=valor;
    nuevo->sig=cabeza;
    cabeza=nuevo;
    printf("Ingrese siguiente valor\n");
    scanf("%d",&valor);
    }
return;
}

void par(puntero cabeza){
puntero anterior;
    while(cabeza!=NULL){
        printf("%2d\n",cabeza->positivo);
        anterior=cabeza;
		cabeza=cabeza->sig;
    }
    if((anterior->positivo%2)==0){
        printf("\nEl ultimo elemento es par\n");
    }
    else{
        printf("\nEl ultimo elemento es impar\n");
    }
return;
}


int main(){
    puntero cabeza;
    crear(cabeza);
    insertar(cabeza);
    par(cabeza);
}
