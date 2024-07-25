#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define C 4
#define F 5

void carga(int arre[F][C]){
    int fila;
    int columna;
printf("ingrese valor de la fila y la columna \n");
scanf("%d",&fila);
scanf("%d",&columna);
if((fila<=5)&&(columna<=4)){
    while((fila!=0)&&(columna!=0)&&(fila<=5)&&(columna<=4)){
        printf("ingrese el valor de la componente deseada\n");
        scanf("%d",&arre[fila-1][columna-1]);
        printf("ingrese valor de la siguiente fila y columna\n");
        scanf("%d",&fila);
        scanf("%d",&columna);
    }
}
else{
    printf("la componente no exite,ingrese valores nuevamente\n\n");
    carga(arre);
    }
    return;

}
void mostrar (int arre[F][C]){
    int i,j;
    for(i=0;i<F;i++){
        for(j=0;j<C;j++){
            printf("%2d",arre[i][j]);
        }
        printf("\n");
    }
    return;
}
int suma(int arre[F][C]){
    int j,ff;
    int acum=0;
    printf("ingrese fila que desea sumar\n");
    scanf("%d",&ff);
    for(j=0;j<C;j++){
        acum+=arre[ff-1][j];
    }
    return acum;
}

void comparar(int arre[F][C]){
    int i;
    int cont=0;
    int acum2=0,acum3=0;
    for(i=0;i<C;i++){
        if(arre[1][i]==arre[2][i]){
            cont+=1;
        }
        acum2+=arre[1][i];
        acum3+=arre[2][i];
    }
    if(cont==4){
        printf("las filas 2 y 3 son iguales\n");
    }
    else{printf("las filas no son iguales\n\n");}
    printf("el promedio de la fila dos es %d\n",acum2/4);
    printf("el promedio de la fila tres es de %d\n",acum3/4);
    return;
}
int mayor (int arre[F][C],int j){
int max=0,i;
for(i=0;i<F;i++){
    if(max<arre[i][j]){
        max=arre[i][j];
    }
}
return max;
}

int main(){
int arre[F][C]={};
int j=0;
int funcion1;
carga(arre);
mostrar(arre);
funcion1=suma(arre);
printf("la suma de la fila deseada es de %d\n",funcion1);
comparar(arre);
printf("el valor maximo de la columna 1 es %d\n",mayor(arre,j));
j+=1;
printf("el valor maximo de la columna 2 es %d\n",mayor(arre,j));
j+=1;
printf("el valor maximo de la columna 3 es %d\n",mayor(arre,j));
j+=1;
printf("el valor maximo de la columna 4 es %d\n",mayor(arre,j));

printf("No podemos enviar una columna como tal o una fila sola.\nPero podemos pasar una variable como parametro que adopte el indice con el cual queremos trabajar\n");
printf("La diferencia es que para mandar una fila unica,hay que trabajar con una variable extra... \nEn cambio usando un for,podemos iterar entre filas y columnas de manera optima");
}
