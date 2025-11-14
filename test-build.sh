#!/bin/bash
# Quick test script to verify build and test process works
# Run this after install-tools.sh to verify everything is set up correctly
#
# This script automatically discovers projects by looking for directories
# that contain both _student/ and _teacher/ subdirectories.
#
# Usage:
#   ./test-build.sh              # Test all discovered projects
#   ./test-build.sh <project>    # Test specific project (e.g., refactor)
#   ./test-build.sh --list       # List all available projects
#   ./test-build.sh --help       # Show this help message
#
# Examples:
#   ./test-build.sh              # Test all projects
#   ./test-build.sh refactor     # Test only the refactor project
#   ./test-build.sh --list       # See what projects are available

set -e

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
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

print_header() {
    echo -e "${BLUE}$1${NC}"
}

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Function to discover projects
discover_projects() {
    local projects=()
    for dir in */; do
        if [ -d "${dir}_student" ] && [ -d "${dir}_teacher" ]; then
            projects+=("${dir%/}")
        fi
    done
    echo "${projects[@]}"
}

# Function to test a single project
test_project() {
    local project=$1
    local project_dir="${project}/"
    
    if [ ! -d "$project_dir" ]; then
        print_error "Project '$project' not found"
        return 1
    fi
    
    if [ ! -d "${project_dir}_student" ] || [ ! -d "${project_dir}_teacher" ]; then
        print_error "Project '$project' does not have required _student/ and _teacher/ directories"
        return 1
    fi
    
    print_header "═══════════════════════════════════════════════════════════"
    print_header "  Testing Project: $project"
    print_header "═══════════════════════════════════════════════════════════"
    echo ""
    
    local failed=false
    
    # Test student build
    print_info "[$project] Testing student workspace build..."
    if cd "${project_dir}_student" && make clean >/dev/null 2>&1 && make build >/dev/null 2>&1; then
        print_success "[$project] Student build: OK"
    else
        print_error "[$project] Student build: FAILED"
        failed=true
    fi
    cd "$SCRIPT_DIR"
    
    # Test student tests
    print_info "[$project] Testing student test suite..."
    if cd "${project_dir}_student" && make test >/dev/null 2>&1; then
        print_success "[$project] Student tests: OK"
    else
        print_error "[$project] Student tests: FAILED"
        failed=true
    fi
    cd "$SCRIPT_DIR"
    
    # Test answer key build
    print_info "[$project] Testing answer key build..."
    if cd "${project_dir}_teacher/answer_key" && make clean >/dev/null 2>&1 && make build >/dev/null 2>&1; then
        print_success "[$project] Answer key build: OK"
    else
        print_error "[$project] Answer key build: FAILED"
        failed=true
    fi
    cd "$SCRIPT_DIR"
    
    # Test answer key tests
    print_info "[$project] Testing answer key test suite..."
    if cd "${project_dir}_teacher/answer_key" && make test-all >/dev/null 2>&1; then
        print_success "[$project] Answer key tests: OK"
    else
        print_error "[$project] Answer key tests: FAILED"
        failed=true
    fi
    cd "$SCRIPT_DIR"
    
    # Test documentation generation
    print_info "[$project] Testing documentation generation..."
    if cd "${project_dir}_student" && make docs >/dev/null 2>&1; then
        print_success "[$project] Documentation generation: OK"
    else
        print_error "[$project] Documentation generation: FAILED"
        failed=true
    fi
    cd "$SCRIPT_DIR"
    
    echo ""
    if [ "$failed" = true ]; then
        print_error "[$project] Some tests failed"
        return 1
    else
        print_success "[$project] All tests passed!"
        return 0
    fi
}

# Show help
show_help() {
    echo "Build and Test Verification Script"
    echo ""
    echo "This script automatically discovers and tests projects in the current directory."
    echo "A project is any directory that contains both _student/ and _teacher/ subdirectories."
    echo ""
    echo "Usage:"
    echo "  ./test-build.sh              # Test all discovered projects"
    echo "  ./test-build.sh <project>    # Test specific project"
    echo "  ./test-build.sh --list       # List available projects"
    echo "  ./test-build.sh --help      # Show this help"
    echo ""
    echo "Examples:"
    echo "  ./test-build.sh              # Test all projects"
    echo "  ./test-build.sh refactor     # Test only refactor project"
    echo ""
    echo "For each project, the script tests:"
    echo "  - Student workspace build"
    echo "  - Student test suite"
    echo "  - Answer key build"
    echo "  - Answer key test suite"
    echo "  - Documentation generation"
    echo ""
}

# Main execution
if [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
    show_help
    exit 0
fi

if [ "$1" = "--list" ] || [ "$1" = "-l" ]; then
    PROJECTS=($(discover_projects))
    if [ ${#PROJECTS[@]} -eq 0 ]; then
        print_error "No projects found."
        print_info "Expected directories with _student/ and _teacher/ subdirectories."
        exit 1
    fi
    echo "Available projects:"
    for project in "${PROJECTS[@]}"; do
        echo "  - $project"
    done
    exit 0
fi

echo ""
print_header "═══════════════════════════════════════════════════════════"
print_header "  Build and Test Verification"
print_header "═══════════════════════════════════════════════════════════"
echo ""

# If project specified, test only that project
if [ -n "$1" ]; then
    test_project "$1"
    exit $?
fi

# Otherwise, test all projects
PROJECTS=($(discover_projects))

if [ ${#PROJECTS[@]} -eq 0 ]; then
    print_error "No projects found. Expected directories with _student/ and _teacher/ subdirectories."
    exit 1
fi

print_info "Found ${#PROJECTS[@]} project(s): ${PROJECTS[*]}"
echo ""

TOTAL_FAILED=0
for project in "${PROJECTS[@]}"; do
    if ! test_project "$project"; then
        TOTAL_FAILED=$((TOTAL_FAILED + 1))
    fi
    echo ""
done

echo ""
print_header "═══════════════════════════════════════════════════════════"
if [ $TOTAL_FAILED -eq 0 ]; then
    print_success "All projects passed! Build system is working correctly."
else
    print_error "$TOTAL_FAILED project(s) had failures."
    exit 1
fi
print_header "═══════════════════════════════════════════════════════════"
echo ""

