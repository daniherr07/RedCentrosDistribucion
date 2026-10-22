#pragma once
#include <string>
#include "Colaborador.h"
#include "ListaEnlazada.h"

// Administra, para UN centro de distribucion, la lista enlazada de sus
// colaboradores. La identificacion del colaborador debe ser unica dentro
// de su centro.
class GestionColaboradores
{
private:
    ListaEnlazada<Colaborador*> colaboradores;

public:
    GestionColaboradores();
    ~GestionColaboradores();

    bool existeIdentificacion(std::string identificacion) const;
    Colaborador* buscarPorIdentificacion(std::string identificacion) const;

    bool registrar(std::string identificacion, std::string nombreCompleto, Fecha fechaIngreso, std::string puesto);

    // La validacion de que el colaborador no aparezca como responsable en
    // solicitudes, despachos o bitacoras la hace CentroDistribucion.
    bool eliminar(std::string identificacion);

    std::string mostrarListado() const;
    int getCantidad() const;
    ListaEnlazada<Colaborador*>* obtenerLista();
};
