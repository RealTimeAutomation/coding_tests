# Tool Installation Guide

This project requires several development tools. Use the provided install script for automatic installation.

## Quick Install

### Linux / WSL / macOS

```bash
# From the project root
bash install-tools.sh
```

The script will:
- Detect your operating system
- Install missing tools automatically
- Verify all installations

### Windows (Native)

For Windows, we recommend using **WSL** (Windows Subsystem for Linux) and running the bash script above.

If you must use Windows natively, run:
```powershell
powershell -ExecutionPolicy Bypass -File install-tools.ps1
```

## Required Tools

### Essential Build Tools
- **gcc** - C compiler
- **make** - Build automation
- **cmake** - Build system generator

### Documentation
- **doxygen** - API documentation generator

### Analysis Tools
- **valgrind** - Memory leak detection (Linux/WSL only, not available on macOS/Windows)
- **cppcheck** - Static code analysis
- **gcov** - Code coverage analysis
- **lcov** - Coverage report generator

## Manual Installation

If the script doesn't work for your system, install manually:

### Debian/Ubuntu/WSL
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake doxygen valgrind cppcheck gcov lcov
```

### Fedora/RHEL/CentOS
```bash
sudo dnf install -y gcc make cmake doxygen valgrind cppcheck gcov lcov
```

### macOS
```bash
# Install Homebrew first: https://brew.sh
brew install cmake doxygen cppcheck lcov

# Note: Valgrind is not available on macOS
# Use AddressSanitizer instead (already included with Xcode)
```

### Windows (Native)
1. Install **MSYS2** or **MinGW-w64** for gcc/make
2. Install **CMake** from https://cmake.org
3. Install **Doxygen** from https://www.doxygen.nl
4. Install **cppcheck** from https://cppcheck.sourceforge.io
5. **Valgrind** is not available on Windows - use AddressSanitizer instead

## Verify Installation

After installation, verify tools are available:

```bash
# Check build tools
gcc --version
make --version
cmake --version

# Check documentation
doxygen --version

# Check analysis tools (Linux/WSL)
valgrind --version
cppcheck --version
gcov --version
lcov --version
```

## Usage

Once tools are installed, you can use:

```bash
cd refactor/_student

# Build the project
make build

# Run tests
make test

# Generate documentation
make docs

# Memory leak detection (Linux/WSL)
make valgrind

# Static analysis
make cppcheck

# Code coverage
make coverage
```

## Troubleshooting

### Permission Errors
If you get permission errors, you may need sudo:
```bash
sudo bash install-tools.sh
```

### macOS: Xcode Command Line Tools
If build tools fail on macOS, install Xcode Command Line Tools:
```bash
xcode-select --install
```

### WSL: Update Package Lists
If installation fails on WSL, update package lists first:
```bash
sudo apt-get update
```

### Valgrind on macOS
Valgrind is not available on macOS. The project uses AddressSanitizer instead, which is built into clang/Xcode.

## Next Steps

After installation:
1. Navigate to `refactor/_student/`
2. Run `make build` to build the project
3. Run `make test` to run tests
4. See `COMMANDS.md` for all available commands

