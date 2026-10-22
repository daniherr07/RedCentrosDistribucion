#pragma once
#include <string>
#include "Despacho.h"
#include "ListaEnlazada.h"

// Administra, para UN centro de distribucion, la lista enlazada de sus
// despachos. No permite eliminar nada (el enunciado lo prohibe para
// despachos y bitacoras); solo se crean y se finalizan.
class GestionDespachos
{
private:
	ListaEnlazada<Despacho*> despachos;

public:
	GestionDespachos();
	~GestionDespachos();

	bool existeCodigo(std::string codigo) const;
	Despacho* buscarPorCodigo(std::string codigo) const;
	bool existeDespachoParaPaquete(Paquete* paquete) const; //cada paquete puede tener como maximo un despacho
	Despacho* buscarPorPaquete(Paquete* paquete) const;

	Despacho* crearDespacho(std::string codigo, SolicitudEnvio* solicitud, Paquete* paquete, Cliente* cliente,
		Colaborador* colaborador, CentroDistribucion* centroOrigen, std::string destino, std::string hora);

	//Solo si el despacho sigue En proceso y el paquete esta En transito
	bool finalizarEntrega(std::string codigo, Colaborador* responsableFinalizacion);

	std::string mostrarListado() const;
	int getCantidad() const;
	ListaEnlazada<Despacho*>* obtenerLista();
};
