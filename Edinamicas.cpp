#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"

int rango(int minimo, int maximo){
   return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void cargar(int *vector,int &tamano){
 int i;
 for (i=0;i<tamano;i++){
vector[i]=rango(1,30);
printf("%3d",vector[i]);
 }
 printf("\n");
 return;
}

int producto(int *v1,int *v2,int tamano){
    int i;
    int vproducto;
for(i=0;i<tamano;i++){
    vproducto+=((v1[i])*(v2[i]));
}
return vproducto;

}

int nueva(int *v,int cont,int cont2,int tamano,int *nuev){
    if(cont2<tamano){
        if(v[cont2]%2==1){
            nuev[cont]=v[cont2];
            nueva(v,cont+1,cont2+1,tamano,nuev);//avanzo una posicion de la estructura y de el vector//
            }
        else{nueva(v,cont,cont2+1,tamano,nuev);}
    }
    else{return cont;}

}

int main(){
	int *vector1,*vector2;
    int tamano,numero;
    int *nuev,cont=0,p;
    int i;
    int cont2=0;
    printf("Ingrese tamano de los vectores\n");
    scanf("%d",&tamano);
    vector1=(int *)malloc(tamano* sizeof(int));
    vector2=(int *)malloc(tamano* sizeof(int));
    srand(getpid());
	cargar(vector1,tamano);
    cargar(vector2,tamano);
    int escalar=producto(vector1,vector2,tamano);
     printf("El producto entre vectores es %d\n",escalar);
     printf("De que vector quiere analizar la paridad de sus numeros?\n");
     scanf("%d",&numero);
      nuev=(int *)malloc(sizeof(int));
     if(numero==1){
        p=nueva(vector1,cont,cont2,tamano,nuev);
        for(i=0;i<p;i++){
         printf("%2d ",nuev[i]);
     }
     }
     else{
         if(numero==2){
             p=nueva(vector2,cont,cont2,tamano,nuev);
             for(i=0;i<p;i++){
         printf("%2d ",nuev[i]);
     }
         }
         else{printf("El numero es incorrecto");
         }
     }
     free(nuev,vector1,vector2);

}
00