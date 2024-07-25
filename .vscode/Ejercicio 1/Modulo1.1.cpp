#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#include "tipo.h"

int longi(FILE *empresas,empresa A){
	long registro;

	fpos_t nBytes;
	empresas=fopen("empresas.DAT","rb");
	fseek(empresas,0,SEEK_END);
	fgetpos(empresas,&nBytes);
	registro=nBytes/sizeof(A);
	printf("La longitud del arhivo es de : %d\n", registro);
	fclose(empresas);
	return registro;
}
