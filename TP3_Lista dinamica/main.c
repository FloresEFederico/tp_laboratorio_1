#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"
/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

/*
 * PREGUNTAR POR LA DATA CSV EN BINARIO
 */

int main()
{
	setbuf(stdout,NULL);
    int option = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    int flagDatosCargados = 0;

    do{
    	if(!utn_getNumero(&option,"\n--MENU PRINCIPAL--\n"
    			"1-Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
    			"2-Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n"
    			"3-Alta de Empleado\n"
    			"4-Modificar datos de Empleado.\n"
    			"5-Baja de Empleado.\n"
    			"6-Listar Empleados.\n"
    			"7-Ordenar Empleados.\n"
    			"8-Guardar los datos de los empleados desde el archivo data.csv (modo texto).\n"
    			"9-Guardar los datos de los empleados desde el archivo data.bin (modo binario).\n"
    			"10-Salir.\nElija una opcion(1-10): ","\nOpcion Invalida!\n",1,10,3))
    	{
			switch(option)
			{
				case 1:
					if(!flagDatosCargados && !controller_loadFromText("data.csv",listaEmpleados))
					{
						printf("\nSe cargo los datos exitosamente!\n");
						flagDatosCargados = 1;
					}else if(flagDatosCargados)
					{
						printf("\nYa se han cargado los datos!\n");
					}
					break;
				case 2:
					if(!flagDatosCargados && !controller_loadFromBinary("data.bin",listaEmpleados))
					{
						printf("\nSe cargo los datos exitosamente!\n");
						flagDatosCargados = 1;
					}else if(flagDatosCargados)
					{
						printf("\nYa se han cargado los datos!\n");
					}
					break;
				case 3:
					if(flagDatosCargados && !controller_addEmployee(listaEmpleados))
					{
						printf("\nSe ha realizado el alta exitosamente!\n");
					}else if(!flagDatosCargados)
					{
						printf("\nDeben cargarse los datos con anterioridad!\n");
					}
					break;
				case 4:
					if(flagDatosCargados && !controller_editEmployee(listaEmpleados))
					{
						printf("\nSe modificaron los datos del empleado exitosamente!\n");
					}else if(!flagDatosCargados)
					{
						printf("\nDeben cargarse los datos con anterioridad!\n");
					}
					break;
				case 5:
					if(flagDatosCargados && !controller_removeEmployee(listaEmpleados))
					{
						printf("\nSe ha realizado la baja exitosamente!\n");
					}else if(!flagDatosCargados)
					{
						printf("\nDeben cargarse los datos con anterioridad!\n");
					}
					break;
				case 6:
					if(!controller_ListEmployee(listaEmpleados))
					{
						printf("------------------------------------------------------------------\n");
					}
					break;
				case 7:
					if(flagDatosCargados && !controller_sortEmployee(listaEmpleados))
					{
						printf("\nSe ordeno a los empleados exitosamente!\n");
					}else if(!flagDatosCargados)
					{
						printf("\nDeben cargarse los datos con anterioridad!\n");
					}
					break;
				case 8:
					if(flagDatosCargados && !controller_saveAsText("data.csv",listaEmpleados))
					{
						printf("\nSe guardaron los datos exitosamente!\n");
					}else if(!flagDatosCargados)
					{
						printf("\nNo hay datos que guardar ya que no se cargo ningun dato!\n");
					}
					break;
				case 9:
					if(flagDatosCargados && !controller_saveAsBinary("data.bin",listaEmpleados))
					{
						printf("\nSe guardaron los datos exitosamente!\n");
					}else if(!flagDatosCargados)
					{
						printf("\nNo hay datos que guardar ya que no se cargo ningun dato!\n");
						printf("Para acceder a los campos debera cargar primero los datos.\n");
					}
			}
    	}
    }while(option != 10);
    employee_deleteAllArray(listaEmpleados,ll_len(listaEmpleados));
    ll_deleteLinkedList(listaEmpleados);
    printf("\nHasta luego!\n");
    return 0;
}

