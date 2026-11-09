#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Genera la fila n del triangulo de Pascal usando memoria dinamica
double* generar_pascal(int n) {
    // Asignación de memoria dinámica exigida en el PDF
    double* fila = (double*)malloc((n + 1) * sizeof(double));
    fila[0] = 1.0;
    for (int i = 1; i <= n; i++) {
        // Cálculo combinatorio eficiente
        fila[i] = fila[i - 1] * (double)(n - i + 1) / (double)i;
    }
    return fila;
}

// Muestra el polinomio (x+1)^n
void mostrar_polinomio(int n, double* coef) {
    printf("\nPolinomio: (x+1)^%d = ", n);
    for (int i = 0; i <= n; i++) {
        if (i > 0) printf(" + ");
        if (coef[i] != 1.0 || (i == n)) printf("%.0f", coef[i]);
        if (n - i > 0) {
            printf("x");
            if (n - i > 1) printf("^%d", n - i);
        }
    }
    printf("\n\n");
}

// Muestra el calculo paso a paso para un valor de x
void evaluar_polinomio(int n, double* coef, double x) {
    printf("Evaluando para x = %.2f por pasos:\n", x);
    double suma = 0;
    for (int i = 0; i <= n; i++) {
        double termino = coef[i] * pow(x, n - i);
        suma += termino;
        printf("Paso %d: termino %.0f * (%.2f)^%d = %.2f | Suma parcial = %.2f\n", i + 1, coef[i], x, n - i, termino, suma);
    }
    printf("Resultado final f(%.2f) = %.2f\n", x, suma);
}

int main() {
    int n;
    double x;
    printf("Ingrese el grado del polinomio (n): ");
    scanf("%d", &n);
    printf("Ingrese el valor de x: ");
    scanf("%lf", &x);

    // Ejecucion de los requerimientos a y b
    double* coeficientes = generar_pascal(n);
    mostrar_polinomio(n, coeficientes);
    evaluar_polinomio(n, coeficientes, x);
    
    // Liberar la memoria dinamica
    free(coeficientes);

    // Requerimiento de medicion de tiempo para n=100
    printf("\n--- PRUEBA DE RENDIMIENTO (n = 100) ---\n");
    clock_t inicio = clock();
    // Iteramos 10,000 veces para que el tiempo sea visible por encima de 0.0000s
    for(int iter = 0; iter < 10000; iter++){ 
        double* c = generar_pascal(100);
        free(c);
    }
    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo para generar n=100 (10000 iteraciones en C): %f segundos\n", tiempo);

    return 0;
}