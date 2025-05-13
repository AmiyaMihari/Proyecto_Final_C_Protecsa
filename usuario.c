#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int opcion = -1;

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
