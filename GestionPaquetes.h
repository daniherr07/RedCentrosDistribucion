#pragma once
#include <string>
#include "Paquete.h"
#include "ListaEnlazada.h"
#include "Bodega.h"

class Cliente;
class CentroDistribucion;
class Colaborador;

// Administra, para UN centro de distribucion, la lista enlazada de sus
// paquetes, y concentra las operaciones de almacenamiento, reubicacion e
// incidencias (todas ellas solo tocan Paquete/Bodega, por lo que no
// necesitan conocer el resto del centro).
class GestionPaquetes
{
private:
	ListaEnlazada<Paquete*> paquetes;

public:
	GestionPaquetes();
	~GestionPaquetes();

	bool existeCodigo(std::string codigo) const;
	Paquete* buscarPorCodigo(std::string codigo) const;

	Paquete* registrarPaquete(std::string codigo, std::string descripcion, double peso, TipoCategoria categoria,
		Cliente* clientePropietario, CentroDistribucion* centro);

	//Solo si el paquete sigue Recibido, sin celda asignada y sin dependencias (las dependencias las valida CentroDistribucion)
	bool eliminar(std::string codigo);

	//Acepta un paquete Recibido, o uno en Incidencia cuyo origen haya sido Recibido (se resuelve almacenando)
	bool almacenarPaquete(Paquete* paquete, Bodega* bodega, int fila, int columna, Colaborador* responsable);

	//Solo paquetes Almacenados; valida primero el destino y libera la celda vieja despues
	bool reubicarPaquete(Paquete* paquete, Bodega* nuevaBodega, int nuevaFila, int nuevaColumna);

	bool reportarIncidencia(std::string codigo, Colaborador* responsable);

	//Resuelve incidencias originadas en Almacenado o En transito. Si el origen fue Recibido, debe
	//resolverse llamando almacenarPaquete (por eso aqui se rechaza ese caso).
	bool resolverIncidencia(std::string codigo, Colaborador* responsable);

	std::string mostrarListado() const;
	int getCantidad() const;
	ListaEnlazada<Paquete*>* obtenerLista();
};
