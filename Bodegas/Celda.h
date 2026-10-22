#pragma once

class Paquete; // Solo se usa como puntero, no se necesita el .h completo aqui

// Una celda es una posicion dentro de la matriz de una bodega. Puede
// estar libre o tener un paquete asignado. Su fila/columna las conoce
// quien la recorre (Bodega), por eso la celda no necesita guardarlas.
class Celda
{
private:
	bool ocupada;
	Paquete* paquete; //No es dueno del paquete, solo lo referencia

public:
	Celda(); //Constructor por defecto, necesario para el new Celda[columnas]

	bool estaOcupada() const;
	Paquete* getPaquete() const;

	bool asignar(Paquete* paqueteNuevo); //false si ya estaba ocupada
	bool liberar(); //false si ya estaba libre
};
