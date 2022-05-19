/*
 * censista.h
 *
 *  Created on: 15 may. 2022
 *      Author: Franco
 */

#ifndef CENSISTA_H_
#define CENSISTA_H_

typedef struct
{
	char nombreDir[50];
	int alturaDir;
}Direccion;

typedef struct
{
	int diaNac;
	int mesNac;
	int anioNac;
}FechaNacimiento;

typedef struct
{
	int idCensista;
	char nombre[50];
	char apellido[50];
	int edad;
	Direccion direccion;
	FechaNacimiento fechaNacimiento;
	char estadoCensista[10];
	int isEmpty;
}Censista;

int idCensista(void);

int initCensistas(Censista *list, int len);

int mostrarCensistas(Censista *list, int len);

int agregarCensista(Censista *list, int len, int id, char nombre[], char apellido[], FechaNacimiento fecha, int edad, Direccion dir);

int cargarDataCensista(Censista *list, int len);

int borrarCensista(Censista *list, int len);

int modificarCensista(Censista *list, int len);

int cargaForzadaCensistas(Censista list[], int len);

int buscarIndexPorIsEmpty(Censista list[], int len);

int buscarCensistaPorId(Censista *list, int len, int id);

#endif /* CENSISTA_H_ */
