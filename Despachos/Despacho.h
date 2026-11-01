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

	bool finalizar();

	std::string mostrar() const;
};
