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

int ordenarPorNombreYEdad(Censista *list, int len)
{
	int retorno = -1;
	int i, j;
	int order;
	Censista auxCensista;

	utn_getNumero(&order,"\nOrden? (1.Menor a mayor, 2.Mayor a menor): ","\nERROR. Seleccione una opcion correcta.", 1, 2, 3);

	if(list != NULL && len > 0)
	{
		switch (order)
		{
		case 1: // menor a mayor
			for(i = 0; i < len - 1; i++)
			{
				for(j = i + 1; j < len; j++)
				{
					if(list[i].isEmpty == LLENO && list[j].isEmpty == LLENO)
					{
						if(strcmp(list[i].nombre, list[j].nombre) > 0)
						{
							auxCensista = list[i];
							list[i] = list[j];
							list[j] = auxCensista;
						}
						else if(strcmp(list[i].nombre, list[j].nombre) == 0 && list[i].edad > list[j].edad)
						{
							auxCensista = list[i];
							list[i] = list[j];
							list[j] = auxCensista;
						}
					}
				}
			}
			retorno = 0;
			mostrarCensistas(list, len);
			break;
		case 2: // mayor a menor
			for(i = 0; i < len - 1; i++)
			{
				for(j = i + 1; j < len; j++)
				{
					if(list[i].isEmpty == LLENO && list[j].isEmpty == LLENO)
					{
						if(strcmp(list[i].nombre, list[j].nombre) < 0)
						{
							auxCensista = list[i];
							list[i] = list[j];
							list[j] = auxCensista;
						}
						else if(strcmp(list[i].nombre, list[j].nombre) == 0 && list[i].edad < list[j].edad)
						{
							auxCensista = list[i];
							list[i] = list[j];
							list[j] = auxCensista;
						}
					}
				}
			}
			retorno = 0;
			mostrarCensistas(list, len);
			break;
		}
	}
	return retorno;
}
