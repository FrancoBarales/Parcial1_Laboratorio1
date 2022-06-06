/*
 ============================================================================
 Name        : PARCIAL_1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "censista.h"
#include "zona.h"
#include "menus.h"
#include "utn.h"
#include "informes.h"


#define FALSE 0
#define TRUE 1

#define LENGTH 100

int main(void)
{
	setbuf(stdout, NULL);

	int flag1 = FALSE;
	int flag2 = FALSE;
	int flag3 = FALSE;
	int opcion;
	int opcionInformes;
	int localidades[50];
	Censista listaDeCensistas[LENGTH];
	Zona listaDeZonas[LENGTH];

	for(int i = 0; i < 50; i++)
	{
		localidades[i] = i;
	}
	initCensistas(listaDeCensistas, LENGTH);
	initZonas(listaDeZonas, LENGTH);
	do
	{
		opcion = menuPrincipal();
		switch(opcion)
		{
			case 1:
				cargarDataCensista(listaDeCensistas, LENGTH);
				flag1 = TRUE;
				break;
			case 2:
				if(flag1 == FALSE)
				{
					printf("\nERROR. No hay censistas cargados.\n");
				}
				else
				{
					modificarCensista(listaDeCensistas, LENGTH);
				}
				break;
			case 3:
				if(flag1 == FALSE)
				{
					printf("\nERROR. No hay censistas cargados.\n");
				}
				else
				{
					borrarCensista(listaDeCensistas, LENGTH);
				}
				break;
			case 4:
				cargarDataZona(listaDeZonas, LENGTH, localidades);
				flag2 = TRUE;
				break;
			case 5:
				if(flag1 == FALSE && flag2 == FALSE)
				{
					printf("\nERROR. No hay censistas ni zonas cargadas.\n");
				}
				else if(flag1 == FALSE)
				{
					printf("\nERROR. No hay censistas cargados.\n");
				}
				else if(flag2 == FALSE)
				{
					printf("\nERROR. No hay zonas cargadas.\n");
				}
				else
				{
					asignarZonaACensista(listaDeZonas, listaDeCensistas, LENGTH);
				}
				break;
			case 6:
				if(flag1 == FALSE || flag2 == FALSE)
				{
					printf("\nERROR. No hay censistas cargados y/o no hay zonas cargadas.\n");
				}
				else
				{
					cargaDeDatos(listaDeZonas, listaDeCensistas, LENGTH);
				}
				break;
			case 7:
				if(flag1 == FALSE)
				{
					printf("\nERROR. No hay censistas cargados.\n");
				}
				else
				{
					mostrarCensistas(listaDeCensistas, LENGTH);
				}
				break;
			case 8:
				if(flag2 == FALSE)
				{
					printf("\nERROR. No hay zonas cargadas.\n");
				}
				else
				{
					mostrarZonas(listaDeZonas, LENGTH);
				}
				break;
			case 9:
				if(flag3 == FALSE)
				{
					cargaForzadaCensistas(listaDeCensistas, LENGTH);
					cargaForzadaZonas(listaDeZonas, LENGTH);
					flag1 = TRUE;
					flag2 = TRUE;
					flag3 = TRUE;
					printf("\nCarga forzada realizada exitosamente.\n");
				}
				else
				{
					printf("\nERROR. La carga forzada ya fue realizada.\n");
				}
				break;
			case 10:
				if(flag1 == FALSE || flag2 == FALSE || flag2 == FALSE)
				{
					printf("\nERROR. Faltan ingresar datos (Opcion 1, 4 o 9).\n");
				}
				else
				{
					opcionInformes = menuInformes();
					switch(opcionInformes)
					{
						case 1:
							contarCensistasActivoYZonaPendiente(listaDeCensistas, listaDeZonas, LENGTH);
							break;
						case 2:
							ordenarPorNombreYApellido(listaDeCensistas, listaDeZonas, LENGTH);
							break;
						case 3:
							localidadConMasCasasAusentes(listaDeZonas, LENGTH);
							break;
						case 4:
							censistaConZonaMasCensada(listaDeZonas, LENGTH);
							break;
						case 5:
							promedioCensosPorCensistaOZona(listaDeCensistas, listaDeZonas, LENGTH);
							break;
					}
				}
				break;
		}
	}while(opcion != 11);

	return EXIT_SUCCESS;
}
