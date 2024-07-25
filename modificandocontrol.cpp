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
}cat;

struct lista {
	emp punto1;
	struct lista *sig;
};

typedef struct lista *puntero;

typedef struct {
	cadena nombre;   //nombre planta//
	int CantProducto;
	puntero cabexa;
} puntoA;

struct punto5 {
	cadena nombre;
	float sueldo;
	struct punto5 *sig;
};

typedef struct punto5 *nuevo;

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
		printf("\nNombre: %s - Categ:%d - Estado Civil:%s - Cant Hijos:%d",cabeza->punto1.nomEmp, cabeza->punto1.NumCat, cabeza->punto1.EstadoS ,cabeza->punto1.hijos);
		printf("\n************************************************************");
		longitud += 1;
		cabeza = cabeza->sig;
	}
	printf("\nTotal de empleados: %d", longitud);
	return;
}

void listado (puntoA registro[N]){
	int i;
	for (i=0;i<N;i++){
		printf("\nNUMERO DE PLANTA: %d               NOMBRE DE PLANTA: %s", i+1, registro[i].nombre);
		printf("\nPRODUCTOS QUE ELABORA: %d\n",registro[i].CantProducto);
		//printf ("\nNombre de empleado     Categoria   Estado civil 	   Cantidad de Hijos");
		printf("\n----------Mostramos informacion de cada empleado------------\n");
		mostrarLista (registro[i].cabexa);
		printf ("\n");      //Para la siguiente planta
		printf ("\n=======================================================================");
	}
	return;
}

void buscar_empleado(puntero cab, FILE * empleados,int dni){
	emp e;
	fpos_t xx;
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
					fgetpos (empleados, &xx);				//Obtener la pos actual del puntero
					e.hijos = cab->punto1.hijos;
					e.NumCat= cab->punto1.NumCat;
					fseek (empleados, xx-sizeof(e), SEEK_SET);		//Apuntar ala direcc anterior
				    fwrite(&e, sizeof(e),1,empleados);           //Grabamos la componente en el archivo
					fclose (empleados);
					printf ("\nCambia realizado");
				}
            }
		}
		cab = cab->sig;
	}
}


void punto3 (puntoA registro[N], FILE *empleados, int xdoc) {
int i;
	for (i=0; i < N; i++) {
		buscar_empleado (registro[i].cabexa, empleados, xdoc);
	}
	return;
}
//F
void nuevoArchivo (FILE *empleados, FILE *aux) {
	emp e;
	fseek (empleados, 0, SEEK_SET);			//Desplaz del puntero en pos inicial del archivo
	while (fread (&e, sizeof(e), 1, empleados) != 0) {
		if (e.dni != -1) {
			fwrite(&e,sizeof(e),1,aux);
		}
	}
}



void buscar_empleado2(puntero cab, FILE * empleados,int dni,FILE *aux){
	emp e;
	fpos_t xx;
	puntero p,anterior;
	rewind (empleados);
	while(cab!=NULL){
		if(dni == cab->punto1.dni) {
			while (fread (&e, sizeof(e), 1, empleados) != 0) {
				if (e.dni == dni) {
            p = cab;
		    anterior = p;
			p = p->sig;
			free(p);
					fseek (empleados, -sizeof(e), SEEK_CUR);		//obtener desplaz puntero
		            e.dni = -1;
		            fwrite (&e, sizeof(e), 1, empleados);
		            printf("\nEl empleado %s ha sido marcado para borrarse", e.nomEmp);
		            nuevoArchivo( empleados , aux );
		            remove ("EMPLEADOS.DAT");
                    rename ("auxiliar.DAT", "EMPLEADOS.DAT");
					printf ("\nCambia realizado");
				}
            }
		}
		cab = cab->sig;
	}
}



void punto4 (puntoA registro[N], FILE *empleados, int xdoc, FILE *auxiliar) {
	int i;
	for (i=0; i < N; i++) {
		buscar_empleado2 (registro[i].cabexa, empleados, xdoc,auxiliar);
	}
	return;
}

/*void punto4 (puntoA registro[N], FILE *empleados, int xdoc, FILE *auxiliar) {

		buscar_doc (registro[i].cabexa, empleados, xdoc, auxiliar);
	return;
}*/

float buscarCat(int nroCat,FILE *categoria){
	cat C;
	rewind (categoria);
	while ((fread (&C, sizeof(C), 1, categoria) != 0) && (nroCat != C.NumCat)) {
			return C.sueldo;
	}
}

void nuevaLista (nuevo cabeza, FILE *categoria , puntero xcab){
	nuevo p;
	float suma;
	while (xcab != NULL) {
		p = (nuevo) malloc (sizeof(struct punto5));
		strcpy (p->nombre, xcab->punto1.nomEmp);
		suma = buscarCat (xcab->punto1.NumCat, categoria);
	    p->sueldo = (xcab->punto1.hijos * 3540) + suma;
		p->sig = cabeza;				//Insertar nodos por delante de cabeza
		cabeza = p;
	}
	return;
}

void punto5 (nuevo cabeza, FILE *categoria, puntoA registro[N]) {
	int i;
	for (i = 0; i < N; i++) {
		nuevaLista (cabeza, categoria, registro[i].cabexa);
	}
}

void mostrarOrd(nuevo kbe){
	while(kbe!=NULL){
		printf("\nNombre del empleado: %s",kbe->nombre);
		printf("\nSueldo del Empleado %.2f", kbe->sueldo);
		kbe = kbe->sig;
	}
	return;
}

void punto6 (nuevo cabeza) {
	nuevo k=NULL, cota=NULL, p;
	cadena aux;
	while (k != cabeza) {
		k = cabeza, p= cabeza;
		while (p->sig != cota) {
			if (strcmp (p->nombre, p->sig->nombre) > 0) {
				strcpy (aux, p->sig->nombre);
				strcpy (p->sig->nombre, p->nombre);
				strcpy (p->nombre, aux);
				k = p;
			}
			p = p->sig;
		}
		cota = k->sig;
	}
	mostrarOrd (cabeza);
}

void punto7(FILE *sueldo, nuevo xkbeza){
	nuevo aux;
	while(xkbeza !=NULL){
	strcpy (aux->nombre , xkbeza->nombre);
	aux->sueldo = xkbeza->sueldo;
	fwrite( &aux, sizeof(aux) ,1, sueldo);
	xkbeza=xkbeza->sig;
	}
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
			       punto4(registro,empleados,doc, auxiliar);
				break;
			case 5: cabeza = NULL;
					punto5(cabeza, categoria,registro);
				break;
			case 6:	punto6(cabeza);
				break;
			case 7:	punto7(sueldo,cabeza);
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
	return 0;
}
