#pragma once
#include <string>
#include "Fecha.h"

enum class EstadoPaquete
{
	RECIBIDO,
	ALMACENADO,
	EN_TRANSITO,
	ENTREGADO,
	INCIDENCIA
};

std::string nombreEstadoPaquete(EstadoPaquete estado);

class Colaborador;

class RegistroBitacora
{
private:
	EstadoPaquete estadoAnterior;
	EstadoPaquete estadoNuevo;
	Fecha fecha;
	Colaborador* responsable;

public:
	RegistroBitacora(EstadoPaquete estadoAnterior, EstadoPaquete estadoNuevo, Fecha fecha, Colaborador* responsable);

	EstadoPaquete getEstadoAnterior() const;
	EstadoPaquete getEstadoNuevo() const;
	Fecha getFecha() const;
	Colaborador* getResponsable() const;

	std::string mostrar() const;
};
