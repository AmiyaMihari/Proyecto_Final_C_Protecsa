#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar productos
typedef struct Producto {
    char nombre[50]; // Nombre del producto
    float costo; // Costo del producto
    struct Producto* siguiente; // Apuntador al siguiente nodo en la lista doblemente ligada
    struct Producto* anterior; // Apuntador al nodo anterior en la lista doblemente ligada
} Producto;

// Estructura para almacenar el carrito de compras de un usuario particular
typedef struct Carrito {
    char nombre[65]; // Nombre del carrito, por ejemplo: "Carrito Amiya"
    Producto* productos; // Apuntador al inicio de la lista doblemente ligada de productos
} Carrito;

// Estructura para almacenar la información del usuario
typedef struct Usuario {
    char nombre[50]; // Nombre del usuario
    char numeroCelular[15]; // Número de celular del usuario
    Carrito* carrito; // Apuntador al carrito de compras asociado al usuario
} Usuario;

// Función para limpiar la pantalla de forma multiplataforma
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // Caso para Windows
    #else
        system("clear"); // Caso para Linux
    #endif
}

// Función para pausar el programa y esperar a que el usuario presione Enter
void pausarPrograma() {
    printf("Presiona Enter para continuar...\n");
    getchar(); // Captura el Enter
    getchar(); // Si hubo un scanf previo, captura el Enter sobrante
}

// Función para crear un nuevo producto (nodo)
Producto* crearProducto(const char* nombre, float costo) { 
    Producto* nuevo = (Producto*)malloc(sizeof(Producto)); // Asigna memoria dinámica para un nuevo nodo de producto
    if (nuevo == NULL) { // Verifica si la asignación de memoria falló
        printf("Error al asignar memoria.\n");
        exit(1); // Termina el programa si no se pudo asignar memoria
    }
    strcpy(nuevo->nombre, nombre); // Copia el nombre del producto al nodo
    nuevo->costo = costo; // Asigna el costo del producto
    nuevo->siguiente = NULL; // Inicializa el apuntador al siguiente nodo como NULL
    nuevo->anterior = NULL; // Inicializa el apuntador al nodo anterior como NULL
    return nuevo; // Retorna el nodo creado
}

// Función para cargar productos desde un archivo
Producto* cargarProductos(const char* archivo) {
    FILE* f = fopen(archivo, "r"); // Abre el archivo en modo lectura
    if (f == NULL) { // Verifica si el archivo no pudo abrirse
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    Producto* inicio = NULL; // Apuntador al inicio de la lista de productos
    Producto* actual = NULL; // Apuntador al nodo actual mientras se construye la lista
    char nombre[50];
    float costo;

    // Lee cada línea del archivo hasta llegar al final (EOF)
    while (fscanf(f, "%s %f", nombre, &costo) != EOF) {
        Producto* nuevo = crearProducto(nombre, costo); // Crea un nuevo nodo de producto

        if (inicio == NULL) {
            // Si es el primer nodo, inicializa la lista
            inicio = nuevo;
        } else {
            // Enlaza el nuevo nodo al final de la lista
            actual->siguiente = nuevo; // El nodo actual apunta al nuevo nodo como siguiente
            nuevo->anterior = actual; // El nuevo nodo apunta al nodo actual como anterior
        }
        actual = nuevo; // Actualiza el nodo actual al nuevo nodo
    }

    fclose(f); // Cierra el archivo después de leerlo
    return inicio; // Retorna el inicio de la lista de productos
}

// Función para crear un usuario y su carrito asociado
Usuario* crearUsuario(const char* nombreUsuario, const char* numeroCelular) {
    Usuario* nuevoUsuario = (Usuario*)malloc(sizeof(Usuario)); // Asigna memoria para un nuevo usuario
    if (!nuevoUsuario) return NULL; // Retorna NULL si no se pudo asignar memoria
    strncpy(nuevoUsuario->nombre, nombreUsuario, sizeof(nuevoUsuario->nombre)); // Copia el nombre del usuario
    strncpy(nuevoUsuario->numeroCelular, numeroCelular, sizeof(nuevoUsuario->numeroCelular)); // Copia el número de celular

    Carrito* nuevoCarrito = (Carrito*)malloc(sizeof(Carrito)); // Asigna memoria para un nuevo carrito
    if (!nuevoCarrito) { // Verifica si la asignación de memoria falló
        free(nuevoUsuario); // Libera la memoria del usuario si falla
        return NULL;
    }
    snprintf(nuevoCarrito->nombre, sizeof(nuevoCarrito->nombre), "Carrito %s", nombreUsuario); // Asigna un nombre al carrito
    nuevoCarrito->productos = NULL; // Inicializa la lista de productos como vacía
    nuevoUsuario->carrito = nuevoCarrito; // Asocia el carrito al usuario

    return nuevoUsuario; // Retorna el usuario creado
}

// Función para agregar un producto al carrito del usuario
void agregarProductoAlCarrito(Carrito* carrito, const char* nombre, float costo) {
    Producto* nuevo = crearProducto(nombre, costo); // Crea un nuevo nodo de producto
    if (carrito->productos == NULL) {
        // Si el carrito está vacío, el nuevo producto es el primero
        carrito->productos = nuevo;
    } else {
        // Si ya hay productos, recorre la lista hasta el final
        Producto* temp = carrito->productos;
        while (temp->siguiente != NULL) temp = temp->siguiente; // Avanza al último nodo
        temp->siguiente = nuevo; // Enlaza el nuevo nodo al final de la lista
        nuevo->anterior = temp; // El nuevo nodo apunta al último nodo como anterior
    }
}

// Función para mostrar y navegar por la lista de productos
void mostrarProductos(Producto* inicio, Usuario* usuario) {
    Producto* actual = inicio; // Apuntador al nodo actual
    char tecla;

    if (actual == NULL) { // Verifica si la lista está vacía
        printf("No hay productos disponibles.\n");
        return;
    }

    while (1) {
        limpiarPantalla();
        printf("=== Producto ===\n");
        printf("Nombre: %s\n", actual->nombre);
        printf("Costo: $%.2f\n", actual->costo);
        printf("\nPresiona 'S' para siguiente, 'A' para anterior, 'C' para agregar al carrito, 'Q' para salir.\n");
        scanf(" %c", &tecla); // Lee la tecla ingresada por el usuario

        if (tecla == 'S' || tecla == 's') {
            // Avanza al siguiente producto si existe
            if (actual->siguiente != NULL) actual = actual->siguiente;
            else { printf("Ya estás en el último producto.\n"); pausarPrograma(); }
        } else if (tecla == 'A' || tecla == 'a') {
            // Retrocede al producto anterior si existe
            if (actual->anterior != NULL) actual = actual->anterior;
            else { printf("Ya estás en el primer producto.\n"); pausarPrograma(); }
        } else if (tecla == 'C' || tecla == 'c') {
            // Agrega el producto actual al carrito
            agregarProductoAlCarrito(usuario->carrito, actual->nombre, actual->costo);
            printf("Producto '%s' agregado al carrito.\n", actual->nombre);
            pausarPrograma();
        } else if (tecla == 'Q' || tecla == 'q') {
            // Sale del bucle
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
        temp = inicio; // Guarda el nodo actual en temp
        inicio = inicio->siguiente; // Avanza al siguiente nodo
        free(temp); // Libera el nodo actual
    }
}

