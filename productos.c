#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar productos
typedef struct Producto {
    char nombre[50];
    float costo;
    struct Producto* siguiente; // Apuntador al nodo siguiente
    struct Producto* anterior;  // Apuntador al nodo anterior
} Producto;

// Estructura para almacenar el carrito de compras de un usuario particular
typedef struct Carrito {
    char nombre[65]; // Ej: "Carrito Amiya"
    Producto* productos; // Lista doblemente ligada de productos
} Carrito;

// Estructura para almacenar la información del usuario
typedef struct Usuario {
    char nombre[50];
    char numeroCelular[15];
    //Producto* carrito; // Apuntador al inicio de la lista de carrito de compras
    Carrito* carrito;
} Usuario;

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

// Nueva función para crear usuario y carrito asociado con nombre de carrito personalizado
Usuario* crearUsuario(const char* nombreUsuario, const char* numeroCelular) {
    Usuario* nuevoUsuario = (Usuario*)malloc(sizeof(Usuario));
    if (!nuevoUsuario) return NULL;
    strncpy(nuevoUsuario->nombre, nombreUsuario, sizeof(nuevoUsuario->nombre));
    strncpy(nuevoUsuario->numeroCelular, numeroCelular, sizeof(nuevoUsuario->numeroCelular));

    Carrito* nuevoCarrito = (Carrito*)malloc(sizeof(Carrito));
    if (!nuevoCarrito) {
        free(nuevoUsuario);
        return NULL;
    }
    snprintf(nuevoCarrito->nombre, sizeof(nuevoCarrito->nombre), "Carrito %s", nombreUsuario);
    nuevoCarrito->productos = NULL;
    nuevoUsuario->carrito = nuevoCarrito;

    return nuevoUsuario;
}

// Adaptar la función para agregar productos al carrito del usuario
void agregarProductoAlCarrito(Carrito* carrito, const char* nombre, float costo) {
    Producto* nuevo = crearProducto(nombre, costo);
    if (carrito->productos == NULL) {
        carrito->productos = nuevo;
    } else {
        Producto* temp = carrito->productos;
        while (temp->siguiente != NULL) temp = temp->siguiente;
        temp->siguiente = nuevo;
        nuevo->anterior = temp;
    }
}

// Función para mostrar y navegar por la lista de productos
// Modifica mostrarProductos para recibir el usuario y usar carrito->productos
// Modifica mostrarProductos para recibir el usuario y usar carrito->productos
void mostrarProductos(Producto* inicio, Usuario* usuario) {
    Producto* actual = inicio;
    char tecla;

    if (actual == NULL) {
        printf("No hay productos disponibles.\n");
        return;
    }

    while (1) {
        limpiarPantalla();
        printf("=== Producto ===\n");
        printf("Nombre: %s\n", actual->nombre);
        printf("Costo: $%.2f\n", actual->costo);
        printf("\nPresiona 'S' para siguiente, 'A' para anterior, 'C' para agregar al carrito, 'Q' para salir.\n");
        scanf(" %c", &tecla);

        if (tecla == 'S' || tecla == 's') {
            if (actual->siguiente != NULL) actual = actual->siguiente;
            else { printf("Ya estás en el último producto.\n"); pausarPrograma(); }
        } else if (tecla == 'A' || tecla == 'a') {
            if (actual->anterior != NULL) actual = actual->anterior;
            else { printf("Ya estás en el primer producto.\n"); pausarPrograma(); }
        } else if (tecla == 'C' || tecla == 'c') {
            agregarProductoAlCarrito(usuario->carrito, actual->nombre, actual->costo);
            printf("Producto '%s' agregado al carrito.\n", actual->nombre);
            pausarPrograma();
        } else if (tecla == 'Q' || tecla == 'q') {
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

