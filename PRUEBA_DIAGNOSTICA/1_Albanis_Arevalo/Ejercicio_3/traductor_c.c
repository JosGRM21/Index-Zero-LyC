#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    const char *c;
    const char *es;
} Palabra;

static const Palabra DICCIONARIO[] = {
    {"auto", "automatico"}, {"break", "romper"}, {"case", "caso"},
    {"char", "caracter"}, {"const", "constante"}, {"continue", "continuar"},
    {"default", "defecto"}, {"do", "hacer"}, {"double", "doble"},
    {"else", "sino"}, {"enum", "enumeracion"}, {"extern", "externo"},
    {"float", "flotante"}, {"for", "para"}, {"goto", "ir_a"},
    {"if", "si"}, {"inline", "en_linea"}, {"int", "entero"},
    {"long", "largo"}, {"register", "registro"}, {"restrict", "restringido"},
    {"return", "retornar"}, {"short", "corto"}, {"signed", "con_signo"},
    {"sizeof", "tamano_de"}, {"static", "estatico"}, {"struct", "estructura"},
    {"switch", "conmutar"}, {"typedef", "definir_tipo"}, {"union", "union"},
    {"unsigned", "sin_signo"}, {"void", "vacio"}, {"volatile", "volatil"},
    {"while", "mientras"}, {NULL, NULL}
};

const char* traducir(const char* p) {
    for (int i = 0; DICCIONARIO[i].c; i++) {
        if (strcmp(DICCIONARIO[i].c, p) == 0) return DICCIONARIO[i].es;
    }
    return NULL;
}

// Carga en memoria dinámica con malloc
char* cargar_archivo(const char* ruta) {
    FILE* f = fopen(ruta, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buf = (char*)malloc(tam + 1);
    fread(buf, 1, tam, f);
    buf[tam] = '\0';
    fclose(f);
    return buf;
}

// Verifica palabras reservadas y genera traducción en buffer dinámico
char* traducir_codigo(const char* txt, int* conteo) {
    char* out = (char*)malloc(strlen(txt) * 3 + 1);
    size_t i = 0, j = 0;
    *conteo = 0;

    while (txt[i]) {
        if (txt[i] == '"' || txt[i] == '\'') {
            char delim = txt[i];
            out[j++] = txt[i++];
            while (txt[i] && txt[i] != delim) {
                if (txt[i] == '\\' && txt[i + 1])
                    out[j++] = txt[i++];
                out[j++] = txt[i++];
            }
            if (txt[i]) out[j++] = txt[i++];
        } else if (txt[i] == '/' && txt[i + 1] == '/') {
            while (txt[i] && txt[i] != '\n')
                out[j++] = txt[i++];
        } else if (txt[i] == '/' && txt[i + 1] == '*') {
            out[j++] = txt[i++];
            out[j++] = txt[i++];
            while (txt[i] && !(txt[i] == '*' && txt[i + 1] == '/'))
                out[j++] = txt[i++];
            if (txt[i]) { out[j++] = txt[i++]; out[j++] = txt[i++]; }
        } else if (isalpha((unsigned char)txt[i]) || txt[i] == '_') {
            char tok[64];
            int k = 0;
            while ((isalnum((unsigned char)txt[i]) || txt[i] == '_') && k < 63)
                tok[k++] = txt[i++];
            tok[k] = '\0';

            const char* es = traducir(tok);
            if (es) {
                (*conteo)++;
                size_t len = strlen(es);
                memcpy(&out[j], es, len);
                j += len;
            } else {
                memcpy(&out[j], tok, k);
                j += k;
            }
        } else {
            out[j++] = txt[i++];
        }
    }
    out[j] = '\0';
    return out;
}

int main() {
    // 1. Cargar archivo dinámicamente
    char* src = cargar_archivo("programa_ejemplo.c");
    if (!src) {
        printf("Error: No se pudo cargar el archivo en memoria dinamica.\n");
        return 1;
    }

    // 2. Verificar y traducir
    int total = 0;
    char* trad = traducir_codigo(src, &total);

    printf("=== TRADUCTOR DE PALABRAS RESERVADAS (C A ESPANOL) ===\n");
    printf("Palabras reservadas encontradas y traducidas: %d\n\n", total);
    printf("--- Codigo Traducido ---\n%s\n", trad);

    // 3. Liberar memoria dinámica
    free(src);
    free(trad);
    return 0;
}
