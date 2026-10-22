#pragma once
#include "TipoCategoria.h"

// Tarifas por kilogramo segun la categoria del paquete. Se guardan como
// datos compartidos (static) de la aplicacion -tal como pide el enunciado-
// en vez de repetirse como literales dentro de cada calculo de costo
// (ver GestionSolicitudes::crearSolicitud).
class Tarifas
{
public:
	static constexpr double TARIFA_GENERAL = 1500.0;
	static constexpr double TARIFA_FRAGIL = 2000.0;
	static constexpr double TARIFA_TECNOLOGIA = 2500.0;
	static constexpr double TARIFA_DOCUMENTOS = 1000.0;

	static double tarifaPorCategoria(TipoCategoria categoria) {
		switch (categoria) {
		case TipoCategoria::GENERAL: return TARIFA_GENERAL;
		case TipoCategoria::FRAGIL: return TARIFA_FRAGIL;
		case TipoCategoria::TECNOLOGIA: return TARIFA_TECNOLOGIA;
		case TipoCategoria::DOCUMENTOS: return TARIFA_DOCUMENTOS;
		default: return 0.0;
		}
	}
};
