/*
 * informes.h
 *
 *  Created on: 19 may. 2022
 *      Author: Franco
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int ordenarPorNombreYApellido(Censista *listCensista, Zona *listZonas, int len);

int contarCensistasActivoYZonaPendiente(Censista *listCensista, Zona *listZonas, int len);

int localidadConMasCasasAusentes(Zona *listZonas, int len);

int censistaConZonaMasCensada(Zona *listZonas, int len);

int promedioCensosPorCensistaOZona(Censista *listCensistas, Zona *listZonas, int len);

#endif /* INFORMES_H_ */
