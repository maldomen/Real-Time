#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int length(char *str){
int l=0;
while(str[l] != '\0' && str[l] != '\n'){
	l++;
	}
	return l;
}

int stringcompadre(char *sr1, char *sr2){
	int len1 = length(sr1);
	int len2 = length(sr2);
	if (len1 < len2){
		return -1;
	}
	else if (len1 > len2){
		return 1;
	}
	else{
		int i;
		for(i=0; i<= len1-1; i++){
			if(sr1[i] != sr2[i]){
				return 2;
			}
		}
		return 0;	
	}
}



int asciitointeger(char *sr1){
//si es char torna -1 si es numero torna numero	
	int i;
	for (i=0; i < length(sr1); i++){
		if (sr1[i]<48 || sr1[i]>57){
			return -1;
		}
	}	
	return atoi(sr1); //fem servir la funcio atoi de la stdlib per convertir una cadena de caracters a enters
}

int main(int argc, char **argv){
	char buff[256];
	int i=0,sum=0;
	
	if (argc ==1 || argc==0 || argc>4){
		
		sprintf(buff, "La sintaxis es: action param1 [param2]\n");
		write(1,buff, length(buff));
		return -1;
		
	}
	else{
		for(i = 0; i < length(argv[1]); i++)
  		argv[1][i] = tolower(argv[1][i]);
	
	if((stringcompadre(argv[1],"compare"))==0){
		
		if(argc<4){
			sprintf(buff, "Per fer servir compare la sintaxis es:params compare string1 string 2 \n");
			write(2,buff, length(buff));
			return -1;
		}
		else if((stringcompadre(argv[2],argv[3]))==0){
			sprintf(buff, "Las cadenas son iguales\n");
			write(1,buff, length(buff));
			return 1;
		}
		else if(stringcompadre(argv[2],argv[3])==1){
			sprintf(buff, "La cadena 1 es mas larga que la cadena 2\n");
			write(1,buff, length(buff));
			return 1;
		}
		else if(stringcompadre(argv[2],argv[3])==-1){
			sprintf(buff, "La cadena 1 es mas corta que la cadena 2\n");
			write(1,buff, length(buff));
			return 1;
		}
		else if(stringcompadre(argv[2],argv[3])==2){
			sprintf(buff, "las cadenas son igual de largas con diferentes caracteres\n");
			write(1,buff, length(buff));
			return 1;
		}
		else{
			sprintf(buff, "error inespeado no se que has hecho pero la has liado\n");
			write(1,buff, length(buff));
			return -1;
		}
	}
		
	else if((stringcompadre(argv[1],"number")==0)){
		if(asciitointeger(argv[2])==-1){
			sprintf(buff, "error inespeado introduzca un formato correcto\n");
			write(1,buff, length(buff));
			return -1;
		}
		else {
			sprintf(buff, "El param1 en haxadecimal es %X\n",asciitointeger(argv[2]));
			write(1,buff, length(buff));
			

			return 1; //hem adaptat una funcio de stackoverflow al nostre
		}

	}
	else{ 
		
		if(argc>=3){
		
		
		for(i=0;i < length(argv[2]);i++){
	
			if(argv[2][i]==argv[1][0]){
				sum=sum+1;
			
			}
		}

		sprintf(buff, "El primer caracter de action aparece %d veces en param1\n",sum);
		write(1,buff, length(buff));
		return 1;
	}		
		else{
			sprintf(buff, "Introduce 1 parametro para buscar cuantas veces aparece el primer caracter en action\n");
			write(1,buff, length(buff));
			return -1;

		}
		

}

}
}

