# Convenience Makefile to build with or without CMake
.PHONY: all clean build test

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

clean:
	@rm -rf build
