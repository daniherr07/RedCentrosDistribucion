#pragma once
#include <string>
#include "Despacho.h"
#include "ListaEnlazada.h"

class GestionDespachos
{
private:
	ListaEnlazada<Despacho*> despachos;

public:
	GestionDespachos();
	~GestionDespachos();

	bool existeCodigo(std::string codigo) const;
	Despacho* buscarPorCodigo(std::string codigo) const;
	bool existeDespachoParaPaquete(Paquete* paquete) const;
	Despacho* buscarPorPaquete(Paquete* paquete) const;

	Despacho* crearDespacho(std::string codigo, SolicitudEnvio* solicitud, Paquete* paquete, Cliente* cliente,
		Colaborador* colaborador, CentroDistribucion* centroOrigen, std::string destino, std::string hora);

	bool finalizarEntrega(std::string codigo, Colaborador* responsableFinalizacion);

	std::string mostrarListado() const;
	int getCantidad() const;
	ListaEnlazada<Despacho*>* obtenerLista();
};
