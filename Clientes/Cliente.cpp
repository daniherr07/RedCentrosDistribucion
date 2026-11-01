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
}

std::string Cliente::getIdentificacion() const { return identificacion; }
std::string Cliente::getNombre() const { return nombre; }
std::string Cliente::getTelefono() const { return telefono; }
std::string Cliente::getCorreo() const { return correo; }

double Cliente::aplicarDescuento(double costoBase) const
{
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
