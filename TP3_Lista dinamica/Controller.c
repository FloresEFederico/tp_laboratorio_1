#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 1;

	FILE* pFile = fopen(path,"r");

	if(pFile != NULL && path != NULL)
	{
		if(!parser_EmployeeFromText(pFile,pArrayListEmployee))
		{
			retorno = 0;
		}
		fclose(pFile);
	}
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 1;

	FILE* pFile = fopen(path,"rb");

	if(pFile != NULL && path != NULL)
	{
		if(!parser_EmployeeFromBinary(pFile,pArrayListEmployee))
		{
			retorno = 0;
		}
		fclose(pFile);
	}
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int sizeLista = ll_len(pArrayListEmployee);
	if(pArrayListEmployee != NULL && sizeLista >= 0)
	{
		if(!employee_altaEmployee(pArrayListEmployee,sizeLista))
		{
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int sizeList = ll_len(pArrayListEmployee);
	if(pArrayListEmployee != NULL && sizeList >= 0)
		{
			if(!employee_modificarEmployee(pArrayListEmployee,sizeList))
			{
				retorno = 0;
			}
		}
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int sizeList = ll_len(pArrayListEmployee);
	if(pArrayListEmployee != NULL && sizeList >= 0)
	{
		if(!employee_bajaEmployee(pArrayListEmployee,sizeList))
		{
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int sizeList = ll_len(pArrayListEmployee);
	if(pArrayListEmployee != NULL && sizeList > 0 && !employee_imprimirArray(pArrayListEmployee,sizeList))
	{
		retorno = 0;
	}else
	{
		printf("\nNo se cargo ningun Empleado!\n");
	}
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int sizeList = ll_len(pArrayListEmployee);
	if(pArrayListEmployee != NULL && sizeList > 0)
	{
			if(!employee_ordenarEmployee(pArrayListEmployee,sizeList))
			{
				retorno = 0;
			}
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 1;
	FILE* pFile = fopen(path,"w");
	Employee* this;
	char auxId[2000];
	char auxNombre[2000];
	char auxHoras[2000];
	char auxSueldo[2000];
	if(pFile != NULL && path != NULL && pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		fprintf(pFile,"id,nombre,horasTrabajadas,sueldo\n");
		for(int i=0;i<ll_len(pArrayListEmployee);i++)
		{
			this = employee_new();
			if(this != NULL)
			{
				this = ll_get(pArrayListEmployee,i);
				if(!employee_getIdTxt(this,auxId) &&
					!employee_getNombre(this,auxNombre) &&
					!employee_getHorasTrabajadasTxt(this,auxHoras) &&
					!employee_getSueldoTxt(this,auxSueldo))
				{
					fprintf(pFile,"%s,%s,%s,%s\n",auxId,auxNombre,auxHoras,auxSueldo);
				}
			}
		}
		retorno = 0;
		fclose(pFile);
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* this;
	FILE* pFile = fopen(path,"wb");
	int sizeList = ll_len(pArrayListEmployee);
	int i;
	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		for(i=0;i<sizeList;i++)
		{
			this = ll_get(pArrayListEmployee,i);
			if(this != NULL)
			{
				fwrite(this,sizeof(Employee),1,pFile);
			}
		}
		retorno = 0;
		fclose(pFile);
	}else
	{
		printf("ERROR");
	}
    return retorno;
}

