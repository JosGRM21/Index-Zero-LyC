# Script para instalar Python automáticamente en Windows 11
Write-Host "Iniciando la instalación de Python para la Prueba Diagnóstica..." -ForegroundColor Cyan

# Ejecuta winget aceptando los acuerdos automáticamente
winget install -e --id Python.Python.3.12 --accept-package-agreements --accept-source-agreements

Write-Host "Instalación de Python finalizada exitosamente." -ForegroundColor Green
Write-Host "Verificando versión:" -ForegroundColor Yellow
python --version