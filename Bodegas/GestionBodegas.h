#pragma once
#include <string>
#include "Bodega.h"
#include "ListaEnlazada.h"

class GestionBodegas
{
private:
	ListaEnlazada<Bodega*> bodegas;

public:
	GestionBodegas();
	~GestionBodegas();

	bool existeCodigo(std::string codigo) const;
	Bodega* buscarPorCodigo(std::string codigo) const;

	bool registrarBodega(std::string codigo, std::string nombre, TipoCategoria tipo, int filas, int columnas);

	bool eliminar(std::string codigo);

	Bodega* mejorBodegaCompatible(TipoCategoria categoria) const;

	std::string mostrarListado() const;
	int getCantidad() const;
	ListaEnlazada<Bodega*>* obtenerLista();
};
