#include "Menu.h"
#include "EntradaUtil.h"
#include <iostream>

Menu::Menu() : menuCentros(red), menuLogistica(red) {
	red.cargarDatosDePrueba(); // datos "quemados" para agilizar pruebas; no reemplaza el ingreso manual
}

CentroDistribucion* Menu::seleccionarCentro() {
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

void Menu::reporteHistorialCliente() {
	CentroDistribucion* centro = seleccionarCentro();
	if (centro == nullptr) {
		return;
	}

	std::cout << "Identificacion del cliente: ";
	std::string id = leerPalabra();
	Cliente* cliente = centro->getGestionClientes()->buscarPorIdentificacion(id);
	if (cliente == nullptr) {
		std::cout << "No existe un cliente con esa identificacion en ese centro.\n";
		return;
	}

	std::cout << "\n" << reportes.historialCliente(centro, cliente) << std::endl;
}

void Menu::reporteClientesPorEnvios() {
	CentroDistribucion* centro = seleccionarCentro();
	if (centro == nullptr) {
		return;
	}
	std::cout << "\n" << reportes.clientesPorCantidadEnvios(centro) << std::endl;
}

void Menu::reporteBitacoraPaquete() {
	std::cout << "Codigo del paquete: ";
	std::string codigo = leerPalabra();

	Paquete* paquete = red.buscarPaqueteGlobal(codigo);
	if (paquete == nullptr) {
		std::cout << "No existe ningun paquete con ese codigo en el sistema.\n";
		return;
	}
	std::cout << "\n" << reportes.bitacoraPaquete(paquete) << std::endl;
}

void Menu::reporteConsultaDespacho() {
	std::cout << "Codigo del paquete: ";
	std::string codigo = leerPalabra();

	Paquete* paquete = red.buscarPaqueteGlobal(codigo);
	if (paquete == nullptr) {
		std::cout << "No existe ningun paquete con ese codigo en el sistema.\n";
		return;
	}
	std::cout << "\n" << reportes.consultaDespachoPaquete(paquete->getCentro(), paquete) << std::endl;
}

void Menu::reporteOcupacionBodegas() {
	std::cout << "\n" << reportes.ocupacionBodegas(&red) << std::endl;
}

void Menu::reporteDespachosPorColaborador() {
	CentroDistribucion* centro = seleccionarCentro();
	if (centro == nullptr) {
		return;
	}

	std::cout << "Identificacion del colaborador: ";
	std::string id = leerPalabra();
	Colaborador* colaborador = centro->getGestionColaboradores()->buscarPorIdentificacion(id);
	if (colaborador == nullptr) {
		std::cout << "No existe un colaborador con esa identificacion en ese centro.\n";
		return;
	}

	std::cout << "\n" << reportes.despachosPorColaborador(centro, colaborador) << std::endl;
}

void Menu::menuReportes() {
	int opcion;
	do {
		std::cout << "\n===== REPORTES Y ESTADISTICAS =====\n";
		std::cout << "1. Historial de un cliente\n";
		std::cout << "2. Clientes por cantidad de envios\n";
		std::cout << "3. Bitacora de un paquete\n";
		std::cout << "4. Consulta de despacho de un paquete\n";
		std::cout << "5. Ocupacion de bodegas\n";
		std::cout << "6. Despachos por colaborador\n";
		std::cout << "7. Volver al menu principal\n";
		std::cout << "Seleccione una opcion: ";
		opcion = leerEntero();

		switch (opcion) {
		case 1: reporteHistorialCliente(); break;
		case 2: reporteClientesPorEnvios(); break;
		case 3: reporteBitacoraPaquete(); break;
		case 4: reporteConsultaDespacho(); break;
		case 5: reporteOcupacionBodegas(); break;
		case 6: reporteDespachosPorColaborador(); break;
		case 7: break;
		default: std::cout << "Opcion invalida.\n"; break;
		}
		if (opcion != 7) {
			pausar();
		}
	} while (opcion != 7);
}

void Menu::menuPrincipal() {
	int opcion;
	do {
		limpiarPantalla();
		std::cout << "\tTicoPack Logistics - Red de Centros de Distribucion\n" << std::endl;
		std::cout << "1. Centros de distribucion (incluye clientes y colaboradores)\n";
		std::cout << "2. Bodegas, paquetes, solicitudes de envio y despachos\n";
		std::cout << "3. Reportes y estadisticas\n";
		std::cout << "4. Salir\n" << std::endl;
		std::cout << "Seleccione una opcion: ";
		opcion = leerEntero();

		switch (opcion) {
		case 1:
			limpiarPantalla();
			menuCentros.menu();
			break;
		case 2:
			limpiarPantalla();
			menuLogistica.menuGeneral();
			break;
		case 3:
			limpiarPantalla();
			menuReportes();
			break;
		case 4:
			break;
		default:
			std::cout << "Opcion invalida.\n";
			pausar();
			break;
		}
	} while (opcion != 4);

	std::cout << "\nGracias por usar el sistema de TicoPack Logistics.\n";
	pausar();
}
