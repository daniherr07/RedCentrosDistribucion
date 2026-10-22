#include "Despacho.h"
#include "Paquete.h"
#include <sstream>

std::string nombreEstadoDespacho(EstadoDespacho estado) {
	switch (estado) {
	case EstadoDespacho::EN_PROCESO: return "En proceso";
	case EstadoDespacho::FINALIZADO: return "Finalizado";
	default: return "Desconocido";
	}
}

Despacho::Despacho(std::string codigoNuevo, SolicitudEnvio* solicitudNueva, Paquete* paqueteNuevo, Cliente* clienteNuevo,
	Colaborador* colaboradorNuevo, CentroDistribucion* centroOrigenNuevo, std::string destinoNuevo, std::string horaNueva)
	: fechaDespacho(Fecha::hoy()) {
	codigo = codigoNuevo;
	solicitud = solicitudNueva;
	paquete = paqueteNuevo;
	cliente = clienteNuevo;
	colaborador = colaboradorNuevo;
	centroOrigen = centroOrigenNuevo;
	destino = destinoNuevo;
	hora = horaNueva;
	estado = EstadoDespacho::EN_PROCESO;
}

std::string Despacho::getCodigo() const { return codigo; }
SolicitudEnvio* Despacho::getSolicitud() const { return solicitud; }
Paquete* Despacho::getPaquete() const { return paquete; }
Cliente* Despacho::getCliente() const { return cliente; }
Colaborador* Despacho::getColaborador() const { return colaborador; }
CentroDistribucion* Despacho::getCentroOrigen() const { return centroOrigen; }
std::string Despacho::getDestino() const { return destino; }
Fecha Despacho::getFechaDespacho() const { return fechaDespacho; }
std::string Despacho::getHora() const { return hora; }
EstadoDespacho Despacho::getEstado() const { return estado; }

bool Despacho::finalizar() {
	if (estado == EstadoDespacho::FINALIZADO) {
		return false;
	}
	estado = EstadoDespacho::FINALIZADO;
	return true;
}

std::string Despacho::mostrar() const {
	std::ostringstream ss;
	ss << "Codigo: " << codigo
		<< " | Paquete: " << (paquete != nullptr ? paquete->getCodigo() : "N/A")
		<< " | Destino: " << destino
		<< " | Fecha: " << fechaDespacho.mostrar() << " " << hora
		<< " | Estado: " << nombreEstadoDespacho(estado);
	return ss.str();
}
