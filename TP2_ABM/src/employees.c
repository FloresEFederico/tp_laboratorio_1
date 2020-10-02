#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "employees.h"

static int showEmployeesWithBiggerSalary(Employee* list, int len, float averageSalary);//utilizada en la funcion totalAndAverageSalary

static int generateIdNewEmployee(void);

/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initEmployees(Employee* list,int len)
{
	int retorno = -1;
	int i;
	if(list != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			list[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/** \brief add in a existing list of employees the values received as parameters
* in the first empty position
* \param list employee*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param salary float
* \param sector int
* \param index int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*
*/
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector,int index)
{
	int retorno= -1;
	Employee auxEmployee;
	if(list != NULL && len > 0 && name != NULL && lastName != NULL  && list[index].isEmpty == TRUE)
	{

		auxEmployee.id = id;
		strncpy(auxEmployee.name,name,LONG_NAME-1);
		strncpy(auxEmployee.lastName,lastName,LONG_NAME-1);
		auxEmployee.salary = salary;
		auxEmployee.sector = sector;
		auxEmployee.isEmpty = FALSE;
		list[index] = auxEmployee;
		retorno = 0;

	}
	return retorno;
}

/** \brief find an Employee by Id en returns the index position in array.
*
* \param list Employee*
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*
*/
int findFreeEmployee(Employee* list, int len)
{
	int indexFound = -1;
	int i;
	if(list != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				indexFound = i;
				break;
			}
		}
	}
	return indexFound;
}

/** \brief find an Employee by Id en returns the index position in array.
*
* \param list Employee*
* \param len int
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*
*/
int findEmployeeById(Employee* list, int len,int id)
{
	int indexFound = -1;
	int i;
	if(list != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].id == id)
			{
				indexFound = i;
				break;
			}
		}
	}
	return indexFound;
}


/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
*
* \param list Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
*/
int removeEmployee(Employee* list, int len, int id)
{
	int retorno = -1;
	int indexFound = findEmployeeById(list,len,id);
	if(list != NULL && len > 0 && indexFound != -1)
	{
		list[indexFound].isEmpty = TRUE;
		retorno = 0;
	}
	return retorno;
}

/** \brief Sort the elements in the array of employees by lastName & sector, the argument order
indicate UP or DOWN order
*
* \param list Employee*
* \param len int
* \param order int [1] indicate DOWN - [0] indicate UP
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int sortEmployeesByLastNameAndSector(Employee* list, int len, int order)
{
	int retorno = -1;
	int i;
	int stateOfOrder = 1;
	Employee auxEmployee;
	if(list != NULL && len > 0 && (order == 1 || order == 0))
	{
		do
		{
			stateOfOrder = 0;
			for(i=0;i<(len-1);i++)
			{
				if((order == 1 && strncmp(list[i].lastName,list[i+1].lastName,LONG_NAME) < 0) ||
				   (order == 0 && strncmp(list[i].lastName,list[i+1].lastName,LONG_NAME) > 0) ||
				   (order == 1 && strncmp(list[i].lastName,list[i+1].lastName,LONG_NAME) == 0 && list[i].sector < list[i+1].sector) ||
				   (order == 0 && strncmp(list[i].lastName,list[i+1].lastName,LONG_NAME) == 0 && list[i].sector > list[i+1].sector))
				{
					auxEmployee = list[i];
					list[i] = list[i+1];
					list[i+1] = auxEmployee;
					stateOfOrder = 1;
				}
			}
		}while(stateOfOrder);
		retorno = 0;
	}
	return retorno;
}

/** \brief Shows the total and Average Salary of all employees with the camp of isEmpty in FALSE.Also, it shows which employee surpasses the average salary.
* \param list Employee*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int totalAndAverageSalary(Employee* list, int len)
{
	int retorno = -1;
	int i;
	float totalSalary = 0;
	float averageSalaryOfEmployees;
	int quantityOfEmployees = 0;
	int flagSalary = 0;
	if(list != NULL && len > 0)
	{
		printf("\n--Total y Promedio de los salarios--\n");
		printf("\n------------------------------------\n");
		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				totalSalary+=list[i].salary;
				quantityOfEmployees++;
				flagSalary = 1;
			}
		}
		if(flagSalary)
		{
			averageSalaryOfEmployees = totalSalary/quantityOfEmployees;
			printf("Total de salarios: %.2f\n"
					"Promedio de salarios: %.2f\n",totalSalary,averageSalaryOfEmployees);
			showEmployeesWithBiggerSalary(list,len,averageSalaryOfEmployees);
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief shows which employee surpasses the average salary.
* \param list Employee*
* \param len int
* \param averageSalary int
* \return int Return (-1) if Error [Invalid length , NULL pointer or Invalid salary] - (0) if Ok
*
*/
static int showEmployeesWithBiggerSalary(Employee* list, int len, float averageSalary)
{
	int retorno = -1;
	int i;
	if(list != NULL && len > 0 && averageSalary > 0)
	{
		printf("\nEmpleados que superan el salario promedio: \n");
		printf("\n   ID 		APELLIDO	NOMBRE		SALARIO		SECTOR\n");
		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].salary > averageSalary)
			{
				printOneEmployee(list[i],len);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/** \brief print the content of employees array
*
* \param list Employee*
* \param length int
* \return int retorno: OK(0)/else(-1)
*
*/
int printEmployees(Employee* list, int length)
{
	int retorno = -1;
	int i;
	int flagFailure = 1;
	if(list != NULL && length > 0)
	{
		printf("\n   ID 		APELLIDO	NOMBRE		SALARIO		SECTOR\n");
		for(i=0;i<length;i++)
		{
			if(list[i].isEmpty == FALSE){
				printOneEmployee(list[i],length);
				flagFailure = 0;
				retorno = 0;
			}
		}
		if(flagFailure)
		{
			printf("\nNo hay empleados que mostrar ya que no hay ninguno dado de alta!\n");
		}
	}
	return retorno;
}

/** \brief print the content of an Employee
*
* \param oneEmployee Employee
* \param length int
* \return int retorno: OK(0)/else(-1)
*
*/
int printOneEmployee(Employee OneEmployee, int length)
{
	int retorno = -1;
	if(length > 0)
	{
		printf("  %4d          %-11s     %-11s     %-5.2f          %d\n",OneEmployee.id,OneEmployee.lastName,OneEmployee.name,OneEmployee.salary,OneEmployee.sector);
		retorno = 0;
	}
	return retorno;
}


//----------------------------------------------------------------------------------------
/**
 * \brief Realiza el alta de un Employee, pidiendole valores y luego utilizando la funcion addEmployee para guardarlos en el array de Employee
 * \param Employee* list: es el puntero al array de Employee
 * \param int len: es el limite del array
 * \return (-1) ERROR/ (0) Ok
 */
int employee_alta(Employee* list,int len)
{
	int retorno = -1;
	int freeIndex;
	int auxId;
	char auxName[LONG_NAME];
	char auxLastName[LONG_NAME];
	float auxSalary;
	int auxSector;

	if(list != NULL &&  len > 0)
	{
		freeIndex = findFreeEmployee(list,len);
		if(freeIndex != -1)
		{
			auxId = generateIdNewEmployee();
			if(!utn_getNombre(auxName,LONG_NAME,"\nIngrese Nombre: ","\nNombre invalido!\n",3) &&
			   !utn_getNombre(auxLastName,LONG_NAME,"\nIngrese Apellido: ","\nNombre Apellido!\n",3) &&
			   !utn_getNumeroFloat(&auxSalary,"\nIngrese salario(10000-99999): ","\nSalario invalido!\n",MIN_SALARY,MAX_SALARY,3) &&
			   !utn_getNumero(&auxSector,"\nIngrese sector(1-4): ","\nSector Invalido!\n",1,4,3) &&
			   !addEmployee(list,len,auxId,auxName,auxLastName,auxSalary,auxSector,freeIndex))
			{

				retorno = 0;
			}
		}else
		{
			printf("\nNo hay espacios libres!\n");
		}
	}
	return retorno;
}

/**
 * \brief modifica a un  alumno solo si el indice corresponde a un No Empty y existe el id,dandole la opcion de modificar el Nombre o el Apellido o el salario o el sector.
 * \param Employee* list: es el puntero al array de Employee
 * \param int len: es el limite del array
 * \return (-1) ERROR/ (0) Ok
 */
int employee_modificar(Employee* list,int len)
{
	int retorno = -1;
	int modOption;
	int findId;
	int findIndex;
	char auxName[LONG_NAME];
	char auxLastName[LONG_NAME];
	float auxSalary;
	int auxSector;
	int flagSuccess = 0;
	if(list != NULL && len > 0)
	{
		printf("\nListado:\n");
		printf("\n--------");
		if(printEmployees(list,len) != -1 && !utn_getNumero(&findId,"\nIngrese el id del Empleado que desea modificar: ","\nId invalido!\n",1000,2000,3))
		{
			findIndex = findEmployeeById(list,len,findId);
			if(findIndex != -1 && !utn_getNumero(&modOption,"\n----------------------\n"
					"¿Que desea modificar?\n"
					"1-Nombre.\n"
					"2-Apellido\n"
					"3-Salario.\n"
					"4-Sector.\n"
					"Elija la opcion(1-4): ","\nOpcion invalida!\n",1,4,3)
			)
			{
				switch(modOption)
				{
				case 1:
					if(!utn_getNombre(auxName,LONG_NAME,"\nIngrese el nuevo nombre: ","\nNombre invalido!\n",3))
					{
						strncpy(list[findIndex].name,auxName,LONG_NAME);
						flagSuccess = 1;
					}else
					{
						printf("\nSe acabaron los reintentos. No se modifico el nombre.\n");
					}
					break;
				case 2:
					if(!utn_getNombre(auxLastName,LONG_NAME,"\nIngrese el nuevo apellido: ","\nApellido invalido!\n",3))
					{
						strncpy(list[findIndex].lastName,auxLastName,LONG_NAME);
						flagSuccess = 1;
					}else
					{
						printf("\nSe acabaron los reintentos. No se modifico el apellido.\n");
					}
					break;
				case 3:
					if(!utn_getNumeroFloat(&auxSalary,"\nIngrese nuevo salario(10000-99999): ","\nSalario invalido!\n",MIN_SALARY,MAX_SALARY,3))
					{
						list[findIndex].salary = auxSalary;
						flagSuccess = 1;
					}else
					{
						printf("\nSe acabaron los reintentos. No se modifico el salario.\n");
					}
					break;
				case 4:
					if(!utn_getNumero(&auxSector,"\nIngrese nuevo sector(1-4): ","\nSector invalido!\n",1,4,3))
					{
						list[findIndex].sector = auxSector;
						flagSuccess = 1;
					}else
					{
						printf("\nSe acabaron los reintentos. No se modifico el sector.\n");
					}
					break;
				}
				if(!flagSuccess)
				{
					printf("\nHubo un error al ingreso de datos.\n");
				}else
				{
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief da de baja a un Employee si el id corresponde a un no Empty.
 * \param Employee* list: es el puntero al array de Employee
 * \param int len: es el limite del array
 * \return (-1) ERROR/ (0) Ok
 */
int employee_baja(Employee* list,int len)
{
	int retorno = -1;
	int findId;
	int findIndex;
	if(list != NULL && len > 0)
	{
		printf("\nListado:\n");
		printf("\n--------");
		if(printEmployees(list,len) != -1 && !utn_getNumero(&findId,"\nIngrese el id del Empleado que desea dar de baja: ","\nId invalido!\n",1000,2000,3))
		{
			findIndex = findEmployeeById(list,len,findId);
			if(findIndex != -1)
			{
				list[findIndex].isEmpty = TRUE;
				retorno = 0;
			}else
			{
				printf("\nNo se encontro un empleado con ese id!\n");
			}
		}else
		{
			printf("\nSe acabo el numero de reintentos para ingresar bien el id!\n");
		}
	}
	return retorno;
}

/**
 * \brief Sub menu del menu Informar.
 * \param Employee* list: es el puntero al array de Employee
 * \param int len: es el limite del array
 * \param int option: es la opcion que el usuario elige.
 * \return (-1) ERROR/ (0) Ok
 */
int subMenuInformeEmployee(Employee* pArray,int len,int option)
{
	int retorno = -1;
	int stateOfOrder;
	if(pArray != NULL && len > 0 && (option >= 1 || option <= 2))
	{
		switch(option)
		{
			case 1:
				if(!utn_getNumero(&stateOfOrder,"¿De que manera desea ordenar?\n0-Ascendente.\n1-Descendente\nElija opcion(0-1): ","\nOpcion invalida!\n",0,1,3) &&
					!sortEmployeesByLastNameAndSector(pArray,len,stateOfOrder))
				{
					printEmployees(pArray,len);
				}else
				{
					printf("\nHubo un error al listar los empleados\n");
				}
				break;
			case 2:
				if(!totalAndAverageSalary(pArray,len))
				{
				}else
				{
					printf("\nAun no se dio de alta a ningun empleado\n");
				}
				break;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief gives value to the id of one employee & increases the id in 1
 * \return idAlumno increased in 1
 */
static int generateIdNewEmployee(void)
{
	static int idEmployee=999;
	idEmployee++;
	return idEmployee;
}
// \(ouo)/
