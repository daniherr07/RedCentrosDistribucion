#pragma once
#include <string>

class RedCentros;
class CentroDistribucion;
class Cliente;
class Colaborador;
class Paquete;

class Reportes
{
public:
	Reportes();

	std::string historialCliente(CentroDistribucion* centro, Cliente* cliente) const;
	std::string clientesPorCantidadEnvios(CentroDistribucion* centro) const;
	std::string bitacoraPaquete(Paquete* paquete) const;
	std::string consultaDespachoPaquete(CentroDistribucion* centro, Paquete* paquete) const;
	std::string ocupacionBodegas(RedCentros* red) const;
	std::string despachosPorColaborador(CentroDistribucion* centro, Colaborador* colaborador) const;
};
