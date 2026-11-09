/**
 * Programa de prueba en C para validar el analizador léxico y traductor.
 * Contiene palabras reservadas, cadenas con palabras clave dentro,
 * comentarios e identificadores compuestos.
 */
#include <stdio.h>
#include <stdlib.h>

// Definición de estructura (struct)
struct Estudiante {
    char nombre[50];
    int edad;
    float promedio;
};

int main(void) {
    int contador = 0;
    float limite = 10.5;
    
    // Este comentario contiene las palabras: for, while, if, return pero no deben traducirse.
    printf("Mensaje: while y for dentro de una cadena no deben ser modificados\n");
    
    for (int i = 0; i < 5; i++) {
        if (i % 2 == 0) {
            contador += i;
        } else {
            contador++;
        }
    }
    
    int opcion = 2;
    switch (opcion) {
        case 1:
            printf("Opcion 1 seleccionada\n");
            break;
        case 2:
            printf("Opcion 2 seleccionada\n");
            break;
        default:
            printf("Opcion por defecto\n");
            break;
    }
    
    while (contador > 0) {
        contador--;
        if (contador == 2) {
            continue;
        }
    }
    
    return 0;
}
