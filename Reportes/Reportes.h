#pragma once
#include <string>

class RedCentros;
class CentroDistribucion;
class Cliente;
class Colaborador;
class Paquete;

// No es dueno de nada: solo recibe punteros (centro, cliente, paquete,
// colaborador, o la red completa) y arma los 6 reportes pedidos devolviendo
// siempre un std::string (quien llama decide cuando imprimirlo).
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
