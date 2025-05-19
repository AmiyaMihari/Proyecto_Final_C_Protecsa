#include <stdio.h>
#include <stdlib.h>
#include "productos.c" // Incluye directamente el archivo productos.c para usar sus funciones y estructuras

// Credenciales del administrador
#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

// Función para verificar el acceso del administrador
int verificar_acceso() {
    char usuario[50]; // Almacena el nombre de usuario ingresado
    char contrasena[50]; // Almacena la contraseña ingresada
    limpiarPantalla(); // Limpia la pantalla antes de solicitar las credenciales
    printf("=== Acceso de Administrador ===\n");
    printf("Usuario: ");
    scanf("%49s", usuario); // Lee el nombre de usuario
    printf("Contraseña: ");
    scanf("%49s", contrasena); // Lee la contraseña

    // Compara las credenciales ingresadas con las definidas
    if (strcmp(usuario, ADMIN_USER) == 0 && strcmp(contrasena, ADMIN_PASS) == 0) {
        printf("Acceso concedido.\n\n");
        return 1; // Retorna 1 si las credenciales son correctas
    } else {
        printf("Acceso denegado.\n\n");
        return 0; // Retorna 0 si las credenciales son incorrectas
    }
}

// Función para gestionar usuarios
void gestionarUsuarios(Usuario*** usuariosPtr, int* cantidadUsuarios) {
    Usuario** usuarios = *usuariosPtr; // Obtiene la lista de usuarios
    int opcionGestion;
    limpiarPantalla(); // Limpia la pantalla
    printf("\n=== GESTIÓN DE USUARIOS ===\n");
    printf("\nUsuarios registrados:\n");
    if (*cantidadUsuarios == 0) {
        printf("No hay usuarios registrados.\n");
    } else {
        // Muestra la lista de usuarios registrados
        for (int i = 0; i < *cantidadUsuarios; i++) {
            printf("%d. %s, Celular: %s\n", i + 1, usuarios[i]->nombre, usuarios[i]->numeroCelular);
        }

        // Pregunta si se desea eliminar un usuario
        printf("\n¿Desea eliminar un usuario? (1: Sí, 0: No): ");
        scanf("%d", &opcionGestion);
        if (opcionGestion == 1) {
            int seleccion;
            printf("Selecciona el número del usuario a eliminar (1-%d): ", *cantidadUsuarios);
            scanf("%d", &seleccion);

            // Verifica que la selección sea válida
            if (seleccion >= 1 && seleccion <= *cantidadUsuarios) {
                int idx = seleccion - 1; // Índice del usuario a eliminar

                // Libera la memoria asociada al usuario
                liberarProductos(usuarios[idx]->carrito->productos);
                free(usuarios[idx]->carrito);
                free(usuarios[idx]);

                // Desplaza los usuarios restantes para llenar el hueco
                for (int j = idx; j < *cantidadUsuarios - 1; j++) {
                    usuarios[j] = usuarios[j + 1];
                }
                (*cantidadUsuarios)--; // Reduce el contador de usuarios
                printf("Usuario eliminado correctamente.\n");
            } else {
                printf("Selección no válida.\n");
            }
        }
    }
    pausarPrograma(); // Pausa el programa para que el usuario pueda leer el mensaje
}

// Menú principal para gestionar usuarios
void menuUsuarios(Usuario*** usuariosPtr, int* cantidadUsuarios, Usuario** usuarioActual) {
    int capacidad = (*cantidadUsuarios > 0) ? *cantidadUsuarios : 2; // Define la capacidad inicial de la lista de usuarios
    Usuario** usuarios = *usuariosPtr; // Obtiene la lista de usuarios
    char opcionStr[10]; // Almacena la opción ingresada como cadena
    int opcion; // Almacena la opción convertida a entero

    // Si la lista de usuarios no está inicializada, la inicializa
    if (usuarios == NULL) {
        usuarios = (Usuario**)malloc(capacidad * sizeof(Usuario*));
        *cantidadUsuarios = 0;
    }

    while (1) {
        limpiarPantalla(); // Limpia la pantalla
        printf("\n=== MENÚ DE USUARIOS ===\n");
        printf("1. Agregar usuario\n");
        printf("2. Gestionar usuarios\n");
        printf("3. Seleccionar usuario\n");
        printf("4. Salir del programa\n");
        printf("Selecciona una opción: ");
        scanf("%s", opcionStr); // Lee la opción como cadena
        opcion = atoi(opcionStr); // Convierte la opción a entero

        switch (opcion) {
            case 1: {
                limpiarPantalla();
                printf("\n=== AGREGAR USUARIO ===\n");
                char nombre[50], celular[15];
                printf("Introduce el nombre del usuario: ");
                scanf("%s", nombre); // Lee el nombre del usuario
                printf("Introduce el número de celular: ");
                scanf("%s", celular); // Lee el número de celular

                // Si se alcanza la capacidad máxima, realoca la memoria
                if (*cantidadUsuarios >= capacidad) {
                    capacidad *= 2; // Duplica la capacidad
                    usuarios = (Usuario**)realloc(usuarios, capacidad * sizeof(Usuario*));
                    if (usuarios == NULL) {
                        printf("Error al asignar memoria.\n");
                        exit(1); // Termina el programa si falla la asignación
                    }
                }

                // Crea un nuevo usuario y lo agrega a la lista
                usuarios[*cantidadUsuarios] = crearUsuario(nombre, celular);
                if (usuarios[*cantidadUsuarios] == NULL) {
                    printf("Error al crear usuario.\n");
                    pausarPrograma();
                    break;
                }
                *usuarioActual = usuarios[*cantidadUsuarios]; // Actualiza el usuario actual
                printf("Usuario '%s' agregado y seleccionado.\n", nombre);
                (*cantidadUsuarios)++; // Incrementa el contador de usuarios
                pausarPrograma();
                goto salir_usuarios; // Salta al menú de la tienda
            }
            case 2: {
                // Verifica el acceso del administrador antes de gestionar usuarios
                if (!verificar_acceso()) {
                    pausarPrograma();
                    break;
                }
                gestionarUsuarios(&usuarios, cantidadUsuarios); // Llama a la función de gestión de usuarios
                break;
            }
            case 3: {
                if (*cantidadUsuarios == 0) {
                    printf("No hay usuarios registrados. Agrega uno primero.\n");
                    pausarPrograma();
                } else {
                    // Muestra la lista de usuarios registrados
                    printf("\nUsuarios registrados:\n");
                    for (int i = 0; i < *cantidadUsuarios; i++) {
                        printf("%d. %s\n", i + 1, usuarios[i]->nombre);
                    }
                    printf("Selecciona un usuario (1-%d): ", *cantidadUsuarios);
                    int seleccion;
                    scanf("%d", &seleccion);

                    // Verifica que la selección sea válida
                    if (seleccion >= 1 && seleccion <= *cantidadUsuarios) {
                        *usuarioActual = usuarios[seleccion - 1]; // Actualiza el usuario actual
                        printf("Usuario '%s' seleccionado.\n", (*usuarioActual)->nombre);
                        pausarPrograma();
                        goto salir_usuarios; // Salta al menú de la tienda
                    } else {
                        printf("Selección no válida.\n");
                        pausarPrograma();
                    }
                }
                break;
            }
            case 4: {
                printf("Saliendo del programa...\n");
                exit(0); // Termina el programa
            }
            default: {
                printf("Opción no válida.\n");
                pausarPrograma();
            }
        }
    }
salir_usuarios:
    *usuariosPtr = usuarios; // Actualiza el puntero en caso de que se haya realocado la memoria
}

// Función para mostrar la información del usuario
void verInformacionUsuario(Usuario* usuario) {
    limpiarPantalla(); // Limpiar la pantalla antes de mostrar la información
    printf("\n=== Información del Usuario ===\n");
    printf("Nombre: %s\n", usuario->nombre);
    printf("Número de Celular: %s\n", usuario->numeroCelular);
    float total = 0.0;
    // Mostrar el último producto agregado al carrito
     Producto* temp = usuario->carrito ? usuario->carrito->productos : NULL;
     Producto* ultimo = NULL;
    if (temp == NULL) {
        printf("Último Producto Agregado: Ninguno (el carrito está vacío).\n");
    } else {
        // Recorrer hasta el último producto
        while (temp != NULL) {
            total += temp->costo;
            ultimo = temp;
            temp = temp->siguiente;
        }
         printf("Último Producto Agregado: %s\n", ultimo->nombre);
         printf("Total del carrito: $%.2f\n", total);
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

    // Llama al menú de usuarios
    menuUsuarios(&usuarios, &cantidadUsuarios, &usuarioActual);

    // Carga los productos desde un archivo
    listaProductos = cargarProductos("productos.txt");
    if (listaProductos == NULL) {
        printf("No se pudieron cargar los productos.\n");
        return 1; // Termina el programa si no se pueden cargar los productos
    }

    do {
        limpiarPantalla(); // Limpia la pantalla
        printf("\n=== Tiendita Interactiva ===\n");
        printf("Usuario actual: %s\n", usuarioActual->nombre);
        printf("1. Ver mi carrito de compras\n");
        printf("2. Ver mi información de usuario\n");
        printf("3. Ver la lista de productos\n");
        printf("4. Salir\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion); // Lee la opción ingresada por el usuario

        switch (opcion) {
            case 1:
                verCarrito(usuarioActual); // Muestra el carrito del usuario actual
                break;
            case 2:
                verInformacionUsuario(usuarioActual); // Muestra la información del usuario actual
                break;
            case 3:
                verListaProductos(usuarioActual); // Muestra la lista de productos
                break;
            case 4:
                menuUsuarios(&usuarios, &cantidadUsuarios, &usuarioActual); // Regresa al menú de usuarios
                break;
            default:
                printf("Opción no válida, intenta de nuevo.\n");
                pausarPrograma();
        }
    } while (1); // Repite el ciclo hasta que el usuario elija salir

    // Libera la memoria de los productos y usuarios antes de salir
    liberarProductos(listaProductos);
    liberarUsuarios(usuarios, cantidadUsuarios);

    return 0; // Termina el programa
}