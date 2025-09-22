# Informe del Taller – Gestión de Producto en C

**Materia:** ISWZ1102 – Programación 1  
**Autores:** (complete aquí)  
**Docente:** (complete aquí)  

## 1. Introducción
Se implementó un sistema en C para que un comerciante gestione la venta de un único producto: registro, venta con validación de stock y descuento por venta, reabastecimiento, consulta y cálculo de ganancias acumuladas. El programa permanece en ejecución mediante un menú hasta que el usuario decida salir.

## 2. Análisis del problema y algoritmo
**Variables principales:** `id`, `nombre`, `stock`, `precio_unitario`, `ganancias`.  
**Estructuras de control:** `if/else`, `switch`, `while` (bucle principal), validación robusta de entradas.  
**Flujo general:**
1. Mostrar menú.  
2. Leer opción.  
3. Ejecutar: registrar/actualizar, vender, reabastecer, consultar, mostrar ganancias o salir.  
4. En venta: validar `unidades>0` y `unidades<=stock`; solicitar descuento `%` entre 0 y 100; actualizar `stock` y `ganancias = ganancias + total` donde `total = unidades*precio - descuento`.  
5. Repetir.

### Respuestas a las preguntas guía
1. ¿Cómo evitar vender más que el stock?  
   Comprobar `if (unidades > stock) { /* impedir venta */ }` antes de descontar unidades.
2. ¿Qué pasa si el usuario ingresa negativos o texto? ¿Cómo evitarlo?  
   Negativos generan estados inválidos; texto rompe `scanf`. Se reemplaza por lectura segura con `fgets` y conversión con `strtol/strtod`, validando que toda la cadena sea numérica.
3. ¿Cómo asegurar ganancias correctas?  
   Calcular en cada venta: `precio_bruto = unidades*precio_unitario; descuento = precio_bruto*(pct/100); total = precio_bruto - descuento; ganancias += total;`

## 3. Implementación del código
Vea el archivo `producto_tienda.c`. Incluye:
- Estructura `Producto` con todos los campos requeridos.
- Funciones para registrar, vender (con descuento), reabastecer y mostrar información.
- Utilidades de entrada robusta para enteros y reales.
- Presentación con `\t` y `\n` donde corresponde.

> Capturas sugeridas: agregue imágenes del editor mostrando las funciones `vender`, `reabastecer` y `main`.

## 4. Validación y Pruebas
### Casos probados
- Intentar vender por encima del stock → programa lo impide.  
- Reabastecer y consultar → stock aumenta correctamente.  
- Varias ventas consecutivas con distintos descuentos → ganancias se acumulan.
- Entradas inválidas (texto/negativas) → se solicita reintento sin fallar.

### Sesión de ejemplo
(Transcripción)
Sistema de gestion de un unico producto (C)
========== MENU ==========
1. Registrar/Actualizar producto
2. Vender
3. Reabastecer
4. Consultar informacion
5. Mostrar ganancias
0. Salir
==========================
Opcion: 1
ID (entero): 1001
Nombre (max 99 chars): Lapicero
Cantidad en stock (entero >= 0): 10
Precio unitario (>= 0): 0.75
Producto registrado/actualizado correctamente.

Opcion: 2
=== Venta ===
Unidades a vender (>= 1): 4
Descuento (%) para esta venta (0-100): 10
Venta realizada: 4 unidad(es) de 'Lapicero'
Precio bruto: $3.00 | Descuento: $0.30 | Total: $2.70
Stock restante: 6

Opcion: 5
Ganancias acumuladas: $2.70

## 5. Conclusiones
- Se reforzaron estructuras básicas de C, validación de entradas y manejo de estados.  
- Los principales retos fueron: diseño de entradas robustas y consistencia del estado (stock/ganancias).  
- Posibles mejoras: persistencia en archivo, soporte para varios productos, reporte de ventas.

## 6. Enlace a GitHub
Cree un repositorio y suba `producto_tienda.c` y este `README_Informe_Taller.md`.  
Sugerencia: `https://github.com/usuario/prog1-gestion-producto-c` (reemplace).
