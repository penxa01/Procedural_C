#include <stdio.h>
#include<string.h>
#define N 6
//Ejercicio 4
	//Construir un programa en lenguaje C que a través de funciones recursivas resuelva los siguientes ítems:
	//a) Cargar un arreglo de enteros, de N componentes.
//	b) Generar un subarreglo con las componentes del arreglo cargado, cuyo valor es mayor o igual al Promedio.
//	c) Indicar cuantas componentes del subarreglo son mayores al promedio y cuantas iguales a éste.
//	d) Ingresar un número y decir si se encuentra en el subarreglo.
//	e) Realice el ítem anterior si el arreglo original estuviera ordenado ascendentemente.	
	


void cargar(int arre[], int inf, int sup){
	int i;
	if(inf!=sup){
		printf("ingrese valor entero \n");
		scanf("%i", &arre[inf]);
		cargar(arre,inf+1,sup);
		
	}
	return;
}
	
int promedio(int arre[], int inf, int sup, int xprom){
	if(inf < sup){
		xprom = xprom + arre[inf];
			promedio(arre, inf+1, sup,xprom);
	}
	
	return (xprom / sup);
	
	
}

int genera (int arre[], int suba[], int inf, int sup, int oprom){
	int cont;
	cont=0;
	if(inf!= sup){
		if(arre[inf] >= oprom){
			suba[cont] = arre[inf];
			cont++;
		}
		genera(arre, suba, inf+1, sup, oprom);
	}
	return(cont);
}

void mayoroigual(int suba[], int inf, int sup, int oprom, int xc){
	if(inf < xc){
		if(suba[inf] > oprom){
			printf("El valor de la componente %d , es mayor que el promedio", inf);
		}
		else{ 
			printf("El valor de la componente %d , es igual que el promedio", inf);
		}
		mayoroigual(suba, inf+1, sup, oprom,xc);
	}
	return;
}
	
int buscar(int suba[], int inf, int sup, int xc, int xnum){
	int i;
	i=0;
	if(inf < xc){
		if(suba[inf] != xnum){
			i++;
		}
		buscar(suba, inf+1, sup, xc, xnum);
	}
	return(i);
}

int main()
{
	int arre[N], o, suba[N], c, num, x;
	int prom;
	prom=0;
	cargar(arre,0,N);
	o= promedio(arre,0,N, prom);
	printf("El promedio de los datos cargados en el arreglo es: %i \n", o);
	c=genera(arre, suba, 0, N, o);
	mayoroigual(suba,0,N,o,c);
	printf("Ingrse numero a buscar");
	scanf("%d", &num);
	x=buscar(suba, 0, N, c, num);
	if(x<c){
		printf("El numero ingresado se encontro en el subarreglo");
	}
	else{ 
		printf("El numero ingresado no se encontro en el arreglo");
	}
}
