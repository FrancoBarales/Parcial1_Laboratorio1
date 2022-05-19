/*
 * zona.h
 *
 *  Created on: 15 may. 2022
 *      Author: Franco
 */

#ifndef ZONA_H_
#define ZONA_H_

typedef struct
{
	int idZona;
	int idCensista;
	int localidad;
	int cantidadVirtual;
	int cantidadInSitu;
	int cantidadAusente;
	char estadoZona[10];
	int isEmpty;
}Zona;

int idZona(void);

int initZonas(Zona *list, int len);

int mostrarZonas(Zona *list, int len);

int agregarZona(Zona *list, int len, int idZona, int localidad, int idCensista);

int cargarDataZona(Zona *list, int len, int localidades[]);

int asignarZonaACensista(Zona *listZonas, Censista *listCensistas, int len);

int borrarZona(Zona *list, int len, int id);

int cargaDeDatos(Zona *list, Censista *listCensistas, int len);

int cargaForzadaZonas(Zona list[], int len);

int buscarZonaPorId(Zona *list, int len, int id);

int buscarZonaPorIsEmpty(Zona list[], int len);

int buscarZonaPorLocalidad(Zona *list, int len, int localidad);

int buscarLocalidadEnArray(int list[], int len, int localidad);

#endif /* ZONA_H_ */
