#include "Fecha.h"
#include <sstream>
#include <iomanip>
#include <ctime>

Fecha::Fecha() {
	dia = 1;
	mes = 1;
	anio = 2026;
}

Fecha::Fecha(int dia, int mes, int anio) {
	this->dia = dia;
	this->mes = mes;
	this->anio = anio;
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

std::string Fecha::mostrar() const {
	std::ostringstream ss;
	ss << std::setfill('0') << std::setw(2) << dia << "/"
		<< std::setfill('0') << std::setw(2) << mes << "/"
		<< anio;
	return ss.str();
}

Fecha Fecha::hoy() {
	time_t ahora = time(nullptr);
	tm local;
	localtime_s(&local, &ahora); // version seguro de localtime en MSVC
	return Fecha(local.tm_mday, local.tm_mon + 1, local.tm_year + 1900);
}
