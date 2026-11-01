#pragma once

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
