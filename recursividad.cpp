#include "stdio.h"
#include "stdlib.h"
#define N 6

void cuestionario(int v,int arre[N]){
   if(v==0){return;}else{
if(v==1){arre[v-1]=arre[v-1]+1;}
else{if(v==2){arre[v-1]=arre[v-1]+1;}
else{if(v==3){arre[v-1]=arre[v-1]+1;}
else{if(v==4){arre[v-1]=arre[v-1]+1;}
else{if(v==5){arre[v-1]=arre[v-1]+1;}
else{if(v==6){arre[v-1]=arre[v-1]+1;}}}}}
}}
 printf("ingerse nuevamente el valor\n");
scanf("%d",&v);
  cuestionario(v,arre);
return;
}
void mostrar(int arre[N]){
    if(arre[0]<4000){printf("el lenguaje 1 tiene menos de 4000 encuestados");}
    else{if(arre[1]<4000){printf("el lenguaje 2 tiene menos de 4000 encuestados");}
    else{if(arre[2]<4000){printf("el lenguaje 3 tiene menos de 4000 encuestados");}
    else{if(arre[3]<4000){printf("el lenguaje 4 tiene menos de 4000 encuestados");}
    else{if(arre[4]<4000){printf("el lenguaje 5 tiene menos de 4000 encuestados");}
    else{if(arre[5]<4000){printf("el lenguaje 6 tiene menos de 4000 encuestados");}}}}}
}return;
}
int main(){
    int arre[N]={};
int valor,i;
printf("ingrese el numero de lenguaje elegido\n");
scanf("&d",&valor);
cuestionario(valor,arre);
 printf("\n");
for(i=0;i<N;i++){
    printf("%d\n",arre[i]);
}
mostrar(arre);
}
