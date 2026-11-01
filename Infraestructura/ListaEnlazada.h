#pragma once
#include "Nodo.h"

template <typename T>
class ListaEnlazada
{
private:
	Nodo<T>* cabeza;
	Nodo<T>* cola;
	int cantidad;

public:
	ListaEnlazada() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

	~ListaEnlazada() {
		vaciar();
	}

	void insertarAlFinal(T dato) {
		Nodo<T>* nuevo = new Nodo<T>(dato);
		if (cabeza == nullptr) {
			cabeza = nuevo;
			cola = nuevo;
		}
		else {
			cola->setSiguiente(nuevo);
			cola = nuevo;
		}
		cantidad++;
	}

	bool eliminarDato(T dato) {
		Nodo<T>* actual = cabeza;
		Nodo<T>* anterior = nullptr;

		while (actual != nullptr) {
			if (actual->getDato() == dato) {
				if (anterior == nullptr) {
					cabeza = actual->getSiguiente();
				}
				else {
					anterior->setSiguiente(actual->getSiguiente());
				}
				if (actual == cola) {
					cola = anterior;
				}
				delete actual;
				cantidad--;
				return true;
			}
			anterior = actual;
			actual = actual->getSiguiente();
		}
		return false;
	}

	void vaciar() {
		Nodo<T>* actual = cabeza;
		while (actual != nullptr) {
			Nodo<T>* siguienteNodo = actual->getSiguiente();
			delete actual;
			actual = siguienteNodo;
		}
		cabeza = nullptr;
		cola = nullptr;
		cantidad = 0;
	}

	void liberarPunteros() {
		Nodo<T>* actual = cabeza;
		while (actual != nullptr) {
			delete actual->getDato();
			actual = actual->getSiguiente();
		}
		vaciar();
	}

	Nodo<T>* getCabeza() const { return cabeza; }
	int getCantidad() const { return cantidad; }
	bool estaVacia() const { return cantidad == 0; }
};
