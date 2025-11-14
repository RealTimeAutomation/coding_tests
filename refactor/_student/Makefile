# Convenience Makefile to build with or without CMake
.PHONY: all clean build test valgrind cppcheck sanitize coverage help

all: build

build:
	@if [ ! -d build ]; then \
		mkdir -p build; \
		chmod 755 build 2>/dev/null || true; \
	fi
	@cd build && cmake .. >/dev/null && $(MAKE) -s

test: build
	@echo "Running initial test suite..."
	@cd build && ./run_tests test_results.md
	@echo ""
	@echo "Initial test results saved to: build/test_results.md"

valgrind: build
	@echo "Running tests with Valgrind (memory leak detection)..."
	@if ! command -v valgrind >/dev/null 2>&1; then \
		echo "❌ Valgrind not found. Install with: sudo apt-get install valgrind"; \
		exit 1; \
	fi
	@cd build && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./run_tests 2>&1 | tee valgrind_output.txt || true
	@echo ""
	@echo "Valgrind output saved to: build/valgrind_output.txt"

cppcheck: build
	@echo "Running cppcheck (static analysis)..."
	@if ! command -v cppcheck >/dev/null 2>&1; then \
		echo "❌ cppcheck not found. Install with: sudo apt-get install cppcheck"; \
		exit 1; \
	fi
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction \
		--xml --xml-version=2 src/legacy/*.c src/*.c 2> build/cppcheck_report.xml || true
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction \
		src/legacy/*.c src/*.c 2>&1 | tee build/cppcheck_report.txt || true
	@echo ""
	@echo "cppcheck reports saved to:"
	@echo "  - build/cppcheck_report.xml"
	@echo "  - build/cppcheck_report.txt"

sanitize: build
	@echo "Building with AddressSanitizer..."
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-fsanitize=address -fno-omit-frame-pointer -g" .. >/dev/null
	@cd build && $(MAKE) -s
	@echo "Running tests with AddressSanitizer..."
	@cd build && ASAN_OPTIONS=detect_leaks=1:halt_on_error=0 ./run_tests 2>&1 | tee sanitizer_output.txt || true
	@echo ""
	@echo "AddressSanitizer output saved to: build/sanitizer_output.txt"

coverage: build
	@echo "Building with code coverage..."
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="--coverage -fprofile-arcs -ftest-coverage" .. >/dev/null
	@cd build && $(MAKE) -s
	@echo "Running tests to generate coverage data..."
	@cd build && ./run_tests >/dev/null 2>&1 || true
	@echo "Generating coverage report..."
	@if command -v gcov >/dev/null 2>&1; then \
		cd build && gcov ../src/legacy/*.c ../src/*.c >/dev/null 2>&1 || true; \
		echo "Coverage files generated in: build/"; \
		echo "View .gcov files for line-by-line coverage"; \
	else \
		echo "⚠️  gcov not found. Install with: sudo apt-get install gcov"; \
	fi
	@if command -v lcov >/dev/null 2>&1; then \
		cd build && lcov --capture --directory . --output-file coverage.info >/dev/null 2>&1 && \
		lcov --remove coverage.info '/usr/*' --output-file coverage.info >/dev/null 2>&1 && \
		genhtml coverage.info --output-directory coverage_html >/dev/null 2>&1 && \
		echo "HTML coverage report: build/coverage_html/index.html"; \
	fi

clean:
	@rm -rf build

help:
	@echo "Available targets:"
	@echo "  make build      - Build the project"
	@echo "  make test       - Run unit tests"
	@echo "  make valgrind   - Run tests with Valgrind (memory leak detection)"
	@echo "  make cppcheck   - Run cppcheck (static code analysis)"
	@echo "  make sanitize   - Build and test with AddressSanitizer"
	@echo "  make coverage   - Generate code coverage report"
	@echo "  make clean      - Remove build directory"
	@echo ""
	@echo "Example:"
	@echo "  make valgrind   # Check for memory leaks"
	@echo "  make cppcheck   # Find potential bugs statically"
	@echo "  make sanitize   # Detect memory errors at runtime"
	@echo "  make coverage   # See which code is tested"
