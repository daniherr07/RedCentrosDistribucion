#pragma once
#include <string>

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
