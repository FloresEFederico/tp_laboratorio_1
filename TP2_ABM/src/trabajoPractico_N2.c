#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "employees.h"


int main(void) {
	setbuf(stdout,NULL);
	Employee listOfEmployees[QTY_EMPLOYEES];
	int option;
	int subOptionInforme;
	initEmployees(listOfEmployees,QTY_EMPLOYEES);
	do
	{
		printf("\n--MENU DE EMPLEADOS(ABM)--\n"
				"----------------------------\n"
				"1-Alta de Empleado.\n"
				"2-Modificar Empleado.\n"
				"3-Baja empleado.\n"
				"4-Informar empleado\n"
				"5-Salir.\n"
				"----------------------------");
		if(!utn_getNumero(&option,"\nElija una opcion(1-5): ","\nOpcion invalida!\n",1,5,3))
		{
			switch(option)
			{
			case 1:
				printf("\nMenu Alta\n----------\n");
				if(!employee_alta(listOfEmployees,QTY_EMPLOYEES))
				{
					printf("\nSe ha dado de alta al empleado exitosamente!\n");
				}else
				{
					printf("\nNo se pudo realizar el alta!\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			case 2:
				printf("\nMenu Modificacion\n------------------\n");
				if(!employee_modificar(listOfEmployees,QTY_EMPLOYEES))
				{
					printf("\nSe ha modificado al empleado exitosamente!\n");
				}else
				{
					printf("\nNo se modifico al empleado!\n");

				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			case 3:
				printf("\nMenu Baja\n----------\n");
				if(!employee_baja(listOfEmployees,QTY_EMPLOYEES))
				{
					printf("\nSe ha dado de baja al empleado exitosamente!\n");
				}else
				{
					printf("\nNo se ha dado de baja ningun empleado!\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			case 4:
				printf("\nMenu Informar\n--------------\n");
				if(!utn_getNumero(&subOptionInforme,"1-Mostrar Empleados ordenados por apellido/sector.\n2-Mostrar el total y promedio de los salarios.\nElija opcion(1-2): ","\nOpcion invalida!\n",1,2,3) &&
				   !subMenuInformeEmployee(listOfEmployees,QTY_EMPLOYEES,subOptionInforme))
				{
					printf("\n------------------------------------\n");
				}
				else
				{
					printf("\nHubo un error al imprimir los empleados!\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			}
		}else{
			printf("\nSe acabo el numero de intentos para ingresar la opcion valida. Saliendo del programa.\n");
			break;
		}
	}while(option != 5);
	printf("\nHasta luego!\n");
	return EXIT_SUCCESS;
}


