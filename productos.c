#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.c"

// Función para limpiar la pantalla de forma multiplataforma
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // caso para Windows
    #else
        system("clear"); // Caso para Linux
    #endif
}

// Función para pausar el programa y esperar a que el usuario presione Enter
// Esta función es útil para que el usuario pueda leer los mensajes de advertencia
void pausarPrograma() {
    printf("Presiona Enter para continuar...\n");
    getchar(); // Captura el Enter
    getchar(); // Si hubo un scanf previo, captura el Enter sobrante
}

// Función para crear un nuevo producto (nodo)
Producto* crearProducto(const char* nombre, float costo) { 
    // Asignamos memoria para un nuevo nodo de producto
    // Usamos malloc para asignar memoria dinámica
    Producto* nuevo = (Producto*)malloc(sizeof(Producto));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    // Copiamos los datos al nuevo nodo
    strcpy(nuevo->nombre, nombre); // Usamos strcpy para copiar el nombre del producto
    nuevo->costo = costo; // Asignamos el costo
    nuevo->siguiente = NULL; // Inicializamos el siguiente nodo NULL
    nuevo->anterior = NULL; // Inicializamos el nodo anterior NULL
    return nuevo;
}

// Función para cargar productos desde un archivo
Producto* cargarProductos(const char* archivo) {
    // f es un puntero a FILE que se usa para abrir y leer el archivo
    // Usamos fopen para abrir el archivo
    FILE* f = fopen(archivo, "r"); // "r" indica que abrimos el archivo en modo lectura
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    Producto* inicio = NULL;
    Producto* actual = NULL;
    char nombre[50];
    float costo;

    // Leer cada línea del archivo hasta llegar al final "EOF" (End Of File)
    // Usamos fscanf para leer el nombre y costo del producto
    // Se espera que el archivo tenga el formato: nombre costo
    //"%s %f" indica que leemos un string y un float
    while (fscanf(f, "%s %f", nombre, &costo) != EOF) {
        Producto* nuevo = crearProducto(nombre, costo);

        if (inicio == NULL) {
            // Primera vez: inicializar la lista
            inicio = nuevo;
        } else {
            // Enlazar el nuevo nodo al final de la lista
            actual->siguiente = nuevo;
            nuevo->anterior = actual;
        }
        actual = nuevo; // Mover el puntero actual al nuevo nodo
    }

    fclose(f); // Cerramos el archivo después de leerlo
    return inicio;
}

// Función para mostrar y navegar por la lista de productos
void mostrarProductos(Producto* inicio, Usuario* usuario) {
    Producto* actual = inicio; // Puntero para recorrer la lista de productos
    char tecla; // Variable para almacenar la tecla presionada

    if (actual == NULL) {
        printf("No hay productos disponibles.\n");
        return;
    }

    while (1) {
        // Mostrar el producto actual
        limpiarPantalla();
        printf("=== Producto ===\n");
        printf("Nombre: %s\n", actual->nombre); // Mostrar el nombre del producto actual
        printf("Costo: $%.2f\n", actual->costo); // Mostrar el costo del producto actual
        printf("\nPresiona 'S' para siguiente, 'A' para anterior, 'C' para agregar al carrito, 'Q' para salir.\n");

        // Leer la tecla presionada
        // %c indica que leeremos un carácter
        scanf(" %c", &tecla); // Espacio antes de %c para ignorar espacios en blanco

        if (tecla == 'S' || tecla == 's') {
            // Ir al siguiente producto
            if (actual->siguiente != NULL) { // Verificamos si hay un siguiente producto
                actual = actual->siguiente;
            } else {
                printf("Ya estás en el último producto.\n");
                pausarPrograma();
            }
        } else if (tecla == 'A' || tecla == 'a') {
            // Ir al producto anterior
            if (actual->anterior != NULL) { // Verificamos si hay un producto anterior
                actual = actual->anterior;
            } else {
                printf("Ya estás en el primer producto.\n");
                pausarPrograma();
            }
        } else if (tecla == 'C' || tecla == 'c') {
            // Agregar el producto al carrito
            Producto* nuevo = crearProducto(actual->nombre, actual->costo);
            if (usuario->carrito == NULL) { // Si el carrito está vacío
                // Asignamos el nuevo producto como el inicio del carrito
                usuario->carrito = nuevo;
            } else { // Si ya hay productos en el carrito
                // Recorremos el carrito hasta el final y agregamos el nuevo producto
                Producto* temp = usuario->carrito; // Puntero temporal para recorrer el carrito
                while (temp->siguiente != NULL) { // Recorremos hasta el último producto
                    temp = temp->siguiente; // Avanzamos al siguiente producto
                }
                // Enlazamos el nuevo producto al final del carrito                
                temp->siguiente = nuevo; // temp->siguiente apunta al nuevo producto
                nuevo->anterior = temp; // nuevo->anterior apunta al último producto del carrito
            }
            printf("Producto '%s' agregado al carrito.\n", actual->nombre);
            pausarPrograma();
        } else if (tecla == 'Q' || tecla == 'q') {
            // Salir de la navegación
            break;
        } else {
            printf("Tecla no válida.\n");
            pausarPrograma();
        }
    }
}

// Función para liberar la memoria de la lista ligada
void liberarProductos(Producto* inicio) {
    Producto* temp; // Puntero temporal para liberar la memoria
    while (inicio != NULL) { // Mientras haya productos en la lista
        // Guardamos el nodo actual en temp
        temp = inicio;
        inicio = inicio->siguiente;
        free(temp); // Liberamos el nodo actual
    }
}