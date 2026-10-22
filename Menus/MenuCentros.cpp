#include "MenuCentros.h"
#include "EntradaUtil.h"
#include <iostream>

MenuCentros::MenuCentros(RedCentros& red) : red(red)
{
}

CentroDistribucion* MenuCentros::seleccionarCentro()
{
    std::cout << red.mostrarListado() << std::endl;
    if (red.getCantidad() == 0) {
        return nullptr;
    }

    std::cout << "Ingrese el codigo del centro: ";
    std::string codigo = leerPalabra();

    CentroDistribucion* centro = red.buscarCentroPorCodigo(codigo);
    if (centro == nullptr) {
        std::cout << "No existe un centro con ese codigo.\n";
    }
    return centro;
}

void MenuCentros::registrarCentro()
{
    std::string codigo, nombre, provincia, direccion, telefono;

    std::cout << "\n>> Registrar centro de distribucion\n";
    std::cout << "Codigo (unico): ";
    codigo = leerPalabra();

    if (red.existeCodigoCentro(codigo)) {
        std::cout << "Ya existe un centro con ese codigo.\n";
        return;
    }

    std::cout << "Nombre: ";
    nombre = leerLinea();
    std::cout << "Provincia: ";
    provincia = leerLinea();
    std::cout << "Direccion: ";
    direccion = leerLinea();
    std::cout << "Telefono: ";
    telefono = leerLinea();

    if (red.registrarCentro(codigo, nombre, provincia, direccion, telefono)) {
        std::cout << "Centro registrado exitosamente.\n";
    }
    else {
        std::cout << "No se pudo registrar el centro. Verifique que ningun dato quede vacio.\n";
    }
}

void MenuCentros::buscarCentro()
{
    std::cout << "\n>> Buscar centro de distribucion\n";
    std::cout << "Codigo del centro: ";
    std::string codigo = leerPalabra();

    CentroDistribucion* centro = red.buscarCentroPorCodigo(codigo);
    if (centro == nullptr) {
        std::cout << "No existe un centro con ese codigo.\n";
    }
    else {
        std::cout << centro->mostrarDatos() << "\n";
    }
}

void MenuCentros::mostrarCentros()
{
    std::cout << "\n" << red.mostrarListado() << std::endl;
}

void MenuCentros::eliminarCentro()
{
    std::cout << "\n>> Eliminar centro de distribucion\n";
    std::cout << "Codigo del centro: ";
    std::string codigo = leerPalabra();

    CentroDistribucion* centro = red.buscarCentroPorCodigo(codigo);
    if (centro == nullptr) {
        std::cout << "No existe un centro con ese codigo.\n";
        return;
    }
    if (centro->tieneDependencias()) {
        std::cout << "No se puede eliminar: el centro todavia tiene clientes, colaboradores, bodegas,\n";
        std::cout << "paquetes, solicitudes o despachos asociados.\n";
        return;
    }

    red.eliminarCentro(codigo);
    std::cout << "Centro eliminado exitosamente.\n";
}

// ---------------------------------------------------------------------
// Clientes
// ---------------------------------------------------------------------

void MenuCentros::registrarClientePersona(CentroDistribucion* centro)
{
    std::cout << "\n>> Registrar cliente (persona fisica)\n";
    std::cout << "Identificacion: ";
    std::string id = leerPalabra();

    if (centro->getGestionClientes()->existeIdentificacion(id)) {
        std::cout << "Ya existe un cliente con esa identificacion en este centro.\n";
        return;
    }

    std::cout << "Nombre completo: ";
    std::string nombre = leerLinea();
    std::cout << "Telefono: ";
    std::string telefono = leerPalabra();
    std::cout << "Correo electronico: ";
    std::string correo = leerPalabra();

    if (centro->getGestionClientes()->registrarPersona(id, nombre, telefono, correo)) {
        std::cout << "Cliente registrado exitosamente.\n";
    }
    else {
        std::cout << "No se pudo registrar el cliente. Verifique los datos ingresados.\n";
    }
}

void MenuCentros::registrarClienteEmpresa(CentroDistribucion* centro)
{
    std::cout << "\n>> Registrar cliente (empresa)\n";
    std::cout << "Identificacion (cedula juridica): ";
    std::string id = leerPalabra();

    if (centro->getGestionClientes()->existeIdentificacion(id)) {
        std::cout << "Ya existe un cliente con esa identificacion en este centro.\n";
        return;
    }

    std::cout << "Nombre o razon social: ";
    std::string nombre = leerLinea();
    std::cout << "Telefono: ";
    std::string telefono = leerPalabra();
    std::cout << "Correo electronico: ";
    std::string correo = leerPalabra();
    std::cout << "Actividad economica: ";
    std::string actividad = leerLinea();

    double descuento;
    do {
        std::cout << "Porcentaje de descuento autorizado (0-100): ";
        descuento = leerDecimal();
        if (descuento < 0.0 || descuento > 100.0) {
            std::cout << "El porcentaje debe estar entre 0 y 100.\n";
        }
    } while (descuento < 0.0 || descuento > 100.0);

    if (centro->getGestionClientes()->registrarEmpresa(id, nombre, telefono, correo, actividad, descuento)) {
        std::cout << "Cliente registrado exitosamente.\n";
    }
    else {
        std::cout << "No se pudo registrar el cliente. Verifique los datos ingresados.\n";
    }
}

void MenuCentros::buscarCliente(CentroDistribucion* centro)
{
    std::cout << "\n>> Buscar cliente\n";
    std::cout << "Identificacion del cliente: ";
    std::string id = leerPalabra();

    Cliente* cliente = centro->getGestionClientes()->buscarPorIdentificacion(id);
    if (cliente == nullptr) {
        std::cout << "No se encontro ningun cliente con esa identificacion en este centro.\n";
    }
    else {
        std::cout << cliente->mostrar() << "\n";
    }
}

void MenuCentros::mostrarClientes(CentroDistribucion* centro)
{
    std::cout << "\n" << centro->getGestionClientes()->mostrarListado() << std::endl;
}

void MenuCentros::eliminarCliente(CentroDistribucion* centro)
{
    std::cout << "\n>> Eliminar cliente\n";
    std::cout << "Identificacion del cliente: ";
    std::string id = leerPalabra();

    if (!centro->getGestionClientes()->existeIdentificacion(id)) {
        std::cout << "No existe un cliente con esa identificacion en este centro.\n";
        return;
    }

    if (centro->eliminarCliente(id)) {
        std::cout << "Cliente eliminado exitosamente.\n";
    }
    else {
        std::cout << "No se puede eliminar: el cliente tiene paquetes, solicitudes o despachos asociados.\n";
    }
}

void MenuCentros::menuClientes(CentroDistribucion* centro)
{
    int opcion;
    do {
        std::cout << "\n>> Clientes de " << centro->getCodigo() << "\n";
        std::cout << "1. Registrar cliente (persona fisica)\n";
        std::cout << "2. Registrar cliente (empresa)\n";
        std::cout << "3. Buscar cliente\n";
        std::cout << "4. Mostrar clientes del centro\n";
        std::cout << "5. Eliminar cliente\n";
        std::cout << "6. Volver\n";
        std::cout << "Seleccione una opcion: ";
        opcion = leerEntero();

        switch (opcion) {
        case 1: registrarClientePersona(centro); break;
        case 2: registrarClienteEmpresa(centro); break;
        case 3: buscarCliente(centro); break;
        case 4: mostrarClientes(centro); break;
        case 5: eliminarCliente(centro); break;
        case 6: break;
        default: std::cout << "Opcion invalida.\n"; break;
        }
        if (opcion != 6) {
            pausar();
        }
    } while (opcion != 6);
}

// ---------------------------------------------------------------------
// Colaboradores
// ---------------------------------------------------------------------

void MenuCentros::registrarColaborador(CentroDistribucion* centro)
{
    std::cout << "\n>> Registrar colaborador\n";
    std::cout << "Identificacion: ";
    std::string id = leerPalabra();

    if (centro->getGestionColaboradores()->existeIdentificacion(id)) {
        std::cout << "Ya existe un colaborador con esa identificacion en este centro.\n";
        return;
    }

    std::cout << "Nombre completo: ";
    std::string nombre = leerLinea();

    int dia, mes, anio;
    std::cout << "Fecha de ingreso:\n";
    std::cout << "  Dia: ";
    dia = leerEntero();
    std::cout << "  Mes: ";
    mes = leerEntero();
    std::cout << "  Anio: ";
    anio = leerEntero();

    std::cout << "Puesto: ";
    std::string puesto = leerLinea();

    if (centro->getGestionColaboradores()->registrar(id, nombre, Fecha(dia, mes, anio), puesto)) {
        std::cout << "Colaborador registrado exitosamente.\n";
    }
    else {
        std::cout << "No se pudo registrar el colaborador. Verifique los datos ingresados.\n";
    }
}

void MenuCentros::buscarColaborador(CentroDistribucion* centro)
{
    std::cout << "\n>> Buscar colaborador\n";
    std::cout << "Identificacion del colaborador: ";
    std::string id = leerPalabra();

    Colaborador* colaborador = centro->getGestionColaboradores()->buscarPorIdentificacion(id);
    if (colaborador == nullptr) {
        std::cout << "No se encontro ningun colaborador con esa identificacion en este centro.\n";
    }
    else {
        std::cout << colaborador->mostrar() << "\n";
    }
}

void MenuCentros::mostrarColaboradores(CentroDistribucion* centro)
{
    std::cout << "\n" << centro->getGestionColaboradores()->mostrarListado() << std::endl;
}

void MenuCentros::eliminarColaborador(CentroDistribucion* centro)
{
    std::cout << "\n>> Eliminar colaborador\n";
    std::cout << "Identificacion del colaborador: ";
    std::string id = leerPalabra();

    if (!centro->getGestionColaboradores()->existeIdentificacion(id)) {
        std::cout << "No existe un colaborador con esa identificacion en este centro.\n";
        return;
    }

    if (centro->eliminarColaborador(id)) {
        std::cout << "Colaborador eliminado exitosamente.\n";
    }
    else {
        std::cout << "No se puede eliminar: el colaborador aparece como responsable en solicitudes,\n";
        std::cout << "despachos o registros de bitacora.\n";
    }
}

void MenuCentros::menuColaboradores(CentroDistribucion* centro)
{
    int opcion;
    do {
        std::cout << "\n>> Colaboradores de " << centro->getCodigo() << "\n";
        std::cout << "1. Registrar colaborador\n";
        std::cout << "2. Buscar colaborador\n";
        std::cout << "3. Mostrar colaboradores del centro\n";
        std::cout << "4. Eliminar colaborador\n";
        std::cout << "5. Volver\n";
        std::cout << "Seleccione una opcion: ";
        opcion = leerEntero();

        switch (opcion) {
        case 1: registrarColaborador(centro); break;
        case 2: buscarColaborador(centro); break;
        case 3: mostrarColaboradores(centro); break;
        case 4: eliminarColaborador(centro); break;
        case 5: break;
        default: std::cout << "Opcion invalida.\n"; break;
        }
        if (opcion != 5) {
            pausar();
        }
    } while (opcion != 5);
}

void MenuCentros::menuClientesYColaboradores()
{
    CentroDistribucion* centro = seleccionarCentro();
    if (centro == nullptr) {
        pausar();
        return;
    }

    int opcion;
    do {
        std::cout << "\n>> Centro " << centro->getCodigo() << ": Clientes y Colaboradores\n";
        std::cout << "1. Gestion de clientes\n";
        std::cout << "2. Gestion de colaboradores\n";
        std::cout << "3. Volver\n";
        std::cout << "Seleccione una opcion: ";
        opcion = leerEntero();

        switch (opcion) {
        case 1: menuClientes(centro); break;
        case 2: menuColaboradores(centro); break;
        case 3: break;
        default: std::cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 3);
}

void MenuCentros::menu()
{
    int opcion;
    do {
        std::cout << "\n===== CENTROS DE DISTRIBUCION =====\n";
        std::cout << "1. Registrar centro de distribucion\n";
        std::cout << "2. Buscar centro de distribucion\n";
        std::cout << "3. Mostrar centros de distribucion\n";
        std::cout << "4. Eliminar centro de distribucion\n";
        std::cout << "5. Clientes y colaboradores de un centro\n";
        std::cout << "6. Volver al menu principal\n";
        std::cout << "Seleccione una opcion: ";
        opcion = leerEntero();

        switch (opcion) {
        case 1: registrarCentro(); break;
        case 2: buscarCentro(); break;
        case 3: mostrarCentros(); break;
        case 4: eliminarCentro(); break;
        case 5: menuClientesYColaboradores(); break;
        case 6: break;
        default: std::cout << "Opcion invalida.\n"; break;
        }
        if (opcion >= 1 && opcion <= 4) {
            pausar();
        }
    } while (opcion != 6);
}
