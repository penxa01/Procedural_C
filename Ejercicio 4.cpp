#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NF 5
#define NC 4

int aleatorio_en_rango(int minimo, int maximo){
	return(minimo + rand()/(RAND_MAX/(maximo-minimo+1)+1));
}


void aleatorizar(int xtabla[][NC]){
	int i, j;
	for (i=0; i<NF; ++i){
		for(j=0; j<NC; ++j){
			xtabla[i][j] = aleatorio_en_rango(1, 100);
		}
	}
	return;
}

int calcular_fila(int fila[]){
	int i, acum=0;
	for(i=0; i<NC; ++i){
		acum += fila[i];
	}
	return(acum);
}

bool iguales_promedio(int xtabla[][NC], int &p2, int &p3){
	int i;
	bool iguales = true;
	p2=0;
	p3=0;
	for(i=0; i<NC; ++i){
		p2 += xtabla[2][i];
		p3 += xtabla[3][i];
	}
	p2 /= NC;
	p3 /= NC;
	i=0;
	while(iguales && (i<NC)){
		iguales = (xtabla[1][i] == xtabla[2][i]);
		i++;
	}
	return(iguales);
}

int mayor_de_columna(int xtabla[][NC], int columna){
	int i, mayor = xtabla[0][columna];
	for(i=1; i<NF; ++i){
		if (mayor < xtabla[i][columna]){
			mayor = xtabla[i][columna];
		}
	}
	return(mayor);
}


int main(){
	int tabla[NF][NC], fila, prom2, prom3;
	bool iguales;
	srand(getpid());
	aleatorizar(tabla);
	printf("Ingresa un número de fila para ver la suma de sus componentes: \n");
	scanf("%i", &fila);
	printf("La suma de las componentes de la fila %i es: %i \n", fila, calcular_fila(tabla[fila]));
	iguales = iguales_promedio(tabla, prom2, prom3);
	if (iguales){
		printf("Las filas 2 y 3 son iguales \n");
		printf("El promedio de ambas filas es: %i", prom2);
	}
	else{
		printf("Las filas 2 y 3 no son iguales \n");
		printf("El promedio de la fila 2 es %i y el de la fila 3 es %i", prom2, prom3);
	}
}
