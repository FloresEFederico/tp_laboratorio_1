/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * 			TESTING DE FUNCIONES DE LINKEDLIST
 *
			startTesting(1);  // ll_newLinkedList
			startTesting(2);  // ll_len
			startTesting(3);  // getNode - test_getNode
			startTesting(4);  // addNode - test_addNode
			startTesting(5);  // ll_add
			startTesting(6);  // ll_get
			startTesting(7);  // ll_set
			startTesting(8);  // ll_remove
			startTesting(9);  // ll_clear
			startTesting(10); // ll_deleteLinkedList
			startTesting(11); // ll_indexOf
			startTesting(12); // ll_isEmpty
			startTesting(13); // ll_push
			startTesting(14); // ll_pop
			startTesting(15); // ll_contains
			startTesting(16); // ll_containsAll
			startTesting(17); // ll_subList
			startTesting(18); // ll_clone
			startTesting(19); // ll_sort
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/main_test.h"
#include "../inc/LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"


int main(void)
{
	setbuf(stdout,NULL);
	LinkedList* listaEmpleados = ll_newLinkedList();
    int flagDatosCargados = 0;
    int option;
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
						printf("------------------------------------------------------------------\n");
					}else if(!flagDatosCargados)
					{
						printf("\nDeben cargarse los datos con anterioridad!\n");
					}
					break;
				case 4:
					if(flagDatosCargados && !controller_editEmployee(listaEmpleados))
					{
						printf("------------------------------------------------------------------\n");
					}else if(!flagDatosCargados)
					{
						printf("\nDeben cargarse los datos con anterioridad!\n");
					}
					break;
				case 5:
					if(flagDatosCargados && !controller_removeEmployee(listaEmpleados))
					{
						printf("------------------------------------------------------------------\n");
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
						printf("------------------------------------------------------------------\n");
					}else if(!flagDatosCargados)
					{
						printf("\nDeben cargarse los datos con anterioridad!\n");
					}
					break;
				case 8:
					if(!controller_saveAsText("data.csv",listaEmpleados))
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
					}
			}
    	}
    }while(option != 10);
    employee_deleteAllArray(listaEmpleados,ll_len(listaEmpleados));
    ll_deleteLinkedList(listaEmpleados);
    printf("\nHasta luego!\n");
	return 0;
}


