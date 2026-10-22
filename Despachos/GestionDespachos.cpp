#include "GestionDespachos.h"
#include "Paquete.h"
#include "CentroDistribucion.h"
#include <sstream>

GestionDespachos::GestionDespachos() {
}

GestionDespachos::~GestionDespachos() {
	despachos.liberarPunteros();
}

bool GestionDespachos::existeCodigo(std::string codigo) const {
	return buscarPorCodigo(codigo) != nullptr;
}

Despacho* GestionDespachos::buscarPorCodigo(std::string codigo) const {
	Nodo<Despacho*>* actual = despachos.getCabeza();
	while (actual != nullptr) {
		if (actual->getDato()->getCodigo() == codigo) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

bool GestionDespachos::existeDespachoParaPaquete(Paquete* paquete) const {
	return buscarPorPaquete(paquete) != nullptr;
}

Despacho* GestionDespachos::buscarPorPaquete(Paquete* paquete) const {
	Nodo<Despacho*>* actual = despachos.getCabeza();
	while (actual != nullptr) {
		if (actual->getDato()->getPaquete() == paquete) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

Despacho* GestionDespachos::crearDespacho(std::string codigo, SolicitudEnvio* solicitud, Paquete* paquete, Cliente* cliente,
	Colaborador* colaborador, CentroDistribucion* centroOrigen, std::string destino, std::string hora) {
	if (codigo.empty() || existeCodigo(codigo)) {
		return nullptr;
	}
	if (existeDespachoParaPaquete(paquete)) { //maximo un despacho por paquete
		return nullptr;
	}

	Despacho* nuevo = new Despacho(codigo, solicitud, paquete, cliente, colaborador, centroOrigen, destino, hora);
	despachos.insertarAlFinal(nuevo);
	return nuevo;
}

bool GestionDespachos::finalizarEntrega(std::string codigo, Colaborador* responsableFinalizacion) {
	Despacho* despacho = buscarPorCodigo(codigo);
	if (despacho == nullptr) {
		return false;
	}
	if (despacho->getEstado() != EstadoDespacho::EN_PROCESO) {
		return false;
	}
	if (despacho->getPaquete()->getEstado() != EstadoPaquete::EN_TRANSITO) {
		return false;
	}
	Paquete* paquete = despacho->getPaquete();
	if (responsableFinalizacion == nullptr
		|| paquete->getCentro()->getGestionColaboradores()->buscarPorIdentificacion(responsableFinalizacion->getIdentificacion()) != responsableFinalizacion) {
		return false; // el responsable debe pertenecer al centro del paquete
	}

	if (!despacho->finalizar()) {
		return false;
	}
	return despacho->getPaquete()->cambiarEstado(EstadoPaquete::ENTREGADO, responsableFinalizacion);
}

std::string GestionDespachos::mostrarListado() const {
	std::stringstream ss;

	if (despachos.estaVacia()) {
		ss << "No hay despachos registrados en este centro.\n";
		return ss.str();
	}

	ss << "----- LISTADO DE DESPACHOS (" << despachos.getCantidad() << ") -----\n";
	Nodo<Despacho*>* actual = despachos.getCabeza();
	while (actual != nullptr) {
		ss << actual->getDato()->mostrar() << "\n";
		actual = actual->getSiguiente();
	}
	return ss.str();
}

int GestionDespachos::getCantidad() const {
	return despachos.getCantidad();
}

ListaEnlazada<Despacho*>* GestionDespachos::obtenerLista() {
	return &despachos;
}
