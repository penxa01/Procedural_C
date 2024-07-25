#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef char cadena[40];
struct inqui {
	float importe;
	cadena nom;
	char cel[12];
	int nrod;
	int pago; /*(1-pago, 2-no pago)*/
};

struct lista {
	cadena nom;
	char cel[12];
	int nrod;
	struct lista *sig;
};
typedef struct lista *puntero;

/*prototipos de funciones*/
void punto_a (FILE *archi);
void punto_b (FILE *archi);
void punto_c (FILE *archi, puntero &cab);
void punto_d (puntero &cab, int numero);

void mostrarArchivo (FILE *archi) {
	struct inqui cli;
	rewind (archi);
	while (fread (&cli, sizeof(cli), 1, archi) != 0) {
		printf("\nNombre del cliente %s", cli.nom);
		printf("\nImporte del cliente %.2f", cli.importe);
		printf("\nCelular del cliente %s", cli.cel);
		printf("\nNumero de Departamento %d", cli.nrod);
		printf("\nOpcion elegida de pago(1-pago,2-no pago) %d", cli.pago);
		printf("\n------------------------------------------------------");
	} 
	return;
}

void mostrarLista (puntero cab) {
	printf("\nMostramos la lista generada\n");
	while (cab != NULL) {
		printf("\nNombre del inquilino: %s", cab->nom);
		printf("\nCelular del inquilino: %s", cab->cel);
		printf("\nNumero de Departamento: %d", cab->nrod);
		printf("\n==============================================");
		cab = cab->sig;
	}
	return;
}

int main (void) {
	FILE *archivo;
	puntero cabeza;
	int numero;
	archivo = fopen ("Inquilino.dat", "r+");
	if (archivo != NULL) {
		mostrarArchivo (archivo);
		punto_a (archivo);
		punto_b (archivo);
		punto_c (archivo, cabeza);
		mostrarLista (cabeza);
		printf("\nIngrese numero de departamento: ");
		scanf("%d", &numero);
		punto_d (cabeza, numero);
	} else {
		printf("\nHubo error en la apertura del archivo\n");
	}
	
	return 0;
}

void punto_a (FILE *archi) {
	cadena nombre;
	struct inqui puntoA;
	long int x;
	rewind (archi);
	printf("\nIngrese nombre del inquilino: ");
	fgets (nombre, 40, stdin);
	strtok (nombre, "\n");
	fread (&puntoA, sizeof(puntoA), 1, archi);
	while ((!feof(archi)) && (strcmp (nombre, puntoA.nom) != 0)) {
		fread (&puntoA, sizeof(puntoA), 1, archi);
	}
	if (!feof(archi)) {
		printf("\nEl importe actual es: %.2f", puntoA.importe);
		printf("\nIngrese el nuevo importe: ");
		x = ftell (archi);
		scanf("%f", &puntoA.importe);
		fseek (archi, x-sizeof(puntoA), SEEK_SET);
		printf("\nInquilino %s, con nuevo importe de %.2f", puntoA.nom, puntoA.importe);
		fwrite (&puntoA, sizeof(puntoA), 1, archi);
	}
	return;
}

void punto_b (FILE *archi) {
	struct inqui puntoB;
	float ac=0;
	rewind (archi);
	while (fread (&puntoB, sizeof(puntoB), 1, archi) != 0) {
		if (puntoB.pago == 2) {
			ac += puntoB.importe;
		}
	}
	printf("\nLo que se debe en alquiler es %.2f", ac);
	return;
}

void punto_c (FILE *archi, puntero &cab) {
	struct inqui puntoC;
	puntero nuevo;
	rewind (archi);
	cab = NULL;
	while (fread (&puntoC, sizeof(puntoC), 1, archi) != 0) {
		if (puntoC. pago == 1) {
			nuevo = (puntero) malloc (sizeof(struct lista));
			strcpy (nuevo->nom, puntoC.nom);
			strcpy (nuevo->cel, puntoC.cel);
			nuevo->nrod = puntoC.nrod;
			
			nuevo->sig = cab;
			cab = nuevo;
		}
	}
	return;
}

void punto_d (puntero &cab, int xnumero) {
	puntero ant, p;
	void eliminar (puntero p, puntero ant, int nro);	//Prototipo
	if (cab->nrod == xnumero) {
		p = cab;
		cab = cab->sig;
		free (p);
	} else {
		p = cab, ant = cab;
		eliminar (p, ant, xnumero);
	}
	return;
}

void eliminar (puntero p, puntero ant, int xnro) {
	if ((p != NULL) && (p->nrod != xnro)) {
		ant = p;
		p = p->sig;
		eliminar (p, ant, xnro);
	} else {
		if (p != NULL) {
			printf("\nEliminamos inquilino %s", p->nom);
			free (p);
		} else {
			printf("\nNo se pudo eliminar inquilino\n");
		}
	}
	return;
}
