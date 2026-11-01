#pragma once
#include <string>
#include "Colaborador.h"
#include "ListaEnlazada.h"

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

    bool eliminar(std::string identificacion);

    std::string mostrarListado() const;
    int getCantidad() const;
    ListaEnlazada<Colaborador*>* obtenerLista();
};
