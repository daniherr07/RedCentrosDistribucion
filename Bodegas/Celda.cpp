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
	if (ocupada) { //Ya hay un paquete aqui, no se puede pisar
		return false;
	}
	paquete = paqueteNuevo;
	ocupada = true;
	return true;
}

bool Celda::liberar() {
	if (!ocupada) { //Ya estaba libre, nada que hacer
		return false;
	}
	paquete = nullptr;
	ocupada = false;
	return true;
}
