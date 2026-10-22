#include "Paquete.h"
#include "Cliente.h"
#include <sstream>

//Tabla de transiciones permitidas segun el enunciado (fila = estado actual, columna = estado destino)
//Orden de los indices: Recibido=0, Almacenado=1, EnTransito=2, Entregado=3, Incidencia=4
static bool TABLA_TRANSICIONES[5][5] = {
	//            Recibido  Almacenado  EnTransito  Entregado  Incidencia
	/*Recibido*/   { false,   true,       false,      false,     true  },
	/*Almacenado*/ { false,   false,      true,       false,     true  },
	/*EnTransito*/ { false,   false,      false,       true,      true  },
	/*Entregado*/  { false,   false,      false,      false,     false },
	/*Incidencia*/ { false,   true,       true,       false,     false }
};

Paquete::Paquete(std::string codigoNuevo, std::string descripcionNueva, double pesoNuevo, TipoCategoria categoriaNueva,
	Cliente* clientePropietarioNuevo, CentroDistribucion* centroNuevo) {
	codigo = codigoNuevo;
	descripcion = descripcionNueva;
	peso = pesoNuevo;
	categoria = categoriaNueva;
	clientePropietario = clientePropietarioNuevo;
	centro = centroNuevo;

	estado = EstadoPaquete::RECIBIDO; //Todo paquete nuevo ingresa como Recibido
	estadoPrevioIncidencia = EstadoPaquete::RECIBIDO;

	bodegaAsignada = nullptr;
	fila = -1;
	columna = -1;
}

Paquete::~Paquete() {
	bitacora.liberarPunteros(); //El paquete es dueno de sus registros de bitacora
}

std::string Paquete::getCodigo() const { return codigo; }
std::string Paquete::getDescripcion() const { return descripcion; }
double Paquete::getPeso() const { return peso; }
TipoCategoria Paquete::getCategoria() const { return categoria; }
Cliente* Paquete::getClientePropietario() const { return clientePropietario; }
CentroDistribucion* Paquete::getCentro() const { return centro; }
EstadoPaquete Paquete::getEstado() const { return estado; }
EstadoPaquete Paquete::getEstadoPrevioIncidencia() const { return estadoPrevioIncidencia; }

Bodega* Paquete::getBodegaAsignada() const { return bodegaAsignada; }
int Paquete::getFila() const { return fila; }
int Paquete::getColumna() const { return columna; }

bool Paquete::tieneUbicacion() const {
	return bodegaAsignada != nullptr;
}

void Paquete::asignarUbicacion(Bodega* bodega, int filaNueva, int columnaNueva) {
	bodegaAsignada = bodega;
	fila = filaNueva;
	columna = columnaNueva;
}

void Paquete::liberarUbicacion() {
	bodegaAsignada = nullptr;
	fila = -1;
	columna = -1;
}

bool Paquete::transicionValida(EstadoPaquete origen, EstadoPaquete destino) {
	int i = static_cast<int>(origen);
	int j = static_cast<int>(destino);
	return TABLA_TRANSICIONES[i][j];
}

bool Paquete::cambiarEstado(EstadoPaquete nuevoEstado, Colaborador* responsable) {
	if (!transicionValida(estado, nuevoEstado)) {
		return false;
	}

	RegistroBitacora* registro = new RegistroBitacora(estado, nuevoEstado, Fecha::hoy(), responsable);
	bitacora.insertarAlFinal(registro);
	estado = nuevoEstado;
	return true;
}

bool Paquete::reportarIncidencia(Colaborador* responsable) {
	if (!transicionValida(estado, EstadoPaquete::INCIDENCIA)) {
		return false;
	}
	estadoPrevioIncidencia = estado; //Se recuerda el origen antes de que cambiarEstado lo sobreescriba
	return cambiarEstado(EstadoPaquete::INCIDENCIA, responsable);
}

std::string Paquete::mostrarBitacora() const {
	std::ostringstream ss;
	if (bitacora.estaVacia()) {
		ss << "\tSin cambios de estado registrados aun.\n";
		return ss.str();
	}
	Nodo<RegistroBitacora*>* actual = bitacora.getCabeza();
	while (actual != nullptr) {
		ss << actual->getDato()->mostrar();
		actual = actual->getSiguiente();
	}
	return ss.str();
}

const ListaEnlazada<RegistroBitacora*>* Paquete::obtenerBitacora() const {
	return &bitacora;
}

std::string Paquete::mostrar() const {
	std::ostringstream ss;
	ss << "Codigo: " << codigo
		<< " | Descripcion: " << descripcion
		<< " | Peso: " << peso << "kg"
		<< " | Categoria: " << nombreCategoria(categoria)
		<< " | Cliente: " << (clientePropietario != nullptr ? clientePropietario->getIdentificacion() : "N/A")
		<< " | Estado: " << nombreEstadoPaquete(estado);
	if (bodegaAsignada != nullptr) {
		ss << " | Ubicacion: " << bodegaAsignada->formatoCelda(fila, columna);
	}
	return ss.str();
}
