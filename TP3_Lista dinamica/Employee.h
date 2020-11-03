#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#define NOMBRE_LEN 128
#define ID_LEN 100
#define HORAS_LEN 100
#define SUELDO_LEN 100
#define MIN_HORAS 1
#define MAX_HORAS 300
#define MIN_SUELDO 10000
#define MAX_SUELDO 60000
typedef struct
{
    int id;
    char nombre[NOMBRE_LEN];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);
void employee_delete(Employee* this);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);


int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

//---------------------------------FUNCIONES AGREGADAS----------------------------------------------------

int employee_altaEmployee(LinkedList* pArrayListEmployee,int len);
int employee_modificarEmployee(LinkedList* pArrayListEmployee,int len);
int employee_bajaEmployee(LinkedList* pArrayListEmployee,int len);
int employee_imprimirArray(LinkedList* pArrayListEmployee,int len);
void employee_imprimirEmployee(Employee* this);
int employee_setIdTxt(Employee* this,char* id);
int employee_setSueldoTxt(Employee* this,char* sueldo);
int employee_setHorasTrabajadasTxt(Employee* this,char* horasTrabajadas);
int employee_getIdTxt(Employee* this,char* id);
int employee_getSueldoTxt(Employee* this,char* sueldo);
int employee_getHorasTrabajadasTxt(Employee* this,char* horasTrabajadas);
int employee_buscarPorIdArray(LinkedList* pArrayListEmployee,int len,int idABuscar);
int employee_deleteAllArray(LinkedList* pArrayListEmployee,int len);
int employee_ordenarEmployee(LinkedList* pArrayListEmployee,int len);


#endif // employee_H_INCLUDED
