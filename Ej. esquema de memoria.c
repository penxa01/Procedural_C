#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#define N 50


int m=0;
int calculo (int v, int w)
{ static int z=0;
if ((w==1)&& (v==0)) z++; return z;
}

void main(void)
{
int a,b, y=0;
printf("\n ingrese par de valores a y b"); scanf("%d %d", &a, &b);
while (a<b)
{
int c;
c=a*b;
calculo (a,b);
int x+=a;
int y+=b;
printf("\n ingrese valor a y b"); scanf("%d %d", &a, &b); printf("\n	%d", c);
}
printf("\n	%d", calculo(a,b));
printf("\n ......%d	%d", x,y);
}
