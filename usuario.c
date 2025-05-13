#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

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
//Aún esta en construcción esta sección
/*
La idea es ingresar usuarios, almacenarlos en un arreglo de estructuras llamado users
Imprimimos una lista de usuarios y eliges de quien quieres ver la informacion
Como si tu fueras el administrador de la tienda
*/


//Definimos las estrcuturas producto y usuario
typedef struct Producto {
    char nombre[100];
    float costo_unit;
    int cantidad;
    struct Producto* siguiente; // Apuntador al siguiente producto en la lista
} Producto;

typedef struct Usuario {
    char nombre[100];
    char numeroCelular[10];
    float totalPagar;
    Producto* carrito; // Apuntador al inicio de la lista de carrito de compras
    } Usuario;


// Declaración de funciones 

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


/*
Por ahora no usaremos esta funcion, daremos una lista de usuarios

Usuario* buscarUsuario( Usuario *users, int totalUsuarios, const char *nombreBuscado) {
    
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(users[i].nombre, nombreBuscado) == 0) {
            return &users[i]; // Retorna el puntero al usuario encontrado
        }
    }
     return NULL; // Retorna NULL si no se encuentra el usuario
}       
    
*/



// Abrimos un menu para agregar usuarios y ver su informacion
int main() {
    int totalUsuarios = 0; // Contador de usuarios
    Usuario *users = NULL; // Inicializar el puntero a la lista de usuarios
    int opcion_acceso, opcion_submenu, opcion_usuarios;
    int salirMenu = 0;
    int salirSubmenu = 0;

    int usuario_actual = 0; // Variable para almacenar el índice del usuario actual
    

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
              printf("No hay usuarios registrados.\n");
                printf("Desea registrarse? (1: Si, 0: No): ");
                int registro;
                scanf("%d", &registro);
                getchar(); // Limpiar el buffer de entrada
                if (registro == 1) {
                    añadirUsuario(&users, &totalUsuarios);
                    usuario_actual = totalUsuarios - 1; // Asignar el índice del nuevo usuario
                    printf("\nBienvenid@: %s\n", users[usuario_actual].nombre);

                    //Aqui ingresamos el menu del archivo main
                    printf("\n--- MENÚ main---\n");
                } else {
                    return 0;
                }
                break;
            }else{
            
            char nombreBuscado[100];
            printf("Ingrese su nombre de usuario para acceder: ");
            fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
            nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0'; // Eliminar el salto de línea
            usuario_actual = buscarUsuario(users, totalUsuarios, nombreBuscado);
            if (usuario_actual != -1) {
                printf("\nBienvenid@: %s\n", users[usuario_actual].nombre);
            //Aqui ingresamos el menu del archivo main
                printf("\n--- MENÚ main---\n");}
            else {
                printf("Usuario no encontrado. ");
                printf("¿Desea registrarse? (1: Si, 0: No): ");
                int registro;
                scanf("%d", &registro);
                getchar(); // Limpiar el buffer de entrada
                if (registro == 1) {
                    añadirUsuario(&users, &totalUsuarios);
                    usuario_actual = totalUsuarios - 1; // Asignar el índice del nuevo usuario
                    printf("\nBienvenid@: %s\n", users[usuario_actual].nombre);

                    //Aqui ingresamos el menu del archivo main
                    printf("\n--- MENÚ main---\n");
                } 
                }
            }
            break;
            
            case 2:
            int acceso = verificar_acceso();
            if (acceso) {
                do {
                // Código exclusivo de administrador
                    printf("Realizando operaciones de administrador...\n");
                
                    imprimirUsuarios(users, totalUsuarios);
                    if (totalUsuarios == 0) {
                        printf("No hay usuarios registrados.\n");
                        break;
                    
                    } else {
                        printf("¿De que usuario deseas ver la información? Escribe 0 para salir: ");
                        scanf("%d", &opcion_usuarios);
                        if (opcion_usuarios == 0){
                            salirSubmenu = 1;
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

    

/*

    do {
        printf("\n--- MENÚ ---\n");
        printf("1. Añadir nuevo usuario\n");
        printf("2. Buscar usuario\n");
        printf("3. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                añadirUsuario(&users, &totalUsuarios);
                break;
                
            case 2:
                if (totalUsuarios == 0) {
                    printf("No hay usuarios registrados.\n");
                    break;
                }
                imprimirUsuarios(users, totalUsuarios);
                printf("¿De que usuario deseas ver la información? ");
                scanf("%d", &opcion);
                verInformacionUsuario(users, opcion-1);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida, intenta de nuevo.\n");
            }
        } while (opcion != 3); // Repetir hasta que el usuario elija "Salir"
    
        return 0;
    }

    */
