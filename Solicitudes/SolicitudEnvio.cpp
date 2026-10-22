#include "SolicitudEnvio.h"
#include "Paquete.h"
#include <sstream>

std::string nombreEstadoSolicitud(EstadoSolicitud estado) {
	switch (estado) {
	case EstadoSolicitud::PENDIENTE: return "Pendiente";
	case EstadoSolicitud::APROBADA: return "Aprobada";
	case EstadoSolicitud::RECHAZADA: return "Rechazada";
	case EstadoSolicitud::ANULADA: return "Anulada";
	default: return "Desconocido";
	}
}

SolicitudEnvio::SolicitudEnvio(std::string codigoNuevo, Cliente* clienteNuevo, Paquete* paqueteNuevo, Colaborador* colaboradorNuevo,
	CentroDistribucion* centroOrigenNuevo, std::string destinoNuevo, double costoEstimadoNuevo)
	: fechaSolicitud(Fecha::hoy()) {
	codigo = codigoNuevo;
	cliente = clienteNuevo;
	paquete = paqueteNuevo;
	colaborador = colaboradorNuevo;
	centroOrigen = centroOrigenNuevo;
	destino = destinoNuevo;
	costoEstimado = costoEstimadoNuevo;
	estado = EstadoSolicitud::PENDIENTE;
}

std::string SolicitudEnvio::getCodigo() const { return codigo; }
Cliente* SolicitudEnvio::getCliente() const { return cliente; }
Paquete* SolicitudEnvio::getPaquete() const { return paquete; }
Colaborador* SolicitudEnvio::getColaborador() const { return colaborador; }
CentroDistribucion* SolicitudEnvio::getCentroOrigen() const { return centroOrigen; }
std::string SolicitudEnvio::getDestino() const { return destino; }
Fecha SolicitudEnvio::getFechaSolicitud() const { return fechaSolicitud; }
double SolicitudEnvio::getCostoEstimado() const { return costoEstimado; }
EstadoSolicitud SolicitudEnvio::getEstado() const { return estado; }

bool SolicitudEnvio::cambiarEstado(EstadoSolicitud nuevoEstado) {
	if (estado != EstadoSolicitud::PENDIENTE) { //Aprobada/Rechazada/Anulada son finales
		return false;
	}
	if (nuevoEstado == EstadoSolicitud::PENDIENTE) {
		return false;
	}
	estado = nuevoEstado;
	return true;
}

std::string SolicitudEnvio::mostrar() const {
	std::ostringstream ss;
	ss << "Codigo: " << codigo
		<< " | Paquete: " << (paquete != nullptr ? paquete->getCodigo() : "N/A")
		<< " | Destino: " << destino
		<< " | Fecha: " << fechaSolicitud.mostrar()
		<< " | Costo estimado: " << costoEstimado
		<< " | Estado: " << nombreEstadoSolicitud(estado);
	return ss.str();
}
