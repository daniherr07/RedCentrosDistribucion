#pragma once
#include <string>
#include "Fecha.h"

class Colaborador
{
private:
    std::string identificacion;
    std::string nombreCompleto;
    Fecha fechaIngreso;
    std::string puesto;

public:
    Colaborador(std::string identificacion, std::string nombreCompleto, Fecha fechaIngreso, std::string puesto);

    std::string getIdentificacion() const;
    std::string getNombreCompleto() const;
    Fecha getFechaIngreso() const;
    std::string getPuesto() const;

    std::string mostrar() const;
};
