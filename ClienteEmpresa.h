#pragma once
#include "Cliente.h"

// Cliente empresa: agrega actividad economica y el porcentaje de
// descuento autorizado (0-100), y sobreescribe aplicarDescuento() para
// que el costo de sus solicitudes de envio se calcule con ese porcentaje.
class ClienteEmpresa : public Cliente
{
private:
    std::string actividadEconomica;
    double porcentajeDescuento;

public:
    ClienteEmpresa(std::string identificacion, std::string nombre, std::string telefono, std::string correo,
        std::string actividadEconomica, double porcentajeDescuento);

    std::string getActividadEconomica() const;
    double getPorcentajeDescuento() const;
    void setPorcentajeDescuento(double porcentajeDescuento);

    double aplicarDescuento(double costoBase) const override;
    std::string getTipoCliente() const override;
    std::string mostrar() const override;
};
