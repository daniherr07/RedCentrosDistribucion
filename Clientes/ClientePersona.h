#pragma once
#include "Cliente.h"

class ClientePersona : public Cliente
{
public:
    ClientePersona(std::string identificacion, std::string nombre, std::string telefono, std::string correo);

    std::string getTipoCliente() const override;
};
