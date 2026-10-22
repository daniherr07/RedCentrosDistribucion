#pragma once
#include <string>
#include "Bodega.h"
#include "ListaEnlazada.h"

// Administra, para UN centro de distribucion, la lista enlazada de sus
// bodegas. El codigo propio de la bodega es unico dentro del centro (y es
// distinto del codigo numerico de tipo de bodega).
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

	//Solo elimina si todas las celdas estan libres (y por lo tanto ningun paquete la tiene asignada)
	bool eliminar(std::string codigo);

	//Entre las bodegas compatibles con la categoria, la de mayor % disponible con al menos una celda libre
	Bodega* mejorBodegaCompatible(TipoCategoria categoria) const;

	std::string mostrarListado() const;
	int getCantidad() const;
	ListaEnlazada<Bodega*>* obtenerLista();
};
