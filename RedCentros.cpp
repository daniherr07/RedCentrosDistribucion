#include "RedCentros.h"
#include <sstream>

RedCentros::RedCentros() {
}

RedCentros::~RedCentros() {
	centros.liberarPunteros();
}

bool RedCentros::existeCodigoCentro(std::string codigo) const {
	return buscarCentroPorCodigo(codigo) != nullptr;
}

CentroDistribucion* RedCentros::buscarCentroPorCodigo(std::string codigo) const {
	Nodo<CentroDistribucion*>* actual = centros.getCabeza();
	while (actual != nullptr) {
		if (actual->getDato()->getCodigo() == codigo) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

bool RedCentros::registrarCentro(std::string codigo, std::string nombre, std::string provincia, std::string direccion, std::string telefono) {
	if (codigo.empty() || nombre.empty() || provincia.empty() || direccion.empty() || telefono.empty()) {
		return false;
	}
	if (existeCodigoCentro(codigo)) {
		return false;
	}

	CentroDistribucion* nuevo = new CentroDistribucion(codigo, nombre, provincia, direccion, telefono);
	centros.insertarAlFinal(nuevo);
	return true;
}

bool RedCentros::eliminarCentro(std::string codigo) {
	CentroDistribucion* centro = buscarCentroPorCodigo(codigo);
	if (centro == nullptr) {
		return false;
	}
	if (centro->tieneDependencias()) {
		return false;
	}

	centros.eliminarDato(centro);
	delete centro;
	return true;
}

std::string RedCentros::mostrarListado() const {
	std::stringstream ss;

	if (centros.estaVacia()) {
		ss << "No hay centros de distribucion registrados.\n";
		return ss.str();
	}

	ss << "----- LISTADO DE CENTROS DE DISTRIBUCION (" << centros.getCantidad() << ") -----\n";
	Nodo<CentroDistribucion*>* actual = centros.getCabeza();
	while (actual != nullptr) {
		ss << actual->getDato()->mostrarDatos() << "\n";
		actual = actual->getSiguiente();
	}
	return ss.str();
}

int RedCentros::getCantidad() const {
	return centros.getCantidad();
}

ListaEnlazada<CentroDistribucion*>* RedCentros::obtenerLista() {
	return &centros;
}

bool RedCentros::existeCodigoPaqueteGlobal(std::string codigo) const {
	return buscarPaqueteGlobal(codigo) != nullptr;
}

Paquete* RedCentros::buscarPaqueteGlobal(std::string codigo) const {
	Nodo<CentroDistribucion*>* actual = centros.getCabeza();
	while (actual != nullptr) {
		Paquete* encontrado = actual->getDato()->getGestionPaquetes()->buscarPorCodigo(codigo);
		if (encontrado != nullptr) {
			return encontrado;
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

bool RedCentros::existeCodigoSolicitudGlobal(std::string codigo) const {
	return buscarSolicitudGlobal(codigo) != nullptr;
}

SolicitudEnvio* RedCentros::buscarSolicitudGlobal(std::string codigo) const {
	Nodo<CentroDistribucion*>* actual = centros.getCabeza();
	while (actual != nullptr) {
		SolicitudEnvio* encontrada = actual->getDato()->getGestionSolicitudes()->buscarPorCodigo(codigo);
		if (encontrada != nullptr) {
			return encontrada;
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

bool RedCentros::existeCodigoDespachoGlobal(std::string codigo) const {
	return buscarDespachoGlobal(codigo) != nullptr;
}

Despacho* RedCentros::buscarDespachoGlobal(std::string codigo) const {
	Nodo<CentroDistribucion*>* actual = centros.getCabeza();
	while (actual != nullptr) {
		Despacho* encontrado = actual->getDato()->getGestionDespachos()->buscarPorCodigo(codigo);
		if (encontrado != nullptr) {
			return encontrado;
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

void RedCentros::cargarDatosDePrueba() {
	registrarCentro("CD01", "Centro San Jose", "San Jose", "Barrio Escalante, 200m norte del parque", "2222-1111");
	registrarCentro("CD02", "Centro Alajuela", "Alajuela", "Centro, frente al parque central", "2222-2222");

	CentroDistribucion* cd01 = buscarCentroPorCodigo("CD01");
	if (cd01 == nullptr) {
		return;
	}

	cd01->getGestionClientes()->registrarPersona("1-1111-1111", "Juan Perez", "8888-1111", "juan@mail.com");
	cd01->getGestionClientes()->registrarEmpresa("3-101-123456", "Comercial XYZ S.A.", "8888-2222", "ventas@xyz.com",
		"Comercio al por menor", 10.0);

	cd01->getGestionColaboradores()->registrar("C001", "Maria Rodriguez", Fecha(15, 3, 2022), "Bodeguero");
	cd01->getGestionColaboradores()->registrar("C002", "Carlos Mendez", Fecha(1, 6, 2023), "Supervisor de envios");

	cd01->getGestionBodegas()->registrarBodega("A", "Bodega General 1", TipoCategoria::GENERAL, 3, 4);
	cd01->getGestionBodegas()->registrarBodega("B", "Bodega Fragil 1", TipoCategoria::FRAGIL, 2, 3);

	Cliente* juan = cd01->getGestionClientes()->buscarPorIdentificacion("1-1111-1111");
	Cliente* xyz = cd01->getGestionClientes()->buscarPorIdentificacion("3-101-123456");
	Colaborador* maria = cd01->getGestionColaboradores()->buscarPorIdentificacion("C001");
	Colaborador* carlos = cd01->getGestionColaboradores()->buscarPorIdentificacion("C002");
	Bodega* bodegaA = cd01->getGestionBodegas()->buscarPorCodigo("A");
	Bodega* bodegaB = cd01->getGestionBodegas()->buscarPorCodigo("B");

	Paquete* pk101 = cd01->getGestionPaquetes()->registrarPaquete("PK101", "Caja de ropa", 5.0, TipoCategoria::GENERAL, juan, cd01);
	Paquete* pk102 = cd01->getGestionPaquetes()->registrarPaquete("PK102", "Lampara de vidrio", 2.0, TipoCategoria::FRAGIL, xyz, cd01);

	if (pk101 != nullptr && bodegaA != nullptr) {
		cd01->getGestionPaquetes()->almacenarPaquete(pk101, bodegaA, 0, 0, maria);
	}
	if (pk102 != nullptr && bodegaB != nullptr) {
		cd01->getGestionPaquetes()->almacenarPaquete(pk102, bodegaB, 0, 0, maria);
	}

	if (pk101 != nullptr) {
		cd01->getGestionSolicitudes()->crearSolicitud("S001", juan, pk101, carlos, cd01, "San Ramon, 100m este de la escuela");
		cd01->aprobarSolicitud("S001", carlos, "D001", "09:30");
	}
}
