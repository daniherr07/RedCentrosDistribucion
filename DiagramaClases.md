# Diagrama de clases — Red de Centros de Distribucion

El diagrama esta en tres formatos:
- [`DiagramaClases.svg`](DiagramaClases.svg): imagen ya renderizada, lista para ver o imprimir.
- [`DiagramaClases.mmd`](DiagramaClases.mmd): fuente en formato [Mermaid](https://mermaid.live), por si
  se necesita regenerar la imagen o editarla como texto.
- [`DiagramaClases.drawio`](DiagramaClases.drawio): el mismo diagrama en formato nativo de
  [draw.io / diagrams.net](https://app.diagrams.net) — abrirlo ahi con **Archivo > Abrir** (o arrastrarlo
  a la ventana del navegador) para editarlo graficamente, mover cajas o exportarlo a PNG/PDF.

Es la version **completa**: las 22 clases del dominio con sus
atributos (`-` privado, `#` protegido, `+` publico), sus metodos principales, y cada linea de relacion
rotulada con su tipo exacto (**Herencia**, **Composicion**, **Asociacion** o **Dependencia** — ver
"Como se clasifico cada relacion" mas abajo).

`MenuCentros` y `MenuLogistica` tienen muchos metodos privados "hoja" que repiten el mismo patron
(`registrarX`/`buscarX`/`mostrarX`/`eliminarX`, uno por cada opcion de cada submenu); para que el
diagrama siga siendo legible se muestra solo su metodo publico de entrada y los orquestadores de cada
submenu (`menuClientes`, `menuBodegas`, etc.). El detalle linea por linea esta en
`Menus/MenuCentros.h`/`Menus/MenuLogistica.h`.

No se dibujan como clases aparte (son detalle de implementacion, no relaciones del dominio): `Nodo<T>` y
`ListaEnlazada<T>` (la lista enlazada propia que usan las 7 colecciones del sistema, en vez de STL),
`Fecha` (usada por `Colaborador`, `RegistroBitacora`, `SolicitudEnvio` y `Despacho`) y `Tarifas`
(tarifas estaticas por `TipoCategoria`, usadas por `GestionSolicitudes` para calcular el costo).

## Como se clasifico cada relacion

- **Herencia**: `ClientePersona` y `ClienteEmpresa` heredan de `Cliente` (unica relacion `is-a` del
  sistema).
- **Composicion** (rombo relleno): la clase contenedora crea el objeto con `new` (o lo tiene como
  miembro por valor) y lo destruye ella misma (`delete` / `liberarPunteros()` en su destructor); la
  parte no tiene sentido fuera del todo y nadie mas la referencia como dueno. Asi se relacionan
  `RedCentros`-`CentroDistribucion`, `CentroDistribucion`-cada `Gestion*`, cada `Gestion*` con su
  entidad (por ejemplo `GestionClientes`-`Cliente`), `Bodega`-`Celda`, `Paquete`-`RegistroBitacora` y
  `Menu` con sus cuatro miembros.
- **Asociacion** (flecha simple): la clase guarda un puntero o referencia a otro objeto como atributo,
  pero no es su dueno (no lo crea ni lo destruye) — por ejemplo `Paquete` referencia a su `Cliente`
  propietario y a la `Bodega` donde esta almacenado, o `MenuCentros`/`MenuLogistica` guardan una
  referencia a `RedCentros`.
- **Dependencia** (flecha punteada): la clase usa a otra solo de paso, como parametro de alguno de sus
  metodos, sin guardarla como atributo. Es el caso de `Reportes`, que no posee nada: recibe
  `RedCentros*`/`CentroDistribucion*`/`Cliente*`/`Colaborador*`/`Paquete*` solo para construir el texto
  de cada reporte.
- No hay **Agregacion** en este diseño: en el primer intento se habia marcado `Gestion*`-entidad como
  agregacion, pero revisando el codigo cada `Gestion*` si destruye sus propios objetos en el
  destructor (`liberarPunteros()`), asi que es Composicion, no Agregacion.

## Resumen de relaciones por modulo

**Infraestructura**
- `RedCentros` *compone* una lista enlazada propia de 0..* `CentroDistribucion`.

**Herencia de clientes**
- `Cliente` (abstracta) es la superclase de `ClientePersona` y `ClienteEmpresa` (herencia, generalizacion).
- `ClienteEmpresa` sobreescribe `aplicarDescuento()` para el calculo del costo de una solicitud.

**Composicion de un centro**
- `CentroDistribucion` *compone* (posee, crea y destruye) una instancia de cada clase de gestion:
  `GestionClientes`, `GestionColaboradores`, `GestionBodegas`, `GestionPaquetes`, `GestionSolicitudes`,
  `GestionDespachos`. Cada una *compone* a su vez su propia lista enlazada de entidades (las crea y las
  destruye en su destructor).

**Bodegas y paquetes**
- `Bodega` *compone* su matriz dinamica de `Celda` (filas x columnas, `Celda**`).
- `Celda` referencia (0..1) al `Paquete` que tiene almacenado.
- `Paquete` referencia a su `Cliente` propietario, a su `CentroDistribucion`, y opcionalmente a la
  `Bodega` donde esta almacenado.
- `Paquete` *compone* su propia bitacora: una lista enlazada de `RegistroBitacora`, cada uno con una
  referencia al `Colaborador` responsable del cambio.

**Solicitudes y despachos**
- `SolicitudEnvio` referencia a `Cliente`, `Paquete`, `Colaborador` y `CentroDistribucion`.
- `Despacho` referencia a la `SolicitudEnvio` que lo origino, ademas de `Paquete`, `Cliente` y `Colaborador`.
- `Reportes` no posee nada: solo consulta `RedCentros`/`CentroDistribucion` para armar los 6 reportes.

**Interfaz**
- `Menu` *compone* `RedCentros`, `Reportes`, `MenuCentros` y `MenuLogistica`.
- `MenuCentros` y `MenuLogistica` reciben `RedCentros` por referencia y operan sobre ella; ninguna clase
  de dominio (entidad o gestion) depende de las clases de menu (la UI nunca se filtra hacia la logica).

## Como regenerar la imagen

```bash
npx @mermaid-js/mermaid-cli -i DiagramaClases.mmd -o DiagramaClases.svg -b white --width 3600
```
