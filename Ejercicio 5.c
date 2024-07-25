#include "stdio.h"
#define F 5
#define C 4

int main(){
int tabla[F][C],i,k;
int acum=0;
int cont=0;
int fila,columna;

printf("ingrese valor de la fila\n");
scanf("%d",&fila);
printf("ingrese valor de la columna\n");
scanf("%d",&columna);
while((columna<=4)&&(fila<=5)&&(fila!=0)){
    printf("ingrese el valor de esa posicion\n");
    scanf("%d",&tabla[fila-1][columna-1]);
    printf("ingrese siguiente valor de la fila\n");
     scanf("%d",&fila);
    printf("ingrese siguiente valor de la columna\n");
    scanf("%d",&columna);
}

for(i = 0; i < F; i++){

    for(k = 0; k < C; k++){
printf("posicion %d,%d = %d  ",i+1,k+1,tabla[i][k]);

    }
}
for(i = 0; i < F; i++){

    for(k = 0; k < C; k++){
    acum=acum+tabla[i][k];

    }
    printf("\nla suma de la fila %d es %d\n",i+1,acum);
    acum=0;
}

for(k = 0; k < C; k++){
    acum=acum+tabla[2][k];

    }
printf("el promedio de la columna %d es: %d\n",3,float(acum/4));

for(i = 0; i < F; i++){

    for(k = 0; k < C; k++){
if(tabla[i][k]>100){
    printf("en la posicion %d,%d hay un numero mayor a 100\n",i+1,k+1);
    cont=cont+1;

}

    }
}
printf("en la tabla hay %d numeros mayores a 100\n",cont);
return 0;
}


