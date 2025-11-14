# PowerShell install script for coding_tests project dependencies (Windows)
# Note: For WSL/Linux environments, use install-tools.sh instead

Write-Host ""
Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
Write-Host "  Coding Tests Project - Tool Installation Script (Windows)" -ForegroundColor Cyan
Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
Write-Host ""

Write-Host "⚠️  WARNING: This project is designed for Linux/WSL environments" -ForegroundColor Yellow
Write-Host ""
Write-Host "Recommended approach:" -ForegroundColor Yellow
Write-Host "  1. Use WSL (Windows Subsystem for Linux)" -ForegroundColor White
Write-Host "  2. Run: bash install-tools.sh" -ForegroundColor White
Write-Host ""
Write-Host "If you must use Windows natively, you'll need to install:" -ForegroundColor Yellow
Write-Host "  - MinGW-w64 or MSYS2 (for gcc, make)" -ForegroundColor White
Write-Host "  - CMake (from https://cmake.org)" -ForegroundColor White
Write-Host "  - Doxygen (from https://www.doxygen.nl)" -ForegroundColor White
Write-Host "  - Valgrind (not available on Windows - use AddressSanitizer instead)" -ForegroundColor White
Write-Host "  - cppcheck (from https://cppcheck.sourceforge.io)" -ForegroundColor White
Write-Host ""

# Check if running in WSL
if (Test-Path "/proc/version") {
    $procVersion = Get-Content "/proc/version"
    if ($procVersion -match "Microsoft|WSL") {
        Write-Host "✅ Detected WSL environment" -ForegroundColor Green
        Write-Host "Please run: bash install-tools.sh" -ForegroundColor White
        exit 0
    }
}

# Check for Chocolatey
if (Get-Command choco -ErrorAction SilentlyContinue) {
    Write-Host "✅ Chocolatey detected" -ForegroundColor Green
    Write-Host ""
    Write-Host "You can install tools using Chocolatey:" -ForegroundColor Yellow
    Write-Host "  choco install cmake -y" -ForegroundColor White
    Write-Host "  choco install doxygen.install -y" -ForegroundColor White
    Write-Host "  choco install cppcheck -y" -ForegroundColor White
    Write-Host ""
    
    $install = Read-Host "Install tools using Chocolatey? (y/N)"
    if ($install -eq "y" -or $install -eq "Y") {
        Write-Host "Installing tools..." -ForegroundColor Cyan
        choco install cmake -y
        choco install doxygen.install -y
        choco install cppcheck -y
        Write-Host "✅ Tools installed" -ForegroundColor Green
    }
} else {
    Write-Host "⚠️  Chocolatey not found" -ForegroundColor Yellow
    Write-Host "Install Chocolatey from: https://chocolatey.org" -ForegroundColor White
    Write-Host "Or install tools manually from their websites" -ForegroundColor White
}

Write-Host ""
Write-Host "For best results, use WSL and run: bash install-tools.sh" -ForegroundColor Yellow
Write-Host ""

