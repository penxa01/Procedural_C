#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#include "tipo.h"


void ordenar(FILE *empleados,empleado B){
	empleado *aux;
	int cont=0
	empleados=fopen("empleados.DAT","r+");
	while((fread(&B),sizeof(B),1,empleados)!=0){
		cont+=1;
	}
	aux=(empleado *)malloc(cont * sizeof(empledo));
	
}
