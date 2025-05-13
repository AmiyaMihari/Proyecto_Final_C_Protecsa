#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "productos.c"


#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

Producto* listaProductos = NULL;
Usuario usuario = {"Jairo", "123123123", 0.0, NULL};

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

void verListaProductos() {
    limpiarPantalla();
    mostrarProductos(listaProductos, &usuario);
}

// Definición de la función del menú interactivo
void menuUsuarioInteractivo(Usuario *users, int usuario_actual) {
    int opcion;

    do {
        limpiarPantalla();

        printf("\n=== Tiendita Interactiva ===\n");
        printf("1. Ver mi carrito de compras\n");
        printf("2. Ver mi información de usuario\n");
        printf("3. Ver la lista de productos\n");
        printf("4. Salir\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                verCarrito();
                break;
            case 2:
            limpiarPantalla();
            verInformacionUsuario(users, usuario_actual);
            pausarPrograma();
                break;
            case 3:
                verListaProductos();
                break;
            case 4:
                printf("Saliendo de tu cuenta...\n");
                pausarPrograma();
                limpiarPantalla();
                break;
            default:
                printf("Opción no válida, intenta de nuevo.\n");
                pausarPrograma();
        }
    } while (opcion != 4);

    liberarProductos(listaProductos);
    liberarProductos(usuario.carrito);
}


int verificar_acceso() {
    char usuario[50];
    char contrasena[50];

    printf("=== Acceso de Administrador ===\n");
    printf("Usuario: ");
    scanf("%49s", usuario);
    printf("Contraseña: ");
    scanf("%49s", contrasena);

    if (strcmp(usuario, ADMIN_USER) == 0 && strcmp(contrasena, ADMIN_PASS) == 0) {
        printf("Acceso concedido.\n\n");
        return 1;
    } else {
        printf("Acceso denegado.\n\n");
        return 0;
    }
}
 

//Imprimes la información del usuario index
void verInformacionUsuario( struct Usuario *usuario, int index) {
   // printf("\nUsuario "); //numero nactivo de la lista de usuarios
    printf("\nNombre: %s\n", usuario[index].nombre);
    printf("Número de celular: %s\n", usuario[index].numeroCelular);
    printf("Total a pagar: %.2f\n", usuario[index].totalPagar);
}


//ingresa nombre y tlefono del usuario
void pedirNuevoUsuario( Usuario *users, int index){
    printf("\nIngrese su nombre: ");
    fgets(users[index].nombre, sizeof(users[index].nombre), stdin);
    users[index].nombre[strcspn(users[index].nombre, "\n")] = '\0'; // Eliminar el salto de línea
    
    printf("Ingrese su número de celular: ");
    fgets(users[index].numeroCelular, sizeof(users[index].numeroCelular), stdin);
    users[index].numeroCelular[strcspn(users[index].numeroCelular, "\n")] = '\0'; // Eliminar el salto de línea
    
    users[index].totalPagar = 0.0; // Inicializar el total a pagar
   
}


// Reajustas el tamño del arreglo y llamas a pedirNuevoUsuario
void añadirUsuario( Usuario **users, int *totalUsuarios) {
    *users = realloc(*users, (*totalUsuarios + 1) * sizeof(Usuario));
    pedirNuevoUsuario(*users, *totalUsuarios);
    printf("Usuario añadido: %s\n", (*users)[*totalUsuarios].nombre);
    (*totalUsuarios)++; // Incrementar el contador de usuarios

}


//Imprime solo los nombres de todos los usuarios
void imprimirUsuarios( Usuario *users, int totalUsuarios) {
    printf("\nLista de usuarios:\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("Usuario %d: %s\n", i + 1, users[i].nombre);
    }
}


int buscarUsuario( Usuario *users, int totalUsuarios, const char *nombreBuscado){
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(users[i].nombre, nombreBuscado) == 0) {
            return i; // Retorna el puntero al usuario encontrado
        }
    }
    return -1; // Retorna -1 si no se encuentra el usuario
}




// Abrimos un menu para agregar usuarios y ver su informacion
int main() {
    int totalUsuarios = 0; // Contador de usuarios
    Usuario *users = NULL; // Inicializar el puntero a la lista de usuarios
    int opcion_acceso, opcion_submenu, opcion_usuarios;
    int salirMenu = 0;
    int salirSubmenu = 0;

    int usuario_actual = 0; // Variable para almacenar el índice del usuario actual
    
    listaProductos = cargarProductos("productos.txt");
    if (listaProductos == NULL) {
        printf("No se pudieron cargar los productos.\n");
        return 1;
    }

    do {
        printf("\n--- MENÚ ---\n");
        printf("1. Entrar como usuario\n");
        printf("2. Entrar como admin\n");
        printf("3. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion_acceso);
        getchar(); // Limpiar el buffer de entrada

        switch (opcion_acceso){
        

        case 1:
            if (totalUsuarios == 0) {
                limpiarPantalla();
                printf("No hay usuarios registrados.\n");
                printf("Desea registrarse? (1: Si, 0: No): ");
                int registro;
                scanf("%d", &registro);
                getchar(); // Limpiar el buffer de entrada
                if (registro == 1) {
                    limpiarPantalla();
                    añadirUsuario(&users, &totalUsuarios);
                    usuario_actual = totalUsuarios - 1; // Asignar el índice del nuevo usuario
                    limpiarPantalla();
                    printf("\nBienvenid@: %s\n", users[usuario_actual].nombre);

                    //Aqui ingresamos el menu del archivo main
                    menuUsuarioInteractivo(users, usuario_actual);
                } else {
                    return 0;
                }
                break;
            }else{
            
            char nombreBuscado[100];
            limpiarPantalla();
            printf("Ingrese su nombre de usuario para acceder: ");
            fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
            nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0'; // Eliminar el salto de línea
            usuario_actual = buscarUsuario(users, totalUsuarios, nombreBuscado);
            if (usuario_actual != -1) {
                printf("\nBienvenid@: %s\n", users[usuario_actual].nombre);
            //Aqui ingresamos el menu del archivo main
                menuUsuarioInteractivo(users, usuario_actual);}
            else {
                printf("Usuario no encontrado. ");
                printf("¿Desea registrarse? (1: Si, 0: No): ");
                int registro;
                scanf("%d", &registro);
                getchar(); // Limpiar el buffer de entrada
                limpiarPantalla();
                if (registro == 1) {
                    añadirUsuario(&users, &totalUsuarios);
                    usuario_actual = totalUsuarios - 1; // Asignar el índice del nuevo usuario
                    printf("\nBienvenid@: %s\n", users[usuario_actual].nombre);

                    //Aqui ingresamos el menu del archivo main
                    menuUsuarioInteractivo(users, usuario_actual);
                } 
                }
            }
            break;
            
            case 2:
            limpiarPantalla();
            int acceso = verificar_acceso();
            if (acceso) {
                printf("Realizando operaciones de administrador...\n");
                pausarPrograma();
                limpiarPantalla(); 
                do {
                // Código exclusivo de administrador
                    limpiarPantalla(); 
                    imprimirUsuarios(users, totalUsuarios);

                    if (totalUsuarios == 0) {
                        printf("No hay usuarios registrados.\n");
                        break;
                    
                    } else {
                        printf("¿De que usuario deseas ver la información? Escribe 0 para salir: ");
                        scanf("%d", &opcion_usuarios);
                        if (opcion_usuarios == 0){
                            salirSubmenu = 1;
                            limpiarPantalla();
                        } else {
                            verInformacionUsuario(users, opcion_usuarios-1);
                            salirSubmenu = 0;
                        }
                    }} while (!salirSubmenu); 
                    break;
            } else {
               // printf("Saliendo del programa.\n");
               
               break;
            }
               break;

        case 3:
            printf("Saliendo del programa...\n");
            salirMenu = 1;
            break;

        default:
            printf("Opción no válida, intenta de nuevo.\n");
        }
} while (!salirMenu); // Repetir hasta que el usuario elija "Salir"

return 0;
}

    

