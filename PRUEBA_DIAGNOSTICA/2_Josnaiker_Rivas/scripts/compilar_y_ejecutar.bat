@echo off
setlocal
:: Se posiciona en la carpeta 2_Josnaiker_Rivas (un nivel arriba de scripts\)
cd /d "%~dp0\.."

echo ===================================================
echo  Compilando y Ejecutando Prueba Diagnostica
echo ===================================================

:: Ejercicio 1 (C++)
echo.
echo [1/3] Ejercicio 1: Ajedrez Caballo (C++)
where g++ >nul 2>&1
if %ERRORLEVEL% equ 0 (
    g++ -O2 "ejercicio_1\ajedrez_caballo.cpp" -o "ejercicio_1\ajedrez_caballo.exe"
    if exist "ejercicio_1\ajedrez_caballo.exe" (
        "ejercicio_1\ajedrez_caballo.exe"
    )
) else (
    echo [OMITIDO] Se requiere g++ para compilar ajedrez_caballo.cpp
)

:: Ejercicio 2 (C y Python)
echo.
echo [2/3] Ejercicio 2: Polinomio de Pascal (C y Python)
where gcc >nul 2>&1
if %ERRORLEVEL% equ 0 (
    gcc -O2 "ejercicio_2\pascal_polinomio.c" -o "ejercicio_2\pascal_polinomio.exe"
    if exist "ejercicio_2\pascal_polinomio.exe" (
        "ejercicio_2\pascal_polinomio.exe"
    )
) else (
    echo [OMITIDO] Se requiere gcc para compilar pascal_polinomio.c
)

where python >nul 2>&1
if %ERRORLEVEL% equ 0 (
    python "ejercicio_2\pascal_polinomio.py"
) else (
    echo [OMITIDO] Se requiere python para ejecutar pascal_polinomio.py
)

:: Ejercicio 3 (C)
echo.
echo [3/3] Ejercicio 3: Traductor C (C)
where gcc >nul 2>&1
if %ERRORLEVEL% equ 0 (
    gcc -O2 "ejercicio_3\traductor_c.c" -o "ejercicio_3\traductor_c.exe"
    if exist "ejercicio_3\traductor_c.exe" (
        "ejercicio_3\traductor_c.exe" "ejercicio_3\muestra_codigo.c"
    )
) else (
    echo [OMITIDO] Se requiere gcc para compilar traductor_c.c
)

echo.
echo ===================================================
pause
