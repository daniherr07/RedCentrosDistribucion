#pragma once
#include <string>

/*
    Clase base de la jerarquia de clientes.

    Tanto el cliente persona fisica como el cliente empresa comparten
    identificacion, nombre, telefono y correo electronico; por eso esos
    cuatro atributos viven aqui y las clases hijas solo agregan lo que
    les es propio (ClienteEmpresa agrega actividad economica y el
    porcentaje de descuento autorizado).

    aplicarDescuento() es el punto de extension pensado para el calculo
    del costo de una solicitud de envio (ver GestionSolicitudes): la
    persona fisica no tiene descuento, asi que el metodo base simplemente
    devuelve el mismo costo recibido.
*/
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
