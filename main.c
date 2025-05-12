#include <stdio.h>
#include <stdlib.h>

// Declaración de funciones
void verCarrito() {
    printf("\nFunción 'Ver mi carrito de compras'\n");
}

void verInformacionUsuario() {
    printf("\nFunción 'Ver mi información de usuario'\n");
}

void verListaProductos() {
    printf("\nFunción 'Ver la lista de productos'\n");
}

int main() {
    int opcion; // Variable para almacenar la opción seleccionada por el usuario

    do {
        // Mostrar el menú
        printf("\n=== Tiendita Interactiva ===\n");
        printf("1. Ver mi carrito de compras\n");
        printf("2. Ver mi información de usuario\n");
        printf("3. Ver la lista de productos\n");
        printf("4. Salir\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion); // Leer la opción ingresada por el usuario

        // Seleccionar la función
        switch (opcion) {
            case 1:
                verCarrito();
                break;
            case 2:
                verInformacionUsuario();
                break;
            case 3:
                verListaProductos();
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida, intenta de nuevo.\n");
        }
    } while (opcion != 4); // Repetir hasta que el usuario elija "Salir"

    return 0;
}