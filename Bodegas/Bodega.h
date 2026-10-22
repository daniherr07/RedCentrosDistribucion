#pragma once
#include <string>
#include "TipoCategoria.h"
#include "Celda.h"

class Paquete;

// Cada bodega reserva dinamicamente su propia matriz de celdas (filas x
// columnas, definidas por el usuario al crearla). Celda** es un arreglo
// de punteros a fila, y cada fila es a su vez un arreglo de Celda -> es
// la "matriz bidimensional dinamica" que pide el enunciado.
class Bodega
{
private:
	std::string codigo;
	std::string nombre;
	TipoCategoria tipo;
	int filas;
	int columnas;
	Celda** matriz;

	int anchoIndice() const; //cuantos digitos usar para fila/columna en el id de celda (A-00, A-12, etc)

public:
	Bodega(std::string codigoNuevo, std::string nombreNuevo, TipoCategoria tipoNuevo, int filasNuevas, int columnasNuevas);
	~Bodega(); //Libera la matriz (cada fila y luego el arreglo de filas)

	std::string getCodigo() const;
	std::string getNombre() const;
	TipoCategoria getTipo() const;
	int getFilas() const;
	int getColumnas() const;

	bool esCompatible(TipoCategoria categoria) const; //Compatibilidad directa: mismo tipo que la categoria del paquete
	bool existeCelda(int fila, int columna) const; //Solo valida rango
	bool estaLibre(int fila, int columna) const;
	Celda* getCelda(int fila, int columna) const;

	bool reservarCelda(int fila, int columna, Paquete* paquete);
	bool liberarCelda(int fila, int columna);

	int totalCeldas() const;
	int contarOcupadas() const;
	int contarLibres() const;
	double porcentajeOcupacion() const;
	double porcentajeDisponible() const;
	bool todasLasCeldasLibres() const; //Usado para poder eliminar la bodega

	std::string formatoCelda(int fila, int columna) const; //"CODIGO-FFCC"
	bool buscarCeldaLibre(int& filaEncontrada, int& columnaEncontrada) const; //Primera libre recorriendo fila por fila
	std::string mostrarMatriz() const; //Representacion grafica en consola
};
