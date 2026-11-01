#pragma once
#include <string>
#include "CentroDistribucion.h"
#include "ListaEnlazada.h"

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

	void cargarDatosDePrueba();
};
