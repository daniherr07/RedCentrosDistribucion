#pragma once
#include <string>

class Cliente
{
protected:
    std::string identificacion;
    std::string nombre;
    std::string telefono;
    std::string correo;

public:
    Cliente(std::string identificacion, std::string nombre, std::string telefono, std::string correo);
    virtual ~Cliente();

    std::string getIdentificacion() const;
    std::string getNombre() const;
    std::string getTelefono() const;
    std::string getCorreo() const;

    virtual double aplicarDescuento(double costoBase) const;
    virtual std::string getTipoCliente() const = 0;
    virtual std::string mostrar() const;
};
