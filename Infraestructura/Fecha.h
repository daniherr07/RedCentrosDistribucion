#pragma once
#include <string>

// Representa una fecha simple (dia/mes/anio), suficiente para lo que pide
// el proyecto (fecha de ingreso, de solicitud, de despacho y de bitacora).
// No se usa ninguna libreria de fechas de la STL mas alla de <ctime> para
// leer la fecha real del sistema en Fecha::hoy().
class Fecha
{
private:
	int dia;
	int mes;
	int anio;

public:
	Fecha();
	Fecha(int dia, int mes, int anio);

	int getDia() const;
	int getMes() const;
	int getAnio() const;

	std::string mostrar() const;

	static Fecha hoy();
};
