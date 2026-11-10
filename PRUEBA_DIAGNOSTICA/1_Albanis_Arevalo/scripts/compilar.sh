#!/usr/bin/env bash
# Compilación de los programas en C para Linux / macOS
set -e

# Ir a la carpeta raíz del estudiante
cd "$(dirname "$0")/.."

echo "[1/2] Compilando Ejercicio 2 (polinomio_pascal.c)..."
gcc -O2 Ejercicio_2/polinomio_pascal.c -o Ejercicio_2/polinomio_pascal

echo "[2/2] Compilando Ejercicio 3 (traductor_c.c)..."
gcc -O2 Ejercicio_3/traductor_c.c -o Ejercicio_3/traductor_c

echo
echo "Compilación finalizada con éxito."
