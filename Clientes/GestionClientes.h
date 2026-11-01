#pragma once
#include <string>
#include "Cliente.h"
#include "ListaEnlazada.h"

class GestionClientes
{
private:
    ListaEnlazada<Cliente*> clientes;

public:
    GestionClientes();
    ~GestionClientes();

    bool existeIdentificacion(std::string identificacion) const;
    Cliente* buscarPorIdentificacion(std::string identificacion) const;

    bool registrarPersona(std::string identificacion, std::string nombre, std::string telefono, std::string correo);
    bool registrarEmpresa(std::string identificacion, std::string nombre, std::string telefono, std::string correo,
        std::string actividadEconomica, double porcentajeDescuento);

    bool eliminar(std::string identificacion);

    std::string mostrarListado() const;
    int getCantidad() const;
    ListaEnlazada<Cliente*>* obtenerLista();
};
