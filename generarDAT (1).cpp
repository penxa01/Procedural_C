#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define P 7
#define C 5

typedef char cadena[30];

typedef struct {
	int nroPlanta;
	cadena nombre;
	int CantProd;
} info;

typedef struct {
	int dni;
	cadena nomEmp;
	cadena EstadoS;
	int hijos;
	int plantaNum;
	int NumCat;
} emp;

typedef struct {
	int NumCat;
	cadena NomCat;
	float sueldo;
} cat;

void cargaPlantas (FILE *planta,info plt){
	int i;
	for(i=0;i < P;i++){
		
		plt.nroPlanta = i+1;
		fflush (stdin);
		printf("Ingrese el nombre de planta %d:\n",i+1);
		getchar();
		fgets(plt.nombre,30,stdin);
		strtok (plt.nombre, "\n");
		printf("Ingrese cantidad de productos que elabora\n");
		scanf("%d",&plt.CantProd);
		fwrite (&plt, sizeof(plt), 1, planta);
		printf ("\n-----------------------------------------------\n");
	}
	
}
	
void cargaEmpleados(FILE *empleados) {
	emp EMP;
	printf("\nIngrese nombre del empleado\n");
	getchar();
	fgets(EMP.nomEmp,30,stdin);
	strtok(EMP.nomEmp, "\n");
	while(strcmp(EMP.nomEmp,"fin")!=0) {
		
		printf("\nIngrese numero de planta: ");
		scanf("%d",&EMP.plantaNum);
		printf("\nIngrese DNI del empleado: ");
		scanf("%d",&EMP.dni);
		printf("\nA que categoria pertenece el empleado(1-5): ");
		scanf("%d",&EMP.NumCat);
		printf("\nQue estado civil posee?(casado-soltero): ");
		scanf("%s", EMP.EstadoS);
		while ((strcmp (EMP.EstadoS, "casado") != 0) && (strcmp (EMP.EstadoS, "soltero") != 0)) {
			printf("\nIngrese devuelta estado civil(casado-soltero): ");
			scanf("%s", EMP.EstadoS);
		}
		printf("\nCuantos hijos posee el empleado: ");
		scanf("%d",&EMP.hijos);
		
		fwrite (&EMP, sizeof(EMP), 1, empleados);			//Guardo en archivo cada componente del arreglo
		
		printf ("\n-----------------------------------------------");
		printf("\nIngrese nombre del empleado: ");
		getchar();
		fgets(EMP.nomEmp,30,stdin);
		strtok(EMP.nomEmp, "\n");
	}
	return;
}

void cargaCateg (FILE *categoria, cat CAT) {
	int i;
	for (i = 0; i < C; i++) {
		CAT.NumCat = i+1;
		printf ("\nIngrese nombre de la Categoria %d: ", CAT.NumCat);
		getchar();
		fgets (CAT.NomCat, 30, stdin);
		strtok (CAT.NomCat, "\n");
		printf ("\nIngrese importe de sueldo: ");
		scanf ("%f", &CAT.sueldo);
		fwrite (&CAT, sizeof (CAT), 1, categoria);
		printf ("\n-----------------------------------------------");
	}
	return;
}

int main (void) {
	FILE *planta,*empleados,*categoria;
	info PLNT;
	cat CAT;
	planta= fopen ("PLANTAS.DAT","wb");
	empleados = fopen ("EMPLEADOS.DAT", "wb");			
	categoria = fopen ("CATEGORIA.DAT", "wb");
			
	if ((planta != NULL) && (empleados != NULL) && (categoria != NULL)) {
		cargaPlantas (planta,PLNT);
		cargaCateg (categoria,CAT );
		cargaEmpleados (empleados);
	} else {
		printf("La apertura no se realizo\n");
		printf("\nEl archivo no ha sido creado correctamente\n");
	}
	fclose (categoria);
	fclose (empleados);
	fclose (planta);
	return 0;
}

