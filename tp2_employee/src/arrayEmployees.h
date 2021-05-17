/*
 * arrayEmployees.h
 *
 *  Created on: 9 may. 2020
 *      Author: reyna
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

typedef struct
{
	int id;
	char name[20];
	char lastName[20];
	float salary;
	int sector;
	int isEmpty;
}sEmployee;

#endif /* ARRAYEMPLOYEES_H_ */

int invalidList(sEmployee* list, int len);
int initEmployees(sEmployee* list, int len);
int noEmployee (int ready);
int menue(char message[350]);
int findEmployeeById(sEmployee* list, int len, int id);
int askData (sEmployee* list, int len, int id);
int addEmployees (sEmployee* list, int len, int id, char name[], char lastName [], float salary, int sector);
int modifyEmployee (sEmployee* list, int len);
int removeEmployee(sEmployee* list, int len, int id);
int statisticsEmployees(sEmployee* list, int len);
int sortEmployees(sEmployee* list, int len, int order);
int requestInfo(sEmployee* list, int len);
void printEmployee(sEmployee emp);
int printEmployees(sEmployee* list, int len);
float inputSalary(char message[40]);
int inputInt(char message[40]);
void inputString(char message[20], char* string);

