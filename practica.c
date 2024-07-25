
#include <stdio.h> // printf
#include <stdlib.h> // rand
#include <unistd.h> // getpid

int rango(int minimo,int maximo);
// Función main
int main(){
    // Hay que alimentar a rand, solamente una vez (seed rand)
    srand(getpid());
    // Ahora ya podemos llamar a la función
    printf("Tengo un aleatorio: %d\n", rango(1,10));
    printf("Tengo un aleatorio: %d\n", rand());
    printf("Tengo un aleatorio: %d\n", rand());
    printf("Tengo un aleatorio: %d\n", rand());
    printf("Tengo un aleatorio: %d\n", rand());
    printf("Tengo un aleatorio: %d\n", rand());
}


int rango(int minimo, int maximo){
   return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}
