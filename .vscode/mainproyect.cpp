#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#include "tipo.h"

int main(){
	FILE *empresas,*empleados;
	int n;
	empresa A;
	empleado B;
	carga(empresas,A); 
	n=longi(empresas,A);
	system("pause");
	system("cls");
	carga2(empleados,B,n);
	system("cls");
	mostrar(empresas,empleados);
	system("pause");
	
}
