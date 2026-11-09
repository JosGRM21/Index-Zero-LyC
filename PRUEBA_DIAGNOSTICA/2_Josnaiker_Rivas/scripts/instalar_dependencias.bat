@echo off
setlocal enabledelayedexpansion

echo ====================================================
echo  Verificando componentes dependientes del lenguaje
echo ====================================================

:: 1. Verificar Python
echo.
echo [1/2] Verificando Python...
where python >nul 2>&1
if %ERRORLEVEL% equ 0 (
    python --version
) else (
    echo [AVISO] Python no esta en el PATH.
    echo Intentando instalar Python via winget...
    winget install --id Python.Python.3.12 -e --accept-source-agreements --accept-package-agreements
)

:: 2. Verificar Compilador C/C++ (GCC / G++)
echo.
echo [2/2] Verificando Compiladores C/C++ (GCC/G++)...
where gcc >nul 2>&1
if %ERRORLEVEL% equ 0 (
    gcc --version | findstr /i "gcc"
    g++ --version | findstr /i "g++"
) else (
    echo [AVISO] GCC/G++ no encontrado en el PATH.
    echo Para compilar los ejercicios en C y C++, se recomienda instalar MinGW-w64:
    echo Ejecutando: winget install MSYS2.MSYS2 o MinGW...
    winget install --id MSYS2.MSYS2 -e --accept-source-agreements --accept-package-agreements
    echo.
    echo NOTA: Tras la instalacion, asegurese de agregar MinGW/bin a la variable de entorno PATH.
)

echo.
echo ====================================================
echo  Proceso de verificacion finalizado.
echo ====================================================
pause
