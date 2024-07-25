#ifndef tipo
#define tipo

typedef char cadena ;

typedef struct empresa{
	cadena nombre[20];
	int cod;
	int CUIT;
	cadena direc[50];
};

typedef struct empleado{
	cadena nomEmp[20];
	int codEmp;
	int dni;
	float sueldo;
	int antiguedad;
};

void carga(FILE *empresas,empresa A);
void carga2(FILE *empleados, empleado B,int n);
int longi(FILE *empresas,empresa A);
void mostrar(FILE *empresas,FILE *empleados);
#endif

