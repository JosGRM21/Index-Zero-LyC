# Verificar Python
echo "=== Verificando Python ==="
if command -v python3 >/dev/null 2>&1; then
    python3 --version
elif command -v python >/dev/null 2>&1; then
    python --version
else
    echo "Python no encontrado. Instalando..."
    if command -v apt-get >/dev/null 2>&1; then
        sudo apt-get update && sudo apt-get install -y python3
    elif command -v dnf >/dev/null 2>&1; then
        sudo dnf install -y python3
    elif command -v pacman >/dev/null 2>&1; then
        sudo pacman -S --noconfirm python
    fi
fi

# Verificar GCC / G++ (C y C++)
echo ""
echo "=== Verificando Compiladores C/C++ (GCC/G++) ==="
if command -v gcc >/dev/null 2>&1 && command -v g++ >/dev/null 2>&1; then
    gcc --version | head -n 1
    g++ --version | head -n 1
else
    echo "GCC/G++ no encontrado. Instalando..."
    if command -v apt-get >/dev/null 2>&1; then
        sudo apt-get update && sudo apt-get install -y build-essential
    elif command -v dnf >/dev/null 2>&1; then
        sudo dnf groupinstall -y "Development Tools"
    elif command -v pacman >/dev/null 2>&1; then
        sudo pacman -S --noconfirm base-devel gcc
    fi
fi

echo ""
echo "Entorno listo para compilar y ejecutar los ejercicios."
