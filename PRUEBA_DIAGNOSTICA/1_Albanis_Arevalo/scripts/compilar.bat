@echo off
REM Compilacion de los programas en C para Windows
cd /d "%~dp0\.."

echo [1/2] Compilando Ejercicio 2 (polinomio_pascal.c)...
gcc -O2 Ejercicio_2\polinomio_pascal.c -o Ejercicio_2\polinomio_pascal.exe

echo [2/2] Compilando Ejercicio 3 (traductor_c.c)...
gcc -O2 Ejercicio_3\traductor_c.c -o Ejercicio_3\traductor_c.exe

echo.
echo Compilacion finalizada con exito.
