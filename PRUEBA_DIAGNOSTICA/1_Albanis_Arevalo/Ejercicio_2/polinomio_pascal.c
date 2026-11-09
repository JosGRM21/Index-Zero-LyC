#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
double get_us() {
    LARGE_INTEGER freq, t;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t);
    return (double)t.QuadPart * 1e6 / (double)freq.QuadPart;
}
#else
double get_us() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1e6 + (double)ts.tv_nsec / 1e3;
}
#endif

// Estructura simple de enteros de precisión exacta (BigInt en base 10)
#define MAX_DIG 300

typedef struct {
    int d[MAX_DIG];
    int len;
} BigInt;

BigInt desde_int(long long n) {
    BigInt r = {{0}, 0};
    if (n == 0) {
        r.d[r.len++] = 0;
        return r;
    }
    while (n > 0) {
        r.d[r.len++] = (int)(n % 10);
        n /= 10;
    }
    return r;
}

int es_uno(BigInt a) {
    return a.len == 1 && a.d[0] == 1;
}

BigInt sumar(BigInt a, BigInt b) {
    BigInt r = {{0}, 0};
    int carry = 0;
    int max = a.len > b.len ? a.len : b.len;
    for (int i = 0; i < max || carry; i++) {
        int sum = carry + (i < a.len ? a.d[i] : 0) + (i < b.len ? b.d[i] : 0);
        r.d[r.len++] = sum % 10;
        carry = sum / 10;
    }
    return r;
}

BigInt multiplicar(BigInt a, BigInt b) {
    BigInt r = {{0}, 0};
    r.len = a.len + b.len;
    for (int i = 0; i < a.len; i++) {
        int carry = 0;
        for (int j = 0; j < b.len || carry; j++) {
            long long cur = r.d[i + j] + carry + (j < b.len ? (long long)a.d[i] * b.d[j] : 0);
            r.d[i + j] = (int)(cur % 10);
            carry = (int)(cur / 10);
        }
    }
    while (r.len > 1 && r.d[r.len - 1] == 0)
        r.len--;
    return r;
}

void imprimir(BigInt a) {
    if (a.len == 0) {
        putchar('0');
        return;
    }
    for (int i = a.len - 1; i >= 0; i--)
        putchar('0' + a.d[i]);
}

BigInt pot_bigint(int base, int exp) {
    BigInt res = desde_int(1);
    BigInt b = desde_int(base);
    for (int i = 0; i < exp; i++)
        res = multiplicar(res, b);
    return res;
}

// Triángulo de Pascal con memoria dinámica y precisión exacta
BigInt** generar_pascal(int n) {
    BigInt** t = (BigInt**)malloc((n + 1) * sizeof(BigInt*));
    for (int i = 0; i <= n; i++) {
        t[i] = (BigInt*)malloc((i + 1) * sizeof(BigInt));
        t[i][0] = desde_int(1);
        t[i][i] = desde_int(1);
        for (int j = 1; j < i; j++)
            t[i][j] = sumar(t[i - 1][j - 1], t[i - 1][j]);
    }
    return t;
}

void liberar_pascal(BigInt** t, int n) {
    for (int i = 0; i <= n; i++) free(t[i]);
    free(t);
}

void mostrar_polinomio(BigInt* coef, int n) {
    printf("(x+1)^%d = ", n);
    for (int i = 0; i <= n; i++) {
        int exp = n - i;
        if (i > 0) printf(" + ");
        if (exp == 0) {
            imprimir(coef[i]);
        } else if (es_uno(coef[i])) {
            if (exp == 1) printf("x");
            else printf("x^%d", exp);
        } else {
            imprimir(coef[i]);
            if (exp == 1) printf("x");
            else printf("x^%d", exp);
        }
    }
    printf("\n");
}

void evaluar_por_pasos(BigInt* coef, int n, int x) {
    printf("\n--- Calculo por pasos para f(%d) = (%d+1)^%d ---\n", x, x, n);
    BigInt total = desde_int(0);
    for (int i = 0; i <= n; i++) {
        int exp = n - i;
        BigInt pot = pot_bigint(x, exp);
        BigInt termino = multiplicar(coef[i], pot);
        total = sumar(total, termino);
        printf("Paso %d: ", i + 1);
        imprimir(coef[i]);
        printf(" * (%d)^%d = ", x, exp);
        imprimir(termino);
        putchar('\n');
    }
    printf("Resultado f(%d) = ", x);
    imprimir(total);
    putchar('\n');
}

int main(int argc, char* argv[]) {
    int n = (argc > 1) ? atoi(argv[1]) : 100;
    int x = (argc > 2) ? atoi(argv[2]) : 2;

    // a) Generar coeficientes con memoria dinámica y mostrar polinomio
    BigInt** t = generar_pascal(n);
    mostrar_polinomio(t[n], n);

    // b) Mostrar por pasos el cálculo para x dado
    evaluar_por_pasos(t[n], n, x);
    liberar_pascal(t, n);

    // Medir tiempo para n = 100
    double t0 = get_us();
    BigInt** t100 = generar_pascal(100);
    double t1 = get_us();
    printf("\nTiempo en C para n=100: %.2f us\n", t1 - t0);
    liberar_pascal(t100, 100);

    return 0;
}
