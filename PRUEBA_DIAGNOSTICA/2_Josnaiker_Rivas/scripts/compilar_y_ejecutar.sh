#!/bin/bash
set -e
# Se posiciona en la carpeta 2_Josnaiker_Rivas (un nivel arriba de scripts/)
cd "$(dirname "$0")/.."

echo "==================================================="
echo " Compilando y Ejecutando Prueba Diagnostica"
echo "==================================================="

# Ejercicio 1 (C++)
echo ""
echo "[1/3] Ejercicio 1: Ajedrez Caballo (C++)"
if command -v g++ >/dev/null 2>&1; then
    g++ -O2 "ejercicio_1/ajedrez_caballo.cpp" -o "ejercicio_1/ajedrez_caballo"
    "ejercicio_1/ajedrez_caballo"
else
    echo "[OMITIDO] Se requiere g++ para compilar ajedrez_caballo.cpp"
fi

# Ejercicio 2 (C y Python)
echo ""
echo "[2/3] Ejercicio 2: Polinomio de Pascal (C y Python)"
if command -v gcc >/dev/null 2>&1; then
    gcc -O2 "ejercicio_2/pascal_polinomio.c" -o "ejercicio_2/pascal_polinomio"
    "ejercicio_2/pascal_polinomio"
else
    echo "[OMITIDO] Se requiere gcc para compilar pascal_polinomio.c"
fi

if command -v python3 >/dev/null 2>&1; then
    python3 "ejercicio_2/pascal_polinomio.py"
elif command -v python >/dev/null 2>&1; then
    python "ejercicio_2/pascal_polinomio.py"
else
    echo "[OMITIDO] Se requiere python para ejecutar pascal_polinomio.py"
fi

# Ejercicio 3 (C)
echo ""
echo "[3/3] Ejercicio 3: Traductor C (C)"
if command -v gcc >/dev/null 2>&1; then
    gcc -O2 "ejercicio_3/traductor_c.c" -o "ejercicio_3/traductor_c"
    "ejercicio_3/traductor_c" "ejercicio_3/muestra_codigo.c"
else
    echo "[OMITIDO] Se requiere gcc para compilar traductor_c.c"
fi

echo ""
echo "==================================================="
