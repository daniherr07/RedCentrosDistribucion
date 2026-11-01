#include "GestionSolicitudes.h"
#include "Paquete.h"
#include "Cliente.h"
#include "Tarifas.h"
#include "CentroDistribucion.h"
#include <sstream>

GestionSolicitudes::GestionSolicitudes() {
}

GestionSolicitudes::~GestionSolicitudes() {
	solicitudes.liberarPunteros();
}

bool GestionSolicitudes::existeCodigo(std::string codigo) const {
	return buscarPorCodigo(codigo) != nullptr;
}

SolicitudEnvio* GestionSolicitudes::buscarPorCodigo(std::string codigo) const {
	Nodo<SolicitudEnvio*>* actual = solicitudes.getCabeza();
	while (actual != nullptr) {
		if (actual->getDato()->getCodigo() == codigo) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

bool GestionSolicitudes::existePendienteParaPaquete(Paquete* paquete) const {
	Nodo<SolicitudEnvio*>* actual = solicitudes.getCabeza();
	while (actual != nullptr) {
		if (actual->getDato()->getPaquete() == paquete && actual->getDato()->getEstado() == EstadoSolicitud::PENDIENTE) {
			return true;
		}
		actual = actual->getSiguiente();
	}
	return false;
}

bool GestionSolicitudes::existeAprobadaParaPaquete(Paquete* paquete) const {
	return buscarAprobadaParaPaquete(paquete) != nullptr;
}

SolicitudEnvio* GestionSolicitudes::buscarAprobadaParaPaquete(Paquete* paquete) const {
	Nodo<SolicitudEnvio*>* actual = solicitudes.getCabeza();
	while (actual != nullptr) {
		if (actual->getDato()->getPaquete() == paquete && actual->getDato()->getEstado() == EstadoSolicitud::APROBADA) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

SolicitudEnvio* GestionSolicitudes::crearSolicitud(std::string codigo, Cliente* cliente, Paquete* paquete, Colaborador* colaborador,
	CentroDistribucion* centroOrigen, std::string destino) {
	if (codigo.empty() || destino.empty()) {
		return nullptr;
	}
	if (cliente == nullptr || paquete == nullptr || colaborador == nullptr) {
		return nullptr;
	}
	if (existeCodigo(codigo)) {
		return nullptr;
	}
	if (paquete->getEstado() != EstadoPaquete::ALMACENADO) {
		return nullptr;
	}
	if (paquete->getClientePropietario() != cliente) {
		return nullptr;
	}
	if (paquete->getCentro() != centroOrigen) {
		return nullptr;
	}
	if (centroOrigen->getGestionColaboradores()->buscarPorIdentificacion(colaborador->getIdentificacion()) != colaborador) {
		return nullptr;
	}
	if (existePendienteParaPaquete(paquete)) {
		return nullptr;
	}
	if (existeAprobadaParaPaquete(paquete)) {
		return nullptr;
	}

	double costoBase = paquete->getPeso() * Tarifas::tarifaPorCategoria(paquete->getCategoria());
	double costoFinal = cliente->aplicarDescuento(costoBase);

	SolicitudEnvio* nueva = new SolicitudEnvio(codigo, cliente, paquete, colaborador, centroOrigen, destino, costoFinal);
	solicitudes.insertarAlFinal(nueva);
	return nueva;
}

bool GestionSolicitudes::rechazar(std::string codigo) {
	SolicitudEnvio* solicitud = buscarPorCodigo(codigo);
	if (solicitud == nullptr) {
		return false;
	}
	return solicitud->cambiarEstado(EstadoSolicitud::RECHAZADA);
}

bool GestionSolicitudes::anular(std::string codigo) {
	SolicitudEnvio* solicitud = buscarPorCodigo(codigo);
	if (solicitud == nullptr) {
		return false;
	}
	return solicitud->cambiarEstado(EstadoSolicitud::ANULADA);
}

std::string GestionSolicitudes::mostrarListado() const {
	std::stringstream ss;

	if (solicitudes.estaVacia()) {
		ss << "No hay solicitudes de envio registradas en este centro.\n";
		return ss.str();
	}

	ss << "solicitudes registradas (" << solicitudes.getCantidad() << "):\n";
	Nodo<SolicitudEnvio*>* actual = solicitudes.getCabeza();
	while (actual != nullptr) {
		ss << actual->getDato()->mostrar() << "\n";
		actual = actual->getSiguiente();
	}
	return ss.str();
}

int GestionSolicitudes::getCantidad() const {
	return solicitudes.getCantidad();
}

ListaEnlazada<SolicitudEnvio*>* GestionSolicitudes::obtenerLista() {
	return &solicitudes;
}
