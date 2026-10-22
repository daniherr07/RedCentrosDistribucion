#pragma once
#include <string>

// Un solo enum representa a la vez la categoria de un Paquete y el tipo de
// una Bodega. Al compartir el mismo tipo, la "compatibilidad directa" que
// pide el enunciado (General-General, Fragil-Fragil, etc.) se reduce a una
// simple comparacion de igualdad (ver Bodega::esCompatible), en vez de
// mantener dos enums distintos con una tabla de equivalencias aparte.
enum class TipoCategoria
{
	GENERAL = 1,
	FRAGIL = 2,
	TECNOLOGIA = 3,
	DOCUMENTOS = 4
};

inline bool codigoCategoriaValido(int codigo) {
	return codigo >= 1 && codigo <= 4;
}

inline TipoCategoria categoriaDesdeCodigo(int codigo) {
	return static_cast<TipoCategoria>(codigo);
}

inline std::string nombreCategoria(TipoCategoria tipo) {
	switch (tipo) {
	case TipoCategoria::GENERAL: return "General";
	case TipoCategoria::FRAGIL: return "Fragil";
	case TipoCategoria::TECNOLOGIA: return "Tecnologia";
	case TipoCategoria::DOCUMENTOS: return "Documentos";
	default: return "Desconocida";
	}
}
