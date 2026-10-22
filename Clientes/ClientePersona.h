#pragma once
#include "Cliente.h"

// Cliente persona fisica: no agrega atributos nuevos, solo identifica el
// tipo de cliente y hereda el comportamiento base (sin descuento).
class ClientePersona : public Cliente
{
public:
    ClientePersona(std::string identificacion, std::string nombre, std::string telefono, std::string correo);

    std::string getTipoCliente() const override;
};
