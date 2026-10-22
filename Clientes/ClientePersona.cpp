#include "ClientePersona.h"

ClientePersona::ClientePersona(std::string identificacion, std::string nombre, std::string telefono, std::string correo)
    : Cliente(identificacion, nombre, telefono, correo)
{
}

std::string ClientePersona::getTipoCliente() const
{
    return "Persona Fisica";
}
