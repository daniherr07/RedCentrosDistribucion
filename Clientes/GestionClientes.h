#pragma once
#include <string>
#include "Cliente.h"
#include "ListaEnlazada.h"

// Administra, para UN centro de distribucion, la lista enlazada de sus
// clientes (persona fisica o empresa). La identificacion de cliente debe
// ser unica dentro del centro al que pertenece (no a nivel de todo el
// sistema), asi que las validaciones de esta clase solo miran su propia
// lista.
class GestionClientes
{
private:
    ListaEnlazada<Cliente*> clientes;

public:
    GestionClientes();
    ~GestionClientes();

    bool existeIdentificacion(std::string identificacion) const;
    Cliente* buscarPorIdentificacion(std::string identificacion) const;

    bool registrarPersona(std::string identificacion, std::string nombre, std::string telefono, std::string correo);
    bool registrarEmpresa(std::string identificacion, std::string nombre, std::string telefono, std::string correo,
        std::string actividadEconomica, double porcentajeDescuento);

    // Elimina el cliente de esta lista. Las dependencias con paquetes,
    // solicitudes y despachos se validan en CentroDistribucion, que es
    // quien conoce las otras colecciones del centro.
    bool eliminar(std::string identificacion);

    std::string mostrarListado() const;
    int getCantidad() const;
    ListaEnlazada<Cliente*>* obtenerLista();
};
