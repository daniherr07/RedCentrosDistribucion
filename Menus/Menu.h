#pragma once
#include "RedCentros.h"
#include "Reportes.h"
#include "MenuCentros.h"
#include "MenuLogistica.h"

class Menu
{
private:
	RedCentros red;
	Reportes reportes;
	MenuCentros menuCentros;
	MenuLogistica menuLogistica;

	CentroDistribucion* seleccionarCentro();

	void menuReportes();
	void reporteHistorialCliente();
	void reporteClientesPorEnvios();
	void reporteBitacoraPaquete();
	void reporteConsultaDespacho();
	void reporteOcupacionBodegas();
	void reporteDespachosPorColaborador();

public:
	Menu();

	void menuPrincipal();
};
