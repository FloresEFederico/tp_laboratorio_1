/*
 * funcionesMatematicas.h
 *
 *  Created on: 11 sep. 2020
 *      Author: Flores E. Federico
 */

#ifndef FUNCIONESMATEMATICAS_H_
#define FUNCIONESMATEMATICAS_H_

//---------------OPERACIONES MATEMATICAS------------------------------
int sumar(float operador1,float operador2,float* pResultado);
int restar(float operador1,float operador2,float* pResultado);
int multiplicar(float operador1,float operador2,float* pResultado);
int dividir(float operador1,float operador2,float* pResultado);
int factorial(int numero);

//---------------MENU DE OPCIONES Y DE RESULTADO------------------------------
void mostrarResultados(float operador1,float operador2,float suma,float resta,float multiplicacion,float division,int factorial1,int factorial2,int flagDivision,int flagFactorial1,int flagFactorial2);
void menuCalculadora(int ingreso1,int ingreso2,float operador1,float operador2);
#endif /* FUNCIONESMATEMATICAS_H_ */
