#pragma once
#include <string>
#include "Fecha.h"

// Colaborador de un centro de distribucion. No participa de la jerarquia
// de Cliente (son conceptos distintos en el enunciado); se identifica
// dentro de su propio centro y es quien aparece como responsable en la
// bitacora de un paquete, en las solicitudes y en los despachos.
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

    void setPuesto(std::string puesto);

    std::string mostrar() const;
};
