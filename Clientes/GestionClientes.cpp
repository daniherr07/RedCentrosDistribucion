#include "GestionClientes.h"
#include "ClientePersona.h"
#include "ClienteEmpresa.h"
#include <sstream>

GestionClientes::GestionClientes()
{
}

GestionClientes::~GestionClientes()
{
    clientes.liberarPunteros();
}

bool GestionClientes::existeIdentificacion(std::string identificacion) const
{
    return buscarPorIdentificacion(identificacion) != nullptr;
}

Cliente* GestionClientes::buscarPorIdentificacion(std::string identificacion) const
{
    Nodo<Cliente*>* actual = clientes.getCabeza();
    while (actual != nullptr) {
        if (actual->getDato()->getIdentificacion() == identificacion) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool GestionClientes::registrarPersona(std::string identificacion, std::string nombre, std::string telefono, std::string correo)
{
    if (identificacion.empty() || nombre.empty() || telefono.empty()) {
        return false;
    }
    if (existeIdentificacion(identificacion)) {
        return false;
    }

    Cliente* nuevo = new ClientePersona(identificacion, nombre, telefono, correo);
    clientes.insertarAlFinal(nuevo);
    return true;
}

bool GestionClientes::registrarEmpresa(std::string identificacion, std::string nombre, std::string telefono, std::string correo,
    std::string actividadEconomica, double porcentajeDescuento)
{
    if (identificacion.empty() || nombre.empty() || telefono.empty() || actividadEconomica.empty()) {
        return false;
    }
    if (porcentajeDescuento < 0.0 || porcentajeDescuento > 100.0) {
        return false;
    }
    if (existeIdentificacion(identificacion)) {
        return false;
    }

    Cliente* nuevo = new ClienteEmpresa(identificacion, nombre, telefono, correo, actividadEconomica, porcentajeDescuento);
    clientes.insertarAlFinal(nuevo);
    return true;
}

bool GestionClientes::eliminar(std::string identificacion)
{
    Cliente* cliente = buscarPorIdentificacion(identificacion);
    if (cliente == nullptr) {
        return false;
    }
    clientes.eliminarDato(cliente);
    delete cliente;
    return true;
}

std::string GestionClientes::mostrarListado() const
{
    std::stringstream ss;

    if (clientes.estaVacia()) {
        ss << "No hay clientes registrados en este centro.\n";
        return ss.str();
    }

    ss << "----- LISTADO DE CLIENTES (" << clientes.getCantidad() << ") -----\n";
    Nodo<Cliente*>* actual = clientes.getCabeza();
    while (actual != nullptr) {
        ss << actual->getDato()->mostrar() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}

int GestionClientes::getCantidad() const
{
    return clientes.getCantidad();
}

ListaEnlazada<Cliente*>* GestionClientes::obtenerLista()
{
    return &clientes;
}
