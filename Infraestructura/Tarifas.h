#pragma once
#include "TipoCategoria.h"

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
