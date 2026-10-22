#pragma once
#include <string>
#include "Fecha.h"

enum class EstadoDespacho
{
	EN_PROCESO,
	FINALIZADO
};

std::string nombreEstadoDespacho(EstadoDespacho estado);

class SolicitudEnvio;
class Paquete;
class Cliente;
class Colaborador;
class CentroDistribucion;

// Un despacho se crea automaticamente al aprobar una solicitud (ver
// CentroDistribucion::aprobarSolicitud). Nace En proceso y solo puede
// pasar a Finalizado cuando el paquete asociado esta En transito.
class Despacho
{
private:
	std::string codigo;
	SolicitudEnvio* solicitud;
	Paquete* paquete;
	Cliente* cliente;
	Colaborador* colaborador;
	CentroDistribucion* centroOrigen;
	std::string destino;
	Fecha fechaDespacho;
	std::string hora;
	EstadoDespacho estado;

public:
	Despacho(std::string codigo, SolicitudEnvio* solicitud, Paquete* paquete, Cliente* cliente, Colaborador* colaborador,
		CentroDistribucion* centroOrigen, std::string destino, std::string hora);

	std::string getCodigo() const;
	SolicitudEnvio* getSolicitud() const;
	Paquete* getPaquete() const;
	Cliente* getCliente() const;
	Colaborador* getColaborador() const;
	CentroDistribucion* getCentroOrigen() const;
	std::string getDestino() const;
	Fecha getFechaDespacho() const;
	std::string getHora() const;
	EstadoDespacho getEstado() const;

	bool finalizar(); //false si ya estaba Finalizado

	std::string mostrar() const;
};
