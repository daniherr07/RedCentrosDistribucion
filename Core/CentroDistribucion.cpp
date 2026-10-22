#include "CentroDistribucion.h"
#include <sstream>

CentroDistribucion::CentroDistribucion(std::string codigo, std::string nombre, std::string provincia, std::string direccion, std::string telefono) {
	this->codigo = codigo;
	this->nombre = nombre;
	this->provincia = provincia;
	this->direccion = direccion;
	this->telefono = telefono;

	clientes = new GestionClientes();
	colaboradores = new GestionColaboradores();
	bodegas = new GestionBodegas();
	paquetes = new GestionPaquetes();
	solicitudes = new GestionSolicitudes();
	despachos = new GestionDespachos();
}

CentroDistribucion::~CentroDistribucion() {
	delete clientes;
	delete colaboradores;
	delete bodegas;
	delete paquetes;
	delete solicitudes;
	delete despachos;
}

std::string CentroDistribucion::getCodigo() const { return codigo; }
std::string CentroDistribucion::getNombre() const { return nombre; }
std::string CentroDistribucion::getProvincia() const { return provincia; }
std::string CentroDistribucion::getDireccion() const { return direccion; }
std::string CentroDistribucion::getTelefono() const { return telefono; }

void CentroDistribucion::setNombre(std::string nombre) { this->nombre = nombre; }
void CentroDistribucion::setProvincia(std::string provincia) { this->provincia = provincia; }
void CentroDistribucion::setDireccion(std::string direccion) { this->direccion = direccion; }
void CentroDistribucion::setTelefono(std::string telefono) { this->telefono = telefono; }

GestionClientes* CentroDistribucion::getGestionClientes() const { return clientes; }
GestionColaboradores* CentroDistribucion::getGestionColaboradores() const { return colaboradores; }
GestionBodegas* CentroDistribucion::getGestionBodegas() const { return bodegas; }
GestionPaquetes* CentroDistribucion::getGestionPaquetes() const { return paquetes; }
GestionSolicitudes* CentroDistribucion::getGestionSolicitudes() const { return solicitudes; }
GestionDespachos* CentroDistribucion::getGestionDespachos() const { return despachos; }

bool CentroDistribucion::tieneDependencias() const {
	return clientes->getCantidad() > 0
		|| colaboradores->getCantidad() > 0
		|| bodegas->getCantidad() > 0
		|| paquetes->getCantidad() > 0
		|| solicitudes->getCantidad() > 0
		|| despachos->getCantidad() > 0;
}

bool CentroDistribucion::eliminarCliente(std::string identificacion) {
	Cliente* cliente = clientes->buscarPorIdentificacion(identificacion);
	if (cliente == nullptr) {
		return false;
	}

	Nodo<Paquete*>* np = paquetes->obtenerLista()->getCabeza();
	while (np != nullptr) {
		if (np->getDato()->getClientePropietario() == cliente) {
			return false; // tiene paquetes asociados
		}
		np = np->getSiguiente();
	}

	Nodo<SolicitudEnvio*>* ns = solicitudes->obtenerLista()->getCabeza();
	while (ns != nullptr) {
		if (ns->getDato()->getCliente() == cliente) {
			return false; // tiene solicitudes asociadas
		}
		ns = ns->getSiguiente();
	}

	Nodo<Despacho*>* nd = despachos->obtenerLista()->getCabeza();
	while (nd != nullptr) {
		if (nd->getDato()->getCliente() == cliente) {
			return false; // tiene despachos asociados
		}
		nd = nd->getSiguiente();
	}

	return clientes->eliminar(identificacion);
}

bool CentroDistribucion::eliminarColaborador(std::string identificacion) {
	Colaborador* colaborador = colaboradores->buscarPorIdentificacion(identificacion);
	if (colaborador == nullptr) {
		return false;
	}

	Nodo<SolicitudEnvio*>* ns = solicitudes->obtenerLista()->getCabeza();
	while (ns != nullptr) {
		if (ns->getDato()->getColaborador() == colaborador) {
			return false; // es responsable de una solicitud
		}
		ns = ns->getSiguiente();
	}

	Nodo<Despacho*>* nd = despachos->obtenerLista()->getCabeza();
	while (nd != nullptr) {
		if (nd->getDato()->getColaborador() == colaborador) {
			return false; // es responsable de un despacho
		}
		nd = nd->getSiguiente();
	}

	// Tambien debe revisarse la bitacora de cada paquete del centro.
	Nodo<Paquete*>* np = paquetes->obtenerLista()->getCabeza();
	while (np != nullptr) {
		Nodo<RegistroBitacora*>* nb = np->getDato()->obtenerBitacora()->getCabeza();
		while (nb != nullptr) {
			if (nb->getDato()->getResponsable() == colaborador) {
				return false; // aparece como responsable en una bitacora
			}
			nb = nb->getSiguiente();
		}
		np = np->getSiguiente();
	}

	return colaboradores->eliminar(identificacion);
}

bool CentroDistribucion::eliminarPaquete(std::string codigoPaquete) {
	Paquete* paquete = paquetes->buscarPorCodigo(codigoPaquete);
	if (paquete == nullptr) {
		return false;
	}

	Nodo<SolicitudEnvio*>* ns = solicitudes->obtenerLista()->getCabeza();
	while (ns != nullptr) {
		if (ns->getDato()->getPaquete() == paquete) {
			return false; // tiene solicitudes asociadas
		}
		ns = ns->getSiguiente();
	}

	Nodo<Despacho*>* nd = despachos->obtenerLista()->getCabeza();
	while (nd != nullptr) {
		if (nd->getDato()->getPaquete() == paquete) {
			return false; // tiene despachos asociados
		}
		nd = nd->getSiguiente();
	}

	return paquetes->eliminar(codigoPaquete);
}

bool CentroDistribucion::aprobarSolicitud(std::string codigoSolicitud, Colaborador* responsable, std::string codigoDespacho, std::string hora) {
	SolicitudEnvio* solicitud = solicitudes->buscarPorCodigo(codigoSolicitud);
	if (solicitud == nullptr || responsable == nullptr) {
		return false;
	}
	if (colaboradores->buscarPorIdentificacion(responsable->getIdentificacion()) != responsable) {
		return false; // el responsable debe pertenecer a este centro
	}
	if (solicitud->getEstado() != EstadoSolicitud::PENDIENTE) {
		return false;
	}

	Paquete* paquete = solicitud->getPaquete();
	if (paquete->getEstado() != EstadoPaquete::ALMACENADO) {
		return false;
	}
	if (despachos->existeDespachoParaPaquete(paquete)) {
		return false; // ya tiene un despacho (no deberia poder pasar, se valida por consistencia)
	}

	if (!solicitud->cambiarEstado(EstadoSolicitud::APROBADA)) {
		return false;
	}

	Despacho* despacho = despachos->crearDespacho(codigoDespacho, solicitud, paquete, solicitud->getCliente(),
		responsable, this, solicitud->getDestino(), hora);
	if (despacho == nullptr) {
		return false;
	}

	Bodega* bodegaAnterior = paquete->getBodegaAsignada();
	int filaAnterior = paquete->getFila();
	int columnaAnterior = paquete->getColumna();

	paquete->cambiarEstado(EstadoPaquete::EN_TRANSITO, responsable);
	paquete->liberarUbicacion();
	if (bodegaAnterior != nullptr) {
		bodegaAnterior->liberarCelda(filaAnterior, columnaAnterior);
	}

	return true;
}

std::string CentroDistribucion::mostrarDatos() const {
	std::stringstream ss;
	ss << "Codigo: " << codigo
		<< " | Nombre: " << nombre
		<< " | Provincia: " << provincia
		<< " | Direccion: " << direccion
		<< " | Telefono: " << telefono;
	return ss.str();
}
