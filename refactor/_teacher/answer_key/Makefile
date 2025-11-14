# Answer Key Makefile
# This builds and tests the corrected reference implementation
# Can also test student code from ../../_student/ using full test suites

.PHONY: all clean build test test-final test-all test-student docs help

all: test-all

build:
	@mkdir -p build
	@cd build && cmake .. >/dev/null && $(MAKE) -s

test: build
	@echo "Running initial test suite (should all pass)..."
	@cd build && ./run_tests test_results.md
	@echo ""
	@echo "Test results written to: build/test_results.md"

test-final: build
	@echo "Running final test suite (should all pass)..."
	@cd build && ./run_tests_final test_results_final.md
	@echo ""
	@echo "Test results written to: build/test_results_final.md"

test-all: test test-final
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "All tests completed successfully!"
	@echo "═══════════════════════════════════════════════════════════"

test-student:
	@if [ ! -d "../../_student" ]; then \
		echo "Error: _student directory not found"; \
		echo "Expected: ../../_student/ (from refactor/_teacher/answer_key/)"; \
		exit 1; \
	fi
	@echo "Testing student code from: ../../_student/"
	@echo "Current branch: $$(cd ../../_student && git branch --show-current 2>/dev/null || echo 'not a git repo')"
	@echo "Building student code with full test suites..."
	@mkdir -p build/student_test
	@cp CMakeLists_student_test.txt build/student_test/CMakeLists.txt
	@cd build/student_test && \
		cmake -DSTUDENT_SOURCE_DIR="$$(cd ../../../../_student && pwd)" \
		      -DANSWER_KEY_DIR="$$(cd ../.. && pwd)" \
		      . 2>/dev/null || \
		cmake -DSTUDENT_SOURCE_DIR="$$(cd ../../../../_student && pwd)" \
		      -DANSWER_KEY_DIR="$$(cd ../.. && pwd)" \
		      .
	@cd build/student_test && $(MAKE) -s
	@echo ""
	@echo "Running initial tests against student code..."
	@cd build/student_test && ./run_tests student_test_results.md || true
	@echo ""
	@echo "Running final tests against student code..."
	@cd build/student_test && ./run_tests_final student_test_results_final.md || true
	@echo ""
	@echo "Test results written to:"
	@echo "  - build/student_test/student_test_results.md"
	@echo "  - build/student_test/student_test_results_final.md"

docs:
	@echo "Generating API documentation..."
	@if ! command -v doxygen >/dev/null 2>&1; then \
		echo "❌ Doxygen not found. Install with:"; \
		echo "   sudo apt-get install doxygen  # Linux"; \
		echo "   brew install doxygen          # macOS"; \
		exit 1; \
	fi
	@doxygen Doxyfile >/dev/null 2>&1 || doxygen Doxyfile
	@echo ""
	@echo "✅ Documentation generated successfully!"
	@echo "   Open docs/html/index.html in your browser"

clean:
	@rm -rf build docs

help:
	@echo "Answer Key Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  make build          - Build the answer key project"
	@echo "  make test           - Run initial tests (should all pass)"
	@echo "  make test-final     - Run final tests (should all pass)"
	@echo "  make test-all       - Run all tests"
	@echo "  make test-student   - Test student code from ../../_student/ with full test suites"
	@echo "  make docs           - Generate API documentation (HTML)"
	@echo "  make clean          - Remove build directory and docs"
	@echo ""
	@echo "Examples:"
	@echo "  make test-all                    # Test answer key"
	@echo "  make test-student                # Test student code with full suites"
	@echo "  make docs                        # Generate API documentation"
