#include "Celda.h"

Celda::Celda() {
	fila = 0;
	columna = 0;
	ocupada = false;
	paquete = nullptr;
}

void Celda::inicializar(int filaNueva, int columnaNueva) {
	fila = filaNueva;
	columna = columnaNueva;
	ocupada = false;
	paquete = nullptr;
}

int Celda::getFila() const {
	return fila;
}

int Celda::getColumna() const {
	return columna;
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
