#pragma once
#include "RedCentros.h"

class MenuLogistica
{
private:
	RedCentros& red;

	CentroDistribucion* seleccionarCentro();
	Colaborador* seleccionarColaborador(CentroDistribucion* centro);
	int leerCategoria();

	void registrarBodega(CentroDistribucion* centro);
	void buscarBodega(CentroDistribucion* centro);
	void mostrarBodegas(CentroDistribucion* centro);
	void consultarMatrizBodega(CentroDistribucion* centro);
	void eliminarBodega(CentroDistribucion* centro);
	void menuBodegas(CentroDistribucion* centro);

	void registrarPaquete(CentroDistribucion* centro);
	void buscarPaquete();
	void mostrarPaquetes(CentroDistribucion* centro);
	void eliminarPaquete();
	void almacenarPaquete(CentroDistribucion* centro);
	void ejecutarAlmacenamiento(CentroDistribucion* centro, Paquete* paquete);
	void reubicarPaquete(CentroDistribucion* centro);
	void reportarIncidencia(CentroDistribucion* centro);
	void resolverIncidencia(CentroDistribucion* centro);
	void menuPaquetes(CentroDistribucion* centro);

	void crearSolicitud(CentroDistribucion* centro);
	void buscarSolicitud();
	void mostrarSolicitudes(CentroDistribucion* centro);
	void aprobarSolicitud(CentroDistribucion* centro);
	void rechazarOAnularSolicitud(CentroDistribucion* centro);
	void menuSolicitudes(CentroDistribucion* centro);

	void buscarDespacho();
	void mostrarDespachos(CentroDistribucion* centro);
	void finalizarDespacho(CentroDistribucion* centro);
	void menuDespachos(CentroDistribucion* centro);

public:
	MenuLogistica(RedCentros& red);

	void menuGeneral();
};
