#pragma once
#include <string>
#include "GestionClientes.h"
#include "GestionColaboradores.h"
#include "GestionBodegas.h"
#include "GestionPaquetes.h"
#include "GestionSolicitudes.h"
#include "GestionDespachos.h"

// Un centro de distribucion mantiene sus propias colecciones (clientes,
// colaboradores, bodegas, paquetes, solicitudes y despachos); cada una de
// esas colecciones vive dentro de su respectiva clase "Gestion*".
//
// Esta clase ademas coordina las operaciones que cruzan varios modulos a
// la vez: aprobar una solicitud toca Paquete + Bodega + SolicitudEnvio +
// Despacho, y eliminar un cliente/colaborador/paquete requiere revisar las
// demas colecciones del centro en busca de referencias pendientes.
class CentroDistribucion
{
private:
	std::string codigo;
	std::string nombre;
	std::string provincia;
	std::string direccion;
	std::string telefono;

	GestionClientes* clientes;
	GestionColaboradores* colaboradores;
	GestionBodegas* bodegas;
	GestionPaquetes* paquetes;
	GestionSolicitudes* solicitudes;
	GestionDespachos* despachos;

public:
	CentroDistribucion(std::string codigo, std::string nombre, std::string provincia, std::string direccion, std::string telefono);
	~CentroDistribucion();

	std::string getCodigo() const;
	std::string getNombre() const;
	std::string getProvincia() const;
	std::string getDireccion() const;
	std::string getTelefono() const;

	GestionClientes* getGestionClientes() const;
	GestionColaboradores* getGestionColaboradores() const;
	GestionBodegas* getGestionBodegas() const;
	GestionPaquetes* getGestionPaquetes() const;
	GestionSolicitudes* getGestionSolicitudes() const;
	GestionDespachos* getGestionDespachos() const;

	// true si tiene algun cliente, colaborador, bodega, paquete, solicitud
	// o despacho asociado (impide eliminar el centro completo).
	bool tieneDependencias() const;

	bool eliminarCliente(std::string identificacion);
	bool eliminarColaborador(std::string identificacion);
	bool eliminarPaquete(std::string codigoPaquete);

	// Aprueba una solicitud Pendiente, crea su despacho asociado y mueve
	// el paquete a En transito liberando su celda. Devuelve false si no
	// se cumple alguna de las condiciones de la seccion 9 del enunciado.
	bool aprobarSolicitud(std::string codigoSolicitud, Colaborador* responsable, std::string codigoDespacho, std::string hora);

	std::string mostrarDatos() const;
};
