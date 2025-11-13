# Teacher-only Makefile for running final comprehensive tests
# This directory should be DELETED before distributing to students
.PHONY: all clean build final

all: final

build:
	@mkdir -p ../build && cd ../build && cmake .. >/dev/null && $(MAKE) -s

final: build
	@echo "Running initial test suite..."
	@cd ../build && ./run_tests test_results.md || true
	@echo ""
	@echo "Running final test suite (will show failures)..."
	@cd ../build && ./run_tests_final test_results_final.md || true
	@echo ""
	@echo "Test results saved to:"
	@echo "  - build/test_results.md (initial tests)"
	@echo "  - build/test_results_final.md (final tests)"

clean:
	@rm -rf ../build

