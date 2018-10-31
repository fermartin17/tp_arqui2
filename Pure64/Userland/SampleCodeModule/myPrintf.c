#include <stdarg.h>
#include "myPutchar.h"

#define NORMAL 0
#define ESP 1

int strlen(char* str){
	int i=0;
	while(str[i]!= '\0'){
		i++;
	}
	return i;
}

void toString(int num,char* resp){
	int digit=0;
	char aux;
	if(num!=0){
    // Arma el numero en el vector
		while(num!=0){
			resp[digit]=(num%10)+'0';
			num=num/10;
			digit++;
		}
    //invierte el orden de los numeros
		for(int i=0;i<digit/2;i++){
			aux=resp[i];
			resp[i]=resp[digit-i-1];
			resp[digit-i-1]=aux;
		}
    //agrega el 0 al final
		resp[digit]=0;
	}
  else{
    //si el numero es cero carga un cero en el vector
		resp[0]='0';
	}
	return;
}

// Toda la informacion sobre argumentos variables la sacamos de esta pagina, seguimos los
//ejemplos utilizados al pie de la letra por el deconocimiento que teniamos
// https://www.tutorialspoint.com/c_standard_library/stdarg_h.htm


void myPrintf(char * cadena,...)
{
	char resp[10];
	va_list ap;
	va_start (ap,cadena);
	int dim=strlen(cadena);
	int caso=NORMAL;
  	int index=0;
	for(int i=0;i<dim;i++){
		if(caso==NORMAL){
			if(cadena[i]!= '%')
				myPutchar(cadena[i]);
			else
				caso=ESP;
		}
    else{
			switch(cadena[i]){
				case 'd':
					toString(va_arg (ap, int),resp);
					while(resp[index]!=0)
						myPutchar(resp[index++]);
					caso=NORMAL;
					break;
				case 'c':
					myPutchar((char)(va_arg(ap,int)));
					caso=NORMAL;
					break;
				case 's':
					myPrintf(va_arg(ap, char*));
					caso=NORMAL;
					break;
				default:
					myPutchar('%');
					myPutchar(cadena[i]);
					caso=NORMAL;
					break;
			}
		}

	}
	va_end(ap);
}

void myPrintfBig(int color,char * cadena,...) {
	char resp[10];
	va_list ap;
	va_start (ap,cadena);
	int dim=strlen(cadena);
	int caso=NORMAL;
  	int index=0;
	for(int i=0;i<dim;i++){
		if(caso==NORMAL){
			if(cadena[i]!= '%')
				myPutcharBig(cadena[i],color);
			else
				caso=ESP;
		}
    else{
			switch(cadena[i]){
				case 'd':
					toString(va_arg (ap, int),resp);
					while(resp[index]!=0)
						myPutcharBig(resp[index++],color);
					caso=NORMAL;
					break;
				case 'c':
					myPutcharBig((char)(va_arg(ap,int)),color);
					caso=NORMAL;
					break;
				case 's':
					myPrintfBig(color,va_arg(ap, char*));
					caso=NORMAL;
					break;
				default:
					myPutcharBig('%',color);
					myPutcharBig(cadena[i],color);
					caso=NORMAL;
					break;
			}
		}

	}
	va_end(ap);
}
