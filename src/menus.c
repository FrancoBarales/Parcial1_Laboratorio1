/*
 * menus.c
 *
 *  Created on: 17 may. 2022
 *      Author: Franco
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"

int menuPrincipal(void)
{
	int opcion;
	printf("\n\nMenu de opciones\n");
	printf("\n1.Cargar censista");
	printf("\n2.Modificar censista");
	printf("\n3.Dar de baja censista");
	printf("\n4.Cargar zona");
	printf("\n5.Asignar zona a censar");
	printf("\n6.Carga de datos");
	printf("\n7.Mostrar censistas");
	printf("\n8.Mostrar zonas");
	printf("\n9.Carga forzada de censistas y zonas");
	printf("\n10.Menu de informes");
	printf("\n11.Salir\n");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Seleccione una opcion correcta.", 1, 11, 3);
	return opcion;
}

int menuModificarCensista(void)
{
	int opcion;
	printf("\n\nQue dato desea modificar?\n");
	printf("\n1.Nombre");
	printf("\n2.Apellido");
	printf("\n3.Fecha de nacimiento");
	printf("\n4.Edad");
	printf("\n5.Direccion");
	printf("\n6.Salir\n");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Seleccione una opcion correcta.", 1, 6, 3);
	return opcion;
}

int menuModificarFechaCensista(void)
{
	int opcion;
	printf("\n\nQue dato desea modificar?\n");
	printf("\n1.Dia");
	printf("\n2.Mes");
	printf("\n3.Anio");
	printf("\n4.Salir");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Seleccione una opcion correcta.", 1, 4, 3);
	return opcion;
}

int menuModificarDireccionCensista(void)
{
	int opcion;
	printf("\n\nQue dato desea modificar?\n");
	printf("\n1.Direccion");
	printf("\n2.Altura");
	printf("\n3.Salir");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Seleccione una opcion correcta.", 1, 3, 3);
	return opcion;
}

int menuInformes(void)
{
	int opcion;
	printf("\n\nQue informe precisa?\n");
	printf("\n1.Informar cantidad de censistas en estado Activo con zona Pendiente.");
	printf("\n2.Ordenar alfabéticamente por apellido y nombre los censistas de localidad N°2,3,4,5.");
	printf("\n3.Informar nombre de localidad con más casas ausentes.");
	printf("\n4.Informar el censista cuya zona fue la más censada.");
	printf("\n5.Informar el promedio de censos por censista/zona.");
	printf("\n6.Salir\n");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Seleccione una opcion correcta.", 1, 6, 3);
	return opcion;
}
