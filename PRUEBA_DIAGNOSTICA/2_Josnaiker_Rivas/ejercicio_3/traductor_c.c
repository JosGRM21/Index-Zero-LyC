#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    const char *en;
    const char *es;
} Diccionario;

static const Diccionario PALABRAS[] = {
    {"auto", "auto"}, {"break", "interrumpir"}, {"case", "caso"}, {"char", "caracter"},
    {"const", "constante"}, {"continue", "continuar"}, {"default", "defecto"}, {"do", "hacer"},
    {"double", "doble"}, {"else", "sino"}, {"enum", "enumeracion"}, {"extern", "externo"},
    {"float", "flotante"}, {"for", "para"}, {"goto", "ir_a"}, {"if", "si"},
    {"inline", "en_linea"}, {"int", "entero"}, {"long", "largo"}, {"register", "registro"},
    {"restrict", "restringido"}, {"return", "retornar"}, {"short", "corto"}, {"signed", "con_signo"},
    {"sizeof", "tamano_de"}, {"static", "estatico"}, {"struct", "estructura"}, {"switch", "segun"},
    {"typedef", "definir_tipo"}, {"union", "union"}, {"unsigned", "sin_signo"}, {"void", "vacio"},
    {"volatile", "volatil"}, {"while", "mientras"}
};
static const int TOTAL_PALABRAS = sizeof(PALABRAS) / sizeof(PALABRAS[0]);

const char *buscar_traduccion(const char *tok) {
    for (int i = 0; i < TOTAL_PALABRAS; i++) {
        if (strcmp(PALABRAS[i].en, tok) == 0) return PALABRAS[i].es;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    const char *nombre_archivo = (argc > 1) ? argv[1] : "muestra_codigo.c";

    // 1. Cargar el programa en memoria de forma dinámica
    FILE *f = fopen(nombre_archivo, "rb");
    if (!f) {
        char ruta_alt[256];
        snprintf(ruta_alt, sizeof(ruta_alt), "ejercicio_3/%s", nombre_archivo);
        f = fopen(ruta_alt, "rb");
    }
    if (!f) {
        char ruta_alt[256];
        snprintf(ruta_alt, sizeof(ruta_alt), "PRUEBA_DIAGNOSTICA/2_Josnaiker_Rivas/ejercicio_3/%s", nombre_archivo);
        f = fopen(ruta_alt, "rb");
    }
    if (!f) {
        printf("Error: No se pudo abrir '%s'\n", nombre_archivo);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *codigo = (char *)malloc(tam + 1);
    if (!codigo) {
        fclose(f);
        printf("Error: Memoria insuficiente.\n");
        return 1;
    }
    fread(codigo, 1, tam, f);
    codigo[tam] = '\0';
    fclose(f);

    printf("=== PRUEBA DIAGNOSTICA - EJERCICIO 3 (TRADUCTOR C -> ESPANOL) ===\n");
    printf("Archivo cargado en memoria dinamica (%ld bytes).\n\n", tam);

    // 2. Búfer dinámico para salida traducida
    char *salida = (char *)malloc(tam * 2 + 1024);
    if (!salida) {
        free(codigo);
        printf("Error: Memoria insuficiente.\n");
        return 1;
    }
    size_t out_len = 0;

    int encontrados = 0;
    size_t i = 0;

    while (i < (size_t)tam) {
        // Ignorar directivas #include (para no alterar nombres de cabeceras como <float.h>)
        if (strncmp(codigo + i, "#include", 8) == 0) {
            while (i < (size_t)tam && codigo[i] != '\n') salida[out_len++] = codigo[i++];
            continue;
        }
        // Ignorar comentarios de una linea //
        if (codigo[i] == '/' && i + 1 < (size_t)tam && codigo[i + 1] == '/') {
            while (i < (size_t)tam && codigo[i] != '\n') salida[out_len++] = codigo[i++];
            continue;
        }
        // Ignorar comentarios de bloque /* ... */
        if (codigo[i] == '/' && i + 1 < (size_t)tam && codigo[i + 1] == '*') {
            salida[out_len++] = codigo[i++];
            salida[out_len++] = codigo[i++];
            while (i + 1 < (size_t)tam && !(codigo[i] == '*' && codigo[i + 1] == '/')) {
                salida[out_len++] = codigo[i++];
            }
            if (i < (size_t)tam) salida[out_len++] = codigo[i++];
            if (i < (size_t)tam) salida[out_len++] = codigo[i++];
            continue;
        }
        // Ignorar literales de texto ("..." y '.')
        if (codigo[i] == '"' || codigo[i] == '\'') {
            char quote = codigo[i];
            salida[out_len++] = codigo[i++];
            while (i < (size_t)tam && codigo[i] != quote) {
                if (codigo[i] == '\\' && i + 1 < (size_t)tam) {
                    salida[out_len++] = codigo[i++];
                }
                salida[out_len++] = codigo[i++];
            }
            if (i < (size_t)tam) salida[out_len++] = codigo[i++];
            continue;
        }
        // Identificadores y palabras reservadas
        if (isalpha((unsigned char)codigo[i]) || codigo[i] == '_') {
            size_t inicio_tok = i;
            while (i < (size_t)tam && (isalnum((unsigned char)codigo[i]) || codigo[i] == '_')) {
                i++;
            }
            size_t t_len = i - inicio_tok;
            char token[64];
            if (t_len < sizeof(token)) {
                memcpy(token, codigo + inicio_tok, t_len);
                token[t_len] = '\0';
                const char *es = buscar_traduccion(token);
                if (es) {
                    encontrados++;
                    size_t es_len = strlen(es);
                    memcpy(salida + out_len, es, es_len);
                    out_len += es_len;
                    continue;
                }
            }
            memcpy(salida + out_len, codigo + inicio_tok, t_len);
            out_len += t_len;
            continue;
        }

        salida[out_len++] = codigo[i++];
    }
    salida[out_len] = '\0';

    printf("Se encontraron y tradujeron %d palabras reservadas.\n", encontrados);

    // Guardar resultado traducido
    FILE *out = fopen("muestra_codigo_traducido.txt", "w");
    if (!out) out = fopen("ejercicio_3/muestra_codigo_traducido.txt", "w");
    if (!out) out = fopen("PRUEBA_DIAGNOSTICA/2_Josnaiker_Rivas/ejercicio_3/muestra_codigo_traducido.txt", "w");
    if (out) {
        fputs(salida, out);
        fclose(out);
        printf("Resultado traducido guardado en: muestra_codigo_traducido.txt\n");
    }

    free(codigo);
    free(salida);
    return 0;
}
