#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* this;
	char auxId[2000];
	char auxNombre[2000];
	char auxHoras[2000];
	char auxSueldo[2000];
	if(pFile != NULL && pArrayListEmployee)
	{
		retorno = 0;
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHoras,auxSueldo);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHoras,auxSueldo) == 4)
			{
				this = employee_new();

				if(this != NULL &&
				   !employee_setIdTxt(this,auxId) &&
				   !employee_setNombre(this,auxNombre) &&
				   !employee_setHorasTrabajadasTxt(this,auxHoras) &&
				   !employee_setSueldoTxt(this,auxSueldo))
				{

					ll_add(pArrayListEmployee,this);
				}
			}

		}while(!feof(pFile));
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* this;
	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			this = employee_new();
			if(this != NULL)
			{
				if(fread(this,sizeof(Employee),1,pFile))
				{
					ll_add(pArrayListEmployee,this);
				}else
				{
					employee_delete(this);
				}
			}
		}while(!feof(pFile));
		retorno = 0;
	}
    return retorno;
}
