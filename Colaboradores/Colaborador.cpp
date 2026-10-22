#include "Colaborador.h"
#include <sstream>

Colaborador::Colaborador(std::string identificacion, std::string nombreCompleto, Fecha fechaIngreso, std::string puesto)
    : fechaIngreso(fechaIngreso)
{
    this->identificacion = identificacion;
    this->nombreCompleto = nombreCompleto;
    this->puesto = puesto;
}

std::string Colaborador::getIdentificacion() const { return identificacion; }
std::string Colaborador::getNombreCompleto() const { return nombreCompleto; }
Fecha Colaborador::getFechaIngreso() const { return fechaIngreso; }
std::string Colaborador::getPuesto() const { return puesto; }

std::string Colaborador::mostrar() const
{
    std::stringstream ss;
    ss << "ID: " << identificacion
        << " | Nombre: " << nombreCompleto
        << " | Puesto: " << puesto
        << " | Ingreso: " << fechaIngreso.mostrar();
    return ss.str();
}
