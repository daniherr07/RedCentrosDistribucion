#pragma once

class Paquete; // Solo se usa como puntero, no se necesita el .h completo aqui

// Una celda es una posicion (fila,columna) dentro de la matriz de una
// bodega. Puede estar libre o tener un paquete asignado.
class Celda
{
private:
	int fila;
	int columna;
	bool ocupada;
	Paquete* paquete; //No es dueno del paquete, solo lo referencia

public:
	Celda(); //Constructor por defecto, necesario para el new Celda[columnas]
	void inicializar(int filaNueva, int columnaNueva); //Bodega lo llama justo despues de crear la matriz

	int getFila() const;
	int getColumna() const;
	bool estaOcupada() const;
	Paquete* getPaquete() const;

	bool asignar(Paquete* paqueteNuevo); //false si ya estaba ocupada
	bool liberar(); //false si ya estaba libre
};
