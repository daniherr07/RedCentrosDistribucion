# Diagrama de clases — Red de Centros de Distribucion

El diagrama completo esta en [`DiagramaClases.svg`](DiagramaClases.svg) (imagen renderizada) y en
[`DiagramaClases.mmd`](DiagramaClases.mmd) (fuente, formato [Mermaid](https://mermaid.live), por si se
necesita regenerar la imagen o editarla).

## Resumen de relaciones por modulo

**Infraestructura**
- `RedCentros` *compone* una lista enlazada propia (`ListaEnlazada<CentroDistribucion*>`) de 0..* `CentroDistribucion`.
- `ListaEnlazada<T>` y `Nodo<T>` son plantillas propias (no STL) usadas por las 7 colecciones del sistema.
- `CentroDistribucion` usa `Fecha` para timbrar operaciones; `Tarifas` usa `TipoCategoria` para las tarifas por kg.

**Herencia de clientes**
- `Cliente` (abstracta) es la superclase de `ClientePersona` y `ClienteEmpresa` (herencia, generalizacion).
- `ClienteEmpresa` sobreescribe `aplicarDescuento()` para el calculo del costo de una solicitud.

**Composicion de un centro**
- `CentroDistribucion` *compone* (posee, crea y destruye) una instancia de cada clase de gestion:
  `GestionClientes`, `GestionColaboradores`, `GestionBodegas`, `GestionPaquetes`, `GestionSolicitudes`,
  `GestionDespachos`. Cada una administra (agregacion) su propia lista enlazada de 0..* entidades.

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
npx @mermaid-js/mermaid-cli -i DiagramaClases.mmd -o DiagramaClases.svg -b white --width 2400
```
