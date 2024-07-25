#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#include "tipo.h"

void carga(FILE *empresas,empresa A){
	fpos_t x;
	empresas=fopen("empresas.DAT","wb");
	printf("Ingrese el nombre de la empresa\n"); 
    fgets(A.nombre,20,stdin);
	strtok(A.nombre,"\n");
	while(strcmp(A.nombre,"fin")!=0){
		printf("Ingrese ubicacion de la casa matriz de la empresa\n");
		getchar();
        fgets(A.direc,50,stdin);
        fgetpos(empresas,&x);
	    A.cod=(int)(x/sizeof(A))+1200;
		printf("Ingrese el CUIT de la empresa\n");
		scanf("%d",&A.CUIT);
		fwrite(&A,sizeof(A),1,empresas);
		printf("Los datos de la empresa fueron cargados con exito\n");
		printf("------------------------------------------\n");
		system("pause");
		system("cls");
		printf("Ingrese nombre de la siguiente empresa\n");
		getchar();
		fgets(A.nombre,20,stdin);
        strtok(A.nombre,"\n");
		}
		fclose(empresas);
	return;
}
