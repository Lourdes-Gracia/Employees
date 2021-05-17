#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arrayEmployees.h"

/**
 * \brief To indicate Invalid length or NULL pointer
 *
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if [Invalid length or NULL pointer] - (0) if Ok
 */

int invalidList(sEmployee* list, int len)
{
	if (len > 0 && list != NULL)
	{
		return 0;
	}
	else
	{
		printf("Lista NULL o fuera de rango.");
		return -1;
	}
}

/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/

int initEmployees(sEmployee* list, int len)
{
	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
		}
		return 0;
	}
}

/**
 * @brief To indicate that the first employee wasn't added.
 *
 * @param ready int ready // 0 TRUE 1 FALSE
 * @return int Return (-1) if Error [No employee has been added yet.] - (0) if Ok
 */

int noEmployee (int ready)
{
	if(!(ready))
	{
		printf("Aun no se han ingresado empleados.\n\n");
		return -1;
	}
	return 0;
}

/**
 * @brief Customizable menue
 *
 * @return int option selected by user
 */

int menue(char message[350])
{
	int option;

	printf( "\n%s\n", message);
	scanf("%d", &option);

	return option;
}

/** \brief find an Employee by Id en returns the index position in array.
* \param list Employee*
* \param len int
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*/

int findEmployeeById(sEmployee* list, int len, int id)
{
	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		for(int i = 0; i < len; i++)
		{
			if (list[i].id == id && list[i].isEmpty == 0)
			{
				return i;
			}
		}
		printf("No existe empleado asociado al ID %d.", id);
		return -1;
	}
}

/** \brief Ask user data
* \param list Employee*
* \param len int
* \param id int
* \return int Return (-1) if [Invalid length or NULL pointer received or employee not found] -
* 					  (0) if OK
*/

int askData(sEmployee* list, int len, int id)
{
	sEmployee auxEmp;

	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		for(int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == 1 )
			{
				inputString("nombre", auxEmp.name);
				inputString("apellido", auxEmp.lastName);
				auxEmp.salary = inputSalary("salario");
				auxEmp.sector = inputInt("sector");

				addEmployees (list, len, id, auxEmp.name, auxEmp.lastName, auxEmp.salary, auxEmp.sector);

				return 0;
			}
		}
		printf("Listado completo. No se pueden ingresar nuevos empleados.\n");
		return -1;
	}
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
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*/

int addEmployees (sEmployee* list, int len, int id, char name[], char lastName [], float salary, int sector)

{
	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == 1 )
			{
				list[i].id = id;
				strcpy(list[i].name, name);
				strcpy(list[i].lastName, lastName);
				list[i].salary = salary;
				list[i].sector = sector;
				list[i].isEmpty = 0;
				return 0;
			}
		}
		printf("Listado completo. No se pueden ingresar nuevos empleados.\n");
		return -1;
	}
}

/** \brief modify employee parameters
* \param list employee*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*/
int modifyEmployee (sEmployee* list, int len)
{
	int index;
	sEmployee auxEmp;

	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		index = findEmployeeById(list, len, inputInt("ID"));

		if (index == -1)
		{
			return -1;
		}
		else
		{
			switch(menue("Seleccione parametro a modificar:\n"
							"1.- Nombre\n"
							"2.- Apellido\n"
							"3.- Salario\n"
							"4.- Sector\n"
							"Presione una tecla para cancelar.\n"))
			{
				case 1:
					printf("Ingrese nuevo nombre: ");
					fflush(stdin);
					gets(auxEmp.name);
					strcpy(list[index].name, auxEmp.name);
				break;
				case 2:
					printf("Ingrese nuevo apellido: ");
					fflush(stdin);
					gets(auxEmp.lastName);
					strcpy(list[index].lastName, auxEmp.lastName);
					break;
				case 3:
					list[index].salary = inputSalary("nuevo salario");
					break;
				case 4:
					list[index].sector = inputInt("nuevo sector");
					break;
				default:
					printf("No se realizaron cambios.\n\n");
					break;
			}
		return 0;
		}
	}
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
* \param list Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*/
int removeEmployee(sEmployee* list, int len, int id)
{
	char confirm = 'n';
	int index;

	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		index = findEmployeeById(list, len, id);

		if(index == -1)
		{
			return -1;
		}
		else
		{
			printf("Esta seguro que desea eliminar a %s %s? s/n ", list[id].name, list[id].lastName);
			fflush(stdin);
			scanf("%c", &confirm);

			if(confirm == 's')
			{
				list[index].isEmpty = 1;
				printf("Usuario eliminado exitosamente.\n");
			}
			else
			{
				printf("No se realizaron cambios.");
			}
		return 0;
		}
	}
}

/** \brief Prints the total and average salary and amount of employees who earn more than average salary.
* \param list Employee*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int statisticsEmployees(sEmployee* list, int len)
{
	float totalSalary = 0;
	int totalEmployees = 0;
	float averageSalary;
	int overAverageSalary = 0;

	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		for(int i = 0; i < len ; i++)
		{
			if (list[i].isEmpty == 0)
			{
				totalSalary+= list[i].salary;
				totalEmployees++;
			}
		}

		if(totalEmployees == 0)
		{
			printf("Se requiere por lo menos un empleado para mostrar datos.\n");
		}
		else
		{
			averageSalary = totalSalary / totalEmployees;

			for (int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == 0 && list[i].salary > averageSalary)
				{
					overAverageSalary++;
				}
			}

			printf("El monto total de los salarios es: $%.2f \n", totalSalary);
			printf("El promedio de los salarios es $%.2f \n", averageSalary);
			printf("Hay %d empleados que cobran por encima del promedio.", overAverageSalary);
		}
		return 0;
	}
}


/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
*
* \param list Employee*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortEmployees(sEmployee* list, int len, int order)
{
	sEmployee auxEmp;


	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		if(order > 2 || order < 1)
		{
			printf("Orden invalido.\n");
		}
		else
		{
			for (int i = 0; i < len -1 ; i++)
			{

				for (int j = i+1; j < len; j ++)
				{
					if (order == 1 && list[i].isEmpty == 0 && (strcmp(list[i].lastName,list[j].lastName) > 0))
					{
						auxEmp = list[i];
						list[i] = list[j];
						list[j] = auxEmp;
					}
					if (order == 1 && list[i].isEmpty == 0 && (strcmp(list[i].lastName,list[j].lastName) == 0 && list[i].sector > list[j].sector))
					{
						auxEmp = list[i];
						list[i] = list[j];
						list[j] = auxEmp;
					}
					if (order == 2 && list[i].isEmpty == 0 && (strcmp(list[i].lastName,list[j].lastName) < 0))
					{
						auxEmp = list[i];
						list[i] = list[j];
						list[j] = auxEmp;
					}
					if (order == 2 && list[i].isEmpty == 0 && (strcmp(list[i].lastName,list[j].lastName) == 0 && list[i].sector > list[j].sector))
					{
						auxEmp = list[i];
						list[i] = list[j];
						list[j] = auxEmp;
					}
				}
			}
			printEmployees(list, len);
		}
	return 0;
	}
}

/** \brief
* \param list Employee*
* \param length int
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int requestInfo(sEmployee* list, int len)
{
	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		if(menue("Por favor, seleccione una opcion:\n"
					"1.- Listado de empleados\n"
					"2.- Estadisticas\n") == 1)
		{
			sortEmployees(list, len, menue("Modo de ordenamiento:\n"
											"1.- Ascendente\n"
											"2.- Descendente\n"));
		}
		else
		{
			statisticsEmployees(list, len);
		}
		return 0;
	}
}

/** \brief prints one employee
* \param sEmploee emp
*/

void printEmployee(sEmployee emp)
{

	printf(	"| %04d | %20s | %20s | $%10.2f |   %3d    |\n", emp.id, emp.name, emp.lastName, emp.salary, emp.sector);
}

/** \brief print the content of employees array in each position
* \param list Employee*
* \param length int
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/

int printEmployees(sEmployee* list, int len)
{
	if((invalidList(list, len)))
	{
		return -1;
	}
	else
	{
		printf(	"#======#======================#======================#=============#==========#\n"
				"|  ID  |        NOMBRE        |       APELLIDO       |   SALARIO   |  SECTOR  |\n"
				"#======#======================#======================#=============#==========#\n");
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				printEmployee(list[i]);
			}
		}
		printf( "#======#======================#======================#=============#==========#\n");
		return 0;
	}
}

/** \brief gets float number, if it's out of range it will be ask again
* \param char message[20]
* \return float num is positive number
*/

float inputSalary(char message[20])
{
	float num;

	printf("Ingrese %s: ", message);
	scanf("%f", &num);

	while (num < 1)
	{
		printf("ERROR: %s fuera de rango. Ingrese %s nuevamente: \n", message, message);
		scanf("%f", &num);
	}
	return num;
}

/** \brief gets int number, if it's out of range it will be ask again
* \param char message[20]
* \return int num is a positive number or (0)
*/
int inputInt(char message[20])
{
	int num;

	printf("Ingrese %s: ", message);
	scanf("%d", &num);

	while (num < 0)
	{
		printf("ERROR: %s fuera de rango. Ingrese %s nuevamente: ", message, message);
		scanf("%d", &num);
	}
	return num;
}

/** \brief gets a char array to check lenght, when it's ok everything turn to lower case,
 * then the first letter of each word is change to upper case
* \param char message[20]
* \param char* string
*/
void inputString(char message[20], char* string)
{
	printf("Ingrese %s: ", message);
	fflush(stdin);
	gets(string);
	int noNum = 0;

	do
	{
	if (strlen(string) > 19)
	{
		printf("ERROR: %s es demasiado largo. Ingrese %s nuevamente: ", message, message);
		fflush(stdin);
		gets(string);
	}
	else
	{
		strlwr(string);

		for (int i = 0; i < strlen(string); i++)
		{
			if(isdigit(string[i]))
			{
				noNum = 1;
				break;
			}
			else
			{
				noNum = 0;
			}
		}
	}
	if (noNum == 1)
	{
		printf("ERROR: No se aceptan numeros. Ingrese %s nuevamente: ", message);
		fflush(stdin);
		gets(string);
	}
	else
	{
		for(int i = 0; i < strlen(string); i++)
		{
			string[0] = toupper(string[0]);
			if(string[i] == ' ')
			{
				string[i+1] = toupper(string[i+1]);
			}
		}
	}
	}while(noNum == 1);

}

