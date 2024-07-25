#include "stdio.h"
#include "conio.h"

int main(){
    FILE *archivo;
    archivo=fopen("archivo.dat","w");
    char c;
    printf("Ingresa una lerta cualquiera\n");
    scanf("%c",&c);
    c=fputc(c,archivo);
    printf("%c",c);
}
