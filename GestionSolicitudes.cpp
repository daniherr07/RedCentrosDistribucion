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
	if (paquete->getEstado() != EstadoPaquete::ALMACENADO) { //solo se puede solicitar envio de un paquete Almacenado
		return nullptr;
	}
	if (paquete->getClientePropietario() != cliente) { //el cliente debe ser el dueno del paquete
		return nullptr;
	}
	if (paquete->getCentro() != centroOrigen) { //el centro de origen debe ser el del paquete
		return nullptr;
	}
	if (centroOrigen->getGestionColaboradores()->buscarPorIdentificacion(colaborador->getIdentificacion()) != colaborador) {
		return nullptr; //el colaborador responsable debe pertenecer a ese mismo centro
	}
	if (existePendienteParaPaquete(paquete)) { //solo una solicitud Pendiente a la vez por paquete
		return nullptr;
	}
	if (existeAprobadaParaPaquete(paquete)) { //ya existe una Aprobada (y por lo tanto su despacho), no se permiten mas
		return nullptr;
	}

	double costoBase = paquete->getPeso() * Tarifas::tarifaPorCategoria(paquete->getCategoria());
	double costoFinal = cliente->aplicarDescuento(costoBase); //polimorfismo: Empresa aplica su descuento, Persona no

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

	ss << "----- LISTADO DE SOLICITUDES (" << solicitudes.getCantidad() << ") -----\n";
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
