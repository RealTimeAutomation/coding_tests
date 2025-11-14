#!/bin/bash
# Install script for coding_tests project dependencies
# Supports: Linux (apt/yum/dnf), macOS (Homebrew), and WSL

# Exit on error for critical failures, but continue for tool checks
set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_info() {
    echo -e "${BLUE}ℹ${NC} $1"
}

print_success() {
    echo -e "${GREEN}✅${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}⚠️${NC} $1"
}

print_error() {
    echo -e "${RED}❌${NC} $1"
}

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to check if running as root/sudo
check_sudo() {
    if [ "$EUID" -ne 0 ] && ! sudo -n true 2>/dev/null; then
        print_warning "Some installations may require sudo privileges"
        print_info "You may be prompted for your password"
    fi
}

# Detect OS and package manager
detect_os() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        if command_exists apt-get; then
            OS="debian"
            PKG_MGR="apt-get"
            INSTALL_CMD="sudo apt-get install -y"
            UPDATE_CMD="sudo apt-get update"
        elif command_exists yum; then
            OS="rhel"
            PKG_MGR="yum"
            INSTALL_CMD="sudo yum install -y"
            UPDATE_CMD="sudo yum check-update || true"
        elif command_exists dnf; then
            OS="fedora"
            PKG_MGR="dnf"
            INSTALL_CMD="sudo dnf install -y"
            UPDATE_CMD="sudo dnf check-update || true"
        else
            print_error "Unsupported Linux distribution. Please install tools manually."
            exit 1
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        OS="macos"
        if ! command_exists brew; then
            print_error "Homebrew not found. Please install Homebrew first:"
            print_info "Visit: https://brew.sh"
            exit 1
        fi
        PKG_MGR="brew"
        INSTALL_CMD="brew install"
        UPDATE_CMD="brew update"
    else
        print_error "Unsupported operating system: $OSTYPE"
        print_info "Please install tools manually"
        exit 1
    fi
    
    print_success "Detected OS: $OS (using $PKG_MGR)"
}

# Install build tools
install_build_tools() {
    print_info "Checking build tools..."
    
    MISSING_BUILD_TOOLS=()
    
    if ! command_exists gcc; then
        MISSING_BUILD_TOOLS+=("gcc")
    fi
    
    if ! command_exists make; then
        MISSING_BUILD_TOOLS+=("make")
    fi
    
    if ! command_exists cmake; then
        MISSING_BUILD_TOOLS+=("cmake")
    fi
    
    if [ ${#MISSING_BUILD_TOOLS[@]} -eq 0 ]; then
        print_success "Build tools already installed (gcc, make, cmake)"
        return
    fi
    
    print_info "Installing build tools: ${MISSING_BUILD_TOOLS[*]}"
    
    if [ "$OS" == "macos" ]; then
        # macOS: Install Xcode Command Line Tools if needed
        if ! xcode-select -p &>/dev/null; then
            print_info "Installing Xcode Command Line Tools..."
            xcode-select --install || true
            print_warning "Please complete Xcode Command Line Tools installation, then run this script again"
            return
        fi
        $INSTALL_CMD cmake
    else
        # Linux
        if [ "$OS" == "debian" ]; then
            $UPDATE_CMD
            $INSTALL_CMD build-essential cmake
        else
            $INSTALL_CMD gcc make cmake
        fi
    fi
    
    print_success "Build tools installed"
}

# Install Doxygen
install_doxygen() {
    print_info "Checking Doxygen..."
    
    if command_exists doxygen; then
        print_success "Doxygen already installed ($(doxygen --version 2>&1 | head -1))"
        return
    fi
    
    print_info "Installing Doxygen..."
    
    if ! $INSTALL_CMD doxygen; then
        print_error "Failed to install Doxygen"
        return 1
    fi
    
    print_success "Doxygen installed"
}

# Install Valgrind
install_valgrind() {
    print_info "Checking Valgrind..."
    
    if command_exists valgrind; then
        print_success "Valgrind already installed ($(valgrind --version 2>&1 | head -1))"
        return
    fi
    
    if [ "$OS" == "macos" ]; then
        print_warning "Valgrind is not available on macOS"
        print_info "Alternative: Use AddressSanitizer (already available with clang)"
        return
    fi
    
    print_info "Installing Valgrind..."
    
    if ! $INSTALL_CMD valgrind; then
        print_error "Failed to install Valgrind"
        return 1
    fi
    
    print_success "Valgrind installed"
}

# Install cppcheck
install_cppcheck() {
    print_info "Checking cppcheck..."
    
    if command_exists cppcheck; then
        print_success "cppcheck already installed ($(cppcheck --version 2>&1 | head -1))"
        return
    fi
    
    print_info "Installing cppcheck..."
    
    if ! $INSTALL_CMD cppcheck; then
        print_error "Failed to install cppcheck"
        return 1
    fi
    
    print_success "cppcheck installed"
}

# Install coverage tools
install_coverage_tools() {
    print_info "Checking coverage tools..."
    
    MISSING_COVERAGE=()
    
    if ! command_exists gcov; then
        MISSING_COVERAGE+=("gcov")
    fi
    
    if ! command_exists lcov; then
        MISSING_COVERAGE+=("lcov")
    fi
    
    if [ ${#MISSING_COVERAGE[@]} -eq 0 ]; then
        print_success "Coverage tools already installed (gcov, lcov)"
        return
    fi
    
    print_info "Installing coverage tools: ${MISSING_COVERAGE[*]}"
    
    if [ "$OS" == "macos" ]; then
        # gcov comes with Xcode, lcov needs to be installed
        if [[ " ${MISSING_COVERAGE[@]} " =~ " lcov " ]]; then
            $INSTALL_CMD lcov
        fi
    else
        if [ "$OS" == "debian" ]; then
            $INSTALL_CMD gcov lcov
        else
            $INSTALL_CMD gcc-c++ lcov
        fi
    fi
    
    print_success "Coverage tools installed"
}

# Verify installations
verify_installations() {
    print_info "Verifying installations..."
    
    TOOLS=("gcc" "make" "cmake" "doxygen")
    if [ "$OS" != "macos" ]; then
        TOOLS+=("valgrind")
    fi
    TOOLS+=("cppcheck" "gcov")
    
    ALL_OK=true
    
    for tool in "${TOOLS[@]}"; do
        if command_exists "$tool"; then
            VERSION=$($tool --version 2>&1 | head -1 || echo "installed")
            print_success "$tool: $VERSION"
        else
            print_error "$tool: NOT FOUND"
            ALL_OK=false
        fi
    done
    
    if [ "$ALL_OK" = true ]; then
        print_success "All tools verified successfully!"
        return 0
    else
        print_error "Some tools are missing. Please install them manually."
        return 1
    fi
}

# Main installation function
main() {
    echo ""
    echo "═══════════════════════════════════════════════════════════"
    echo "  Coding Tests Project - Tool Installation Script"
    echo "═══════════════════════════════════════════════════════════"
    echo ""
    
    detect_os
    check_sudo
    echo ""
    
    install_build_tools
    echo ""
    
    install_doxygen
    echo ""
    
    install_valgrind
    echo ""
    
    install_cppcheck
    echo ""
    
    install_coverage_tools
    echo ""
    
    verify_installations
    echo ""
    
    echo "═══════════════════════════════════════════════════════════"
    print_success "Installation complete!"
    echo ""
    print_info "You can now use:"
    print_info "  - make build    (build projects)"
    print_info "  - make test     (run tests)"
    print_info "  - make docs     (generate documentation)"
    print_info "  - make valgrind (memory leak detection)"
    print_info "  - make cppcheck (static analysis)"
    print_info "  - make coverage (code coverage)"
    echo ""
}

# Run main function
main "$@"

