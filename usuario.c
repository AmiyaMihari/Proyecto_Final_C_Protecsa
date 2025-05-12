#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Aún esta en construcción esta sección
/*
La idea es ingresar usuarios, almacenarlos en un arreglo de estructuras llamado users
y luego poder buscar a un usuario en específico por su nombre e imprimir su información.
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
void verInformacionUsuario( struct Usuario *usuario, int nactivo) {
    printf("\nUsuario activo'\n"); //numero nactivo de la lista de usuarios
    printf("Nombre: %s\n", usuario[nactivo].nombre);
    printf("Número de celular: %s\n", usuario[nactivo].numeroCelular);
    printf("Total a pagar: %.2f\n", usuario[nactivo].totalPagar);
}

void pedirNuevoUsuario( Usuario *users, int index){
    printf("Ingrese su nombre: ");
    fgets(users[index].nombre, sizeof(users[index].nombre), stdin);
    users[index].nombre[strcspn(users[index].nombre, "\n")] = '\0'; // Eliminar el salto de línea
    printf("Ingrese su número de celular: ");
    fgets(users[index].numeroCelular, sizeof(users[index].numeroCelular), stdin);
    users[index].numeroCelular[strcspn(users[index].numeroCelular, "\n")] = '\0'; // Eliminar el salto de línea
    users[index].totalPagar = 0.0; // Inicializar el total a pagar
}

void añadirUsuario( Usuario *users, int *index){
    users = realloc(users, (*index + 1) * sizeof( Usuario));
    pedirNuevoUsuario(&users[*index], *index);
    printf("Usuario añadido correctamente.\n");
}

Usuario* buscarUsuario( Usuario *users, int totalUsuarios, const char *nombreBuscado) {
    
    for (int i = 0; i < totalUsuarios; i++) {
        if (strstr(users[i].nombre, nombreBuscado) == 0) {
            return &users[i]; // Retorna el puntero al usuario encontrado
        }
    }
     return NULL; // Retorna NULL si no se encuentra el usuario
}       
    

//buscarUsuario()

int main() {
    int totalUsuarios = 0; // Contador de usuarios
    Usuario *users = NULL; // Inicializar el puntero a la lista de usuarios
    printf("Quieres añadir un nuevo usuario? (1: Si, 0: No): ");
    int opcion;
    scanf("%d", &opcion);
    getchar(); // Limpiar el buffer de entrada
    if (opcion == 1) {
        añadirUsuario(users, &totalUsuarios);
        totalUsuarios++;
    } else {
        printf("Quieres buscar un usuario? (1: Si, 0: No): ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada  
        if (opcion == 1) {
            char nombreBuscado[100];
            printf("Ingrese el nombre del usuario a buscar: ");
            fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
            nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0'; // Eliminar el salto de línea
            Usuario *usuarioEncontrado = buscarUsuario(users, totalUsuarios, nombreBuscado);
            if (usuarioEncontrado != NULL) {
                verInformacionUsuario(usuarioEncontrado, totalUsuarios);
            } else {
                printf("Usuario no encontrado.\n");
            }
        }

    }
        

    

return 0;
}
