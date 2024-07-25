#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#include "tipo.h"

void mostrar(FILE *empresas,FILE *empleados){
	empleados=fopen("empleados.DAT","rb");
	empresas=fopen("empresas.DAT","rb");
	rewind(empresas);
	rewind(empleados);
	empleado x;
	empresa y;
	float suel,totalH,totalD;
	int i;
	fread(&x,sizeof(x),1,empleados);
	while(!feof(empleados)){
		i=x.codEmp;
		totalH=0;
		totalD=0;
		fread(&y,sizeof(y),1,empresas);
		printf("Empresa: %s\n",y.nombre);
		printf("Nommbre de empleado.                      Remuneracion\n");
		while((!feof(empleados))&&(x.codEmp==i)){
			suel=x.sueldo+ x.antiguedad* x.sueldo;
			printf("%s                                    %.0f\n",x.nomEmp,suel);
			totalH+=suel-((x.sueldo*0.11)+(x.sueldo*0.03))-3.80;
			totalD+=((x.sueldo*0.11)+(x.sueldo*0.03))+suel +3.80;
			fread(&x,sizeof(x),1,empleados);	
		}
	 printf("Total pagado en concepto de haberes:%.0f\n",totalH);
	 printf("Total pagado en concepto de descuento: %.0f\n",totalD);
	 printf("-----------------------------------------------\N");
	}
	
	/*empleado x;
	empresa y;
	float totalH=0;
	float totalD=0;
	int i;
	empresas=fopen("empresas.DAT","rb");
	empleados=fopen("empleados.DAT","rb");
	  while(fread(&y,sizeof(y),1,empresas)!=0){
	  	  totalH=0;
	      totalD=0;
	      
	  	printf("Empresa: %s\n",y.nombre);
	  	printf("Nommbre de empleado.                      Remuneracion\n");
	  	while((fread(&x,sizeof(x),1,empleados)!=0) && (y.cod==x.codEmp)){
	  		printf("%s                                    %.0f\n",x.nomEmp,x.sueldo);
	  		totalH+=x.sueldo;
	  		totalD+=x.sueldo;
		  }
		  printf("Total pagado en concepto de haberes:%.0f\n",totalH);
		  printf("Total pagado en concepto de descuento: %.0f\n",totalD);
		  printf("\n");*/   //ESTA VERSION DE CODIGO SOLO MOSTRABA LA PRIMERA EMPRESA//
		   
	  
	  fclose(empresas);
	  fclose(empleados);
	
}
