#include <stdio.h>

// Programa de prueba para verificar identificadores y palabras reservadas
int main() {
    int contador = 0;
    float limite = 10.5;
    char letra = 'a';
    int informacion = 100; // La variable 'informacion' contiene 'for', no debe alterarse

    /* Bucle de prueba: las palabras for, if, else, return deben traducirse */
    for (int i = 0; i < 5; i++) {
        if (i % 2 == 0) {
            contador += i;
        } else {
            contador -= 1;
        }
    }

    // Texto literal: las palabras dentro de comillas no deben traducirse
    printf("Mensaje: while loop and for loop inside string\n");

    while (contador < 10) {
        contador++;
        if (contador == 8) {
            break;
        }
    }

    return 0;
}
