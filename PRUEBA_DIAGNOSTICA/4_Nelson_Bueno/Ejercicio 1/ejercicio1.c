#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

// Valida matemáticamente que el salto corresponda a un caballo (forma de L)
bool es_salto_valido(int x_actual, int y_actual, int x_nuevo, int y_nuevo) {
    int dx = abs(x_actual - x_nuevo);
    int dy = abs(y_actual - y_nuevo);
    return ((dx == 1 && dy == 2) || (dx == 2 && dy == 1));
}

// Procesa y verifica una cadena de movimientos según los requerimientos
void verificar_movimientos(const char* pos_inicial, int n, const char* cadena_movimientos, bool modo_rendimiento) {
    int x_actual = pos_inicial[0] - 'a' + 1; // Convierte 'a'-'h' a 1-8
    int y_actual = pos_inicial[1] - '0';     // Convierte '1'-'8' a 1-8

    // Clonamos la cadena para segmentarla con strtok sin afectar la original
    char movs[4000];
    strncpy(movs, cadena_movimientos, sizeof(movs));

    char *token = strtok(movs, " ");
    int mov_actual = 1;

    while (token != NULL && mov_actual <= n) {
        // Regla: Validar que la pieza sea un caballo ('K' u otra letra no permitida)
        if (token[0] != 'K') {
            if (!modo_rendimiento) printf("salida: INCORRECTO falla letra %c no pertenece a un caballo.\n", token[0]);
            return;
        }

        int x_nuevo = token[1] - 'a' + 1;
        int y_nuevo = token[2] - '0';

        // Regla: Validar límites del tablero de ajedrez (8x8)
        if (x_nuevo < 1 || x_nuevo > 8 || y_nuevo < 1 || y_nuevo > 8) {
            if (!modo_rendimiento) printf("salida: INCORRECTO falla en el movimiento %d (fuera del tablero).\n", mov_actual);
            return;
        }

        // Regla: Validar movimiento válido del caballo
        if (!es_salto_valido(x_actual, y_actual, x_nuevo, y_nuevo)) {
            if (!modo_rendimiento) printf("salida: INCORRECTO falla en el movimiento %d.\n", mov_actual);
            return;
        }

        x_actual = x_nuevo;
        y_actual = y_nuevo;
        token = strtok(NULL, " ");
        mov_actual++;
    }

    if (!modo_rendimiento) printf("salida: movimiento CORRECTO.\n");
}

int main() {
    printf("--- CASOS DE PRUEBA DEL DOCUMENTO ---\n");
    printf("Prueba 1 (a1, n=4): "); verificar_movimientos("a1", 4, "Kc2 Kd4 Kb3 Kc5", false);
    printf("Prueba 2 (a1, n=4): "); verificar_movimientos("a1", 4, "Kc2 Kd4 Kb4 Kc5", false);
    printf("Prueba 3 (a2, n=5): "); verificar_movimientos("a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7", false); // Ajustado a sintaxis correcta de cadena continua
    printf("Prueba 4 (a2, n=5): "); verificar_movimientos("a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7", false);
    printf("Prueba 5 (a8, n=2): "); verificar_movimientos("a8", 2, "Kb6 Kd7", false);
    printf("Prueba 6 (a8, n=2): "); verificar_movimientos("a8", 2, "Kb6 Kb7", false);
    printf("Prueba 7 (a1, n=10): "); verificar_movimientos("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4", false);
    printf("Prueba 8 (a1, n=10): "); verificar_movimientos("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4", false);
    printf("Prueba 9 (a1, n=10): "); verificar_movimientos("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4", false);

    printf("\n--- PRUEBA DE RENDIMIENTO (10 ITERACIONES, 500 MOVIMIENTOS) ---\n");
    
    // Cadena concatenada a partir del bloque masivo del PDF
    const char* movs_500 = "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4";

    clock_t inicio = clock();
    
    for(int i = 0; i < 10; i++) {
        verificar_movimientos("a2", 500, movs_500, true);
    }
    
    clock_t fin = clock();
    double tiempo_gastado = (double)(fin - inicio) / CLOCKS_PER_SEC;
    
    printf("Tiempo de ejecucion para validar 500 movimientos 10 veces: %f segundos\n", tiempo_gastado);

    return 0;
}