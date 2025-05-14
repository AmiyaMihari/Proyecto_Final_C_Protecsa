#include <stdio.h>
#include <stdlib.h>
#include "productos.c" // Incluir directamente el archivo productos.c

// Variables globales para productos y usuario
Producto* listaProductos = NULL;
// Información inventada por el momento
// Definimos la estructructura del usuario usando la función del archivo productos.c
Usuario usuario;

// Definición de funciones

// Función para mostrar la información del usuario
void verInformacionUsuario() {
    limpiarPantalla();
    printf("\n=== Información del Usuario ===\n");
    printf("Nombre: %s\n", usuario.nombre);
    printf("Número de Celular: %s\n", usuario.numeroCelular);
    pausarPrograma();
}

// Función para mostrar el carrito de compras
void verCarrito() {
    limpiarPantalla();
    Producto* temp = usuario.carrito; // Puntero temporal para recorrer el carrito
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

// Función para mostrar la lista de productos
void verListaProductos() {
    limpiarPantalla();
    mostrarProductos(listaProductos, &usuario);
}

void solicitarDatosUsuario() {
    limpiarPantalla(); // Limpiar la pantalla antes de pedir información
    printf("=== Bienvenido a la Tiendita Interactiva ===\n");
    printf("Por favor, proporciona tu información:\n");

    // Solicitar el nombre del usuario
    printf("Nombre: ");
    fflush(stdin); // Asegurarse de limpiar el buffer (opcional según el compilador)
    fgets(usuario.nombre, sizeof(usuario.nombre), stdin);
    usuario.nombre[strcspn(usuario.nombre, "\n")] = '\0'; // Eliminar el salto de línea

    // Solicitar el número de celular del usuario
    printf("Número de Celular: ");
    fflush(stdin); // Asegurarse de limpiar el buffer (opcional según el compilador)
    fgets(usuario.numeroCelular, sizeof(usuario.numeroCelular), stdin);
    usuario.numeroCelular[strcspn(usuario.numeroCelular, "\n")] = '\0'; // Eliminar el salto de línea

    // Inicializar el carrito del usuario como vacío
    usuario.carrito = NULL;
}

int main() {
    int opcion; // Variable para almacenar la opción seleccionada por el usuario

    solicitarDatosUsuario();

    // Cargar productos desde el archivo
    listaProductos = cargarProductos("productos.txt");
    if (listaProductos == NULL) {
        printf("No se pudieron cargar los productos.\n");
        return 1;
    }

    do {
        // Limpiar la pantalla
        limpiarPantalla();
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
                pausarPrograma();
        }
    } while (opcion != 4); // Repetir hasta que el usuario elija "Salir"

    // Liberar la memoria de la lista de productos y del carrito
    liberarProductos(listaProductos);
    liberarProductos(usuario.carrito);

    return 0;
}