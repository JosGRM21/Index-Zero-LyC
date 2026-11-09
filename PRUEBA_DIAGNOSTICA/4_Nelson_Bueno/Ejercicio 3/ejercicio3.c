#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Diccionario básico de palabras reservadas en C y sus traducciones
const char* reservadas_c[] = {"int", "float", "void", "return", "if", "else", "while", "for", "include"};
const char* reservadas_esp[] = {"entero", "flotante", "vacio", "retornar", "si", "sino", "mientras", "para", "incluir"};
#define CANTIDAD_PALABRAS 9

// Función que busca la palabra en el diccionario y retorna su traducción
const char* traducir(const char* palabra) {
    for (int i = 0; i < CANTIDAD_PALABRAS; i++) {
        if (strcmp(palabra, reservadas_c[i]) == 0) {
            return reservadas_esp[i];
        }
    }
    return palabra; // Si no es reservada, la deja igual (ej. variables, llaves, paréntesis)
}

int main() {
    // 1. Un programa C "crudo" para analizar
    const char* codigo_simulado = "int main ( ) { \n if ( x > 0 ) \n return 1 ; \n else \n return 0 ; \n }";
    
    // 2. Cargado en memoria de forma DINÁMICA (Requisito del PDF)
    char* memoria_dinamica = (char*)malloc(strlen(codigo_simulado) + 1);
    if (memoria_dinamica == NULL) {
        printf("Fallo crítico: No se pudo asignar memoria.\n");
        return 1;
    }
    
    // Copiamos el código a nuestro bloque de memoria dinámica
    strcpy(memoria_dinamica, codigo_simulado);

    printf("--- CODIGO ORIGINAL CARGADO EN RAM ---\n%s\n\n", memoria_dinamica);
    printf("--- CODIGO TRADUCIDO AL ESPANOL ---\n");

    // 3. Verificamos y traducimos token por token (separando por espacios y saltos de línea)
    char* token = strtok(memoria_dinamica, " \n\t");
    while (token != NULL) {
        printf("%s ", traducir(token));
        token = strtok(NULL, " \n\t"); // Avanza a la siguiente palabra
    }
    printf("\n\n");

    // 4. Liberamos la memoria dinámica para evitar fugas
    free(memoria_dinamica);

    return 0;
}