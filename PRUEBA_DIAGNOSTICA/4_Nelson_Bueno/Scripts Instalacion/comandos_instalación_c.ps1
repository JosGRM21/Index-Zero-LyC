# Script para instalar el compilador GCC (MinGW-w64 vía WinLibs) en Windows 11
Write-Host "Iniciando la instalación del compilador de C (WinLibs MinGW)..." -ForegroundColor Cyan

# Instala WinLibs, una distribución moderna y ligera de MinGW-w64 para Windows
winget install -e --id BrechtSanders.WinLibs.MCF.UCRT --accept-package-agreements --accept-source-agreements

Write-Host "Instalación del compilador GCC finalizada exitosamente." -ForegroundColor Green
Write-Host "NOTA: Cierra esta consola y abre una nueva antes de verificar la versión." -ForegroundColor Yellow