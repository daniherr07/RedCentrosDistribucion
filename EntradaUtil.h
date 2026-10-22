#pragma once
#include <iostream>
#include <string>
#include <limits>

// Funciones de lectura robusta de datos por consola, compartidas por los
// tres modulos de menu (Menu, MenuCentros, MenuLogistica) para no repetir
// la misma validacion de entrada tres veces.
inline int leerEntero() {
	int numero;
	while (!(std::cin >> numero)) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Entrada invalida. Ingrese un numero entero: ";
	}
	return numero;
}

inline double leerDecimal() {
	double numero;
	while (!(std::cin >> numero)) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Entrada invalida. Ingrese un numero: ";
	}
	return numero;
}

// Lee una linea completa (permite espacios). Si justo antes se leyo con
// cin >> (leerEntero/leerDecimal/leerPalabra), queda pendiente el '\n' de
// esa linea y hay que descartarlo; pero si la llamada anterior tambien fue
// leerLinea(), ese '\n' ya se consumio y NO hay que descartar nada, o se
// perderia la siguiente linea completa. Por eso solo se ignora un '\n'
// cuando es realmente el proximo caracter pendiente en el buffer.
inline std::string leerLinea() {
	if (std::cin.peek() == '\n') {
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}
	std::string linea;
	std::getline(std::cin, linea);
	return linea;
}

inline std::string leerPalabra() {
	std::string palabra;
	std::cin >> palabra;
	return palabra;
}

inline bool leerConfirmacion(const std::string& mensaje) {
	char respuesta;
	std::cout << mensaje << " (S/N): ";
	std::cin >> respuesta;
	return respuesta == 'S' || respuesta == 's';
}

inline void pausar() {
	system("pause");
}

inline void limpiarPantalla() {
	system("cls");
}
