# Proyecto final del curso de C de Protecsa.

## Autores
- **Gretchen Itzel Rincón Villa**
- **Guillermo Jair Montiel Juárez**

## Descripción

Este programa es una aplicación interactiva que permite gestionar usuarios, productos y carritos de compras. Los usuarios pueden agregar productos a su carrito, ver la lista de productos disponibles, y gestionar su información personal.

## Archivos del proyecto

El programa está compuesto por los siguientes archivos:

- **main.c**: Contiene la función principal del programa y la lógica para interactuar con los usuarios.
- **productos.c**: Implementa las funciones relacionadas con la gestión de productos y carritos de compras.
- **productos.txt**: Archivo de texto que almacena la lista de productos disponibles, con su nombre y costo.
- **README.md**: Este archivo, que contiene la documentación del proyecto.

## Cómo usar el programa

1. **Compilación**:
   Para compilar el programa, utiliza un compilador de C. Si usas `gcc`:

```bash
   gcc main.c -o Proyecto_Final_C_Protecsa
```
Asegúrate de tener en la misma carpeta el archivo **productos.c**

2. Ejecución: Una vez compilado, ejecuta el programa desde la terminal:

```bash
./Proyecto_Final_C_Protecsa
```

Asegúrate de tener en la misma carpeta del ejecutable el archivo **productos.txt**

3. Interacción:
- Al iniciar, el programa mostrará un menú para gestionar usuarios.
- Puedes agregar usuarios, seleccionar un usuario actual o gestionar usuarios existentes.
- Una vez seleccionado un usuario, podrás:
    - Ver el carrito de compras.
    - Ver la información del usuario.
    - Ver la lista de productos disponibles y agregar productos al carrito.

4. Archivos requeridos:

-- Asegúrate de que el archivo **productos.txt** esté en el mismo directorio que el ejecutable. Este archivo debe contener los productos disponibles en el siguiente formato:

```bash
nombre_producto costo
```

Ejemplo de productos.txt

```bash
Manzana 10.5
Pan 25.0
Leche 20.0
```

## **Notas:**
El programa utiliza memoria dinámica para gestionar usuarios y productos. Asegúrate de liberar correctamente la memoria al finalizar.
Si necesitas modificar la lista de productos, edita el archivo productos.txt antes de ejecutar el programa.

Para cualquier información, no dudes en contactar a los creadores.