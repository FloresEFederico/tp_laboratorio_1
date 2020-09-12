/*
 ============================================================================
 Name        : TP1_Calculadora.c
 Author      : Flores Federico 1-H 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style

 Enunciado: Hacer una calculadora. Para ello el programa iniciara
 y contara con un menu de opciones:
 1.Ingresar 1er operando.
 2.Ingresar 2do operando.
 3.Calcular todas las operaciones.
 4.Informar resultados.
 5.Salir.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "funcionesMatematicas.h"

#define MIN -32768
#define MAX 32767



int main(void) {
	setbuf(stdout,NULL);
	int opciones;
	int flagOperador1 = 0;
	int flagOperador2 = 0;
	int flagPrimerIngreso = 0;
	int flagSegundoIngreso = 0;
	int flagDivisionPorCero = 0;
	int flagFactorialDePrimerOperando = 0;
	int flagFactorialDeSegundoOperando = 0;
	int flagResultados = 0;
	int flagFailure = 0;
	float numero1;
	float numero2;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;
	float resultadoDivision;
	int resultadoFactorialDePrimerOperando;
	int resultadoFactorialDeSegundoOperando;

	do{
		menuCalculadora(flagPrimerIngreso,flagSegundoIngreso,numero1,numero2);
		if(!utn_getNumero(&opciones,"Elija una opcion(1-5):","\nOpcion invalida!Debe ser un numero de 1 a 5\n",1,5,4)){

			switch(opciones){
			case 1:
				printf("\nPRIMER OPERANDO:\n");
				if(!utn_getNumeroFloat(&numero1,"Ingrese un numero: ","\nNumero invalido!\n",MIN,MAX,3)){
					flagPrimerIngreso = 1;
					flagOperador1= 1;
					flagResultados=0;
				}else{
					printf("\nSe acabaron los intentos del ingreso del primer operando.\n");
					flagFailure = 1;
				}
				break;
			case 2:
				printf("\nSEGUNDO OPERANDO:\n");
				if(!utn_getNumeroFloat(&numero2,"Ingrese un numero: ","\nNumero invalido!\n",MIN,MAX,3)){
					flagSegundoIngreso = 1;
					flagOperador2= 1;
					flagResultados=0;
				}else{
					printf("\nSe acabaron los intentos del ingreso del segundo operando.\n");
					flagFailure = 1;
				}
				break;
			case 3:
				printf("\nCALCULO DE OPERACIONES!\n\n");
				if(flagOperador1 && flagOperador2){
					sumar(numero1,numero2,&resultadoSuma);
					restar(numero1,numero2,&resultadoResta);
					multiplicar(numero1,numero2,&resultadoMultiplicacion);
					if(numero2 != 0){
						dividir(numero1,numero2,&resultadoDivision);
						flagDivisionPorCero = 0;
					}else{
						flagDivisionPorCero = 1;
					}
					if(numero1 <= 0){
						flagFactorialDePrimerOperando = 1;
					}else if(numero1 > 16){
						flagFactorialDePrimerOperando = 2;
					}else{
						resultadoFactorialDePrimerOperando = factorial(numero1);
						flagFactorialDePrimerOperando = 0;
					}
					if(numero2 <= 0){
						flagFactorialDeSegundoOperando = 1;
					}else if(numero2 > 16){
						flagFactorialDeSegundoOperando = 2;
					}else{
						resultadoFactorialDeSegundoOperando = factorial(numero2);
						flagFactorialDeSegundoOperando = 0;
					}
					printf("\nSe ha podido calcular satisfactoriamente!\nPresiones enter para continuar...\n");
					flagResultados = 1;
				}else{
					printf("Primero hay que ingresar un valor tanto al 1er operando como al 2do operando!.\nPresione enter para continuar...\n");
				}
				getchar();
				break;
			case 4:
				printf("\n\nRESULTADOS!\n\n");
				if(flagResultados){
					mostrarResultados(numero1,numero2,resultadoSuma,resultadoResta,resultadoMultiplicacion,resultadoDivision,resultadoFactorialDePrimerOperando,resultadoFactorialDeSegundoOperando,flagDivisionPorCero,flagFactorialDePrimerOperando,flagFactorialDeSegundoOperando);
					printf("\nPresione enter para continuar...\n");
				}else{
					printf("Antes de mostrar los resultados, se debe calcular todas las operaciones!\nPresione enter para continuar...\n");
				}
				getchar();
				break;
			}
		}else{
			printf("\nSe acabo el numero de intentos para ingresar la opcion!\n");
			flagFailure = 1;
		}
		if(flagFailure){
			printf("\nHubo un error al cargar los datos!\nSaliendo del programa\n");
			break;
		}
	}while(opciones != 5);

	printf("\n\n¡Hasta luego!\n\n");
	return EXIT_SUCCESS;
}
