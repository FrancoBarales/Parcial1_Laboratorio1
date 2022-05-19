/*
 * censista.c
 *
 *  Created on: 15 may. 2022
 *      Author: Franco
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "censista.h"
#include "zona.h"
#include "menus.h"
#include "utn.h"

#define VACIO 0
#define LLENO 1
#define ANIOACTUAL 2022

int idCensista(void)
{
    static int id = 1000;
    id++;
    return id;
}

int initCensistas(Censista *list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			list[i].isEmpty = VACIO;
		}
		retorno = 0;
	}
	return retorno;
}

int mostrarCensistas(Censista *list, int len)
{
	int retorno = -1;

	printf(
				"\n+------+------------------+------------------+----------------------+--------------+------+----------------------------+"
				"\n|ID    |NOMBRE            |APELLIDO          |FECHA NACIMIENTO      |ESTADO        |EDAD  |DOMICILIO                   |"
				"\n+------+------------------+------------------+----------------------+--------------+------+----------------------------+");

	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty != VACIO)
			{
				mostrarDataCensista(list[i]);
			}
		}
		retorno = 0;
	}

	return retorno;
}

void mostrarDataCensista(Censista list)
{
	printf("\n|%-6d|%-18s|%-18s|%-2d/%-2d/%-16d|%-14s|%-6d|%-20s N°%-5d|"
							"\n+------+------------------+------------------+----------------------+--------------+------+----------------------------+",
						   list.idCensista,
						   list.nombre,
						   list.apellido,
						   list.fechaNacimiento.diaNac,
						   list.fechaNacimiento.mesNac,
						   list.fechaNacimiento.anioNac,
						   list.estadoCensista,
						   list.edad,
						   list.direccion.nombreDir,
						   list.direccion.alturaDir);
}

int agregarCensista(Censista *list, int len, int id, char nombre[], char apellido[], FechaNacimiento fecha, int edad, Direccion dir)
{
	int retorno = -1;
	int index = buscarIndexPorIsEmpty(list, len);
	Censista nuevoCensista;

	if(index != -1 && list != NULL && len > 0)
	{
		nuevoCensista.idCensista = id;
		strcpy(nuevoCensista.nombre, nombre);
		strcpy(nuevoCensista.apellido, apellido);
		nuevoCensista.fechaNacimiento.diaNac = fecha.diaNac;
		nuevoCensista.fechaNacimiento.mesNac = fecha.mesNac;
		nuevoCensista.fechaNacimiento.anioNac = fecha.anioNac;
		nuevoCensista.edad = 2022 - nuevoCensista.fechaNacimiento.anioNac;
		strcpy(nuevoCensista.direccion.nombreDir, dir.nombreDir);
		nuevoCensista.direccion.alturaDir = dir.alturaDir;
		strcpy(nuevoCensista.estadoCensista, "INACTIVO");
		nuevoCensista.isEmpty = LLENO;
		list[index] = nuevoCensista;
		retorno = 0;
	}
	return retorno;
}

int cargarDataCensista(Censista *list, int len)
{
	int retorno = -1;
	int verifCensista;
	int auxEdad;
	Censista nuevoCensista;
	FechaNacimiento nuevaFechaNacimiento;
	Direccion nuevaDireccion;

	if(list != NULL && len > 0)
	{
		nuevoCensista.idCensista = idCensista();
		utn_getNombre(nuevoCensista.nombre, 1, 51, "\nIngrese el nombre del censista: ", "\nERROR. Datos no validos.", 30);
		utn_getNombre(nuevoCensista.apellido, 1, 51, "\nIngrese el apellido del censista: ", "\nERROR. Datos no validos.", 30);
		printf("\n-----------------Fecha de Nacimiento------------------\n");
		utn_getNumero(&nuevaFechaNacimiento.diaNac,"\nIngrese el dia de nacimiento: ","\nERROR. Opcion incorrecta.", 1, 31, 30);
		utn_getNumero(&nuevaFechaNacimiento.mesNac,"\nIngrese el mes de nacimiento: ","\nERROR. Opcion incorrecta.", 1, 12, 30);
		utn_getNumero(&nuevaFechaNacimiento.anioNac,"\nIngrese el año de nacimiento: ","\nERROR. Opcion incorrecta.", 1900, 2004, 30);
		auxEdad = ANIOACTUAL - nuevaFechaNacimiento.anioNac;
		printf("\nEdad: %d\n", auxEdad);
		printf("\n-----------------Direccion particular------------------\n");
		utn_getNombre(nuevaDireccion.nombreDir, 1, 50, "\nIngrese el nombre de la calle: ","\nERROR. Datos no validos.", 30);
		utn_getNumero(&nuevaDireccion.alturaDir,"\nIngrese la altura: ","\nERROR. Opcion incorrecta.",1, 99999, 30);
		verifCensista = agregarCensista(list, len,
				nuevoCensista.idCensista,
				nuevoCensista.nombre,
				nuevoCensista.apellido,
				nuevaFechaNacimiento,
				nuevoCensista.edad,
				nuevaDireccion);
		if(verifCensista != -1)
		{
			printf("\nDatos cargados exitosamente.");
			retorno = 0;
		}
		else
		{
			printf("\nERROR. No se pudieron cargar los datos.\n");
		}
	}
	return retorno;
}

int borrarCensista(Censista *list, int len)
{
	char respuesta[3];
	int retorno = -1;
	int index;
	int auxId;

	utn_getNumero(&auxId,"\nIngrese el Id del censista: ","\nERROR. Opcion incorrecta.", 1000, 5000, 30);
	index = buscarCensistaPorId(list, len, auxId);
	if(index == 0)
	{
		utn_getNombre(respuesta, 1, 3, "\nEsta seguro que quiere dar de baja al censista? (SI/NO):", "ERROR.\n" , 3);
		strEnMinuscula(respuesta);
		if(index != -1 && strcmp(respuesta, "si") == 0)
		{
			list[index].isEmpty = VACIO;
			retorno = 0;
		}
	}
	else
	{
		printf("\nERROR. No se pudo encontrar el index especificado.\n");
	}

	return retorno;
}

int modificarCensista(Censista *list, int len)
{
	int retorno = -1;
	int auxId;
	int opcion;
	int opcionFecha;
	int opcionDireccion;
	int index;
	int verificacionId;

	mostrarCensistas(list, len);
	utn_getNumero(&auxId, "\nIngrese el id del censista que desea modificar: ","\nERROR. Opcion incorrecta.", 1000, 5000, 3);

	verificacionId = buscarCensistaPorId(list, len, auxId);
	if(verificacionId == 0)
	{
		index = buscarCensistaPorId(list, len, auxId);
		if(index != -1)
		{
			opcion = menuModificarCensista();
			switch(opcion)
			{
				case 1:
					utn_getNombre(list[index].nombre, 1, 51, "\nIngrese el nombre del censista: ", "\nERROR. Datos no validos.", 30);
					break;
				case 2:
					utn_getNombre(list[index].apellido, 1, 51, "\nIngrese el apellido del censista: ", "\nERROR. Datos no validos.", 30);
					break;
				case 3:
					opcionFecha = menuModificarFechaCensista();
					switch(opcionFecha)
					{
						case 1:
							utn_getNumero(&list[index].fechaNacimiento.diaNac,"\nIngrese el dia de nacimiento: ","\nERROR. Opcion incorrecta.", 1, 31, 30);
							break;
						case 2:
							utn_getNumero(&list[index].fechaNacimiento.mesNac,"\nIngrese el mes de nacimiento: ","\nERROR. Opcion incorrecta.", 1, 12, 30);
							break;
						case 3:
							utn_getNumero(&list[index].fechaNacimiento.anioNac,"\nIngrese el año de nacimiento: ","\nERROR. Opcion incorrecta.", 1900, 2004, 30);
							break;
						case 4:
							break;
					}
					break;
				case 4:
					utn_getNumero(&list[index].edad,"\nIngrese la edad del censista: ","\nERROR. Opcion incorrecta.", 18, 120, 30);
					break;
				case 5:
					opcionDireccion = menuModificarDireccionCensista();
					switch(opcionDireccion)
					{
						case 1:
							utn_getNombre(list[index].direccion.nombreDir, 1, 50, "\nIngrese el nombre de la calle: ","\nERROR. Datos no validos.", 30);
							break;
						case 2:
							utn_getNumero(&list[index].direccion.alturaDir,"\nIngrese la altura: ","\nERROR. Opcion incorrecta.",1, 30000, 30);
							break;
						case 3:
							break;
					}
					break;
			}
			retorno = 0;
		}
	}
	else
	{
		printf("\nERROR.No se pudo encontrar el ID especificado.");
	}
	return retorno;
}

int cargaForzadaCensistas(Censista list[], int len)
{
	int retorno = -1;
	FechaNacimiento fecha1 = {5,7,1975};
	FechaNacimiento fecha2 = {3,11,1979};
	FechaNacimiento fecha3 = {5,5,1976};
	FechaNacimiento fecha4 = {10,8,1973};
	FechaNacimiento fecha5 = {18,8,1980};
	Direccion direccion1 = {"Castillo", 873};
	Direccion direccion2 = {"Rivadavia", 2545};
	Direccion direccion3 = {"Campos Salles", 174};
	Direccion direccion4 = {"Roosevelt", 1664};
	Direccion direccion5 = {"Olazabal", 619};

	if(list != NULL && len > 0)
	{
		agregarCensista(list, len, 4991, "Hernan", "Crespo", fecha1, 46, direccion1);
		agregarCensista(list, len, 4992, "Pablo", "Aimar", fecha2, 42, direccion2);
		agregarCensista(list, len, 4993, "Juan Pablo", "Sorin", fecha3, 46, direccion3);
		agregarCensista(list, len, 4994, "Javier", "Zanetti", fecha4, 48, direccion4);
		agregarCensista(list, len, 4995, "Esteban", "Cambiasso", fecha5, 41, direccion5);
		retorno = 0;
	}

	return retorno;
}


int buscarIndexPorIsEmpty(Censista list[], int len)
{
	int retorno = -1;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == VACIO)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

int buscarCensistaPorId(Censista *list, int len, int id)
{
	int retorno = -1;

	for(int i = 0; i < len; i++)
	{
		if(list[i].idCensista == id)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}




