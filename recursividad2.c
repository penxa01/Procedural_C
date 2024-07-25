#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#define N 10

int aleatorio_en_rango(int minimo, int maximo){
   return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void carga(int arre[N],int i){

    if(i<N){
        arre[i]=aleatorio_en_rango(1,100);
        printf("%3d",arre[i]);
        carga(arre,i+1);
    }else{return;}
}

int suma(int arre[N],int inf,int sup){
 if(inf<=sup){
     return arre[inf]+suma(arre,inf+1,sup);
 }else{return 0;}
}

void subarreglo(int arre[N],int sub[N],int i,int cont){
    if(i<N){
        if(arre[i]>(suma(arre,0,9)/10)){
            sub[cont]=arre[i];
            subarreglo(arre,sub,i+1,cont+1);
        }
        subarreglo(arre,sub,i+1,cont);
    }
    printf("%2d",sub[cont]);
    return;
}

int main (){
    int arre[N];
    int sub[N];
    int i=0;
    srand(getpid());
    carga(arre,i);
    printf("\nLa suma de las componentes es de %d",suma(arre,0,9));
    printf("\n El promedio de las componentes es de %d\n",suma(arre,0,9)/10);
    subarreglo(arre,sub,i,0);

}
