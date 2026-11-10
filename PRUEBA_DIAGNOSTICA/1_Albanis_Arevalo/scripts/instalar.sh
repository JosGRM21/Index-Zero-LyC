#!/usr/bin/env bash
# Script de instalación/verificación de componentes en Linux (Debian/Ubuntu)

echo "=== Verificando componentes dependientes del lenguaje ==="

# Actualizar paquetes e instalar GCC y Python3 si no están presentes
if ! command -v gcc &> /dev/null || ! command -v python3 &> /dev/null; then
    echo "Instalando compilador GCC y Python 3..."
    sudo apt-get update -y
    sudo apt-get install -y build-essential python3
else
    echo "GCC y Python 3 ya se encuentran instalados."
fi

gcc --version | head -n 1
python3 --version
