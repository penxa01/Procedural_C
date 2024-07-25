#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#include "tipo.h"

void carga2(FILE *empleados, empleado B,int n){
	int i;
	empleados=fopen("empleados.DAt","wb");
	for(i=1200;i<n+1200;i++){
		printf("ingrese el nombre del empleado de la empresa nro codigo: %d\n",i);
		fgets(B.nomEmp,20,stdin);
		strtok(B.nomEmp,"\n");
		while(strcmp(B.nomEmp,"fin")!=0){
			B.codEmp=i;
			printf("Ingrese dni del empleado\n");
			scanf("%d",&B.dni);
			printf("Ingrese sueldo\n");
			scanf("%f",&B.sueldo);
			printf("Ingrese años de antiguedad del empleado\n");
			scanf("%d",&B.antiguedad);
			fwrite(&B,sizeof(B),1,empleados);
			printf("La carga se hizo exitosamente\n");
			system("pause");
			system("cls");
			printf("Ingrese siguiente empleado de la empresa nro de codigo: %d\n",i);
			getchar();
			fgets(B.nomEmp,20,stdin);
			strtok(B.nomEmp,"\n");
		}
	
	}
	fclose(empleados);
	
}
