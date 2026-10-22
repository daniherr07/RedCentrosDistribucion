#pragma once
#include "RedCentros.h"
#include "Reportes.h"
#include "MenuCentros.h"
#include "MenuLogistica.h"

// Clase raiz de la interfaz: posee la Red de centros y las dos fachadas de
// menu (MenuCentros y MenuLogistica), ademas de resolver directamente el
// grupo de Reportes, que necesita cruzar datos de varios modulos a la vez.
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
