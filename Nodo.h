#pragma once

// Nodo generico para las listas enlazadas simples del proyecto.
// Es una plantilla propia del equipo (no es parte de la STL): el curso
// solo prohibe contenedores/algoritmos de la STL, no el uso de templates
// propios para evitar repetir la misma clase once veces.
template <typename T>
class Nodo
{
private:
	T dato;
	Nodo<T>* siguiente;

public:
	Nodo(T dato) : dato(dato), siguiente(nullptr) {}

	T getDato() const { return dato; }
	void setDato(T nuevoDato) { dato = nuevoDato; }

	Nodo<T>* getSiguiente() const { return siguiente; }
	void setSiguiente(Nodo<T>* nuevoSiguiente) { siguiente = nuevoSiguiente; }
};
