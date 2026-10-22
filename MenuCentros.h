#pragma once
#include "RedCentros.h"

// Interfaz de consola para los grupos de opciones "Centros de
// distribucion", "Clientes" y "Colaboradores". Las entidades y las
// clases de gestion no leen ni escriben en consola: toda la entrada y
// salida de este modulo vive aqui.
class MenuCentros
{
private:
    RedCentros& red;

    CentroDistribucion* seleccionarCentro();

    void registrarCentro();
    void buscarCentro();
    void mostrarCentros();
    void eliminarCentro();

    void menuClientes(CentroDistribucion* centro);
    void registrarClientePersona(CentroDistribucion* centro);
    void registrarClienteEmpresa(CentroDistribucion* centro);
    void buscarCliente(CentroDistribucion* centro);
    void mostrarClientes(CentroDistribucion* centro);
    void eliminarCliente(CentroDistribucion* centro);

    void menuColaboradores(CentroDistribucion* centro);
    void registrarColaborador(CentroDistribucion* centro);
    void buscarColaborador(CentroDistribucion* centro);
    void mostrarColaboradores(CentroDistribucion* centro);
    void eliminarColaborador(CentroDistribucion* centro);

    void menuClientesYColaboradores();

public:
    MenuCentros(RedCentros& red);

    void menu();
};
