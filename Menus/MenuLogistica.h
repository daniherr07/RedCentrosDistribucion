#pragma once
#include "RedCentros.h"

// Interfaz de consola para "Bodegas y consulta de matrices", "Paquetes"
// (incluye almacenamiento, reubicacion e incidencias), "Solicitudes de
// envio" y "Despachos". Igual que en MenuCentros, toda la E/S de estos
// cuatro grupos vive en esta clase; las clases de dominio solo validan y
// devuelven resultados.
class MenuLogistica
{
private:
	RedCentros& red;

	CentroDistribucion* seleccionarCentro();
	Colaborador* seleccionarColaborador(CentroDistribucion* centro); //pide identificacion y valida que exista en el centro
	int leerCategoria(); //pide 1-4 hasta que sea valido y lo devuelve

	//--- Bodegas ---
	void registrarBodega(CentroDistribucion* centro);
	void buscarBodega(CentroDistribucion* centro);
	void mostrarBodegas(CentroDistribucion* centro);
	void consultarMatrizBodega(CentroDistribucion* centro);
	void eliminarBodega(CentroDistribucion* centro);
	void menuBodegas(CentroDistribucion* centro);

	//--- Paquetes ---
	void registrarPaquete(CentroDistribucion* centro);
	void buscarPaquete(CentroDistribucion* centro);
	void mostrarPaquetes(CentroDistribucion* centro);
	void eliminarPaquete(CentroDistribucion* centro);
	void almacenarPaquete(CentroDistribucion* centro);
	void ejecutarAlmacenamiento(CentroDistribucion* centro, Paquete* paquete); //logica compartida: recomendar bodega/celda y guardar
	void reubicarPaquete(CentroDistribucion* centro);
	void reportarIncidencia(CentroDistribucion* centro);
	void resolverIncidencia(CentroDistribucion* centro);
	void menuPaquetes(CentroDistribucion* centro);

	//--- Solicitudes de envio ---
	void crearSolicitud(CentroDistribucion* centro);
	void buscarSolicitud(CentroDistribucion* centro);
	void mostrarSolicitudes(CentroDistribucion* centro);
	void aprobarSolicitud(CentroDistribucion* centro);
	void rechazarOAnularSolicitud(CentroDistribucion* centro);
	void menuSolicitudes(CentroDistribucion* centro);

	//--- Despachos ---
	void buscarDespacho(CentroDistribucion* centro);
	void mostrarDespachos(CentroDistribucion* centro);
	void finalizarDespacho(CentroDistribucion* centro);
	void menuDespachos(CentroDistribucion* centro);

public:
	MenuLogistica(RedCentros& red);

	void menuGeneral(); //entra eligiendo un centro y de ahi deja ir a bodegas/paquetes/solicitudes/despachos
};
