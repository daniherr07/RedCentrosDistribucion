#pragma once
#include "Nodo.h"

// Lista enlazada simple, generica y dinamica, de uso exclusivo de este
// proyecto (reemplaza a std::vector/std::list/std::map en todas las
// colecciones que el enunciado pide poder crecer en tiempo de ejecucion).
//
// Ownership: la lista NO libera automaticamente los datos que contiene
// (casi siempre T es un puntero a una entidad, p.ej. Cliente*, Paquete*),
// porque muchas veces ese mismo dato tambien vive referenciado desde otra
// lista (por ejemplo un Cliente* esta en la lista de GestionClientes, pero
// tambien lo apuntan los Paquete y las SolicitudEnvio, sin ser su dueno).
// Quien realmente es dueno de los objetos (los Gestion*) debe invocar
// liberarPunteros() en su propio destructor.
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

	// Elimina (sin liberar memoria del dato) el primer nodo cuyo dato sea
	// igual al recibido. Pensado para T = puntero, donde "==" compara
	// identidad (misma direccion de memoria).
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

	// Libera unicamente los nodos de la lista; el dato que contenian no se
	// toca (uso normal cuando la lista no es duena de sus datos).
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

	// Recorre la lista haciendo "delete" de cada dato apuntado y luego
	// libera los nodos. Debe usarse unicamente desde la clase que es
	// verdadera propietaria de esos objetos.
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
