/*
 * employees.h
 *
 *  Created on: 27 sep. 2020
 *      Author: Flores E. Federico
 */

#ifndef EMPLOYEES_H_
#define EMPLOYEES_H_
#define LONG_NAME 51
#define QTY_EMPLOYEES 1000
#define MAX_SALARY 99999
#define MIN_SALARY 10000
#define TRUE 1
#define FALSE 0

typedef struct
{
	int id;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	float salary;
	int sector;
	int isEmpty;
}Employee;

int initEmployees(Employee* list,int len);
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector,int index);
int findFreeEmployee(Employee* list, int len);
int findEmployeeById(Employee* list, int len,int id);
int removeEmployee(Employee* list, int len, int id);
int printEmployees(Employee* list, int length);
int printOneEmployee(Employee OneEmployee, int length);
int sortEmployeesByLastNameAndSector(Employee* list, int len, int order);
int totalAndAverageSalary(Employee* list, int len);
int subMenuInformeEmployee(Employee* pArray,int len,int option);
//----------------------------------------------------
int employee_alta(Employee* list,int len);
int employee_modificar(Employee* list,int len);
int employee_baja(Employee* list,int len);
#endif /* EMPLOYEES_H_ */
