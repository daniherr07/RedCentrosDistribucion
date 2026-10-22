// main.cpp : Punto de entrada del programa. Vive en la raiz del proyecto
// (fuera de cualquier carpeta de modulo) para que sea facil de encontrar;
// toda la logica real esta repartida en las carpetas Infraestructura/,
// Core/, Clientes/, Colaboradores/, Bodegas/, Paquetes/, Solicitudes/,
// Despachos/, Reportes/ y Menus/.
#include "Menu.h"

int main() {
    Menu menu;
    menu.menuPrincipal();
    return 0;
}
