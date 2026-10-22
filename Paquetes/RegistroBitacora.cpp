#include "RegistroBitacora.h"
#include "Colaborador.h"
#include <sstream>

std::string nombreEstadoPaquete(EstadoPaquete estado) {
	switch (estado) {
	case EstadoPaquete::RECIBIDO: return "Recibido";
	case EstadoPaquete::ALMACENADO: return "Almacenado";
	case EstadoPaquete::EN_TRANSITO: return "En transito";
	case EstadoPaquete::ENTREGADO: return "Entregado";
	case EstadoPaquete::INCIDENCIA: return "Incidencia";
	default: return "Desconocido";
	}
}

RegistroBitacora::RegistroBitacora(EstadoPaquete estadoAnteriorNuevo, EstadoPaquete estadoNuevoNuevo, Fecha fechaNueva, Colaborador* responsableNuevo)
	: fecha(fechaNueva) {
	estadoAnterior = estadoAnteriorNuevo;
	estadoNuevo = estadoNuevoNuevo;
	responsable = responsableNuevo;
}

EstadoPaquete RegistroBitacora::getEstadoAnterior() const {
	return estadoAnterior;
}

EstadoPaquete RegistroBitacora::getEstadoNuevo() const {
	return estadoNuevo;
}

Fecha RegistroBitacora::getFecha() const {
	return fecha;
}

Colaborador* RegistroBitacora::getResponsable() const {
	return responsable;
}

std::string RegistroBitacora::mostrar() const {
	std::ostringstream ss;
	ss << "\t[" << fecha.mostrar() << "] " << nombreEstadoPaquete(estadoAnterior)
		<< " -> " << nombreEstadoPaquete(estadoNuevo)
		<< " (Responsable: " << (responsable != nullptr ? responsable->getNombreCompleto() : "N/A") << ")\n";
	return ss.str();
}
