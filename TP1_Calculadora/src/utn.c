/*
 * utn.c
 *
 *  Created on: 3 sep. 2020
 *      Author: Flores E. Federico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int getInt(int* pResultado); //utilizada en utn_getNumero
static int esNumerica(char* cadena);//utilizada en getInt
static int myGets(char* cadena, int longitud);//utilizada en getInt, getFloat y getString
static int getFloat(float* pFloat);// utilizada en utn_getNumeroFloat
static int esNumeroDecimal(char* buffer); // utilizada en getFloat
static int getString(char* pResultado,int longitud); //utilizada en utn_getCadena
static int esSoloLetras(char* pResultado); //utilizada en getString

/*
 * utn_getNumero : pide al usuario un numero entero
 * pResultado : Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * mensaje : El mensaje que imprime para pedir un valor.
 * mensajeError: El mensaje que imprime si el rango no es valido.
 * minimo : valor minimo valido (inclusive)
 * maximo : valor maximo valido (inclusive)
 * Reintentos: cantidad de veces que tiene el usuario para ingresar un valor valido
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos){
	int retorno = -1;
	int bufferInt;
	int resultadoScan;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos > 0){
		do{
			printf("%s", mensaje);
			fflush(stdin);
			resultadoScan = getInt(&bufferInt);
			if(resultadoScan == 1 && bufferInt >= minimo && bufferInt <= maximo){
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}else{
				printf("\n-REINTENTOS : %d\n",reintentos);
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/*
 * getInt: pide un texto al usuario, lo almacena como cadena, valida y convierte el texto a numero y lo devuelve como int
 * presultado: puntero numero entero
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int getInt(int* pResultado){
	int retorno = 0;
	int resultadoGets;
	char buffer[64];
	if(pResultado != NULL){
		resultadoGets = myGets(buffer,sizeof(buffer));
		if(resultadoGets && esNumerica(buffer)){
			*pResultado = atoi(buffer);
			retorno = 1;
		}
	}
	return retorno;
}

/*
 * esNumerica: Recibe una cadena de caracteres y devuelve 1 en caso de que el texto este compuesto solo por numeros
 * cadena: cadena de caracteres
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int esNumerica(char* cadena){
	int retorno = 1;
	int i = 0;
	if(cadena[0] == '-' ){
		i = 1;
	}
	for(;cadena[i] != '\0';i++){
		if(cadena[i] < '0' || cadena[i] > '9' ){
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/**
* myGets: Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena un máximo de ' longitud - 1' caracteres .
* cadena: Puntero al espacio de memoria donde se copiara la cadena obtenida
* longitud:  Define el tamaño de cadena
* Retorno: 1 (EXITO) si se obtiene una cadena y 0 (ERROR) si no
*
*/
static int myGets(char* cadena, int longitud){
	int retorno = 0;
	if(cadena != NULL && longitud > 0 && fgets(cadena,longitud,stdin)){
		fflush(stdin);
		if(cadena[strlen(cadena)-1] == '\n'){
			cadena[strlen(cadena)-1] = '\0';
		}
		retorno = 1;
	}
	return retorno;
}

/*
 * utn_getNumeroFloat : pide al usuario un numero flotante
 * pResultado : Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * mensaje : El mensaje que imprime para pedir un valor.
 * mensajeError: El mensaje que imprime si el rango no es valido.
 * minimo : valor minimo valido (inclusive)
 * maximo : valor maximo valido (inclusive)
 * Reintentos: cantidad de veces que tiene el usuario para ingresar un valor valido
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos){
	int retorno = -1;
	float bufferFloat;
	int resultadoScan;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos > 0){
		do{
			printf("%s", mensaje);
			fflush(stdin);
			resultadoScan = getFloat(&bufferFloat);
			if(resultadoScan && minimo <= bufferFloat && maximo >= bufferFloat){
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}else{
				printf("%s", mensajeError);
				printf("\n-REINTENTOS: %d \n",reintentos);
				reintentos--;
			}

		}while(reintentos >= 0);
	}
	return retorno;
}

/*
 * getFloat: pide un texto al usuario, lo almacena como cadena, valida y convierte el texto a numero y lo devuelve como float
 * presultado: puntero numero float
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int getFloat(float* pFloat){
	int retorno = 0;
	char bufferFloat[64];
	int resultadoScan;
	if(pFloat != NULL){
		fflush(stdin);
		resultadoScan = myGets(bufferFloat,sizeof(bufferFloat));
		if(resultadoScan && esNumeroDecimal(bufferFloat)){
			*pFloat = atof(bufferFloat);
			retorno = 1;
		}
	}
	return retorno;
}

/*
 * esNumeroDecimal: Recibe una cadena de caracteres y devuelve 1 en caso de que el texto este compuesto solo por numeros y/o una sola coma
 * cadena: cadena de caracteres
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int esNumeroDecimal(char* buffer){
	int retorno = 1;
	int contadorDePuntos = 0;
	int i;
	if(buffer != NULL && strlen(buffer) > 0){
		if(buffer[0] == '-' ){
			i = 1;
		}
		for( ;buffer[i] != '\0';i++){
			if(buffer[i] < '0' || buffer[i] > '9'){
				if(buffer[i] != '.'){
					retorno = 0;
					break;
				}else{
					contadorDePuntos++;
				}
				if(contadorDePuntos == 2){
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}


/*
 * utn_getCaracter : pide al usuario una letra
 * pResultado : Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * mensaje : El mensaje que imprime para pedir un valor.
 * mensajeError: El mensaje que imprime si el rango no es valido.
 * minimo : valor minimo valido (inclusive)
 * maximo : valor maximo valido (inclusive)
 * Reintentos: cantidad de veces que tiene el usuario para ingresar un valor valido
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int utn_getCaracter(char* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos){
	int retorno = -1;
	char bufferChar;
	int resultadoScan;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos > 0){
		do{
			printf("%s", mensaje);
			fflush(stdin);
			resultadoScan = scanf("%c",&bufferChar);
			if(resultadoScan == 1 && bufferChar >= minimo && bufferChar <= maximo){
				*pResultado = bufferChar;
				retorno = 0;
				break;
			}else{
				printf("\n-REINTENTOS : %d\n",reintentos);
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}



/*
 * imprimirArray: imprime los datos de un array de enteros
 * array: array de enteros
 * len: longitud de array
 * Retorno: VOID
 */
void imprimirArray(int array[],int lengitud){
	int i;
	for(i=0;i<lengitud;i++){
		printf("%d ",array[i]);
	}
}

/*
 * insertion: burbujeo de de un array de enteros
 * array: array de enteros
 * len: longitud de array
 * Retorno: VOID
 */
void insertion(int array[],int len){
	int i;
	int j;
	int temp;
	for(i=1;i<len;i++){
		temp = array[i];
		j = i - 1;
		while(j >= 0 && temp < array[j]){ 	// temp<array[j] o temp>array[j]
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = temp; //insercion
	}
}


/*
 * utn_getString: pide al usuario un string
 * pResultado : Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * longitud: tamaño total del array de caracteres
 * mensaje : El mensaje que imprime para pedir un valor.
 * mensajeError: El mensaje que imprime si el rango no es valido.
 * Reintentos: cantidad de veces que tiene el usuario para ingresar un valor valido
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */

int utn_getCadena(char* pResultado,int longitud,char* mensaje,char* mensajeError,int reintentos){
	int retorno = -1;
	char bufferChar[45];

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos > 0){
		do{
			printf("%s",mensaje);
			if(getString(bufferChar,sizeof(bufferChar))){
				strncpy(pResultado,bufferChar,longitud);
				retorno = 0;
				break;
			}else{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}


/*
 * getString: pide un texto al usuario, lo almacena como cadena, valida y lo devuelve
 * presultado: puntero a  array de caracter
 * longitud: tamaño del array
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int getString(char* pResultado,int longitud){
	int retorno = 0;
	char buffAux[1000];
	if(pResultado != NULL && longitud > 0){
		fflush(stdin);
		if(myGets(buffAux,sizeof(buffAux)) && esSoloLetras(buffAux)){
			strncpy(pResultado,buffAux,longitud);
			retorno = 1;
		}
	}
	return retorno;
}

/*
 * esSoloLetras: Recibe una cadena de caracteres y devuelve 1 en caso de que el texto este compuesto solo por letras y/o espacio
 * pResultado: cadena de caracteres
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int esSoloLetras(char* pResultado){
	int retorno = 1;
	int i;
	if(pResultado != NULL){
		for(i=0;pResultado[i] != '\0';i++){
			if((pResultado[i] != ' ') && (pResultado[i] < 'a' || pResultado[i] > 'z') && (pResultado[i] < 'A' || pResultado[i] > 'Z')){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*
 * esAlfaNumerica: Recibe una cadena de caracteres y devuelve 1 en caso de que el texto este compuesto solo por letras y/o espacio y/o numeros
 * pResultado: cadena de caracteres
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */

int esAlfaNumerica(char* pResultado){
	int retorno = 1;
	int i;
	if(pResultado != NULL){
		for(i=0;pResultado[i] != '\0';i++){
			if((pResultado[i] != ' ') && (pResultado[i] < 'a' || pResultado[i] > 'z') && (pResultado[i] < 'A' || pResultado[i] > 'Z') && (pResultado[i] < '0' || pResultado[i] > '9')){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int esTelefono(char* pResultado){
	int retorno = 1;
	int i;
	int numeroDeGuiones = 0;
	if(pResultado != NULL){
		for(i=0;pResultado[i] != '\0';i++){
			if(((pResultado[i] != '-') && (pResultado[i] < '0' || pResultado[i] > '9')) || (numeroDeGuiones > 1)){
				retorno = 0;
				break;
			}
			if(pResultado[i] == '-'){
				numeroDeGuiones++;
			}
		}
	}
	return retorno;
}
