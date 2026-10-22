#pragma once
#include <string>
#include "SolicitudEnvio.h"
#include "ListaEnlazada.h"

// Administra, para UN centro de distribucion, la lista enlazada de sus
// solicitudes de envio. Aqui se calcula el costo (peso * tarifa, con el
// descuento aplicado via el polimorfismo de Cliente::aplicarDescuento).
class GestionSolicitudes
{
private:
	ListaEnlazada<SolicitudEnvio*> solicitudes;

public:
	GestionSolicitudes();
	~GestionSolicitudes();

	bool existeCodigo(std::string codigo) const;
	SolicitudEnvio* buscarPorCodigo(std::string codigo) const;

	bool existePendienteParaPaquete(Paquete* paquete) const;
	bool existeAprobadaParaPaquete(Paquete* paquete) const;
	SolicitudEnvio* buscarAprobadaParaPaquete(Paquete* paquete) const;

	SolicitudEnvio* crearSolicitud(std::string codigo, Cliente* cliente, Paquete* paquete, Colaborador* colaborador,
		CentroDistribucion* centroOrigen, std::string destino);

	bool rechazar(std::string codigo);
	bool anular(std::string codigo);

	std::string mostrarListado() const;
	int getCantidad() const;
	ListaEnlazada<SolicitudEnvio*>* obtenerLista();
};
