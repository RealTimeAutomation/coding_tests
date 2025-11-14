#!/bin/bash
# Quick test script to verify build and test process works
# Run this after install-tools.sh to verify everything is set up correctly

set -e

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_success() {
    echo -e "${GREEN}✅${NC} $1"
}

print_error() {
    echo -e "${RED}❌${NC} $1"
}

print_info() {
    echo -e "${YELLOW}ℹ${NC} $1"
}

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo ""
echo "═══════════════════════════════════════════════════════════"
echo "  Build and Test Verification"
echo "═══════════════════════════════════════════════════════════"
echo ""

# Test student build
print_info "Testing student workspace build..."
cd refactor/_student
if make clean >/dev/null 2>&1 && make build >/dev/null 2>&1; then
    print_success "Student build: OK"
else
    print_error "Student build: FAILED"
    exit 1
fi

# Test student tests
print_info "Testing student test suite..."
if make test >/dev/null 2>&1; then
    print_success "Student tests: OK"
else
    print_error "Student tests: FAILED"
    exit 1
fi

# Test answer key build
print_info "Testing answer key build..."
cd ../_teacher/answer_key
if make clean >/dev/null 2>&1 && make build >/dev/null 2>&1; then
    print_success "Answer key build: OK"
else
    print_error "Answer key build: FAILED"
    exit 1
fi

# Test answer key tests
print_info "Testing answer key test suite..."
if make test-all >/dev/null 2>&1; then
    print_success "Answer key tests: OK"
else
    print_error "Answer key tests: FAILED"
    exit 1
fi

# Test documentation generation
print_info "Testing documentation generation..."
cd ../../_student
if make docs >/dev/null 2>&1; then
    print_success "Documentation generation: OK"
else
    print_error "Documentation generation: FAILED"
    exit 1
fi

echo ""
echo "═══════════════════════════════════════════════════════════"
print_success "All tests passed! Build system is working correctly."
echo "═══════════════════════════════════════════════════════════"
echo ""

