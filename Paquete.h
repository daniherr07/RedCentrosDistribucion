#pragma once
#include <string>
#include "TipoCategoria.h"
#include "RegistroBitacora.h"
#include "ListaEnlazada.h"
#include "Bodega.h"

class Cliente;
class Colaborador;
class CentroDistribucion;

// Representa un paquete dentro del sistema. Ademas de sus datos basicos,
// guarda su bitacora de cambios de estado (lista enlazada propia, nunca
// se borran registros) y, mientras este Almacenado, la bodega+celda que
// ocupa.
class Paquete
{
private:
	std::string codigo;
	std::string descripcion;
	double peso;
	TipoCategoria categoria;
	Cliente* clientePropietario; //No es dueno, solo referencia
	CentroDistribucion* centro; //No es dueno, solo referencia

	EstadoPaquete estado;
	EstadoPaquete estadoPrevioIncidencia; //A que estado volver cuando se resuelva la Incidencia actual

	Bodega* bodegaAsignada; //nullptr si no esta almacenado
	int fila;
	int columna;

	ListaEnlazada<RegistroBitacora*> bitacora; //El paquete SI es dueno de sus registros de bitacora

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

	// Valida la transicion contra la tabla de estados y, si es valida,
	// agrega el registro correspondiente a la bitacora.
	bool cambiarEstado(EstadoPaquete nuevoEstado, Colaborador* responsable);

	// Pasa el paquete a Incidencia recordando desde que estado venia, para
	// que GestionPaquetes sepa como resolverla despues.
	bool reportarIncidencia(Colaborador* responsable);

	std::string mostrarBitacora() const;
	const ListaEnlazada<RegistroBitacora*>* obtenerBitacora() const;

	std::string mostrar() const;
};
