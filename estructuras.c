// Estructura para almacenar productos
typedef struct Producto {
    char nombre[50];
    float costo;
    struct Producto* siguiente; // Apuntador al nodo siguiente
    struct Producto* anterior;  // Apuntador al nodo anterior
} Producto;

// Estructura para almacenar la información del usuario
typedef struct Usuario {
    char nombre[50];
    char numeroCelular[15];
    float totalPagar;
    Producto* carrito; // Apuntador al inicio de la lista de carrito de compras
} Usuario;