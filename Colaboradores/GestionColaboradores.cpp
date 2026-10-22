#include "GestionColaboradores.h"
#include <sstream>

GestionColaboradores::GestionColaboradores()
{
}

GestionColaboradores::~GestionColaboradores()
{
    colaboradores.liberarPunteros();
}

bool GestionColaboradores::existeIdentificacion(std::string identificacion) const
{
    return buscarPorIdentificacion(identificacion) != nullptr;
}

Colaborador* GestionColaboradores::buscarPorIdentificacion(std::string identificacion) const
{
    Nodo<Colaborador*>* actual = colaboradores.getCabeza();
    while (actual != nullptr) {
        if (actual->getDato()->getIdentificacion() == identificacion) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool GestionColaboradores::registrar(std::string identificacion, std::string nombreCompleto, Fecha fechaIngreso, std::string puesto)
{
    if (identificacion.empty() || nombreCompleto.empty() || puesto.empty()) {
        return false;
    }
    if (existeIdentificacion(identificacion)) {
        return false;
    }

    Colaborador* nuevo = new Colaborador(identificacion, nombreCompleto, fechaIngreso, puesto);
    colaboradores.insertarAlFinal(nuevo);
    return true;
}

bool GestionColaboradores::eliminar(std::string identificacion)
{
    Colaborador* colaborador = buscarPorIdentificacion(identificacion);
    if (colaborador == nullptr) {
        return false;
    }
    colaboradores.eliminarDato(colaborador);
    delete colaborador;
    return true;
}

std::string GestionColaboradores::mostrarListado() const
{
    std::stringstream ss;

    if (colaboradores.estaVacia()) {
        ss << "No hay colaboradores registrados en este centro.\n";
        return ss.str();
    }

    ss << "----- LISTADO DE COLABORADORES (" << colaboradores.getCantidad() << ") -----\n";
    Nodo<Colaborador*>* actual = colaboradores.getCabeza();
    while (actual != nullptr) {
        ss << actual->getDato()->mostrar() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}

int GestionColaboradores::getCantidad() const
{
    return colaboradores.getCantidad();
}

ListaEnlazada<Colaborador*>* GestionColaboradores::obtenerLista()
{
    return &colaboradores;
}
