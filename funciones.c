#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "productos.c"
#include "carrito.c"


//C0ntr4señ4s del admin
#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"


//Diagrama de funciones, llamas la funcion menuLogin, eso nos permite ingresar como admin o usario
//Dentro de menuLogin, se llama a la funcion menuUsuarioInteractivo o menuAdminInteractivo
//Admin es independiente y muestra todos los usarios
//menuUsuarioInteractivo llama a la funcion verCarrito [carrito.c] verListaProductos[carrito.c] y verInformacionUsuario [este programa]



//FUncion para ver nombre / numerocelular / total a pagar del usuario
//Se usará en el menu interactivo del usuario
void verInformacionUsuario( Usuario *usuario) {
     printf("\nNombre: %s\n", usuario -> nombre);
     printf("Número de celular: %s\n", usuario -> numeroCelular);
     printf("Total a pagar: %.2f\n", usuario -> totalPagar);
 }


 // Menu que se ejecuta cuando el usuario ya está registrado
void menuUsuarioInteractivo(Usuario *usuario) {
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
                verCarrito(usuario);
                break;
            case 2:
            limpiarPantalla();
            verInformacionUsuario(usuario);
            pausarPrograma();
                break;
            case 3:
                verListaProductos(usuario);
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
    liberarProductos(usuario -> carrito);
}


//Funcion para verificar el acceso del admin, las contraseñas estan en DEFINE
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

//FUncion para imprimir todos los usuarios del arreglo. Usada en el menu de admin
void imprimirUsuarios( Usuario *users, int totalUsuarios) {
    printf("\nLista de usuarios:\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("Usuario %d: %s\n", i + 1, users[i].nombre);
    }
}


//FUncion para añadir un nuevo usuario en el arreglo de usuarios
//ESTA FUNCION SI TRABJA SOBRE EL ARREGLO DE USUARIOS
void añadirUsuario( Usuario **users, int *totalUsuarios) {
    *users = realloc(*users, (*totalUsuarios + 1) * sizeof(Usuario));
    printf("\nIngrese su nombre: ");
    fgets((*users)[*totalUsuarios].nombre, sizeof((*users)[*totalUsuarios].nombre), stdin);
    (*users)[*totalUsuarios].nombre[strcspn((*users)[*totalUsuarios].nombre, "\n")] = '\0'; // Eliminar el salto de línea
    
    printf("Ingrese su número de celular: ");
    fgets((*users)[*totalUsuarios].numeroCelular, sizeof((*users)[*totalUsuarios].numeroCelular), stdin);
    (*users)[*totalUsuarios].numeroCelular[strcspn((*users)[*totalUsuarios].numeroCelular, "\n")] = '\0'; // Eliminar el salto de línea
    
    (*users)[*totalUsuarios].totalPagar = 0.0; // Inicializar el total a pagar

    printf("Usuario añadido: %s\n", (*users)[*totalUsuarios].nombre);
    (*totalUsuarios)++; // Incrementar el contador de usuarios

}

// Funcion para buscar un usuario en el arreglo de usuarios
// Se usa en el menu login para saber si el usuario existe
int buscarUsuario( Usuario *users, int totalUsuarios){
    
    char nombreBuscado[100];
    printf("Ingrese su nombre de usuario para acceder: ");
    fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
    nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0'; // Eliminar el salto de línea
    

    for (int i = 0; i < totalUsuarios; i++) { //Buscamos en todo el arreglo
        if (strcmp(users[i].nombre, nombreBuscado) == 0) {
            return i; // Retorna el puntero al usuario encontrado
        }
    }
    return -1; // Retorna -1 si no se encuentra el usuario
}



//Menu principal de login
int menuLogin(){

int totalUsuarios = 0; // Contador de usuarios
    Usuario *users = NULL; // Inicializar el puntero a la lista de usuarios
    int usuario_actual = 0; // Variable para almacenar el índice del usuario actual
    int opcion_acceso, opcion_submenu, opcion_usuarios;
    int salirMenu = 0;
    int salirSubmenu = 0;
    

    do {
        printf("\n--- MENÚ ---\n");
        printf("1. Entrar como usuario\n");
        printf("2. Entrar como admin\n");
        printf("3. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion_acceso);
        getchar(); // Limpiar el buffer de entrada

        switch (opcion_acceso){
        

        case 1: //ENtrar como usuario
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
                    Usuario usuario = users[usuario_actual];
                    limpiarPantalla();

                    
                    printf("\nBienvenid@: %s\n", usuario.nombre);
                    pausarPrograma();
                    menuUsuarioInteractivo(&usuario);
                } else {
                    return 0;
                }
                break;
            }else{ //Si la lista de usuarios no está vacía
            limpiarPantalla();
            usuario_actual = buscarUsuario(users, totalUsuarios);

            if (usuario_actual != -1) { //Como el usuario fue encontrado, entramos al mismo menu
                Usuario usuario = users[usuario_actual];
                printf("\nBienvenid@: %s\n", usuario.nombre);
                pausarPrograma();
                menuUsuarioInteractivo(&usuario);}

            else { //Si el usuario no fue encontrado, procuremos registrarlo
                printf("Usuario no encontrado. ");
                printf("¿Desea registrarse? (1: Si, 0: No): ");
                int registro;
                scanf("%d", &registro);
                getchar(); 
                limpiarPantalla();
                if (registro == 1) {
                    añadirUsuario(&users, &totalUsuarios);
                    usuario_actual = totalUsuarios - 1; // Asignar el índice del nuevo usuario
                    Usuario usuario = users[usuario_actual];
                    printf("\nBienvenid@: %s\n", usuario.nombre);
                    pausarPrograma();
                    menuUsuarioInteractivo(&usuario);
                } 
                }
            }
            break;
            
            case 2: //Entrar como admin
            limpiarPantalla();
            int acceso = verificar_acceso();

            if (acceso) { //Damos la lista de usuarios y podemos devolver informacion
                printf("Realizando operaciones de administrador...\n");
                pausarPrograma();
                limpiarPantalla(); 
                do {
                    limpiarPantalla(); 
                    imprimirUsuarios(users, totalUsuarios);

                    if (totalUsuarios == 0) {
                        printf("No hay usuarios registrados.\n");
                        break;
                    
                    } else { //SI hay usuarios registrados, podemos ver su info
                        printf("¿De que usuario deseas ver la información? Escribe 0 para salir: ");
                        scanf("%d", &opcion_usuarios);
                        Usuario usuario = users[opcion_usuarios-1]; 

                        if (opcion_usuarios == 0){
                            salirSubmenu = 1;
                            limpiarPantalla();
                        } else {
                            verInformacionUsuario(&usuario);
                            pausarPrograma();
                            salirSubmenu = 0;
                        }
                    }} while (!salirSubmenu); 
                    break;
            } else {
               
               break;
            }
               break;

        case 3: //Salir
            printf("Saliendo del programa...\n");
            limpiarPantalla();
            salirMenu = 1;
            break;

        default:
            printf("Opción no válida, intenta de nuevo.\n");
        }
} while (!salirMenu); // Repetir hasta que el usuario elija "Salir"
return 0;


}

int main() {
    //Llamamos al menu de login
    menuLogin();
    
    return 0;
}