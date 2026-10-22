#pragma once
#include <string>
#include "CentroDistribucion.h"
#include "ListaEnlazada.h"

// Clase raiz del sistema: mantiene la lista enlazada de todos los centros
// de distribucion (la "Red"). Tambien resuelve las busquedas y
// validaciones de unicidad que son GLOBALES al sistema (paquete,
// solicitud y despacho se identifican por un codigo unico en toda la red,
// no solo dentro de un centro), recorriendo los centros uno por uno.
class RedCentros
{
private:
	ListaEnlazada<CentroDistribucion*> centros;

public:
	RedCentros();
	~RedCentros();

	bool existeCodigoCentro(std::string codigo) const;
	CentroDistribucion* buscarCentroPorCodigo(std::string codigo) const;

	bool registrarCentro(std::string codigo, std::string nombre, std::string provincia, std::string direccion, std::string telefono);
	bool eliminarCentro(std::string codigo);

	std::string mostrarListado() const;
	int getCantidad() const;
	ListaEnlazada<CentroDistribucion*>* obtenerLista();

	bool existeCodigoPaqueteGlobal(std::string codigo) const;
	Paquete* buscarPaqueteGlobal(std::string codigo) const;

	bool existeCodigoSolicitudGlobal(std::string codigo) const;
	SolicitudEnvio* buscarSolicitudGlobal(std::string codigo) const;

	bool existeCodigoDespachoGlobal(std::string codigo) const;
	Despacho* buscarDespachoGlobal(std::string codigo) const;

	// Carga datos de ejemplo ("quemados") para agilizar las pruebas, tal
	// como recomienda el enunciado. No reemplaza las opciones de menu
	// para ingresar datos nuevos, que siguen estando disponibles.
	void cargarDatosDePrueba();
};
