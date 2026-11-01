#include "Celda.h"

Celda::Celda() {
	ocupada = false;
	paquete = nullptr;
}

bool Celda::estaOcupada() const {
	return ocupada;
}

Paquete* Celda::getPaquete() const {
	return paquete;
}

bool Celda::asignar(Paquete* paqueteNuevo) {
	if (ocupada) {
		return false;
	}
	paquete = paqueteNuevo;
	ocupada = true;
	return true;
}

bool Celda::liberar() {
	if (!ocupada) {
		return false;
	}
	paquete = nullptr;
	ocupada = false;
	return true;
}
