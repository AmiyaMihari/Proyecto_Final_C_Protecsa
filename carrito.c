#include <stdio.h>
#include <stdlib.h>
#include "productos.c"

Producto* listaProductos = NULL;
//Usuario usuario = {"Jairo", "123123123", 0.0, NULL};

void verCarrito( Usuario *usuario) {
    limpiarPantalla();
    Producto* temp = usuario->carrito; // Puntero temporal para recorrer el carrito
    float total = 0.0; // Variable para almacenar el total a pagar

    if (temp == NULL) {
        printf("\nEl carrito está vacío.\n");
        pausarPrograma();
        return;
    }

    printf("\n=== Carrito de Compras ===\n");
    while (temp != NULL) {
        printf("Producto: %s - Costo: $%.2f\n", temp->nombre, temp->costo);
        total += temp->costo; // Sumar el costo del producto al total
        temp = temp->siguiente; // Avanzar al siguiente producto
    }
    printf("\nTotal a pagar: $%.2f\n", total);
    pausarPrograma();
}

void verListaProductos( Usuario *usuario) {
    limpiarPantalla();
    mostrarProductos(listaProductos, usuario);
}