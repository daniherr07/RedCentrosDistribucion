#include "Cliente.h"
#include <sstream>

Cliente::Cliente(std::string identificacion, std::string nombre, std::string telefono, std::string correo)
{
    this->identificacion = identificacion;
    this->nombre = nombre;
    this->telefono = telefono;
    this->correo = correo;
}

Cliente::~Cliente()
{
    // No hay memoria propia que liberar; el destructor existe (y es
    // virtual) para que ClientePersona/ClienteEmpresa se destruyan
    // correctamente a traves de un puntero Cliente*.
}

std::string Cliente::getIdentificacion() const { return identificacion; }
std::string Cliente::getNombre() const { return nombre; }
std::string Cliente::getTelefono() const { return telefono; }
std::string Cliente::getCorreo() const { return correo; }

void Cliente::setNombre(std::string nombre)
{
    this->nombre = nombre;
}

void Cliente::setTelefono(std::string telefono)
{
    this->telefono = telefono;
}

void Cliente::setCorreo(std::string correo)
{
    this->correo = correo;
}

double Cliente::aplicarDescuento(double costoBase) const
{
    // Persona fisica: no hay descuento, el costo final es el costo base.
    return costoBase;
}

std::string Cliente::mostrar() const
{
    std::stringstream ss;
    ss << "ID: " << identificacion
        << " | Nombre: " << nombre
        << " | Telefono: " << telefono
        << " | Correo: " << correo
        << " | Tipo: " << getTipoCliente();
    return ss.str();
}
