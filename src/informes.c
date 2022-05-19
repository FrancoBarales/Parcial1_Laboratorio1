/*
 * informes.c
 *
 *  Created on: 19 may. 2022
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

int ordenarPorNombreYApellido(Censista *listCensista, Zona *listZonas, int len)
{
	int retorno = -1;
	int i, j;
	int order;
	Censista auxCensista;

	utn_getNumero(&order,"\nOrden? (1.Menor a mayor, 2.Mayor a menor): ","\nERROR. Seleccione una opcion correcta.", 1, 2, 30);

	if(listCensista != NULL && len > 0)
	{
		switch (order)
		{
		case 1: // menor a mayor
			for(i = 0; i < len - 1; i++)
			{
				for(j = i + 1; j < len; j++)
				{
					if(listZonas[i].localidad == 2 || listZonas[i].localidad == 3 || listZonas[i].localidad == 4 || listZonas[i].localidad == 5)
					{
						if(listCensista[i].isEmpty == LLENO && listCensista[j].isEmpty == LLENO)
						{
							if(strcmp(listCensista[i].nombre, listCensista[j].nombre) > 0)
							{
								auxCensista = listCensista[i];
								listCensista[i] = listCensista[j];
								listCensista[j] = auxCensista;
							}
							else if(strcmp(listCensista[i].nombre, listCensista[j].nombre) == 0 && listCensista[i].apellido > listCensista[j].apellido)
							{
								auxCensista = listCensista[i];
								listCensista[i] = listCensista[j];
								listCensista[j] = auxCensista;
							}
						}
					}
				}
			}
			retorno = 0;
			mostrarCensistas(listCensista, len);
			break;
		case 2: // mayor a menor
			for(i = 0; i < len - 1; i++)
			{
				for(j = i + 1; j < len; j++)
				{
					if(listZonas[i].localidad == 2 || listZonas[i].localidad == 3 || listZonas[i].localidad == 4 || listZonas[i].localidad == 5)
					{
						if(listCensista[i].isEmpty == LLENO && listCensista[j].isEmpty == LLENO)
						{
							if(strcmp(listCensista[i].nombre, listCensista[j].nombre) < 0)
							{
								auxCensista = listCensista[i];
								listCensista[i] = listCensista[j];
								listCensista[j] = auxCensista;
							}
							else if(strcmp(listCensista[i].nombre, listCensista[j].nombre) == 0 && listCensista[i].apellido < listCensista[j].apellido)
							{
								auxCensista = listCensista[i];
								listCensista[i] = listCensista[j];
								listCensista[j] = auxCensista;
							}
						}
					}
				}
			}
			retorno = 0;
			mostrarCensistas(listCensista, len);
			break;
		}
	}
	return retorno;
}


int contarCensistasActivoYZonaPendiente(Censista *listCensista, Zona *listZonas, int len)
{
    int retorno = -1;
    int contador = 0;

    if(listCensista != NULL && listZonas != NULL && len > 0)
    {
        for(int i=0; i<len; i++)
        {
			if(strcmp(listCensista[i].estadoCensista, "ACTIVO") == 0)
			{
				if(strcmp(listZonas[i].estadoZona, "PENDIENTE") == 0)
				{
					contador++;
				}
			}
        }
        retorno = contador;
    }

    printf("\nHay %d Censistas en estado activo y zona pendiente.", contador);
    return retorno;
}

int localidadConMasCasasAusentes(Zona *listZonas, int len)
{
	int retorno = -1;
	int flag1 = 0;
	int mayorCantidadAusentes = 0;
	int localidadConMayorCantAusentes;

	if(listZonas != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(flag1 == 0)
			{
				mayorCantidadAusentes = listZonas[i].cantidadAusente;
				localidadConMayorCantAusentes = listZonas[i].localidad;
				flag1 = 1;
			}
			else if(listZonas[i].cantidadAusente > mayorCantidadAusentes)
			{
				mayorCantidadAusentes = listZonas[i].cantidadAusente;
				localidadConMayorCantAusentes = listZonas[i].localidad;
			}
		}
	}

	printf("\nLa localidad con mayor cantidad de ausentes es la localidad N°%d con %d ausentes.", localidadConMayorCantAusentes, mayorCantidadAusentes);
	return retorno;
}

int censistaConZonaMasCensada(Zona *listZonas, int len)
{
	int retorno = -1;
	int flag1 = 0;
	int cantidadZonaMasCensada;
	int idCensistaZonaMasCensada;

	if(listZonas != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(flag1 == 0)
			{
				cantidadZonaMasCensada = listZonas[i].cantidadInSitu + listZonas[i].cantidadVirtual;
				idCensistaZonaMasCensada = listZonas[i].idCensista;
				flag1 = 1;
			}
			else if((listZonas[i].cantidadInSitu + listZonas[i].cantidadVirtual) > cantidadZonaMasCensada)
			{
				cantidadZonaMasCensada = listZonas[i].cantidadInSitu + listZonas[i].cantidadVirtual;
				idCensistaZonaMasCensada = listZonas[i].idCensista;
			}
		}
	}

	printf("\nEl censista de Id N°%d tuvo la zona mas censada, con %d censados en total.", idCensistaZonaMasCensada, cantidadZonaMasCensada);
	return retorno;
}

int promedioCensosPorCensistaOZona(Censista *listCensistas, Zona *listZonas, int len)
{
	int retorno = -1;
	int order;
	int contadorZonas;
	int contadorCensistas;
	int censosPorCensista;
	int censosPorZona;
	float promedioCensistas;
	float promedioZonas;

	utn_getNumero(&order,"\nQue opcion desea? (1.Por Censista, 2.Por Zona): ","\nERROR. Seleccione una opcion correcta.", 1, 2, 30);

	if(listZonas != NULL && len > 0)
	{
		switch(order)
		{
			case 1:
				for(int i=0; i<len; i++)
				{
					if(listCensistas[i].idCensista != -1)
					{
						if(listZonas[i].idCensista == listCensistas[i].idCensista)
						{
							censosPorCensista++;
						}
					}
					contadorCensistas++;
				}
				promedioCensistas = censosPorCensista / contadorCensistas;

				printf("\nEl promedio de censos por censista es de %f censos.", promedioCensistas);
				break;
			case 2:
				for(int i=0; i<len; i++)
				{
					if(listZonas[i].idCensista != -1)
					{
						censosPorZona++;
					}
					contadorZonas++;
				}
				promedioZonas = censosPorZona / contadorZonas;

				printf("\nEl promedio de censos por zona es de %f censos.", promedioZonas);
				break;
		}
	}
	return retorno;
}

