#include "GestionPaquetes.h"
#include "CentroDistribucion.h"
#include <sstream>

//El enunciado exige que el colaborador responsable de un cambio de estado
//pertenezca al mismo centro de distribucion del paquete (seccion 5).
static bool perteneceAlCentroDelPaquete(Paquete* paquete, Colaborador* colaborador) {
	if (colaborador == nullptr) {
		return false;
	}
	return paquete->getCentro()->getGestionColaboradores()->buscarPorIdentificacion(colaborador->getIdentificacion()) == colaborador;
}

GestionPaquetes::GestionPaquetes() {
}

GestionPaquetes::~GestionPaquetes() {
	paquetes.liberarPunteros();
}

bool GestionPaquetes::existeCodigo(std::string codigo) const {
	return buscarPorCodigo(codigo) != nullptr;
}

Paquete* GestionPaquetes::buscarPorCodigo(std::string codigo) const {
	Nodo<Paquete*>* actual = paquetes.getCabeza();
	while (actual != nullptr) {
		if (actual->getDato()->getCodigo() == codigo) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

Paquete* GestionPaquetes::registrarPaquete(std::string codigo, std::string descripcion, double peso, TipoCategoria categoria,
	Cliente* clientePropietario, CentroDistribucion* centro) {
	if (codigo.empty() || descripcion.empty()) {
		return nullptr;
	}
	if (peso <= 0.0) { //el enunciado exige peso mayor que cero
		return nullptr;
	}
	if (clientePropietario == nullptr) {
		return nullptr;
	}
	if (existeCodigo(codigo)) { //ojo: la unicidad real es GLOBAL, RedCentros valida eso antes de llamar aqui
		return nullptr;
	}

	Paquete* nuevo = new Paquete(codigo, descripcion, peso, categoria, clientePropietario, centro);
	paquetes.insertarAlFinal(nuevo);
	return nuevo;
}

bool GestionPaquetes::eliminar(std::string codigo) {
	Paquete* paquete = buscarPorCodigo(codigo);
	if (paquete == nullptr) {
		return false;
	}
	if (paquete->getEstado() != EstadoPaquete::RECIBIDO) { //solo se puede eliminar si sigue Recibido
		return false;
	}
	if (paquete->tieneUbicacion()) {
		return false;
	}

	paquetes.eliminarDato(paquete);
	delete paquete;
	return true;
}

bool GestionPaquetes::almacenarPaquete(Paquete* paquete, Bodega* bodega, int fila, int columna, Colaborador* responsable) {
	if (paquete == nullptr || bodega == nullptr) {
		return false;
	}

	bool desdeRecibido = paquete->getEstado() == EstadoPaquete::RECIBIDO;
	bool desdeIncidenciaDeRecibido = paquete->getEstado() == EstadoPaquete::INCIDENCIA
		&& paquete->getEstadoPrevioIncidencia() == EstadoPaquete::RECIBIDO;

	if (!desdeRecibido && !desdeIncidenciaDeRecibido) {
		return false;
	}
	if (!perteneceAlCentroDelPaquete(paquete, responsable)) {
		return false;
	}
	if (!bodega->esCompatible(paquete->getCategoria())) { //compatibilidad directa categoria<->tipo
		return false;
	}
	if (!bodega->existeCelda(fila, columna) || !bodega->estaLibre(fila, columna)) {
		return false;
	}
	if (!bodega->reservarCelda(fila, columna, paquete)) {
		return false;
	}

	paquete->asignarUbicacion(bodega, fila, columna);
	paquete->cambiarEstado(EstadoPaquete::ALMACENADO, responsable); //valido en ambos casos de entrada (ver tabla de transiciones)
	return true;
}

bool GestionPaquetes::reubicarPaquete(Paquete* paquete, Bodega* nuevaBodega, int nuevaFila, int nuevaColumna) {
	if (paquete == nullptr || nuevaBodega == nullptr) {
		return false;
	}
	if (paquete->getEstado() != EstadoPaquete::ALMACENADO) {
		return false;
	}
	if (!nuevaBodega->esCompatible(paquete->getCategoria())) {
		return false;
	}
	if (!nuevaBodega->existeCelda(nuevaFila, nuevaColumna) || !nuevaBodega->estaLibre(nuevaFila, nuevaColumna)) {
		return false;
	}

	//Primero se reserva el destino; solo si eso funciona se libera la celda anterior (orden exigido por el enunciado)
	if (!nuevaBodega->reservarCelda(nuevaFila, nuevaColumna, paquete)) {
		return false;
	}

	Bodega* bodegaVieja = paquete->getBodegaAsignada();
	int filaVieja = paquete->getFila();
	int columnaVieja = paquete->getColumna();

	if (bodegaVieja != nullptr) {
		bodegaVieja->liberarCelda(filaVieja, columnaVieja);
	}

	paquete->asignarUbicacion(nuevaBodega, nuevaFila, nuevaColumna);
	return true;
}

bool GestionPaquetes::reportarIncidencia(std::string codigo, Colaborador* responsable) {
	Paquete* paquete = buscarPorCodigo(codigo);
	if (paquete == nullptr || !perteneceAlCentroDelPaquete(paquete, responsable)) {
		return false;
	}
	return paquete->reportarIncidencia(responsable);
}

bool GestionPaquetes::resolverIncidencia(std::string codigo, Colaborador* responsable) {
	Paquete* paquete = buscarPorCodigo(codigo);
	if (paquete == nullptr || !perteneceAlCentroDelPaquete(paquete, responsable)) {
		return false;
	}
	if (paquete->getEstado() != EstadoPaquete::INCIDENCIA) {
		return false;
	}

	EstadoPaquete previo = paquete->getEstadoPrevioIncidencia();
	if (previo == EstadoPaquete::RECIBIDO) {
		return false; //este caso se resuelve almacenando el paquete, no con este metodo
	}
	return paquete->cambiarEstado(previo, responsable);
}

std::string GestionPaquetes::mostrarListado() const {
	std::stringstream ss;

	if (paquetes.estaVacia()) {
		ss << "No hay paquetes registrados en este centro.\n";
		return ss.str();
	}

	ss << "----- LISTADO DE PAQUETES (" << paquetes.getCantidad() << ") -----\n";
	Nodo<Paquete*>* actual = paquetes.getCabeza();
	while (actual != nullptr) {
		ss << actual->getDato()->mostrar() << "\n";
		actual = actual->getSiguiente();
	}
	return ss.str();
}

int GestionPaquetes::getCantidad() const {
	return paquetes.getCantidad();
}

ListaEnlazada<Paquete*>* GestionPaquetes::obtenerLista() {
	return &paquetes;
}
