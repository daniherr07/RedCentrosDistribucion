#pragma once
#include <string>
#include "Paquete.h"
#include "ListaEnlazada.h"
#include "Bodega.h"

class Cliente;
class CentroDistribucion;
class Colaborador;

class GestionPaquetes
{
private:
	ListaEnlazada<Paquete*> paquetes;

public:
	GestionPaquetes();
	~GestionPaquetes();

	bool existeCodigo(std::string codigo) const;
	Paquete* buscarPorCodigo(std::string codigo) const;

	Paquete* registrarPaquete(std::string codigo, std::string descripcion, double peso, TipoCategoria categoria,
		Cliente* clientePropietario, CentroDistribucion* centro);

	bool eliminar(std::string codigo);

	bool almacenarPaquete(Paquete* paquete, Bodega* bodega, int fila, int columna, Colaborador* responsable);

	bool reubicarPaquete(Paquete* paquete, Bodega* nuevaBodega, int nuevaFila, int nuevaColumna);

	bool reportarIncidencia(std::string codigo, Colaborador* responsable);

	bool resolverIncidencia(std::string codigo, Colaborador* responsable);

	std::string mostrarListado() const;
	int getCantidad() const;
	ListaEnlazada<Paquete*>* obtenerLista();
};
