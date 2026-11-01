#include "ClienteEmpresa.h"
#include <sstream>

ClienteEmpresa::ClienteEmpresa(std::string identificacion, std::string nombre, std::string telefono, std::string correo,
    std::string actividadEconomica, double porcentajeDescuento)
    : Cliente(identificacion, nombre, telefono, correo)
{
    this->actividadEconomica = actividadEconomica;
    this->porcentajeDescuento = porcentajeDescuento;
}

std::string ClienteEmpresa::getActividadEconomica() const { return actividadEconomica; }
double ClienteEmpresa::getPorcentajeDescuento() const { return porcentajeDescuento; }

double ClienteEmpresa::aplicarDescuento(double costoBase) const
{
    return costoBase - (costoBase * porcentajeDescuento / 100.0);
}

std::string ClienteEmpresa::getTipoCliente() const
{
    return "Empresa";
}

std::string ClienteEmpresa::mostrar() const
{
    std::stringstream ss;
    ss << Cliente::mostrar();
    ss << " | Actividad: " << actividadEconomica
        << " | Descuento: " << porcentajeDescuento << "%";
    return ss.str();
}
