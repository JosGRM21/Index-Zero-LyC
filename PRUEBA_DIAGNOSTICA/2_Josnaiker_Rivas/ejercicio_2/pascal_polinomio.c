#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura para enteros de hasta 100 dígitos (suficiente para n=100, x=2 -> 3^100 tiene 48 dígitos)
typedef struct {
    unsigned char d[100]; // Dígitos en base 10 (d[0] = unidades)
    int len;
} BigInt;

BigInt crear_bigint_desde_int(int v) {
    BigInt res;
    memset(&res, 0, sizeof(res));
    if (v == 0) {
        res.len = 1;
        return res;
    }
    while (v > 0) {
        res.d[res.len++] = v % 10;
        v /= 10;
    }
    return res;
}

BigInt sumar_bigint(BigInt a, BigInt b) {
    BigInt res;
    memset(&res, 0, sizeof(res));
    int max_len = (a.len > b.len) ? a.len : b.len;
    int carry = 0;

    for (int i = 0; i < max_len || carry; i++) {
        int sum = carry;
        if (i < a.len) sum += a.d[i];
        if (i < b.len) sum += b.d[i];
        res.d[res.len++] = sum % 10;
        carry = sum / 10;
    }
    return res;
}

BigInt multiplicar_bigint(BigInt a, BigInt b) {
    BigInt res;
    memset(&res, 0, sizeof(res));
    if ((a.len == 1 && a.d[0] == 0) || (b.len == 1 && b.d[0] == 0)) {
        res.len = 1;
        return res;
    }

    for (int i = 0; i < a.len; i++) {
        int carry = 0;
        for (int j = 0; j < b.len || carry; j++) {
            int cur = res.d[i + j] + carry;
            if (j < b.len) {
                cur += a.d[i] * b.d[j];
            }
            res.d[i + j] = cur % 10;
            carry = cur / 10;
            if (i + j + 1 > res.len) {
                res.len = i + j + 1;
            }
        }
    }
    return res;
}

void imprimir_bigint(BigInt b) {
    for (int i = b.len - 1; i >= 0; i--) {
        putchar('0' + b.d[i]);
    }
}

// Genera la fila n del Triángulo de Pascal con memoria dinámica
BigInt *generar_pascal(int n) {
    BigInt *fila = (BigInt *)calloc(n + 1, sizeof(BigInt));
    fila[0].d[0] = 1;
    fila[0].len = 1;

    for (int i = 1; i <= n; i++) {
        fila[i] = fila[0]; // 1
        for (int j = i - 1; j > 0; j--) {
            fila[j] = sumar_bigint(fila[j], fila[j - 1]);
        }
    }
    return fila;
}

void mostrar_polinomio(BigInt *c, int n) {
    printf("Polinomio generado (x+1)^%d:\n", n);
    for (int k = 0; k <= n; k++) {
        int grado = n - k;
        printf("  + ");
        imprimir_bigint(c[k]);
        if (grado == 1) {
            printf("x\n");
        } else if (grado > 1) {
            printf("x^%d\n", grado);
        } else {
            printf("\n");
        }
    }
}

void calcular_por_pasos(BigInt *c, int n, int x) {
    BigInt total = crear_bigint_desde_int(0);
    BigInt x_pot = crear_bigint_desde_int(1); // x^0 = 1
    BigInt x_val = crear_bigint_desde_int(x);

    printf("\n--- Calculo por pasos para n=%d, x=%d ---\n", n, x);
    // Recorremos de x^0 hasta x^n multiplicando x_pot por x en cada paso
    for (int grado = 0; grado <= n; grado++) {
        int k = n - grado; // c[k] corresponde al término x^grado
        BigInt termino = multiplicar_bigint(c[k], x_pot);
        total = sumar_bigint(total, termino);

        printf("Paso %d (x^%d): termino = ", grado + 1, grado);
        imprimir_bigint(termino);
        printf(", acumulado = ");
        imprimir_bigint(total);
        printf("\n");

        if (grado < n) {
            x_pot = multiplicar_bigint(x_pot, x_val);
        }
    }

    printf("Resultado final f(%d) = ", x);
    imprimir_bigint(total);
    printf("\n");
}

int main() {
    printf("=== PRUEBA DIAGNOSTICA - EJERCICIO 2 (C CON PRECISION EXACTA) ===\n\n");

    // a y b: Demostración con n = 4, x = 2
    int n_demo = 4;
    int x_demo = 2;
    BigInt *c_demo = generar_pascal(n_demo);
    mostrar_polinomio(c_demo, n_demo);
    calcular_por_pasos(c_demo, n_demo, x_demo);
    free(c_demo);

    // Medición del tiempo promedio para generar n = 100 (1000 iteraciones para compensar resolución de clock())
    int iteraciones = 1000;
    clock_t inicio = clock();
    for (int it = 0; it < iteraciones; it++) {
        BigInt *c = generar_pascal(100);
        free(c);
    }
    clock_t fin = clock();

    double tiempo_ms = (((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0) / iteraciones;
    printf("\nTiempo necesario para generar n=100 en C: %.6f ms (promedio sobre %d ejecuciones)\n", tiempo_ms, iteraciones);

    return 0;
}
