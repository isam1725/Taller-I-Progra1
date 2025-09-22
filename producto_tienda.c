#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_MAX_LEN 100

typedef struct {
    int id;
    char nombre[NAME_MAX_LEN];
    long stock;
    double precio_unitario;
    double ganancias;
} Producto;

/* --- Utilidades de entrada segura --- */
int leer_linea(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) return 0;
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';
    return 1;
}

int leer_entero(const char *prompt, long *out) {
    char buf[256];
    char *endptr;
    while (1) {
        printf("%s", prompt);
        if (!leer_linea(buf, sizeof buf)) return 0;
        if (buf[0] == '\0') { puts("Entrada vacia. Intente nuevamente."); continue; }
        long val = strtol(buf, &endptr, 10);
        if (*endptr == '\0') { *out = val; return 1; }
        puts("Entrada invalida. Ingrese un numero entero.");
    }
}

int leer_real(const char *prompt, double *out) {
    char buf[256];
    char *endptr;
    while (1) {
        printf("%s", prompt);
        if (!leer_linea(buf, sizeof buf)) return 0;
        if (buf[0] == '\0') { puts("Entrada vacia. Intente nuevamente."); continue; }
        double val = strtod(buf, &endptr);
        if (*endptr == '\0') { *out = val; return 1; }
        puts("Entrada invalida. Ingrese un numero (usar punto decimal).");
    }
}

/* --- Funciones del negocio --- */

void registrar_producto(Producto *p) {
    long idTmp;
    double precio;
    long stock;
    char nombre[NAME_MAX_LEN];

    puts("\n=== Registro/Actualizacion de Producto ===");
    leer_entero("ID (entero): ", &idTmp);
    printf("Nombre (max %d chars): ", NAME_MAX_LEN-1);
    leer_linea(nombre, sizeof nombre);
    leer_entero("Cantidad en stock (entero >= 0): ", &stock);
    leer_real("Precio unitario (>= 0): ", &precio);

    if (stock < 0) stock = 0;
    if (precio < 0) precio = 0.0;

    p->id = (int)idTmp;
    strncpy(p->nombre, nombre, NAME_MAX_LEN-1);
    p->nombre[NAME_MAX_LEN-1] = '\0';
    p->stock = stock;
    p->precio_unitario = precio;
    // ganancias no se toca en actualizacion
    puts("Producto registrado/actualizado correctamente.\n");
}

void mostrar_producto(const Producto *p) {
    puts("\n=== Informacion del producto ===");
    printf("ID: %d\n", p->id);
    printf("Nombre: %s\n", p->nombre);
    printf("Stock: %ld\n", p->stock);
    printf("Precio unitario: $%.2f\n", p->precio_unitario);
    printf("Ganancias acumuladas: $%.2f\n\n", p->ganancias);
}

void vender(Producto *p) {
    if (p->precio_unitario <= 0) {
        puts("Primero registre el producto con precio valido.");
        return;
    }
    long unidades;
    double descuento_pct = 0.0;

    puts("\n=== Venta ===");
    if (!leer_entero("Unidades a vender (>= 1): ", &unidades)) return;
    if (unidades <= 0) { puts("Las unidades deben ser positivas."); return; }

    if (unidades > p->stock) {
        printf("No hay stock suficiente. Stock disponible: %ld\n", p->stock);
        return;
    }

    leer_real("Descuento (%) para esta venta (0-100): ", &descuento_pct);
    if (descuento_pct < 0) descuento_pct = 0;
    if (descuento_pct > 100) descuento_pct = 100;

    double precio_bruto = unidades * p->precio_unitario;
    double descuento = precio_bruto * (descuento_pct / 100.0);
    double total = precio_bruto - descuento;

    p->stock -= unidades;
    p->ganancias += total;

    printf("Venta realizada: %ld unidad(es) de '%s'\n", unidades, p->nombre);
    printf("Precio bruto: $%.2f | Descuento: $%.2f | Total: $%.2f\n", precio_bruto, descuento, total);
    printf("Stock restante: %ld\n\n", p->stock);
}

void reabastecer(Producto *p) {
    long unidades;
    puts("\n=== Reabastecer ===");
    if (!leer_entero("Unidades a agregar (>= 1): ", &unidades)) return;
    if (unidades <= 0) { puts("Las unidades deben ser positivas."); return; }
    if (unidades > 1000000000L) { puts("Cantidad demasiado grande."); return; }
    p->stock += unidades;
    printf("Reabastecimiento exitoso. Stock actual: %ld\n\n", p->stock);
}

void menu() {
    puts("========== MENU ==========");
    puts("1. Registrar/Actualizar producto");
    puts("2. Vender");
    puts("3. Reabastecer");
    puts("4. Consultar informacion");
    puts("5. Mostrar ganancias");
    puts("0. Salir");
    puts("==========================");
}

int main(void) {
    Producto producto = {0};
    producto.ganancias = 0.0;

    int opcion;
    char buf[256];

    puts("Sistema de gestion de un unico producto (C)");
    while (1) {
        menu();
        printf("Opcion: ");
        if (!leer_linea(buf, sizeof buf)) break;
        if (sscanf(buf, "%d", &opcion) != 1) { puts("Opcion invalida."); continue; }
        switch (opcion) {
            case 1: registrar_producto(&producto); break;
            case 2: vender(&producto); break;
            case 3: reabastecer(&producto); break;
            case 4: mostrar_producto(&producto); break;
            case 5: printf("Ganancias acumuladas: $%.2f\n\n", producto.ganancias); break;
            case 0: puts("Saliendo..."); return 0;
            default: puts("Opcion invalida."); break;
        }
    }
    return 0;
}
