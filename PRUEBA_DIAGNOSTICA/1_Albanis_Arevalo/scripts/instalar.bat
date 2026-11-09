@echo off
REM Script de verificacion/instalacion de componentes para Windows (Python y GCC)

echo === Verificando Python ===
where python >nul 2>&1
if %errorlevel% neq 0 (
    echo Python no esta instalado o no se encuentra en el PATH.
    echo Instalando Python mediante winget...
    winget install Python.Python.3.12 --accept-package-agreements --accept-source-agreements
) else (
    echo Python detectado correctamente:
    python --version
)

echo.
echo === Verificando Compilador C (GCC) ===
where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo GCC no esta instalado o no se encuentra en el PATH.
    echo Instalando MinGW-w64 mediante winget...
    winget install MSYS2.MSYS2 --accept-package-agreements --accept-source-agreements
) else (
    echo GCC detectado correctamente:
    gcc --version | findstr /i "gcc"
)

echo.
echo Componentes verificados.
