#pragma once
#include <string>
#include "Fecha.h"

enum class EstadoSolicitud
{
	PENDIENTE,
	APROBADA,
	RECHAZADA,
	ANULADA
};

std::string nombreEstadoSolicitud(EstadoSolicitud estado);

class Cliente;
class Paquete;
class Colaborador;
class CentroDistribucion;

// Una solicitud de envio nace Pendiente y de ahi solo puede pasar a
// Aprobada, Rechazada o Anulada; esos tres estados son finales (ya no se
// puede volver a cambiar el estado de la solicitud).
class SolicitudEnvio
{
private:
	std::string codigo;
	Cliente* cliente;
	Paquete* paquete;
	Colaborador* colaborador;
	CentroDistribucion* centroOrigen;
	std::string destino;
	Fecha fechaSolicitud;
	double costoEstimado;
	EstadoSolicitud estado;

public:
	SolicitudEnvio(std::string codigo, Cliente* cliente, Paquete* paquete, Colaborador* colaborador,
		CentroDistribucion* centroOrigen, std::string destino, double costoEstimado);

	std::string getCodigo() const;
	Cliente* getCliente() const;
	Paquete* getPaquete() const;
	Colaborador* getColaborador() const;
	CentroDistribucion* getCentroOrigen() const;
	std::string getDestino() const;
	Fecha getFechaSolicitud() const;
	double getCostoEstimado() const;
	EstadoSolicitud getEstado() const;

	bool cambiarEstado(EstadoSolicitud nuevoEstado); //solo PENDIENTE -> {APROBADA,RECHAZADA,ANULADA}

	std::string mostrar() const;
};
