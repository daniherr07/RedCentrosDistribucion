#pragma once
#include <iostream>
#include <string>
#include <limits>

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
