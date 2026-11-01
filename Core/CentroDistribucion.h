#pragma once
#include <string>
#include "GestionClientes.h"
#include "GestionColaboradores.h"
#include "GestionBodegas.h"
#include "GestionPaquetes.h"
#include "GestionSolicitudes.h"
#include "GestionDespachos.h"

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

	bool tieneDependencias() const;

	bool eliminarCliente(std::string identificacion);
	bool eliminarColaborador(std::string identificacion);
	bool eliminarPaquete(std::string codigoPaquete);

	bool aprobarSolicitud(std::string codigoSolicitud, Colaborador* responsable, std::string codigoDespacho, std::string hora);

	std::string mostrarDatos() const;
};
