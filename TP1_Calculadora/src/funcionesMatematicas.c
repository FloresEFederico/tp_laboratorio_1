/*
 * funcionesMatematicas.c
 *
 *  Created on: 11 sep. 2020
 *      Author: Flores E. Federico
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * sumar : funcion que suma dos numeros pasados por parametros, devolviendo el resultado a un puntero float pasado por referencia.
 * operador1: primer operador
 * operador2: segundo operador
 * pResultado: puntero a float donde se escribe el resultado de la suma.
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int sumar(float operador1,float operador2,float* pResultado){
	int retorno = 1;
	float suma;
	if(pResultado != NULL){
		suma = operador1+operador2;
		*pResultado = suma;
		retorno = 0;
	}
	return retorno;
}

/*
 * restar : funcion que resta dos numeros pasados por parametros, devolviendo el resultado a un puntero float pasado por referencia.
 * operador1: primer operador
 * operador2: segundo operador
 * pResultado: puntero a float donde se escribe el resultado de la resta.
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int restar(float operador1,float operador2,float* pResultado){
	int retorno = 1;
	float resta;
	if(pResultado != NULL){
		resta = operador1-operador2;
		*pResultado = resta;
		retorno = 0;
	}
	return retorno;
}

/*
 * multiplicar : funcion que multiplica dos numeros pasados por parametros, devolviendo el resultado a un puntero float pasado por referencia.
 * operador1: primer operador
 * operador2: segundo operador
 * pResultado: puntero a float donde se escribe el resultado de la multiplicacion.
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int multiplicar(float operador1,float operador2,float* pResultado){
	int retorno = 1;
	float multiplicacion;
	if(pResultado != NULL){
		multiplicacion = operador1*operador2;
		*pResultado = multiplicacion;
		retorno = 0;
	}
	return retorno;
}

/*
 * dividir : funcion que divide dos numeros pasados por parametros, devolviendo el resultado a un puntero float pasado por referencia.
 * operador1: primer operador
 * operador2: segundo operador
 * pResultado: puntero a float donde se escribe el resultado de la division.
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int dividir(float operador1,float operador2,float* pResultado){
	int retorno = 1;
	float division;
	if(pResultado != NULL){
		division = operador1/operador2;
		*pResultado = division;
		retorno = 0;
	}
	return retorno;
}

/*
 * factorial: calcula el factorial de un numero, retornando el resultado.
 * numero: numero entero
 * Retorno: devuelve resp.
 *
 */
int factorial(int numero){
	int resp;
	if(numero == 1){
		return 1;
	}
	resp = numero*factorial(numero-1);
	return resp;
}


/*
 * menuCalculadora: menu principal de la calculadora.
 * ingreso1: flag del primer ingreso
 * ingreso2: flag del segundo ingreso
 * operador1: 1er operando
 * operador2: 2er operando
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
void menuCalculadora(int ingreso1,int ingreso2,float operador1,float operador2){
	if(!ingreso1 && !ingreso2){
		printf("\nMENU CALCULADORA:\n\n"
				"1.Ingresar 1er operando (A = ?)\n"
				"2.Ingresar 2do operando (B = ?)\n"
				"3.Calcular todas las operaciones\n"
				"4.Informar Resultados\n"
				"5.Salir\n");
	}else if(ingreso1 && !ingreso2){
		printf("\nMENU CALCULADORA:\n\n"
				"1.Ingresar 1er operando (A = %.2f)\n"
				"2.Ingresar 2do operando (B = ?)\n"
				"3.Calcular todas las operaciones\n"
				"4.Informar Resultados\n"
				"5.Salir\n",operador1);
	}else if(!ingreso1 && ingreso2){
		printf("\nMENU CALCULADORA:\n\n"
				"1.Ingresar 1er operando (A = ?)\n"
				"2.Ingresar 2do operando (B = %.2f)\n"
				"3.Calcular todas las operaciones\n"
				"4.Informar Resultados\n"
				"5.Salir\n",operador2);
	}else if(ingreso1 && ingreso2){
		printf("\nMENU CALCULADORA:\n\n"
				"1.Ingresar 1er operando (A = %.2f)\n"
				"2.Ingresar 2do operando (B = %.2f)\n"
				"3.Calcular todas las operaciones\n"
				"4.Informar Resultados\n"
				"5.Salir\n",operador1,operador2);
	}
}

/*
 * mostrarResultados: Muestra los resultados de las operaciones realizadas, teniendo en cuenta si se pudo dividir o factorizar los numeros.
 * operador1 : 1er operando
 * operador2 : 2do operando
 * suma: resultado de la suma
 * resta: resultado de la resta
 * multiplicacion : resultado de la multiplicacion
 * division: resultado de la division
 * factorial1: resultado del factorial del 1er numero
 * factorial2: resultado del factorial del 2do numero
 * flagDivision: flag de la division
 * flagFactorial1: flag del factorial del primer numero
 * flagFactorial2: flag del factorial del segundo numero
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
void mostrarResultados(float operador1,float operador2,float suma,float resta,float multiplicacion,float division,int factorial1,int factorial2,int flagDivision,int flagFactorial1,int flagFactorial2){
	printf("Suma:\n");
	printf(" %.2f + %.2f = %.2f\n",operador1,operador2,suma);
	printf("---------------------------------\n");
	printf("Resta:\n");
	printf(" %.2f - %.2f = %.2f\n",operador1,operador2,resta);
	printf("---------------------------------\n");
	printf("Multiplicacion:\n");
	printf(" %.2f * %.2f = %.2f\n",operador1,operador2,multiplicacion);
	printf("---------------------------------\n");
	printf("Division:\n");
	if(!flagDivision){
		printf(" %.2f / %.2f = %.2f\n",operador1,operador2,division);
	}else{
		printf("¡No se pudo realizar la division ya que el operador2 es 0!\n");
	}
	printf("---------------------------------\n");
	printf("Factorial del 1er numero:\n");
	if(flagFactorial1 == 0){
		printf(" %.0f! = %d\n",operador1,factorial1);
	}else if(flagFactorial1 == 1){
		printf("¡No se pudo hacer el factorial del numero porque no puede ser igual o menor a 0!\n");
	}else if(flagFactorial1 == 2){
		printf("¡Error, el numero es muy grande!\n");
	}
	printf("---------------------------------\n");
	printf("Factorial del 2do numero:\n");
	if(flagFactorial2 == 0){
		printf(" %.0f! = %d\n",operador2,factorial2);
	}else if(flagFactorial2 == 1){
		printf("¡No se pudo hacer el factorial del numero porque no puede ser igual o menor a 0!\n");
	}else if(flagFactorial2 == 2){
		printf("¡Error, el numero es muy grande!\n");
	}
	printf("---------------------------------\n");
}
//             \(owo)
