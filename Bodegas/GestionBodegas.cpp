#include "GestionBodegas.h"
#include <sstream>

GestionBodegas::GestionBodegas() {
}

GestionBodegas::~GestionBodegas() {
	bodegas.liberarPunteros();
}

bool GestionBodegas::existeCodigo(std::string codigo) const {
	return buscarPorCodigo(codigo) != nullptr;
}

Bodega* GestionBodegas::buscarPorCodigo(std::string codigo) const {
	Nodo<Bodega*>* actual = bodegas.getCabeza();
	while (actual != nullptr) {
		if (actual->getDato()->getCodigo() == codigo) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

bool GestionBodegas::registrarBodega(std::string codigo, std::string nombre, TipoCategoria tipo, int filas, int columnas) {
	if (codigo.empty() || nombre.empty()) {
		return false;
	}
	if (filas <= 0 || columnas <= 0) { //el enunciado exige filas y columnas enteras mayores que cero
		return false;
	}
	if (existeCodigo(codigo)) {
		return false;
	}

	Bodega* nueva = new Bodega(codigo, nombre, tipo, filas, columnas);
	bodegas.insertarAlFinal(nueva);
	return true;
}

bool GestionBodegas::eliminar(std::string codigo) {
	Bodega* bodega = buscarPorCodigo(codigo);
	if (bodega == nullptr) {
		return false;
	}
	if (!bodega->todasLasCeldasLibres()) { //hay al menos un paquete almacenado ahi, no se puede borrar
		return false;
	}

	bodegas.eliminarDato(bodega);
	delete bodega;
	return true;
}

Bodega* GestionBodegas::mejorBodegaCompatible(TipoCategoria categoria) const {
	Bodega* mejor = nullptr;
	double mejorPorcentaje = -1.0;

	Nodo<Bodega*>* actual = bodegas.getCabeza();
	while (actual != nullptr) {
		Bodega* candidata = actual->getDato();
		if (candidata->esCompatible(categoria) && candidata->contarLibres() > 0) {
			if (candidata->porcentajeDisponible() > mejorPorcentaje) {
				mejorPorcentaje = candidata->porcentajeDisponible();
				mejor = candidata;
			}
		}
		actual = actual->getSiguiente();
	}
	return mejor;
}

std::string GestionBodegas::mostrarListado() const {
	std::stringstream ss;

	if (bodegas.estaVacia()) {
		ss << "No hay bodegas registradas en este centro.\n";
		return ss.str();
	}

	ss << "----- LISTADO DE BODEGAS (" << bodegas.getCantidad() << ") -----\n";
	Nodo<Bodega*>* actual = bodegas.getCabeza();
	while (actual != nullptr) {
		Bodega* b = actual->getDato();
		ss << "Codigo: " << b->getCodigo()
			<< " | Nombre: " << b->getNombre()
			<< " | Tipo: " << nombreCategoria(b->getTipo())
			<< " | Distribucion: " << b->getFilas() << "x" << b->getColumnas()
			<< " | Ocupacion: " << b->porcentajeOcupacion() << "%\n";
		actual = actual->getSiguiente();
	}
	return ss.str();
}

int GestionBodegas::getCantidad() const {
	return bodegas.getCantidad();
}

ListaEnlazada<Bodega*>* GestionBodegas::obtenerLista() {
	return &bodegas;
}
