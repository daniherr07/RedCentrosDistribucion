#include "Bodega.h"
#include "Paquete.h"
#include <sstream>
#include <iomanip>

Bodega::Bodega(std::string codigoNuevo, std::string nombreNuevo, TipoCategoria tipoNuevo, int filasNuevas, int columnasNuevas) {
	codigo = codigoNuevo;
	nombre = nombreNuevo;
	tipo = tipoNuevo;
	filas = filasNuevas;
	columnas = columnasNuevas;

	matriz = new Celda * [filas]; //arreglo de punteros a fila
	for (int i = 0; i < filas; i++) {
		matriz[i] = new Celda[columnas]; //cada fila es un arreglo de Celda, ya libres por el constructor de Celda
	}
}

Bodega::~Bodega() {
	for (int i = 0; i < filas; i++) {
		delete[] matriz[i];
	}
	delete[] matriz;
}

std::string Bodega::getCodigo() const { return codigo; }
std::string Bodega::getNombre() const { return nombre; }
TipoCategoria Bodega::getTipo() const { return tipo; }
int Bodega::getFilas() const { return filas; }
int Bodega::getColumnas() const { return columnas; }

bool Bodega::esCompatible(TipoCategoria categoria) const {
	return tipo == categoria;
}

bool Bodega::existeCelda(int fila, int columna) const {
	if (fila < 0 || fila >= filas) { //fuera de rango de filas
		return false;
	}
	if (columna < 0 || columna >= columnas) { //fuera de rango de columnas
		return false;
	}
	return true;
}

bool Bodega::estaLibre(int fila, int columna) const {
	if (!existeCelda(fila, columna)) {
		return false;
	}
	return !matriz[fila][columna].estaOcupada();
}

Celda* Bodega::getCelda(int fila, int columna) const {
	if (!existeCelda(fila, columna)) {
		return nullptr;
	}
	return &matriz[fila][columna];
}

bool Bodega::reservarCelda(int fila, int columna, Paquete* paquete) {
	if (!existeCelda(fila, columna)) {
		return false;
	}
	return matriz[fila][columna].asignar(paquete);
}

bool Bodega::liberarCelda(int fila, int columna) {
	if (!existeCelda(fila, columna)) {
		return false;
	}
	return matriz[fila][columna].liberar();
}

int Bodega::totalCeldas() const {
	return filas * columnas;
}

int Bodega::contarOcupadas() const {
	int total = 0;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (matriz[i][j].estaOcupada()) {
				total++;
			}
		}
	}
	return total;
}

int Bodega::contarLibres() const {
	return totalCeldas() - contarOcupadas();
}

double Bodega::porcentajeOcupacion() const {
	if (totalCeldas() == 0) {
		return 0.0;
	}
	return (contarOcupadas() * 100.0) / totalCeldas();
}

double Bodega::porcentajeDisponible() const {
	if (totalCeldas() == 0) {
		return 0.0;
	}
	return (contarLibres() * 100.0) / totalCeldas();
}

bool Bodega::todasLasCeldasLibres() const {
	return contarOcupadas() == 0;
}

int Bodega::anchoIndice() const {
	//El enunciado usa 1 digito por indice cuando van de 0 a 9 (A-00, A-12).
	//Si una bodega tiene 10 o mas filas o columnas, se usan 2 (o mas) digitos
	//por indice para que fila y columna se sigan distinguiendo con claridad.
	int maxIndice = (filas - 1 > columnas - 1) ? filas - 1 : columnas - 1;
	if (maxIndice < 0) {
		maxIndice = 0;
	}
	int ancho = 1;
	int valor = maxIndice;
	while (valor >= 10) {
		valor /= 10;
		ancho++;
	}
	return ancho;
}

std::string Bodega::formatoCelda(int fila, int columna) const {
	int ancho = anchoIndice();
	std::ostringstream ss;
	ss << codigo << "-"
		<< std::setfill('0') << std::setw(ancho) << fila
		<< std::setfill('0') << std::setw(ancho) << columna;
	return ss.str();
}

bool Bodega::buscarCeldaLibre(int& filaEncontrada, int& columnaEncontrada) const {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (!matriz[i][j].estaOcupada()) {
				filaEncontrada = i;
				columnaEncontrada = j;
				return true;
			}
		}
	}
	return false;
}

std::string Bodega::mostrarMatriz() const {
	std::ostringstream ss;
	ss << "Bodega " << codigo << " (" << nombre << " - " << nombreCategoria(tipo) << ")\n";
	ss << "Distribucion: " << filas << " filas x " << columnas << " columnas\n\n";

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			ss << formatoCelda(i, j) << ":";
			if (matriz[i][j].estaOcupada()) {
				ss << matriz[i][j].getPaquete()->getCodigo();
			}
			else {
				ss << "LIBRE";
			}
			ss << "\t";
		}
		ss << "\n";
	}
	return ss.str();
}
