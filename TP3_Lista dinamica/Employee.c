#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include <string.h>
#include "utn.h"
#include "ctype.h"

static int isValidId(int id);
static int esNumerica(char* cadena,int limite);
static int isValidNombre(char* pResultado,int limite);
static int toNombre(char text[],int len);
static int employee_generadorDeId(LinkedList* pArrayListEmployee,int len);

static int employee_ordenarNombres(void* this,void* thanThis);
static int employee_ordenarIds(void* this,void* thanThis);
static int employee_ordenarHorasTrabajadas(void* this,void* thanThis);
static int employee_ordenarSueldos(void* this,void* thanThis);


/**
 * \brief genera espacio para un empleado
 * \return espacio en memoria si todoOK, de lo contrario devuelve NULL.
 */
Employee* employee_new()
{
	return (Employee*)malloc(sizeof(Employee));
}

/**
 * \brief agrega a un empleado los valores en modo texto pasados por parametros.
 * \param char* idStr: id en modo texto
 * \param char* nombreStr: nombre
 * \param char* horasTrabajadasStr: horas trabajadas en modo texto
 * \param char* sueldoStr: sueldo en modo texto.
 * \return el puntero a Empleado si salio el seteo de datos estuvo bien, sino devuelve un NULL
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
	Employee* this = employee_new();
	int auxId;
	int auxHoras;
	int auxSueldo;
	if(this != NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		auxId = atoi(idStr);
		auxHoras = atoi(horasTrabajadasStr);
		auxSueldo = atoi(sueldoStr);
		if(!employee_setId(this,auxId) &&
		   !employee_setNombre(this,nombreStr) &&
		   !employee_setHorasTrabajadas(this,auxHoras) &&
		   !employee_setSueldo(this,auxSueldo))
		{
			return this;
		}
	}
	return NULL;
}
/**
 * \brief libera la memoria de un puntero a Empleado
 * \param Employee* this: puntero de Employee
 */
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

/**
 * \brief carga a un empleado el id pasado por parametro validando si el id es correcto.
 * \param Employee* this: puntero de Employee
 * \param int id: Id entero
 * \return (-1) ERROR/ (0) Ok
 */
int employee_setId(Employee* this,int id)
{
	int retorno = -1;
	static int maximoId = -1;
	if (this != NULL && isValidId(id))
	{
		retorno = 0;
		if (id < 0)
		{
			maximoId++;
			this->id = maximoId;
		}
		else
		{
			if (id > maximoId)
			{
				maximoId = id;
				this->id = id;
			}
		}
	}
	return retorno;
}
/**
 * \brief obtiene el Id de un empleado.
 * \param Employee* this: puntero de Employee
 * \param int* id: puntero Id
 * \return (-1) ERROR/ (0) Ok
 */
int employee_getId(Employee* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		*id = this->id;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief setea un nombre al campo de nombre de un empleado validando si el valor pasado por parametro es correcto.
 * \param Employee* this: puntero de Employee
 * \param char* nombre: nombre tipo char*
 * \return (-1) ERROR/ (0) Ok
 */
int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(isValidNombre(nombre,NOMBRE_LEN) && toNombre(nombre,NOMBRE_LEN))
		{
			strncpy(this->nombre,nombre,NOMBRE_LEN);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief obtiene el nombre de un empleado.
 * \param Employee* this: puntero de Employee
 * \param char* nombre: nombre tipo char*
 * \return (-1) ERROR/ (0) Ok
 */
int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		strncpy(nombre,this->nombre,NOMBRE_LEN);
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief setea en el campo horasTrabajadas del Empleado pasado por parametro, el valor de horasTrabajadas tambien pasado por parametro
 * \param Employee* this: puntero de Employee
 * \param int horasTrabajadas: horasTrabajadas del tipo entero
 * \return (-1) ERROR/ (0) Ok
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	char bufferHoras[400];
	sprintf(bufferHoras,"%d",horasTrabajadas);
	if(this != NULL && esNumerica(bufferHoras,sizeof(bufferHoras)))
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief obtiene las horas trabajadas de un empleado.
 * \param Employee* this: puntero de Employee
 * \param int* horasTrabajadas: puntero HorasTrabajadas
 * \return (-1) ERROR/ (0) Ok
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief setea en el campo sueldo del Empleado pasado por parametro, el valor de sueldo tambien pasado por parametro
 * \param Employee* this: puntero de Employee
 * \param int sueldo: sueldo del tipo entero
 * \return (-1) ERROR/ (0) Ok
 */
int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	char bufferSueldo[400];
	sprintf(bufferSueldo,"%d",sueldo);
	if(this != NULL && esNumerica(bufferSueldo,sizeof(bufferSueldo)))
	{
		this->sueldo = sueldo;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief obtiene el sueldo de un empleado.
 * \param Employee* this: puntero de Employee
 * \param int* sueldo: puntero sueldo
 * \return (-1) ERROR/ (0) Ok
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		*sueldo = this->sueldo;
		retorno = 0;
	}
	return retorno;
}

/*
 * isValidId: Recibe un id y valida si el id es valido
 * int id: id a ser validado
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int isValidId(int id)
{
	int respuesta = 0;
	char bufferId[400];
	sprintf(bufferId,"%d",id);
	if(id >= 0 && esNumerica(bufferId,sizeof(bufferId)))
	{
		respuesta = 1;
	}
	return respuesta;
}

/**
* esNumerica: Verifica si la cadena ingresada es numerica
* cadena: cadena de caracteres a ser analizada
* limite: limite de la cadena
* Retorno: 1 (verdadero) si la cadena es numerica , 0 (falso) si no y -1 en caso de ERROR de parametro
*
*/
static int esNumerica(char* cadena,int limite)
{
	int retorno = 1;
	int i = 0;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		if(cadena[0] == '+')
		{
			i = 1;
		}
		for(;cadena[i] != '\0';i++)
		{
			if(cadena[i] < '0' || cadena[i] > '9' )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*
 * isValidNombre: Recibe una cadena de caracteres y su limite, y pregunta si el nombre es valido
 * pResultado: cadena de caracteres
 * limite: tamaño del texto
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int isValidNombre(char* pResultado,int limite)
{
	int respuesta = 1;
	int i;
	if(pResultado != NULL && limite > 0){
		for(i=0; i <= limite && pResultado[i] != '\0';i++){
			if((pResultado[i] < 'a' || pResultado[i] > 'z') &&
			   (pResultado[i] < 'A' || pResultado[i] > 'Z') &&
			   pResultado[i] != ' ' &&
			   pResultado[i] != '-')
			{
				respuesta = 0;
				break;
			}
		}
	}
	return respuesta;
}

/*
 * toNombre: Recibe una cadena de caracteres, convirtiendo la primera letra en mayuscula y las demas en minuscula
 * pResultado: cadena de caracteres
 * limite: tamaño del texto
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int toNombre(char text[],int len)
{
	int retorno = 0;
	int i;
	if(text != NULL && len > 0)
	{
		for(i=0;i<len && text[i] != '\0';i++)
		{
			if(i!=0)
			{
				text[i] = tolower(text[i]);
			}else
			{
				text[i] = toupper(text[i]);
			}
		}
		retorno = 1;
	}
	return retorno;
}


//---------------------------------FUNCIONES AGREGADAS----------------------------------------------------


/**
 * \brief Realiza el alta de un Employee, pidiendole valores y luego utilizando la funcion employee_newParametros para guardarlos en una lista dinamica
 * \param LinkedList* pArrayListEmployee: puntero de LinkedList
 * \param int len: es el limite del array
 * \return (-1) ERROR/ (0) Ok
 */
int employee_altaEmployee(LinkedList* pArrayListEmployee,int len)
{
	int retorno = -1;
	Employee* this;
	int auxId;
	char auxIdTxt[ID_LEN];
	char auxNombre[NOMBRE_LEN];
	char auxHoras[HORAS_LEN];
	char auxSueldo[SUELDO_LEN];
	if(pArrayListEmployee != NULL && len >= 0)
	{
		auxId = len;
		if(!utn_getNombre(auxNombre,NOMBRE_LEN,"Ingrese nombre: ","\nNombre Invalido!\n",3) &&
		   !utn_getNumeroTxt(auxHoras,HORAS_LEN,"\ningrese horas trabajadas(1/300): ","\nNumero Invalido!\n",MIN_HORAS,MAX_HORAS,3) &&
		   !utn_getNumeroTxt(auxSueldo,SUELDO_LEN,"\ningrese Sueldo(10000/60000): ","\nSueldo Invalido!\n",MIN_SUELDO,MAX_SUELDO,3))
		{
			auxId = employee_generadorDeId(pArrayListEmployee,len);
			sprintf(auxIdTxt,"%d",auxId);
			this = employee_newParametros(auxIdTxt,auxNombre,auxHoras,auxSueldo);
			if(this != NULL)
			{
				ll_add(pArrayListEmployee,this);
				this = NULL;
				retorno = 0;
			}else
			{
				printf("\nHubo un error en el pAuxAlumno\n");
			}
		}
	}
	return retorno;
}

/**
 * \brief Modifica los datos de un Employee, pidiendo un id, preguntando que campo quiere modificar y luego pide un valor nuevo para modificarlo
 * \param LinkedList* pArrayListEmployee: puntero de LinkedList
 * \param int len: es el limite del array
 * \return (-1) ERROR/ (0) Ok
 */
int employee_modificarEmployee(LinkedList* pArrayListEmployee,int len)
{
	int retorno = -1;
	int auxId;
	int indiceAModificar;
	Employee* this;
	int opcionModificar;
	int flagModificar = 0;
	char auxNombre[NOMBRE_LEN];
	int auxHoras;
	int auxSueldo;
	if(pArrayListEmployee != NULL && len > 0 && !utn_getNumero(&auxId,"\nIngrese el ID de un Empleado: ","\nNumero Invalido!\n",1,10000,3))
	{
		indiceAModificar = employee_buscarPorIdArray(pArrayListEmployee,len,auxId);
		if(indiceAModificar != -1)
		{
			this = (Employee*)ll_get(pArrayListEmployee,indiceAModificar);
			employee_imprimirEmployee(this);
			if(!utn_getNumero(&opcionModificar,"\n1-Nombre.\n2-Cantidad de horas trabajadas.\n3-Sueldo.\n4-Salir\n¿Que desea modificar?(1-4): ","\nOpcion invalida!\n",1,4,3))
			{
				switch(opcionModificar)
				{
				case 1:
					if(!utn_getNombre(auxNombre,NOMBRE_LEN,"\nIngrese el nuevo nombre: ","\nNombre invalido!\n",3) &&
						!employee_setNombre(this,auxNombre))
					{
						printf("\nSe ha modificado el nombre!\n");
						flagModificar = 1;
					}
					break;
				case 2:
					if(!utn_getNumero(&auxHoras,"\nIngrese la nueva cantidad de horas trabajadas(1-300): ","\nCantidad invalida!\n",MIN_HORAS,MAX_HORAS,3) &&
					   !employee_setHorasTrabajadas(this,auxHoras))
					{
						printf("\nSe ha modificado la cantidad de horas trabajadas!\n");
						flagModificar = 1;
					}
					break;
				case 3:
					if(!utn_getNumero(&auxSueldo,"\nIngrese el nuevo Sueldo(10000-60000): ","\nSueldo invalido!\n",MIN_SUELDO,MAX_SUELDO,3) &&
					   !employee_setSueldo(this,auxSueldo))
					{
						printf("\nSe ha modificado el Sueldo!\n");
						flagModificar = 1;
					}
					break;
				default:
					printf("\nCancelando la modificacion.\n");
					flagModificar = 1;
				}
			}
			if(flagModificar)
			{
				retorno = 0;
			}
		}else
		{
			printf("\nNo se encontro a ningun Empleado con ese Id\n");
		}
	}
	return retorno;
}


/**
 * \brief Da de baja un Employee, pidiendo un id, preguntando si confirma la baja y en caso de que si, lo borra de la lista.
 * \param LinkedList* pArrayListEmployee: puntero de LinkedList
 * \param int len: es el limite del array
 * \return (-1) ERROR/ (0) Ok
 */
int employee_bajaEmployee(LinkedList* pArrayListEmployee,int len)
{
	int retorno = -1;
		int auxId;
		int indiceDeBaja;
		Employee* this;
		int opcionABorrar;
		if(pArrayListEmployee != NULL && len > 0 && !utn_getNumero(&auxId,"\nIngrese el ID de un Empleado que desea dar de baja: ","\nNumero Invalido!\n",1,10000,3))
		{
			indiceDeBaja = employee_buscarPorIdArray(pArrayListEmployee,len,auxId);
			if(indiceDeBaja != -1)
			{
				this = (Employee*)ll_get(pArrayListEmployee,indiceDeBaja);
				employee_imprimirEmployee(this);
				if(!utn_getNumero(&opcionABorrar,"\n¿Desea confirmar la baja?\n1-Si.\n2-No.\nElija opcion(1-2): ","\nOpcion invalida!\n",1,2,3))
				{
					if(opcionABorrar == 1)
					{
						employee_delete(this);
						ll_remove(pArrayListEmployee,indiceDeBaja);
					}else
					{
						printf("\nCancelando la baja\n");
					}
					retorno = 0;
				}else
				{
					printf("\nSe acabo el numero de reintentos para ingresar una opcion valida!\n");
				}
			}else
			{
				printf("\nNo se encontro a ningun Empleado con ese Id\n");
			}
		}
		return retorno;
}

int employee_imprimirArray(LinkedList* pArrayListEmployee,int len)
{
	int retorno = -1;
	int i;
	Employee* this;
	int flagIn = 0;
	if(pArrayListEmployee != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			this = employee_new();
			if(this != NULL)
			{
				this = (Employee*)ll_get(pArrayListEmployee,i);
				employee_imprimirEmployee(this);
				flagIn = 1;
			}
		}
		if(flagIn)
		{
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief Modifica imprime los datos de un Employee
 * \param Employee* this: puntero a Empleado
 */
void employee_imprimirEmployee(Employee* this)
{
	int auxId;
	char auxNombre[NOMBRE_LEN];
	int auxHoras;
	int auxSueldo;
	if(!employee_getId(this,&auxId) && !employee_getNombre(this,auxNombre) && !employee_getHorasTrabajadas(this,&auxHoras) && !employee_getSueldo(this,&auxSueldo))
	{
		printf("Id: %04d  Nombre: %-15s  horas: %-4d  sueldo: %05d\n",auxId,auxNombre,auxHoras,auxSueldo);
	}
}


/**
 * \brief obtiene un id de tipo char de un empleado pasado por referencia.
 * \param Employee* this: puntero de Employee
 * \param char* id: id del tipo char donde sera guardado el id
 * \return (-1) ERROR/ (0) Ok
 */
int employee_getIdTxt(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		sprintf(id,"%d",this->id);
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief obtiene un sueldo de tipo char de un empleado pasado por referencia.
 * \param Employee* this: puntero de Employee
 * \param char* sueldo: sueldo del tipo char donde sera guardado el Sueldo
 * \return (-1) ERROR/ (0) Ok
 */
int employee_getSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		sprintf(sueldo,"%d",this->sueldo);
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief obtiene el campo horasTrabajadas de tipo char de un empleado pasado por referencia.
 * \param Employee* this: puntero de Employee
 * \param char* horasTrabajadas: campo horasTrabajadas del tipo char donde sera guardado las horasTrabajadas
 * \return (-1) ERROR/ (0) Ok
 */
int employee_getHorasTrabajadasTxt(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief setea a un empleado un id de tipo char pasado por parametro, pasandolo a entero.
 * \param Employee* this: puntero de Employee
 * \param char* id: id del tipo char
 * \return (-1) ERROR/ (0) Ok
 */
int employee_setIdTxt(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		if(esNumerica(id,1000))
		{
			this->id = atoi(id);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief setea a un empleado un sueldo de tipo char pasado por parametro, pasandolo a entero.
 * \param Employee* this: puntero de Employee
 * \param char* sueldo: sueldo del tipo char
 * \return (-1) ERROR/ (0) Ok
 */
int employee_setSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		if(esNumerica(sueldo,1000))
		{
			this->sueldo = atoi(sueldo);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief setea a un empleado las horas trabajadas en tipo char pasado por parametro, pasandolo a entero.
 * \param Employee* this: puntero de Employee
 * \param char* horasTrabajadas: horas del tipo char
 * \return (-1) ERROR/ (0) Ok
 */
int employee_setHorasTrabajadasTxt(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		if(esNumerica(horasTrabajadas,1000))
		{
			this->horasTrabajadas = atoi(horasTrabajadas);
			retorno = 0;
		}
	}
	return retorno;
}


/**
 * \brief busca el id de un empleado comparandolo con el idABuscar pasado por referencia
 * \param LinkedList* pArrayListEmployee: puntero a la lista de empleados
 * \param int len: longitud de la lista
 * \param int idABuscar: id a ser buscado
 * \return (-1) ERROR/ (i) Ok
 */
int employee_buscarPorIdArray(LinkedList* pArrayListEmployee,int len,int idABuscar)
{
	int indiceEncontrado = -1;
	int i;
	Employee* this;
	int auxId;
	if(pArrayListEmployee != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			this = employee_new();
			if(this != NULL)
			{
				this = (Employee*)ll_get(pArrayListEmployee,i);
				if(!employee_getId(this,&auxId) && auxId == idABuscar)
				{
					indiceEncontrado = i;
					break;
				}
			}
		}
	}
	return indiceEncontrado;
}


/**
 * \brief ordena los empleados segun su id, nombre, horas trabajadas o sueldo, eligiendo tambien  de que manera se ordenaran si ascendente o descendente.
 * \param LinkedList* pArrayListEmployee: puntero a la lista de empleados
 * \param int len: longitud de la lista
 * \return (-1) ERROR/ (i) Ok
 */
int employee_ordenarEmployee(LinkedList* pArrayListEmployee,int len)
{
	int retorno = -1;
	int opcionOrdenar;
	int orden;
	int flagOrdenar = 0;
	if(pArrayListEmployee != NULL && len > 0 && !utn_getNumero(&opcionOrdenar,"\n-Menu ordenar Empleados\n"
																			  "1-Ordenar por Id.\n"
																			  "2-Ordenar por Nombre.\n"
																			  "3-Ordenar por Horas Trabajadas.\n"
																			  "4-Ordenar por SUeldos.\n"
																			  "5-Salir\nElija una opcion(1-5): ","\nOpcion invalida!",1,5,3))
	{
		switch(opcionOrdenar)
		{
		case 1:
			printf("\nOrdenamiento por ID\n");
			if(!utn_getNumero(&orden,"\n¿De que manera desea ordenar a los Empleados?\n0-Ascendente.\n1-Descendente.\n2-Salir\nElija una opcion(0-1): ","\nOpcion invalida!",0,2,3))
			{
				if(orden != 2)
				{
					printf("\nEspere unos segundos hasta que se ordenen...\n");
					ll_sort(pArrayListEmployee,employee_ordenarIds,orden);
				}else
				{
					printf("\nSe cancelo el ordenamiento, volviendo al menu principal.\n");
				}
				flagOrdenar = 1;
			}else
			{
				printf("\nSe acabo el numero de intentos para ingresar una opcion valida!\n");
			}
			break;
		case 2:
			printf("\nOrdenamiento por Nombre\n");
			if(!utn_getNumero(&orden,"\n¿De que manera desea ordenar a los Empleados?\n0-Ascendente.\n1-Descendente.\n2-Salir\nElija una opcion(0-1): ","\nOpcion invalida!",0,2,3))
			{
				if(orden != 2)
				{
					printf("\nEspere unos segundos hasta que se ordenen...\n");
					ll_sort(pArrayListEmployee,employee_ordenarNombres,orden);
				}else
				{
					printf("\nSe cancelo el ordenamiento, volviendo al menu principal.\n");
				}
				flagOrdenar = 1;
			}else
			{
				printf("\nSe acabo el numero de intentos para ingresar una opcion valida!\n");
			}
			break;
		case 3:
			printf("\nOrdenamiento por Horas Trabajadas\n");
			if(!utn_getNumero(&orden,"\n¿De que manera desea ordenar a los Empleados?\n0-Ascendente.\n1-Descendente.\n2-Salir\nElija una opcion(0-1): ","\nOpcion invalida!",0,2,3))
			{
				if(orden != 2)
				{
					printf("\nEspere unos segundos hasta que se ordenen...\n");
					ll_sort(pArrayListEmployee,employee_ordenarHorasTrabajadas,orden);
				}else
				{
					printf("\nSe cancelo el ordenamiento, volviendo al menu principal.\n");
				}
				flagOrdenar = 1;
			}else
			{
				printf("\nSe acabo el numero de intentos para ingresar una opcion valida!\n");
			}
			break;
		case 4:
			printf("\nOrdenamiento por Sueldos\n");
			if(!utn_getNumero(&orden,"\n¿De que manera desea ordenar a los Empleados?\n0-Ascendente.\n1-Descendente.\n2-Salir\nElija una opcion(0-1): ","\nOpcion invalida!",0,2,3))
			{
				if(orden != 2)
				{
					printf("\nEspere unos segundos hasta que se ordenen...\n");
					ll_sort(pArrayListEmployee,employee_ordenarSueldos,orden);
				}else
				{
					printf("\nSe cancelo el ordenamiento, volviendo al menu principal.\n");
				}
				flagOrdenar = 1;
			}else
			{
				printf("\nSe acabo el numero de intentos para ingresar una opcion valida!\n");
			}
			break;
		default:
			flagOrdenar = 1;
		}
		if(flagOrdenar)
		{
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief compara los nombres de los empleados pasados por parametros.
 * \param void* this: puntero a void.
 * \param void* thanThis: puntero a void
 * \return (1) Si el primer nombre es mayor que el segundo, (-1) si el primer nombre es menor que el segundo, (0) si error
 */
static int employee_ordenarNombres(void* this,void* thanThis)
{
	int respuesta = 0;
	char auxNombreUno[NOMBRE_LEN];
	char auxNombreDos[NOMBRE_LEN];
	if(this != NULL && thanThis != NULL && !employee_getNombre(this,auxNombreUno) && !employee_getNombre(thanThis,auxNombreDos))
	{
		if(strncmp(auxNombreUno,auxNombreDos,NOMBRE_LEN) < 0)
		{
			respuesta = 1;
		}else if(strncmp(auxNombreUno,auxNombreDos,NOMBRE_LEN) > 0)
		{
			respuesta = -1;
		}
	}
	return respuesta;
}
static int employee_ordenarIds(void* this,void* thanThis)
{
	int respuesta = 0;
	int auxIdUno;
	int auxIdDos;

	if(this != NULL && thanThis != NULL && !employee_getId(this,&auxIdUno) && !employee_getId(thanThis,&auxIdDos))
	{
		if(auxIdUno < auxIdDos)
		{
			respuesta = 1;
		}else if(auxIdUno > auxIdDos)
		{
			respuesta = -1;
		}
	}
	return respuesta;
}

static int employee_ordenarHorasTrabajadas(void* this,void* thanThis)
{
	int respuesta = 0;
	int auxHorasUno;
	int auxHorasDos;

	if(this != NULL && thanThis != NULL && !employee_getHorasTrabajadas(this,&auxHorasUno) && !employee_getHorasTrabajadas(thanThis,&auxHorasDos))
	{
		if(auxHorasUno < auxHorasDos)
		{
			respuesta = 1;
		}else if(auxHorasUno > auxHorasDos)
		{
			respuesta = -1;
		}
	}
	return respuesta;
}
static int employee_ordenarSueldos(void* this,void* thanThis)
{
	int respuesta = 0;
	int auxSueldoUno;
	int auxSueldoDos;

	if(this != NULL && thanThis != NULL && !employee_getSueldo(this,&auxSueldoUno) && !employee_getSueldo(thanThis,&auxSueldoDos))
	{
		if(auxSueldoUno < auxSueldoDos)
		{
			respuesta = 1;
		}else if(auxSueldoUno > auxSueldoDos)
		{
			respuesta = -1;
		}
	}
	return respuesta;
}

/**
 * \brief elimina todos los empleados de la lista dinamica
 * \param linkedList* pArrayListEmployee: lista dinamica de empleados
 * \param int len: longitud de la lista.
 * \return 0 si todoOK / -1 ERROR;
 */
int employee_deleteAllArray(LinkedList* pArrayListEmployee,int len)
{
	int retorno = -1;
	Employee* this;
	int i;
	if(pArrayListEmployee != NULL && len > 0)
	{
		for(i=len-1;i>=0;i--)
		{
			this = (Employee*)ll_get(pArrayListEmployee,i);
			if(this != NULL)
			{
				employee_delete(this);
				this = NULL;
				ll_remove(pArrayListEmployee,i);
			}
		}
	}
	return retorno;
}

/**
 * \brief genera un id estatico
 * \param linkedList* pArrayListEmployee: lista dinamica de empleados
 * \param int len: longitud de la lista.
 * \return id;
 */
static int employee_generadorDeId(LinkedList* pArrayListEmployee,int len)
{
	static int idMaximo;
	static int flagIn = 0;
	Employee* this;
	int auxId;
	int i;
	if(pArrayListEmployee != NULL && len > 0)
	{
		if(!flagIn)
		{
			for(i=0;i<len;i++)
			{
				this = (Employee*)ll_get(pArrayListEmployee,i);
				if(this != NULL && !employee_getId(this,&auxId) && (i == 0 || idMaximo < auxId))
				{
					idMaximo = auxId;
					flagIn = 1;
				}
			}

		}
		if(flagIn)
		{
			idMaximo++;
		}
	}
	return idMaximo;
}


