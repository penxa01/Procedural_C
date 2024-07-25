#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define N 7

typedef char cadena[30];

typedef struct {
	int nroPlanta;
	cadena nombre;
	int CantProd;
} info;						//Struct de 7 plantas 

typedef struct {
	int dni;
	cadena nomEmp;
	cadena EstadoS;
	int hijos;
	int plantaNum;
	int NumCat;
} emp;						//Struct x empleado

typedef struct {
	int NumCat;
	cadena NomCat;
	float sueldo;
}cat;						//Struct x categoria

struct lista {
	emp punto1;
	struct lista *sig;
};									

typedef struct lista *puntero;			//Arreglo de plantas punto1

typedef struct {
	cadena nombre;   
	int CantProducto;
	puntero cabexa;  
} puntoA;

struct punto5 {
	cadena nombre;
	float sueldo;
	struct punto5 *sig;
};

typedef struct punto5 *nuevo;				//lista de punto5

typedef struct {
	cadena nom;
	float sueldo;
} psiete;							//Struct de punto 7

int menu(){
	int opcion;
	printf("\n[1]Generar un arreglo de 7 componentes\n");
	printf("[2]Listado con los datos almacenados\n");
	printf("[3]Ingresa dni y modifica info. de un empleado\n");
	printf("[4]Ingresa dni y elimina info. de un empleado\n");
	printf("[5]Crear lista para empleados con sueldo adicional con hijos\n");
	printf("[6]Listado ordenado alfabeticamente\n");
	printf("[7]Generar un archivo con la informacion de la lista\n");
	printf("[0] Salir del Programa\n");
	printf ("\n--->  ");
	scanf ("%d", &opcion);
	return opcion;
}
//Creamos lista en forma ordenada, por num de planta	
void insertarLista (puntero &cab, FILE *empleados, int nroP) {
	emp E;
	rewind (empleados);
	puntero nuevo;
	while (fread (&E, sizeof(E), 1, empleados) != 0) {
		if (E.plantaNum == nroP) {
			nuevo = (puntero) malloc (sizeof (struct lista));
			strcpy (nuevo->punto1.nomEmp, E.nomEmp);        
			strcpy (nuevo->punto1.EstadoS, E.EstadoS);
			nuevo->punto1.dni = E.dni;
			nuevo->punto1.hijos = E.hijos;
			nuevo->punto1.plantaNum = E.plantaNum;
			nuevo->punto1.NumCat = E.NumCat;
			
			nuevo->sig = cab;
			cab = nuevo;
		}
	}
	return;
}

void cargaPunto1 (puntoA registro[N], FILE *planta, FILE *empleados) {
	int i=0;
	info p;
	while ((fread (&p, sizeof(p), 1, planta) != 0 ) && (i < N)) {
		if (strcmp (registro[i].nombre, p.nombre) != 0) {
			strcpy (registro[i].nombre, p.nombre);
			registro[i].CantProducto= p.CantProd; 
		}
		registro[i].cabexa = NULL;
		insertarLista (registro[i].cabexa, empleados, i+1);
		i++;
	}
	return;
}
	
void mostrarLista(puntero cabeza){
	int longitud=0;
	while(cabeza!=NULL){
		printf("\n%20s	%3d	%10s	%3d", cabeza->punto1.nomEmp, cabeza->punto1.NumCat, cabeza->punto1.EstadoS ,cabeza->punto1.hijos);
		printf("\n");
		longitud += 1;
		cabeza = cabeza->sig;
	}
	printf("\nTotal de empleados: %d", longitud);
	return;
}
//mostramos toda la informacion del arreglo del punto 1
void listado (puntoA registro[N]){
	int i;
	for (i=0;i<N;i++){
		printf("\nNUMERO DE PLANTA: %d               NOMBRE DE PLANTA: %s", i+1, registro[i].nombre);
		printf("\nPRODUCTOS QUE ELABORA: %d\n",registro[i].CantProducto);
		printf ("\nNombre de empleado	Categoria Estado Civil  Cantidad de Hijos");
		mostrarLista (registro[i].cabexa);
		printf ("\n=======================================================================");
	}
	return;
}
//buscamos empleado para modificar info, punto 3
int buscar_empleado(puntero cab, FILE * empleados,int dni){
	emp e;
	int b=0;
	long int xx;						//En vez de declarar tipo fpos_t, colocamos long int por compilador
	//fpos_t xx;
	rewind (empleados);
	while(cab!=NULL){
		if(dni == cab->punto1.dni) {
			printf("\nModificamos informacion del documento encontrado %d\n",cab->punto1.dni);
			printf("\nIngrese la nueva cantidad de hijos: ");
			scanf("%d", &cab->punto1.hijos);
			printf("\nIngrese la nueva categoria ala que pertenece: ");
			scanf ("%d", &cab->punto1.NumCat);
			
			while (fread (&e, sizeof(e), 1, empleados) != 0) {
				if (e.dni == dni) {
					fseek (empleados, 0, SEEK_END);					//Colocamos desplz del puntero al final del Archivo
					//fgetpos (empleados, &xx);						//Obtener la pos actual del puntero
					xx = ftell (empleados);							//Obtener pos actual del puntero, para Linux
					e.hijos = cab->punto1.hijos;
					e.NumCat= cab->punto1.NumCat;
					fseek (empleados, xx-sizeof(e), SEEK_SET);		//Apuntar ala direcc anterior
				    fwrite(&e, sizeof(e),1,empleados);           //Grabamos la componente en el archivo
					printf ("\nCambia realizado");
					b = 1;					//Para comprobar si se realizo el cambio
				}
            }
		}
		cab = cab->sig;
	}
	return b;
}


void punto3 (puntoA registro[N], FILE *empleados, int xdoc) {
int i=0;
	while ((i < N) && (buscar_empleado (registro[i].cabexa, empleados, xdoc) == 0)) {
		i++;
	}
	return;
}
//creamos archivo auxiliar que almacena informacion que no se elimina
void nuevoArchivo (FILE *empleados, FILE *aux, int dni) {
	emp e;
	fseek (empleados, 0, SEEK_SET);			//Desplaz del puntero en pos inicial del archivo
	while (fread (&e, sizeof(e), 1, empleados) != 0) {
		if (e.dni != dni) {
			fwrite(&e,sizeof(e),1,aux);
		} else {
			printf("\nEl empleado a eliminar es %s\n", e.nomEmp);
		}
	}
}
//eliminamos nodo de acuerdo al dni ingresado (punto4)
int buscar_doc(puntero cabeza, int dni){
	puntero p, anterior;
	int b=0;
	if (cabeza->punto1.dni == dni) {
		p = cabeza;
		cabeza = cabeza->sig;
		b = 1;
		free (p);
	} else {
		p = cabeza; anterior= cabeza;
		while ((p != NULL) && (p->punto1.dni != dni)) {
			anterior = p;
			p = p->sig;
		}
		if (p != NULL) {
			anterior->sig = p->sig;
			b = 1;
			free (p);
		} 
	}
	return b;
}

void punto4 (puntoA registro[N], int xdoc) {
	int i=0;
	while ((i < N) && (buscar_doc (registro[i].cabexa, xdoc) == 0)) {
		i++;
	}
	return;
}	

float buscarCat(int nroCat,FILE *categoria){
	float s;
	cat C;
	rewind (categoria);
	while (fread (&C, sizeof(C), 1, categoria) != 0) {
		if (nroCat == C.NumCat) {
			s =  C.sueldo;
		}
	}
	return s;
}
//creamos lista insertando nodos en forma ORDENADA alfabeticamente
void punto5 (nuevo &cabeza, FILE *categoria, FILE *empleados) {
	emp e;
	nuevo p, n, anterior;
	float suma;
	printf("\nGeneramos nueva Lista\n");
	while (fread (&e, sizeof(e),1 , empleados) != 0) {
		n = (nuevo) malloc (sizeof (struct punto5));
		strcpy (n->nombre, e.nomEmp);  
		suma = buscarCat (e.NumCat, categoria);      
		n->sueldo = (e.hijos * 3540) + suma;
		
		if (cabeza == NULL) {
			cabeza = n;
			n->sig = NULL;
		} else {
			if (strcmp (cabeza->nombre, n->nombre) > 0) {
				n->sig = cabeza;
				cabeza = n;
			} else {
				p = cabeza->sig;
				anterior = cabeza;
				while ((p != NULL) && (strcmp (n->nombre, p->nombre) > 0)) {
					anterior = p;
					p = p->sig;
				}
				anterior->sig = n;
				n->sig = p;
			}
		}
	}
}

void mostrarOrd (nuevo kbe) {
	printf("\nMostramos la LISTA generada\n");
	while (kbe!=NULL) {
		printf("\nNombre del empleado: %s",kbe->nombre);
		printf("\nSueldo del Empleado %.2f", kbe->sueldo);
		printf("\n****************************************");
		kbe = kbe->sig;	
	}
	return;
}
//creamos el archivo sueldo y almacenamos cada nodo en cada componente
void punto7 (FILE *sueldo, nuevo xkbeza) {
	psiete aux;
	
	while (xkbeza !=NULL) {
		strcpy (aux.nom , xkbeza->nombre);
		aux.sueldo = xkbeza->sueldo;
		fwrite( &aux, sizeof(aux) ,1, sueldo);
		xkbeza = xkbeza->sig;
	}
}

void mostrarPunto7 (FILE *sueldo) {
	psiete m;
	rewind (sueldo);
	printf("\nMostramos la INFO que se encuentra en el archivo SUELDO\n");
	while (fread (&m, sizeof(m), 1, sueldo) != 0) {
		printf("\nNombre del Empleado: %s", m.nom);
		printf("\nSu sueldo es $ %.2f", m.sueldo);
		printf("\n-------------------------------");
	}
	return;
}

int main (void) {
	FILE *planta,*empleados,*categoria, *auxiliar,*sueldo;
	puntoA registro[N];
	int op, doc;
	nuevo cabeza;
	planta = fopen ("PLANTAS.DAT", "rb");
	empleados = fopen("EMPLEADOS.DAT", "r+");
	categoria = fopen ("CATEGORIA.DAT", "rb");
	auxiliar = fopen ("auxiliar.DAT", "wb");
	sueldo = fopen ("sueldo.DAT" , "wb");
	
	cabeza = NULL;					//Lista creada y vacia del punto 5
	if ((planta != NULL) && (empleados != NULL) && (categoria != NULL)) {
		do {
			op = menu ();
			switch (op) {
			case 1: cargaPunto1 (registro, planta, empleados); 
				break;
			case 2: listado(registro);
				break;
			case 3: printf("\nIngrese un Documento de algun empleado: ");
					scanf("%d", & doc);
					punto3 (registro, empleados, doc);
				break;
			case 4:printf("\nIngrese DNI del empleado que desea eliminar su informacion: ");
			       scanf("%d" , & doc);
			       punto4(registro,doc);
				   nuevoArchivo( empleados , auxiliar, doc);
				   fclose (empleados);
				   fclose (auxiliar);
				   remove ("EMPLEADOS.DAT");
				   rename ("auxiliar.DAT", "EMPLEADOS.DAT");
				break;
			case 5: empleados = fopen ("EMPLEADOS.DAT", "r+");
					punto5(cabeza, categoria, empleados);
				break;
			case 6:	mostrarOrd (cabeza);
				break;
			case 7:	punto7(sueldo,cabeza);
					fclose (sueldo);
					sueldo = fopen ("sueldo.DAT" , "rb");
					mostrarPunto7 (sueldo);
				break;
			default: printf ("\nIngreso opcion INCORRECTA, intentelo de nuevo\n");
				break;
			case 0: printf("\nIngreso SALIR, termina el programa\n");
				break;
			}
		} while (op != 0);
	} else {
		printf("La apertura no se realizo\n");
		printf("\nLos archivos no ha sido creado correctamente\n");
	}
	
	fclose (planta);
	fclose (categoria);
	fclose (sueldo);
	return 0;
}
