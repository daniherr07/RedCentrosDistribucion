#include "MenuLogistica.h"
#include "EntradaUtil.h"
#include <iostream>

//Valida un texto de hora con formato HH:MM (24 horas), sin usar <regex>
static bool horaValida(const std::string& hora) {
	if (hora.size() != 5 || hora[2] != ':') {
		return false;
	}
	for (int i = 0; i < 5; i++) {
		if (i == 2) {
			continue;
		}
		if (hora[i] < '0' || hora[i] > '9') {
			return false;
		}
	}
	int horas = (hora[0] - '0') * 10 + (hora[1] - '0');
	int minutos = (hora[3] - '0') * 10 + (hora[4] - '0');
	return horas <= 23 && minutos <= 59;
}

MenuLogistica::MenuLogistica(RedCentros& red) : red(red) {
}

CentroDistribucion* MenuLogistica::seleccionarCentro() {
	std::cout << red.mostrarListado() << std::endl;
	if (red.getCantidad() == 0) {
		return nullptr;
	}

	std::cout << "Ingrese el codigo del centro: ";
	std::string codigo = leerPalabra();

	CentroDistribucion* centro = red.buscarCentroPorCodigo(codigo);
	if (centro == nullptr) {
		std::cout << "No existe un centro con ese codigo.\n";
	}
	return centro;
}

Colaborador* MenuLogistica::seleccionarColaborador(CentroDistribucion* centro) {
	std::cout << "Identificacion del colaborador responsable: ";
	std::string id = leerPalabra();

	Colaborador* colaborador = centro->getGestionColaboradores()->buscarPorIdentificacion(id);
	if (colaborador == nullptr) {
		std::cout << "No existe un colaborador con esa identificacion en este centro.\n";
	}
	return colaborador;
}

int MenuLogistica::leerCategoria() {
	int codigo;
	do {
		std::cout << "Categorias disponibles:\n";
		std::cout << "  1. General\n  2. Fragil\n  3. Tecnologia\n  4. Documentos\n";
		std::cout << "Seleccione el codigo de categoria: ";
		codigo = leerEntero();
		if (!codigoCategoriaValido(codigo)) {
			std::cout << "Codigo de categoria invalido.\n";
		}
	} while (!codigoCategoriaValido(codigo));
	return codigo;
}

// =======================================================================
// Bodegas
// =======================================================================

void MenuLogistica::registrarBodega(CentroDistribucion* centro) {
	std::cout << "\n----- Registrar bodega -----\n";
	std::cout << "Codigo de la bodega (unico en el centro): ";
	std::string codigo = leerPalabra();

	if (centro->getGestionBodegas()->existeCodigo(codigo)) {
		std::cout << "Ya existe una bodega con ese codigo en este centro.\n";
		return;
	}

	std::cout << "Nombre de la bodega: ";
	std::string nombre = leerLinea();
	TipoCategoria tipo = categoriaDesdeCodigo(leerCategoria());

	int filas, columnas;
	do {
		std::cout << "Cantidad de filas (entero mayor que 0): ";
		filas = leerEntero();
		if (filas <= 0) {
			std::cout << "Debe ser mayor que cero.\n";
		}
	} while (filas <= 0);

	do {
		std::cout << "Cantidad de columnas (entero mayor que 0): ";
		columnas = leerEntero();
		if (columnas <= 0) {
			std::cout << "Debe ser mayor que cero.\n";
		}
	} while (columnas <= 0);

	if (centro->getGestionBodegas()->registrarBodega(codigo, nombre, tipo, filas, columnas)) {
		std::cout << "Bodega registrada exitosamente.\n";
	}
	else {
		std::cout << "No se pudo registrar la bodega.\n";
	}
}

void MenuLogistica::buscarBodega(CentroDistribucion* centro) {
	std::cout << "\n----- Buscar bodega -----\n";
	std::cout << "Codigo de la bodega: ";
	std::string codigo = leerPalabra();

	Bodega* bodega = centro->getGestionBodegas()->buscarPorCodigo(codigo);
	if (bodega == nullptr) {
		std::cout << "No existe una bodega con ese codigo en este centro.\n";
		return;
	}

	std::cout << "Codigo: " << bodega->getCodigo()
		<< " | Nombre: " << bodega->getNombre()
		<< " | Tipo: " << nombreCategoria(bodega->getTipo())
		<< " | Distribucion: " << bodega->getFilas() << "x" << bodega->getColumnas()
		<< " | Ocupacion: " << bodega->porcentajeOcupacion() << "%\n";
}

void MenuLogistica::mostrarBodegas(CentroDistribucion* centro) {
	std::cout << "\n" << centro->getGestionBodegas()->mostrarListado() << std::endl;
}

void MenuLogistica::consultarMatrizBodega(CentroDistribucion* centro) {
	std::cout << "\n----- Consultar matriz de una bodega -----\n";
	std::cout << "Codigo de la bodega: ";
	std::string codigo = leerPalabra();

	Bodega* bodega = centro->getGestionBodegas()->buscarPorCodigo(codigo);
	if (bodega == nullptr) {
		std::cout << "No existe una bodega con ese codigo en este centro.\n";
		return;
	}
	std::cout << "\n" << bodega->mostrarMatriz() << std::endl;
}

void MenuLogistica::eliminarBodega(CentroDistribucion* centro) {
	std::cout << "\n----- Eliminar bodega -----\n";
	std::cout << "Codigo de la bodega: ";
	std::string codigo = leerPalabra();

	Bodega* bodega = centro->getGestionBodegas()->buscarPorCodigo(codigo);
	if (bodega == nullptr) {
		std::cout << "No existe una bodega con ese codigo en este centro.\n";
		return;
	}
	if (!bodega->todasLasCeldasLibres()) {
		std::cout << "No se puede eliminar: la bodega tiene al menos un paquete almacenado.\n";
		return;
	}

	centro->getGestionBodegas()->eliminar(codigo);
	std::cout << "Bodega eliminada exitosamente.\n";
}

void MenuLogistica::menuBodegas(CentroDistribucion* centro) {
	int opcion;
	do {
		std::cout << "\n----- Bodegas de " << centro->getCodigo() << " -----\n";
		std::cout << "1. Registrar bodega\n";
		std::cout << "2. Buscar bodega\n";
		std::cout << "3. Mostrar bodegas del centro\n";
		std::cout << "4. Consultar matriz de una bodega\n";
		std::cout << "5. Eliminar bodega\n";
		std::cout << "6. Volver\n";
		std::cout << "Seleccione una opcion: ";
		opcion = leerEntero();

		switch (opcion) {
		case 1: registrarBodega(centro); break;
		case 2: buscarBodega(centro); break;
		case 3: mostrarBodegas(centro); break;
		case 4: consultarMatrizBodega(centro); break;
		case 5: eliminarBodega(centro); break;
		case 6: break;
		default: std::cout << "Opcion invalida.\n"; break;
		}
		if (opcion != 6) {
			pausar();
		}
	} while (opcion != 6);
}

// =======================================================================
// Paquetes
// =======================================================================

void MenuLogistica::registrarPaquete(CentroDistribucion* centro) {
	std::cout << "\n----- Registrar paquete -----\n";
	std::cout << "Codigo del paquete (unico en todo el sistema): ";
	std::string codigo = leerPalabra();

	if (red.existeCodigoPaqueteGlobal(codigo)) {
		std::cout << "Ya existe un paquete con ese codigo en el sistema.\n";
		return;
	}

	std::cout << "Descripcion: ";
	std::string descripcion = leerLinea();
	if (descripcion.empty()) {
		std::cout << "La descripcion no puede estar vacia.\n";
		return;
	}

	double peso;
	do {
		std::cout << "Peso en kg (mayor que 0): ";
		peso = leerDecimal();
		if (peso <= 0.0) {
			std::cout << "El peso debe ser mayor que cero.\n";
		}
	} while (peso <= 0.0);

	TipoCategoria categoria = categoriaDesdeCodigo(leerCategoria());

	std::cout << "Identificacion del cliente propietario (debe pertenecer a este centro): ";
	std::string idCliente = leerPalabra();
	Cliente* cliente = centro->getGestionClientes()->buscarPorIdentificacion(idCliente);
	if (cliente == nullptr) {
		std::cout << "No existe un cliente con esa identificacion en este centro.\n";
		return;
	}

	Paquete* nuevo = centro->getGestionPaquetes()->registrarPaquete(codigo, descripcion, peso, categoria, cliente, centro);
	if (nuevo != nullptr) {
		std::cout << "Paquete registrado exitosamente con estado Recibido.\n";
	}
	else {
		std::cout << "No se pudo registrar el paquete.\n";
	}
}

void MenuLogistica::buscarPaquete(CentroDistribucion* centro) {
	std::cout << "\n----- Buscar paquete -----\n";
	std::cout << "Codigo del paquete: ";
	std::string codigo = leerPalabra();

	Paquete* paquete = centro->getGestionPaquetes()->buscarPorCodigo(codigo);
	if (paquete == nullptr) {
		std::cout << "No existe un paquete con ese codigo en este centro.\n";
		return;
	}
	std::cout << paquete->mostrar() << "\n";
}

void MenuLogistica::mostrarPaquetes(CentroDistribucion* centro) {
	std::cout << "\n" << centro->getGestionPaquetes()->mostrarListado() << std::endl;
}

void MenuLogistica::eliminarPaquete(CentroDistribucion* centro) {
	std::cout << "\n----- Eliminar paquete -----\n";
	std::cout << "Codigo del paquete: ";
	std::string codigo = leerPalabra();

	if (centro->getGestionPaquetes()->buscarPorCodigo(codigo) == nullptr) {
		std::cout << "No existe un paquete con ese codigo en este centro.\n";
		return;
	}

	if (centro->eliminarPaquete(codigo)) {
		std::cout << "Paquete eliminado exitosamente.\n";
	}
	else {
		std::cout << "No se puede eliminar: el paquete no esta Recibido, tiene una ubicacion asignada,\n";
		std::cout << "o tiene solicitudes/despachos asociados.\n";
	}
}

void MenuLogistica::ejecutarAlmacenamiento(CentroDistribucion* centro, Paquete* paquete) {
	TipoCategoria categoria = paquete->getCategoria();
	Bodega* recomendada = centro->getGestionBodegas()->mejorBodegaCompatible(categoria);

	if (recomendada == nullptr) {
		std::cout << "No existe una bodega compatible con espacio disponible para la categoria "
			<< nombreCategoria(categoria) << ".\n";
		return;
	}

	int filaRecomendada = -1, columnaRecomendada = -1;
	recomendada->buscarCeldaLibre(filaRecomendada, columnaRecomendada);

	std::cout << "Bodega recomendada: " << recomendada->getCodigo() << " (" << recomendada->getNombre() << "),"
		<< " celda recomendada: " << recomendada->formatoCelda(filaRecomendada, columnaRecomendada)
		<< " (" << recomendada->porcentajeDisponible() << "% disponible)\n";

	Bodega* bodegaElegida = recomendada;
	int filaElegida = filaRecomendada;
	int columnaElegida = columnaRecomendada;

	if (!leerConfirmacion("Desea usar la bodega y celda recomendadas?")) {
		std::cout << "Codigo de la bodega donde desea almacenar: ";
		std::string codigoBodega = leerPalabra();
		bodegaElegida = centro->getGestionBodegas()->buscarPorCodigo(codigoBodega);
		if (bodegaElegida == nullptr) {
			std::cout << "No existe una bodega con ese codigo en este centro.\n";
			return;
		}
		if (!bodegaElegida->esCompatible(categoria)) {
			std::cout << "Esa bodega no es compatible con la categoria del paquete.\n";
			return;
		}

		std::cout << bodegaElegida->mostrarMatriz() << std::endl;
		std::cout << "Fila de la celda: ";
		filaElegida = leerEntero();
		std::cout << "Columna de la celda: ";
		columnaElegida = leerEntero();
	}

	Colaborador* responsable = seleccionarColaborador(centro);
	if (responsable == nullptr) {
		return;
	}

	if (centro->getGestionPaquetes()->almacenarPaquete(paquete, bodegaElegida, filaElegida, columnaElegida, responsable)) {
		std::cout << "Paquete almacenado exitosamente en " << bodegaElegida->formatoCelda(filaElegida, columnaElegida) << ".\n";
	}
	else {
		std::cout << "No se pudo almacenar el paquete. Verifique que la celda exista y este disponible.\n";
	}
}

void MenuLogistica::almacenarPaquete(CentroDistribucion* centro) {
	std::cout << "\n----- Almacenar paquete -----\n";
	std::cout << "Codigo del paquete: ";
	std::string codigo = leerPalabra();

	Paquete* paquete = centro->getGestionPaquetes()->buscarPorCodigo(codigo);
	if (paquete == nullptr) {
		std::cout << "No existe un paquete con ese codigo en este centro.\n";
		return;
	}

	bool desdeRecibido = paquete->getEstado() == EstadoPaquete::RECIBIDO;
	bool desdeIncidenciaDeRecibido = paquete->getEstado() == EstadoPaquete::INCIDENCIA
		&& paquete->getEstadoPrevioIncidencia() == EstadoPaquete::RECIBIDO;

	if (!desdeRecibido && !desdeIncidenciaDeRecibido) {
		std::cout << "El paquete debe estar Recibido para poder almacenarse. Estado actual: "
			<< nombreEstadoPaquete(paquete->getEstado()) << "\n";
		return;
	}

	ejecutarAlmacenamiento(centro, paquete);
}

void MenuLogistica::reubicarPaquete(CentroDistribucion* centro) {
	std::cout << "\n----- Reubicar paquete -----\n";
	std::cout << "Codigo del paquete: ";
	std::string codigo = leerPalabra();

	Paquete* paquete = centro->getGestionPaquetes()->buscarPorCodigo(codigo);
	if (paquete == nullptr) {
		std::cout << "No existe un paquete con ese codigo en este centro.\n";
		return;
	}
	if (paquete->getEstado() != EstadoPaquete::ALMACENADO) {
		std::cout << "Solo se pueden reubicar paquetes Almacenados. Estado actual: "
			<< nombreEstadoPaquete(paquete->getEstado()) << "\n";
		return;
	}

	Bodega* bodegaActual = paquete->getBodegaAsignada();
	std::cout << "Ubicacion actual: " << bodegaActual->formatoCelda(paquete->getFila(), paquete->getColumna()) << "\n";

	std::cout << "Codigo de la bodega destino (puede ser la misma u otra compatible): ";
	std::string codigoBodega = leerPalabra();
	Bodega* bodegaDestino = centro->getGestionBodegas()->buscarPorCodigo(codigoBodega);
	if (bodegaDestino == nullptr) {
		std::cout << "No existe una bodega con ese codigo en este centro.\n";
		return;
	}

	std::cout << bodegaDestino->mostrarMatriz() << std::endl;
	std::cout << "Fila de la celda destino: ";
	int fila = leerEntero();
	std::cout << "Columna de la celda destino: ";
	int columna = leerEntero();

	if (centro->getGestionPaquetes()->reubicarPaquete(paquete, bodegaDestino, fila, columna)) {
		std::cout << "Paquete reubicado exitosamente a " << bodegaDestino->formatoCelda(fila, columna) << ".\n";
	}
	else {
		std::cout << "No se pudo reubicar el paquete. Verifique compatibilidad, existencia y disponibilidad de la celda destino.\n";
	}
}

void MenuLogistica::reportarIncidencia(CentroDistribucion* centro) {
	std::cout << "\n----- Reportar incidencia -----\n";
	std::cout << "Codigo del paquete: ";
	std::string codigo = leerPalabra();

	if (centro->getGestionPaquetes()->buscarPorCodigo(codigo) == nullptr) {
		std::cout << "No existe un paquete con ese codigo en este centro.\n";
		return;
	}

	Colaborador* responsable = seleccionarColaborador(centro);
	if (responsable == nullptr) {
		return;
	}

	if (centro->getGestionPaquetes()->reportarIncidencia(codigo, responsable)) {
		std::cout << "Incidencia registrada exitosamente.\n";
	}
	else {
		std::cout << "No se pudo registrar la incidencia (el estado actual del paquete no lo permite).\n";
	}
}

void MenuLogistica::resolverIncidencia(CentroDistribucion* centro) {
	std::cout << "\n----- Resolver incidencia -----\n";
	std::cout << "Codigo del paquete: ";
	std::string codigo = leerPalabra();

	Paquete* paquete = centro->getGestionPaquetes()->buscarPorCodigo(codigo);
	if (paquete == nullptr) {
		std::cout << "No existe un paquete con ese codigo en este centro.\n";
		return;
	}
	if (paquete->getEstado() != EstadoPaquete::INCIDENCIA) {
		std::cout << "Ese paquete no se encuentra en Incidencia.\n";
		return;
	}

	if (paquete->getEstadoPrevioIncidencia() == EstadoPaquete::RECIBIDO) {
		std::cout << "Esta incidencia se origino estando el paquete Recibido: se resuelve almacenandolo.\n";
		ejecutarAlmacenamiento(centro, paquete);
		return;
	}

	Colaborador* responsable = seleccionarColaborador(centro);
	if (responsable == nullptr) {
		return;
	}

	if (centro->getGestionPaquetes()->resolverIncidencia(codigo, responsable)) {
		std::cout << "Incidencia resuelta exitosamente.\n";
	}
	else {
		std::cout << "No se pudo resolver la incidencia.\n";
	}
}

void MenuLogistica::menuPaquetes(CentroDistribucion* centro) {
	int opcion;
	do {
		std::cout << "\n----- Paquetes de " << centro->getCodigo() << " -----\n";
		std::cout << "1. Registrar paquete\n";
		std::cout << "2. Buscar paquete\n";
		std::cout << "3. Mostrar paquetes del centro\n";
		std::cout << "4. Eliminar paquete\n";
		std::cout << "5. Almacenar paquete\n";
		std::cout << "6. Reubicar paquete\n";
		std::cout << "7. Reportar incidencia\n";
		std::cout << "8. Resolver incidencia\n";
		std::cout << "9. Volver\n";
		std::cout << "Seleccione una opcion: ";
		opcion = leerEntero();

		switch (opcion) {
		case 1: registrarPaquete(centro); break;
		case 2: buscarPaquete(centro); break;
		case 3: mostrarPaquetes(centro); break;
		case 4: eliminarPaquete(centro); break;
		case 5: almacenarPaquete(centro); break;
		case 6: reubicarPaquete(centro); break;
		case 7: reportarIncidencia(centro); break;
		case 8: resolverIncidencia(centro); break;
		case 9: break;
		default: std::cout << "Opcion invalida.\n"; break;
		}
		if (opcion != 9) {
			pausar();
		}
	} while (opcion != 9);
}

// =======================================================================
// Solicitudes de envio
// =======================================================================

void MenuLogistica::crearSolicitud(CentroDistribucion* centro) {
	std::cout << "\n----- Crear solicitud de envio -----\n";
	std::cout << "Codigo de la solicitud (unico en todo el sistema): ";
	std::string codigo = leerPalabra();

	if (red.existeCodigoSolicitudGlobal(codigo)) {
		std::cout << "Ya existe una solicitud con ese codigo en el sistema.\n";
		return;
	}

	std::cout << "Codigo del paquete: ";
	std::string codigoPaquete = leerPalabra();
	Paquete* paquete = centro->getGestionPaquetes()->buscarPorCodigo(codigoPaquete);
	if (paquete == nullptr) {
		std::cout << "No existe un paquete con ese codigo en este centro.\n";
		return;
	}

	Colaborador* colaborador = seleccionarColaborador(centro);
	if (colaborador == nullptr) {
		return;
	}

	std::cout << "Destino de entrega (direccion o descripcion): ";
	std::string destino = leerLinea();

	SolicitudEnvio* nueva = centro->getGestionSolicitudes()->crearSolicitud(
		codigo, paquete->getClientePropietario(), paquete, colaborador, centro, destino);

	if (nueva != nullptr) {
		std::cout << "Solicitud creada exitosamente. Costo estimado: " << nueva->getCostoEstimado() << "\n";
	}
	else {
		std::cout << "No se pudo crear la solicitud. Verifique que el paquete este Almacenado y que no tenga\n";
		std::cout << "ya una solicitud Pendiente o Aprobada.\n";
	}
}

void MenuLogistica::buscarSolicitud(CentroDistribucion* centro) {
	std::cout << "\n----- Buscar solicitud -----\n";
	std::cout << "Codigo de la solicitud: ";
	std::string codigo = leerPalabra();

	SolicitudEnvio* solicitud = centro->getGestionSolicitudes()->buscarPorCodigo(codigo);
	if (solicitud == nullptr) {
		std::cout << "No existe una solicitud con ese codigo en este centro.\n";
		return;
	}
	std::cout << solicitud->mostrar() << "\n";
}

void MenuLogistica::mostrarSolicitudes(CentroDistribucion* centro) {
	std::cout << "\n" << centro->getGestionSolicitudes()->mostrarListado() << std::endl;
}

void MenuLogistica::aprobarSolicitud(CentroDistribucion* centro) {
	std::cout << "\n----- Aprobar solicitud -----\n";
	std::cout << "Codigo de la solicitud: ";
	std::string codigo = leerPalabra();

	SolicitudEnvio* solicitud = centro->getGestionSolicitudes()->buscarPorCodigo(codigo);
	if (solicitud == nullptr) {
		std::cout << "No existe una solicitud con ese codigo en este centro.\n";
		return;
	}
	if (solicitud->getEstado() != EstadoSolicitud::PENDIENTE) {
		std::cout << "Solo se pueden aprobar solicitudes Pendientes. Estado actual: "
			<< nombreEstadoSolicitud(solicitud->getEstado()) << "\n";
		return;
	}

	Colaborador* responsable = seleccionarColaborador(centro);
	if (responsable == nullptr) {
		return;
	}

	std::cout << "Codigo del despacho a crear (unico en todo el sistema): ";
	std::string codigoDespacho = leerPalabra();
	if (red.existeCodigoDespachoGlobal(codigoDespacho)) {
		std::cout << "Ya existe un despacho con ese codigo en el sistema.\n";
		return;
	}

	std::string hora;
	do {
		std::cout << "Hora del despacho (formato HH:MM): ";
		hora = leerPalabra();
		if (!horaValida(hora)) {
			std::cout << "Formato de hora invalido.\n";
		}
	} while (!horaValida(hora));

	if (centro->aprobarSolicitud(codigo, responsable, codigoDespacho, hora)) {
		std::cout << "Solicitud aprobada y despacho " << codigoDespacho << " creado exitosamente.\n";
	}
	else {
		std::cout << "No se pudo aprobar la solicitud. Verifique que el paquete siga Almacenado y que\n";
		std::cout << "no tenga ya un despacho asociado.\n";
	}
}

void MenuLogistica::rechazarOAnularSolicitud(CentroDistribucion* centro) {
	std::cout << "\n----- Rechazar o anular solicitud -----\n";
	std::cout << "Codigo de la solicitud: ";
	std::string codigo = leerPalabra();

	SolicitudEnvio* solicitud = centro->getGestionSolicitudes()->buscarPorCodigo(codigo);
	if (solicitud == nullptr) {
		std::cout << "No existe una solicitud con ese codigo en este centro.\n";
		return;
	}
	if (solicitud->getEstado() != EstadoSolicitud::PENDIENTE) {
		std::cout << "Solo se puede cambiar el estado de solicitudes Pendientes.\n";
		return;
	}

	int opcion;
	do {
		std::cout << "1. Rechazar\n2. Anular\nSeleccione una opcion: ";
		opcion = leerEntero();
		if (opcion != 1 && opcion != 2) {
			std::cout << "Opcion invalida.\n";
		}
	} while (opcion != 1 && opcion != 2);

	bool exito = (opcion == 1)
		? centro->getGestionSolicitudes()->rechazar(codigo)
		: centro->getGestionSolicitudes()->anular(codigo);

	std::cout << (exito ? "Solicitud actualizada exitosamente.\n" : "No se pudo actualizar la solicitud.\n");
}

void MenuLogistica::menuSolicitudes(CentroDistribucion* centro) {
	int opcion;
	do {
		std::cout << "\n----- Solicitudes de envio de " << centro->getCodigo() << " -----\n";
		std::cout << "1. Crear solicitud\n";
		std::cout << "2. Buscar solicitud\n";
		std::cout << "3. Mostrar solicitudes del centro\n";
		std::cout << "4. Aprobar solicitud (genera su despacho)\n";
		std::cout << "5. Rechazar o anular solicitud\n";
		std::cout << "6. Volver\n";
		std::cout << "Seleccione una opcion: ";
		opcion = leerEntero();

		switch (opcion) {
		case 1: crearSolicitud(centro); break;
		case 2: buscarSolicitud(centro); break;
		case 3: mostrarSolicitudes(centro); break;
		case 4: aprobarSolicitud(centro); break;
		case 5: rechazarOAnularSolicitud(centro); break;
		case 6: break;
		default: std::cout << "Opcion invalida.\n"; break;
		}
		if (opcion != 6) {
			pausar();
		}
	} while (opcion != 6);
}

// =======================================================================
// Despachos
// =======================================================================

void MenuLogistica::buscarDespacho(CentroDistribucion* centro) {
	std::cout << "\n----- Buscar despacho -----\n";
	std::cout << "Codigo del despacho: ";
	std::string codigo = leerPalabra();

	Despacho* despacho = centro->getGestionDespachos()->buscarPorCodigo(codigo);
	if (despacho == nullptr) {
		std::cout << "No existe un despacho con ese codigo en este centro.\n";
		return;
	}
	std::cout << despacho->mostrar() << "\n";
}

void MenuLogistica::mostrarDespachos(CentroDistribucion* centro) {
	std::cout << "\n" << centro->getGestionDespachos()->mostrarListado() << std::endl;
}

void MenuLogistica::finalizarDespacho(CentroDistribucion* centro) {
	std::cout << "\n----- Finalizar entrega de un despacho -----\n";
	std::cout << "Codigo del despacho: ";
	std::string codigo = leerPalabra();

	Despacho* despacho = centro->getGestionDespachos()->buscarPorCodigo(codigo);
	if (despacho == nullptr) {
		std::cout << "No existe un despacho con ese codigo en este centro.\n";
		return;
	}
	if (despacho->getEstado() != EstadoDespacho::EN_PROCESO) {
		std::cout << "Ese despacho ya fue finalizado.\n";
		return;
	}

	Colaborador* responsable = seleccionarColaborador(centro);
	if (responsable == nullptr) {
		return;
	}

	if (centro->getGestionDespachos()->finalizarEntrega(codigo, responsable)) {
		std::cout << "Entrega finalizada exitosamente. El paquete ahora esta Entregado.\n";
	}
	else {
		std::cout << "No se pudo finalizar la entrega (verifique que el paquete este En transito).\n";
	}
}

void MenuLogistica::menuDespachos(CentroDistribucion* centro) {
	int opcion;
	do {
		std::cout << "\n----- Despachos de " << centro->getCodigo() << " -----\n";
		std::cout << "1. Buscar despacho\n";
		std::cout << "2. Mostrar despachos del centro\n";
		std::cout << "3. Finalizar entrega\n";
		std::cout << "4. Volver\n";
		std::cout << "Seleccione una opcion: ";
		opcion = leerEntero();

		switch (opcion) {
		case 1: buscarDespacho(centro); break;
		case 2: mostrarDespachos(centro); break;
		case 3: finalizarDespacho(centro); break;
		case 4: break;
		default: std::cout << "Opcion invalida.\n"; break;
		}
		if (opcion != 4) {
			pausar();
		}
	} while (opcion != 4);
}

// =======================================================================
// Menu general de este modulo
// =======================================================================

void MenuLogistica::menuGeneral() {
	CentroDistribucion* centro = seleccionarCentro();
	if (centro == nullptr) {
		pausar();
		return;
	}

	int opcion;
	do {
		std::cout << "\n===== Centro " << centro->getCodigo() << ": Bodegas, Paquetes, Solicitudes y Despachos =====\n";
		std::cout << "1. Bodegas y consulta de matrices\n";
		std::cout << "2. Paquetes (almacenamiento, reubicacion, incidencias)\n";
		std::cout << "3. Solicitudes de envio\n";
		std::cout << "4. Despachos\n";
		std::cout << "5. Volver al menu principal\n";
		std::cout << "Seleccione una opcion: ";
		opcion = leerEntero();

		switch (opcion) {
		case 1: menuBodegas(centro); break;
		case 2: menuPaquetes(centro); break;
		case 3: menuSolicitudes(centro); break;
		case 4: menuDespachos(centro); break;
		case 5: break;
		default: std::cout << "Opcion invalida.\n"; break;
		}
	} while (opcion != 5);
}
