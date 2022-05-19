/*
 * zona.c
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
#include "utn.h"

#define VACIO 0
#define LLENO 1

#define LENGTH 100

int idZona(void)
{
    static int id = 6000;
    id++;
    return id;
}

int initZonas(Zona *list, int len)
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

int mostrarZonas(Zona *list, int len)
{
	int retorno = -1;

	printf(
			"\n Aclaraciones: (-1 = NO HAY DATOS)                                                                     "
			"\n+---------------+---------------+---------------+-----------------+-----------------+-----------------+"
			"\n|ID ZONA        |LOCALIDAD      |ID CENSISTA    |CENSADOS IN SITU |CENSADOS VIRTUAL |CENSADOS AUSENTES|"
			"\n+---------------+---------------+---------------+-----------------+-----------------+-----------------+");

	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty != VACIO)
			{
				printf("\n|%-15d|%-15d|%-15d|%-17d|%-17d|%-17d|"
											"\n+---------------+---------------+---------------+-----------------+-----------------+-----------------+",
											list[i].idZona,
											list[i].localidad,
											list[i].idCensista,
											list[i].cantidadInSitu,
											list[i].cantidadVirtual,
											list[i].cantidadAusente);
			}
		}
		retorno = 0;
	}

	return retorno;
}

int agregarZona(Zona *list, int len, int idZona, int localidad, int idCensista)
{
	int retorno = -1;
	int index = buscarZonaPorIsEmpty(list, len);
	Zona nuevaZona;

	if(index != -1 && list != NULL && len > 0)
	{
		nuevaZona.idZona = idZona;
		nuevaZona.localidad = localidad;
		nuevaZona.idCensista = -1;
		nuevaZona.cantidadInSitu = -1;
		nuevaZona.cantidadVirtual = -1;
		nuevaZona.cantidadAusente = -1;
		list[index] = nuevaZona;
		retorno = 0;
	}
	return retorno;
}

int cargarDataZona(Zona *list, int len, int localidades[])
{
	int retorno = -1;
	int verifZona;
	int verifLocalidad;
	int auxLocalidad;
	Zona nuevaZona;

	if(list != NULL && len > 0)
	{
		nuevaZona.idZona = idZona();
		utn_getNumero(&auxLocalidad,"\nIngrese la localidad: ","\nERROR. Opcion incorrecta.", 1, 50, 30);
		verifLocalidad = buscarLocalidadEnArray(localidades, 50, auxLocalidad);
		if(verifLocalidad == 0)
		{
			nuevaZona.localidad = auxLocalidad;
			nuevaZona.idCensista = -1;
			nuevaZona.cantidadInSitu = -1;
			nuevaZona.cantidadVirtual = -1;
			nuevaZona.cantidadAusente = -1;
			strcpy(nuevaZona.estadoZona, "PENDIENTE");
			verifZona = agregarZona(list, len, nuevaZona.idZona, nuevaZona.localidad, nuevaZona.idCensista);
			if(verifZona != -1)
			{
				printf("\nDatos cargados exitosamente.");
				retorno = 0;
			}
			else
			{
				printf("\nERROR. No se pudieron cargar los datos.\n");
			}
		}
		else
		{
			printf("\nERROR. La localidad no se encontro en la lista.\n");
		}

	}
	return retorno;
}

int borrarZona(Zona *list, int len, int id)
{
	char respuesta[3];
	int retorno = -1;
	int index;

	index = buscarZonaPorId(list, len, id);
	if(index == 0)
	{
		utn_getNombre(respuesta, 1, 3, "\nEsta seguro que quiere dar de baja esta zona? (SI/NO): ", "ERROR. Opcion incorrecta.\n" , 3);
		strEnMinuscula(respuesta);
		if(index != -1 && strcmp(respuesta, "si") == 0)
		{
			list[index].isEmpty = VACIO;
			printf("\nLa zona de Id %d fue dada de baja exitosamente.", index);
			retorno = 0;
		}
	}
	else
	{
		printf("\nERROR. No se pudo encontrar el index especificado.\n");
	}

	return retorno;
}

int asignarZonaACensista(Zona *listZonas, Censista *listCensistas, int len)
{
	int retorno = -1;
	int indexCensista;
	int indexZona;
	int auxIdCensista;
	int auxIdZona;


	if(listZonas != NULL && listCensistas != NULL && len > 0)
	{
		utn_getNumero(&auxIdCensista,"\nIngrese el Id del censista: ","\nERROR. Opcion incorrecta.", 1000, 5000, 30);
		indexCensista = buscarCensistaPorId(listCensistas, LENGTH, auxIdCensista);
		if(strcmp(listCensistas[indexCensista].estadoCensista, "ACTIVO") != 0)
		{
			if(indexCensista != -1)
			{
				utn_getNumero(&auxIdZona,"\nIngrese el Id de la zona: ","\nERROR. Opcion incorrecta.", 6000, 9000, 30);
				indexZona = buscarZonaPorId(listZonas, len, auxIdZona);
				if(indexZona != -1)
				{
					if(listZonas[indexZona].idCensista == -1)
					{
						listZonas[indexZona].idCensista = auxIdCensista;
						strcpy(listCensistas[indexCensista].estadoCensista, "ACTIVO");
						printf("\nLa zona de Id %d fue asignada al Censista %s %s, de Id N° %d.", auxIdZona, listCensistas[indexCensista].nombre, listCensistas[indexCensista].apellido, auxIdCensista);
						retorno = 0;
					}
					else
					{
						printf("ERROR. La zona ya tiene asignada un censista.");
					}
				}
				else
				{
					printf("ERROR. No se encontro el id especificado de la zona.");
				}

			}
			else
			{
				printf("ERROR. No se encontro el Id especificado del censista.");
			}
		}
		else
		{
			printf("ERROR. El censista ya tiene una zona asignada.");
		}
	}
	return retorno;
}

int cargaDeDatos(Zona *listZonas, Censista *listCensistas, int len)
{
	int retorno = -1;
	int indexZona, indexCensista;
	int auxIdZona, auxIdCensista;
	int censadosInSitu;
	int censadosVirtual;
	int censadosAusentes;

	utn_getNumero(&auxIdZona,"\nIngrese el Id de la zona: ","\nERROR. Opcion incorrecta.", 6000, 9000, 30);
	indexZona = buscarZonaPorId(listZonas, LENGTH, auxIdZona);
	if(listZonas[indexZona].idCensista != -1)
	{
		printf("\nZona encontrada.");
		if(listZonas[indexZona].cantidadVirtual == -1)
		{
			utn_getNumero(&censadosInSitu,"\nIngrese la cantidad de censados in situ: ","\nERROR. Opcion incorrecta.", 1, 1500, 30);
			utn_getNumero(&censadosVirtual,"\nIngrese la cantidad de censados de manera virtual: ","\nERROR. Opcion incorrecta.", 1, 1500, 30);
			utn_getNumero(&censadosAusentes,"\nIngrese la cantidad de ausentes: ","\nERROR. Opcion incorrecta.", 1, 1500, 30);
			listZonas[indexZona].cantidadInSitu = censadosInSitu;
			listZonas[indexZona].cantidadVirtual = censadosVirtual;
			listZonas[indexZona].cantidadAusente = censadosAusentes;
			strcpy(listZonas[indexZona].estadoZona, "FINALIZADO");
			auxIdCensista = listZonas[indexZona].idCensista;
			indexCensista = buscarCensistaPorId(listCensistas, len, auxIdCensista);
			strcpy(listCensistas[indexCensista].estadoCensista, "LIBERADO");
			printf("\nLa zona de Id N°%d fue completada, y el censista %s %s de Id N°%d fue liberado.", auxIdZona, listCensistas[indexCensista].nombre, listCensistas[indexCensista].apellido, listCensistas[indexCensista].idCensista);
			retorno = 0;
		}
		else
		{
			printf("\nERROR. La zona ya fue censada.");
		}
	}
	else
	{
		printf("\nERROR. La zona especificada no tiene asignada un censista. (Opcion 5).");
	}
	return retorno;
}

int cargaForzadaZonas(Zona list[], int len)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		agregarZona(list, len, 8991, 6, 6001);
		agregarZona(list, len, 8992, 37, 6002);
		agregarZona(list, len, 8993, 24, 6003);
		agregarZona(list, len, 8994, 41, 6004);
		agregarZona(list, len, 8995, 12, 6005);
		retorno = 0;
	}

	return retorno;
}

int buscarZonaPorId(Zona *list, int len, int id)
{
	int retorno = -1;

	for(int i = 0; i < len; i++)
	{
		if(list[i].idZona == id)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}

int buscarZonaPorIsEmpty(Zona list[], int len)
{
	int retorno = -1;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == VACIO)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

int buscarZonaPorLocalidad(Zona *list, int len, int localidad)
{
	int retorno = -1;

	for (int i = 0; i < len; i++)
	{
		if (list[i].localidad == localidad)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}

int buscarLocalidadEnArray(int list[], int len, int localidad)
{
	int retorno = -1;

	for (int i = 0; i < len; i++)
	{
		if (list[i] == localidad)
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}
