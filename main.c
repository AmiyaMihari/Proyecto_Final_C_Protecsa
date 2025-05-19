#include <stdio.h>
#include <stdlib.h>
#include "productos.c" // Incluir directamente el archivo productos.c

// Variables globales para productos y usuario
// Definimos la estructructura del usuario usando la función del archivo productos.c
//Usuario usuario;

// Menú de gestión de usuarios
void menuUsuarios(Usuario*** usuariosPtr, int* cantidadUsuarios, Usuario** usuarioActual) {
    int capacidad = (*cantidadUsuarios > 0) ? *cantidadUsuarios : 2;
    Usuario** usuarios = *usuariosPtr;
    char opcion[10];

    if (usuarios == NULL) {
        usuarios = (Usuario**)malloc(capacidad * sizeof(Usuario*));
        *cantidadUsuarios = 0;
    }

    while (1) {
        limpiarPantalla();
        printf("\n=== MENÚ DE USUARIOS ===\n");
        printf("1. Agregar usuario\n");
        printf("2. Ver usuarios registrados\n");
        printf("3. Seleccionar usuario\n");
        printf("4. Salir del programa\n");
        printf("Selecciona una opción: ");
        scanf("%s", opcion);

        if (strcmp(opcion, "1") == 0) {
            char nombre[50], celular[15];
            printf("Introduce el nombre del usuario: ");
            scanf("%s", nombre);
            printf("Introduce el número de celular: ");
            scanf("%s", celular);

            // Si se rebasa la capacidad, realoca
            if (*cantidadUsuarios >= capacidad) {
                capacidad *= 2;
                usuarios = (Usuario**)realloc(usuarios, capacidad * sizeof(Usuario*));
                if (usuarios == NULL) {
                    printf("Error al asignar memoria.\n");
                    exit(1);
                }
            }

            usuarios[*cantidadUsuarios] = crearUsuario(nombre, celular);
            if (usuarios[*cantidadUsuarios] == NULL) {
                printf("Error al crear usuario.\n");
                continue;
            }
            printf("Usuario '%s' agregado correctamente.\n", nombre);
            (*cantidadUsuarios)++;

        } else if (strcmp(opcion, "2") == 0) {
            printf("\nUsuarios registrados:\n");
            if (*cantidadUsuarios == 0) {
                printf("No hay usuarios registrados.\n");
            } else {
                for (int i = 0; i < *cantidadUsuarios; i++) {
                    printf("%d. %s, Celular: %s\n", i + 1, usuarios[i]->nombre, usuarios[i]->numeroCelular);
                }
            }
            pausarPrograma();

        } else if (strcmp(opcion, "3") == 0) {
            if (*cantidadUsuarios == 0) {
                printf("No hay usuarios registrados. Agrega uno primero.\n");
                pausarPrograma();
            } else {
                printf("\nUsuarios registrados:\n");
                for (int i = 0; i < *cantidadUsuarios; i++) {
                    printf("%d. %s\n", i + 1, usuarios[i]->nombre);
                }
                printf("Selecciona un usuario (1-%d): ", *cantidadUsuarios);
                int seleccion;
                scanf("%d", &seleccion);
                if (seleccion >= 1 && seleccion <= *cantidadUsuarios) {
                    *usuarioActual = usuarios[seleccion - 1];
                    printf("Usuario '%s' seleccionado.\n", (*usuarioActual)->nombre);
                    pausarPrograma();
                    break; // Salir del menú de usuarios
                } else {
                    printf("Selección no válida.\n");
                    pausarPrograma();
                }
            }

        } else if (strcmp(opcion, "4") == 0) {
            printf("Saliendo del programa...\n");
            exit(0); // Terminar el programa
        } else {
            printf("Opción no válida.\n");
            pausarPrograma();
        }
    }
    *usuariosPtr = usuarios; // Actualiza el puntero si se realocó
}

// Función para mostrar la información del usuario
void verInformacionUsuario(Usuario* usuario) {
    limpiarPantalla(); // Limpiar la pantalla antes de mostrar la información
    printf("\n=== Información del Usuario ===\n");
    printf("Nombre: %s\n", usuario->nombre);
    printf("Número de Celular: %s\n", usuario->numeroCelular);

    // Mostrar el último producto agregado al carrito
     Producto* temp = usuario->carrito ? usuario->carrito->productos : NULL;
    if (temp == NULL) {
        printf("Último Producto Agregado: Ninguno (el carrito está vacío).\n");
    } else {
        // Recorrer hasta el último producto
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
         printf("Último Producto Agregado: %s - Costo: $%.2f\n", temp->nombre, temp->costo);
    }

    pausarPrograma(); // Esperar a que el usuario presione Enter
}

// Función para mostrar el carrito de compras
void verCarrito(Usuario* usuario) {
    limpiarPantalla();
    Producto* temp = usuario->carrito ? usuario->carrito->productos : NULL; // Puntero temporal para recorrer el carrito
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
void verListaProductos(Usuario* usuario) {
    limpiarPantalla();
    mostrarProductos(cargarProductos("productos.txt"), usuario);
}


void liberarUsuarios(Usuario** usuarios, int cantidadUsuarios) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        liberarProductos(usuarios[i]->carrito->productos);
        free(usuarios[i]->carrito);
        free(usuarios[i]);
    }
    free(usuarios);
}




int main() {
    Usuario** usuarios = NULL;       // Lista dinámica de usuarios
    int cantidadUsuarios = 0;        // Número de usuarios registrados
    Usuario* usuarioActual = NULL;   // Usuario actualmente seleccionado
    Producto* listaProductos = NULL; // Lista de productos cargados

    int opcion; // Variable para almacenar la opción seleccionada por el usuario

    //Aquí debe de ir FUNCION DE USUARIOS
    menuUsuarios(&usuarios, &cantidadUsuarios, &usuarioActual);

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
        printf("Usuario actual: %s\n", usuarioActual->nombre);
        printf("1. Ver mi carrito de compras\n");
        printf("2. Ver mi información de usuario\n");
        printf("3. Ver la lista de productos\n");
        printf("4. Salir\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion); // Leer la opción ingresada por el usuario

        // Seleccionar la función
        switch (opcion) {
            case 1:
                verCarrito(usuarioActual);
                break;
            case 2:
                verInformacionUsuario(usuarioActual);
                break;
            case 3:
                verListaProductos(usuarioActual);
                break;
            case 4:
                //printf("Saliendo del programa...\n");
                menuUsuarios(&usuarios, &cantidadUsuarios, &usuarioActual);
                break;
            default:
                printf("Opción no válida, intenta de nuevo.\n");
                pausarPrograma();
        }
    } while (1); // Repetir hasta que el usuario elija "Salir"

    // Liberar la memoria de la lista de productos y del carrito
    liberarProductos(listaProductos);
    liberarUsuarios(usuarios, cantidadUsuarios);

    return 0;
}