#pragma once

class Paquete;

class Celda
{
private:
	bool ocupada;
	Paquete* paquete;

public:
	Celda();

	bool estaOcupada() const;
	Paquete* getPaquete() const;

	bool asignar(Paquete* paqueteNuevo);
	bool liberar();
};
