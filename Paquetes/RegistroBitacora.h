#pragma once
#include <string>
#include "Fecha.h"

// Estados posibles de un paquete. Vive aqui (y no en Paquete.h) porque la
// bitacora tambien lo necesita y asi evitamos un include circular.
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

// Un registro de bitacora es inmutable una vez creado (el enunciado pide
// que no puedan eliminarse). Cada paquete guarda su propia lista enlazada
// de registros, en el mismo orden en que ocurrieron los cambios.
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
