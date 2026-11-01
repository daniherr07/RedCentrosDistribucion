#pragma once
#include <string>
#include "TipoCategoria.h"
#include "Celda.h"

class Paquete;

class Bodega
{
private:
	std::string codigo;
	std::string nombre;
	TipoCategoria tipo;
	int filas;
	int columnas;
	Celda** matriz;

	int anchoIndice() const;

public:
	Bodega(std::string codigoNuevo, std::string nombreNuevo, TipoCategoria tipoNuevo, int filasNuevas, int columnasNuevas);
	~Bodega();

	std::string getCodigo() const;
	std::string getNombre() const;
	TipoCategoria getTipo() const;
	int getFilas() const;
	int getColumnas() const;

	bool esCompatible(TipoCategoria categoria) const;
	bool existeCelda(int fila, int columna) const;
	bool estaLibre(int fila, int columna) const;
	Celda* getCelda(int fila, int columna) const;

	bool reservarCelda(int fila, int columna, Paquete* paquete);
	bool liberarCelda(int fila, int columna);

	int totalCeldas() const;
	int contarOcupadas() const;
	int contarLibres() const;
	double porcentajeOcupacion() const;
	double porcentajeDisponible() const;
	bool todasLasCeldasLibres() const;

	std::string formatoCelda(int fila, int columna) const;
	bool buscarCeldaLibre(int& filaEncontrada, int& columnaEncontrada) const;
	std::string mostrarMatriz() const;
};
