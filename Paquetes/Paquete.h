#pragma once
#include <string>
#include "TipoCategoria.h"
#include "RegistroBitacora.h"
#include "ListaEnlazada.h"
#include "Bodega.h"

class Cliente;
class Colaborador;
class CentroDistribucion;

class Paquete
{
private:
	std::string codigo;
	std::string descripcion;
	double peso;
	TipoCategoria categoria;
	Cliente* clientePropietario;
	CentroDistribucion* centro;

	EstadoPaquete estado;
	EstadoPaquete estadoPrevioIncidencia;

	Bodega* bodegaAsignada;
	int fila;
	int columna;

	ListaEnlazada<RegistroBitacora*> bitacora;

public:
	Paquete(std::string codigo, std::string descripcion, double peso, TipoCategoria categoria,
		Cliente* clientePropietario, CentroDistribucion* centro);
	~Paquete();

	std::string getCodigo() const;
	std::string getDescripcion() const;
	double getPeso() const;
	TipoCategoria getCategoria() const;
	Cliente* getClientePropietario() const;
	CentroDistribucion* getCentro() const;
	EstadoPaquete getEstado() const;
	EstadoPaquete getEstadoPrevioIncidencia() const;

	Bodega* getBodegaAsignada() const;
	int getFila() const;
	int getColumna() const;
	bool tieneUbicacion() const;

	void asignarUbicacion(Bodega* bodega, int filaNueva, int columnaNueva);
	void liberarUbicacion();

	static bool transicionValida(EstadoPaquete origen, EstadoPaquete destino);

	bool cambiarEstado(EstadoPaquete nuevoEstado, Colaborador* responsable);

	bool reportarIncidencia(Colaborador* responsable);

	std::string mostrarBitacora() const;
	const ListaEnlazada<RegistroBitacora*>* obtenerBitacora() const;

	std::string mostrar() const;
};
