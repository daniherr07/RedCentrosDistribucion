#include "Reportes.h"
#include "RedCentros.h"
#include <sstream>

Reportes::Reportes() {
}

std::string Reportes::historialCliente(CentroDistribucion* centro, Cliente* cliente) const {
	std::ostringstream ss;
	if (centro == nullptr || cliente == nullptr) {
		return "Datos invalidos\n";
	}

	ss << "Historial de " << cliente->getNombre() << " (" << cliente->getIdentificacion() << "):\n\n";

	ss << "Solicitudes de envio:\n";
	bool alguna = false;
	Nodo<SolicitudEnvio*>* s = centro->getGestionSolicitudes()->obtenerLista()->getCabeza();
	while (s != nullptr) {
		if (s->getDato()->getCliente() == cliente) {
			ss << "\t" << s->getDato()->mostrar() << "\n";
			alguna = true;
		}
		s = s->getSiguiente();
	}
	if (!alguna) {
		ss << "\tSin solicitudes registradas.\n";
	}

	ss << "\nDespachos:\n";
	alguna = false;
	Nodo<Despacho*>* d = centro->getGestionDespachos()->obtenerLista()->getCabeza();
	while (d != nullptr) {
		if (d->getDato()->getCliente() == cliente) {
			ss << "\t" << d->getDato()->mostrar() << "\n";
			alguna = true;
		}
		d = d->getSiguiente();
	}
	if (!alguna) {
		ss << "\tSin despachos registrados.\n";
	}

	return ss.str();
}

std::string Reportes::clientesPorCantidadEnvios(CentroDistribucion* centro) const {
	if (centro == nullptr) {
		return "Centro invalido\n";
	}

	int n = centro->getGestionClientes()->getCantidad();
	if (n == 0) {
		return "No hay clientes registrados en este centro\n";
	}

	Cliente** clientesArr = new Cliente * [n];
	int* conteo = new int[n];

	Nodo<Cliente*>* actual = centro->getGestionClientes()->obtenerLista()->getCabeza();
	int idx = 0;
	while (actual != nullptr) {
		clientesArr[idx] = actual->getDato();
		conteo[idx] = 0;
		idx++;
		actual = actual->getSiguiente();
	}

	Nodo<Despacho*>* d = centro->getGestionDespachos()->obtenerLista()->getCabeza();
	while (d != nullptr) {
		if (d->getDato()->getEstado() == EstadoDespacho::FINALIZADO) {
			for (int i = 0; i < n; i++) {
				if (clientesArr[i] == d->getDato()->getCliente()) {
					conteo[i]++;
					break;
				}
			}
		}
		d = d->getSiguiente();
	}

	// Ordenamiento por insercion (propio, sin algoritmos de la STL), estable:
	// en un empate, los clientes conservan el orden en que ya estaban en la lista.
	for (int i = 1; i < n; i++) {
		int conteoActual = conteo[i];
		Cliente* clienteActual = clientesArr[i];
		int j = i - 1;
		while (j >= 0 && conteo[j] < conteoActual) {
			conteo[j + 1] = conteo[j];
			clientesArr[j + 1] = clientesArr[j];
			j--;
		}
		conteo[j + 1] = conteoActual;
		clientesArr[j + 1] = clienteActual;
	}

	std::ostringstream ss;
	ss << "Clientes de " << centro->getCodigo() << " ordenados por cantidad de envios finalizados:\n";
	for (int i = 0; i < n; i++) {
		ss << "\t" << conteo[i] << " envio(s) - " << clientesArr[i]->mostrar() << "\n";
	}

	delete[] clientesArr;
	delete[] conteo;
	return ss.str();
}

std::string Reportes::bitacoraPaquete(Paquete* paquete) const {
	if (paquete == nullptr) {
		return "Paquete invalido\n";
	}
	std::ostringstream ss;
	ss << "Bitacora del paquete " << paquete->getCodigo() << " (del mas antiguo al mas reciente):\n";
	ss << paquete->mostrarBitacora();
	return ss.str();
}

std::string Reportes::consultaDespachoPaquete(CentroDistribucion* centro, Paquete* paquete) const {
	if (centro == nullptr || paquete == nullptr) {
		return "Datos invalidos\n";
	}

	SolicitudEnvio* aprobada = centro->getGestionSolicitudes()->buscarAprobadaParaPaquete(paquete);
	Despacho* despacho = centro->getGestionDespachos()->buscarPorPaquete(paquete);

	std::ostringstream ss;
	ss << "Paquete: " << paquete->getCodigo() << "\n";

	if (aprobada != nullptr) {
		ss << "Solicitud aprobada: " << aprobada->mostrar() << "\n";
	}
	else {
		ss << "Este paquete no tiene una solicitud aprobada.\n";
	}

	if (despacho != nullptr) {
		ss << "Despacho: " << despacho->mostrar() << "\n";
	}
	else {
		ss << "Este paquete no posee un despacho asociado.\n";
	}

	return ss.str();
}

std::string Reportes::ocupacionBodegas(RedCentros* red) const {
	if (red == nullptr) {
		return "Red invalida\n";
	}
	if (red->getCantidad() == 0) {
		return "No hay centros de distribucion registrados\n";
	}

	std::ostringstream ss;
	Nodo<CentroDistribucion*>* c = red->obtenerLista()->getCabeza();
	while (c != nullptr) {
		CentroDistribucion* centro = c->getDato();
		ss << "Centro " << centro->getCodigo() << " (" << centro->getNombre() << "):\n";

		if (centro->getGestionBodegas()->getCantidad() == 0) {
			ss << "\tSin bodegas registradas.\n";
		}
		else {
			Nodo<Bodega*>* b = centro->getGestionBodegas()->obtenerLista()->getCabeza();
			while (b != nullptr) {
				Bodega* bodega = b->getDato();
				ss << "\tBodega " << bodega->getCodigo()
					<< " | Total: " << bodega->totalCeldas()
					<< " | Ocupadas: " << bodega->contarOcupadas()
					<< " | Disponibles: " << bodega->contarLibres()
					<< " | Ocupacion: " << bodega->porcentajeOcupacion() << "%\n";
				b = b->getSiguiente();
			}
		}
		ss << "\n";
		c = c->getSiguiente();
	}

	return ss.str();
}

std::string Reportes::despachosPorColaborador(CentroDistribucion* centro, Colaborador* colaborador) const {
	if (centro == nullptr || colaborador == nullptr) {
		return "Datos invalidos\n";
	}

	std::ostringstream ss;
	ss << "Despachos gestionados por " << colaborador->getNombreCompleto() << ":\n";
	bool alguno = false;
	Nodo<Despacho*>* d = centro->getGestionDespachos()->obtenerLista()->getCabeza();
	while (d != nullptr) {
		if (d->getDato()->getColaborador() == colaborador) {
			ss << "\t" << d->getDato()->mostrar() << "\n";
			alguno = true;
		}
		d = d->getSiguiente();
	}
	if (!alguno) {
		ss << "\tEste colaborador no tiene despachos asociados.\n";
	}
	return ss.str();
}
