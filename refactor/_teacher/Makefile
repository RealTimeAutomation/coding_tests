# Teacher-only Makefile for running comprehensive tests and comparisons
# This directory should be DELETED before distributing to students
.PHONY: all clean build test final compare

all: test

build:
	@mkdir -p ../_student/build && cd ../_student/build && cmake .. >/dev/null && $(MAKE) -s

# Test both student and answer key solutions, then compare
test: compare

# Build and test answer key solution
test-answer-key:
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "  Testing Answer Key Solution (Reference Implementation)"
	@echo "═══════════════════════════════════════════════════════════"
	@echo "[1/4] Cleaning previous builds..."
	@cd answer_key && $(MAKE) clean >/dev/null 2>&1 && echo "  ✅ Cleaned" || echo "  ⚠️  Nothing to clean"
	@echo "[2/4] Building answer key..."
	@cd answer_key && $(MAKE) build 2>&1 | grep -E "(Building|Linking|Built target)" | tail -3 || echo "  ✅ Build complete"
	@echo "[3/4] Running initial tests (64 tests)..."
	@if [ -f answer_key/build/run_tests ]; then \
		cd answer_key/build && ./run_tests test_results.md 2>&1 | tail -6 | head -5; \
	else \
		echo "  ⚠️  run_tests not found, building..."; \
		cd answer_key && $(MAKE) build >/dev/null 2>&1 && cd build && ./run_tests test_results.md 2>&1 | tail -6 | head -5 || echo "  ❌ Tests failed to run"; \
	fi
	@echo "[4/4] Running final tests (96 tests)..."
	@if [ -f answer_key/build/run_tests_final ]; then \
		cd answer_key/build && ./run_tests_final test_results_final.md 2>&1 | tail -6 | head -5; \
	else \
		echo "  ⚠️  run_tests_final not found, building..."; \
		cd answer_key && $(MAKE) build >/dev/null 2>&1 && cd build && ./run_tests_final test_results_final.md 2>&1 | tail -6 | head -5 || echo "  ❌ Tests failed to run"; \
	fi
	@echo "✅ Answer key tests completed"

# Build and test student solution
test-student:
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "  Testing Student Solution"
	@echo "═══════════════════════════════════════════════════════════"
	@echo "[1/3] Building student code..."
	@$(MAKE) build 2>&1 | grep -E "(Building|Linking|Built target)" | tail -3 || echo "  ✅ Build complete"
	@echo "[2/3] Running initial test suite (64 tests)..."
	@cd ../_student/build && ./run_tests test_results.md 2>&1 | sed 's/Segmentation fault (core dumped)/Segmentation fault/g' | tee /tmp/student_init_tests.log | tail -8 | head -6
	@echo "[3/3] Running final test suite (96 tests)..."
	@cd ../_student/build && (./_teacher_build/run_tests_final test_results_final.md 2>&1 | sed 's/Segmentation fault (core dumped)/Segmentation fault/g' | tee /tmp/student_final_tests.log | tail -8 | head -6 || true)
	@echo "✅ Student tests completed"

# Compare results and generate report
compare: test-answer-key test-student
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "  Generating Comparison Report"
	@echo "═══════════════════════════════════════════════════════════"
	@chmod +x compare_results.sh 2>/dev/null || true
	@if [ ! -f "../_student/build/test_results.md" ]; then \
		echo "⚠️  Warning: Student initial test results not found"; \
	fi
	@if [ ! -f "../_student/build/test_results_final.md" ]; then \
		echo "⚠️  Warning: Student final test results not found"; \
	fi
	@if [ ! -f "answer_key/build/test_results.md" ]; then \
		echo "⚠️  Warning: Answer key initial test results not found"; \
		echo "  Attempting to run answer key tests..."; \
		cd answer_key && $(MAKE) test >/dev/null 2>&1 || true; \
	fi
	@if [ ! -f "answer_key/build/test_results_final.md" ]; then \
		echo "⚠️  Warning: Answer key final test results not found"; \
		echo "  Attempting to run answer key final tests..."; \
		cd answer_key && $(MAKE) test-final >/dev/null 2>&1 || true; \
	fi
	@./compare_results.sh \
		"../_student/build/test_results.md" \
		"../_student/build/test_results_final.md" \
		"answer_key/build/test_results.md" \
		"answer_key/build/test_results_final.md" \
		"comparison_report.md" 2>&1 || (echo "⚠️  Comparison script had issues, but continuing..." && touch comparison_report.md)
	@if [ -f comparison_report.md ] && [ -s comparison_report.md ]; then \
		echo "✅ Report generated successfully"; \
		echo ""; \
		echo "═══════════════════════════════════════════════════════════"; \
		echo "  📊 COMPARISON SUMMARY"; \
		echo "═══════════════════════════════════════════════════════════"; \
		echo ""; \
		grep -A 6 "^## Summary" comparison_report.md | head -8 | sed 's/^|/│/g' | sed 's/^## Summary/## Summary/' || true; \
		echo ""; \
		echo "📄 Full detailed report: comparison_report.md"; \
		echo ""; \
	else \
		echo "⚠️  Comparison report generation had issues"; \
		echo "  Student results: ../_student/build/test_results*.md"; \
		echo "  Answer key results: answer_key/build/test_results*.md"; \
		echo ""; \
	fi

# Legacy: just test student with final tests
final: build
	@echo "Running initial test suite..."
	@cd ../_student/build && ./run_tests test_results.md || true
	@echo ""
	@echo "Running final test suite (will show failures)..."
	@cd ../_student/build && (./_teacher_build/run_tests_final test_results_final.md 2>&1 | sed 's/Segmentation fault (core dumped)/Segmentation fault/g') || true
	@echo ""
	@echo "Test results saved to:"
	@echo "  - _student/build/test_results.md (initial tests)"
	@echo "  - _student/build/test_results_final.md (final tests)"

valgrind-student: build
	@echo "Running student tests with Valgrind..."
	@if ! command -v valgrind >/dev/null 2>&1; then \
		echo "❌ Valgrind not found. Install with: sudo apt-get install valgrind"; \
		exit 1; \
	fi
	@cd ../_student/build && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./run_tests 2>&1 | tee valgrind_student.txt || true
	@echo "Valgrind output: ../_student/build/valgrind_student.txt"

valgrind-answer-key:
	@echo "Running answer key tests with Valgrind..."
	@if ! command -v valgrind >/dev/null 2>&1; then \
		echo "❌ Valgrind not found. Install with: sudo apt-get install valgrind"; \
		exit 1; \
	fi
	@cd answer_key && $(MAKE) build >/dev/null 2>&1
	@cd answer_key/build && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./run_tests 2>&1 | tee valgrind_answer_key.txt || true
	@echo "Valgrind output: answer_key/build/valgrind_answer_key.txt"

valgrind: valgrind-student valgrind-answer-key
	@echo ""
	@echo "✅ Valgrind analysis complete for both solutions"

cppcheck-student:
	@echo "Running cppcheck on student code..."
	@if ! command -v cppcheck >/dev/null 2>&1; then \
		echo "❌ cppcheck not found. Install with: sudo apt-get install cppcheck"; \
		exit 1; \
	fi
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction \
		-I ../_student/include --xml --xml-version=2 ../_student/src/legacy/*.c ../_student/src/*.c 2> cppcheck_student.xml || true
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction \
		-I ../_student/include ../_student/src/legacy/*.c ../_student/src/*.c 2>&1 | tee cppcheck_student.txt || true
	@echo "cppcheck reports: cppcheck_student.xml, cppcheck_student.txt"

cppcheck-answer-key:
	@echo "Running cppcheck on answer key code..."
	@if ! command -v cppcheck >/dev/null 2>&1; then \
		echo "❌ cppcheck not found. Install with: sudo apt-get install cppcheck"; \
		exit 1; \
	fi
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction \
		-I answer_key/include --xml --xml-version=2 answer_key/src/legacy/*.c answer_key/src/*.c 2> cppcheck_answer_key.xml || true
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction \
		-I answer_key/include answer_key/src/legacy/*.c answer_key/src/*.c 2>&1 | tee cppcheck_answer_key.txt || true
	@echo "cppcheck reports: cppcheck_answer_key.xml, cppcheck_answer_key.txt"

cppcheck: cppcheck-student cppcheck-answer-key
	@echo ""
	@echo "✅ cppcheck analysis complete for both solutions"

sanitize-student: build
	@echo "Building student code with AddressSanitizer..."
	@cd ../_student/build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-fsanitize=address -fno-omit-frame-pointer -g" .. >/dev/null
	@cd ../_student/build && $(MAKE) -s
	@echo "Running student tests with AddressSanitizer..."
	@cd ../_student/build && ASAN_OPTIONS=detect_leaks=1:halt_on_error=0 ./run_tests 2>&1 | tee sanitizer_student.txt || true
	@echo "AddressSanitizer output: ../_student/build/sanitizer_student.txt"

sanitize-answer-key:
	@echo "Building answer key with AddressSanitizer..."
	@cd answer_key/build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-fsanitize=address -fno-omit-frame-pointer -g" .. >/dev/null
	@cd answer_key/build && $(MAKE) -s
	@echo "Running answer key tests with AddressSanitizer..."
	@cd answer_key/build && ASAN_OPTIONS=detect_leaks=1:halt_on_error=0 ./run_tests 2>&1 | tee sanitizer_answer_key.txt || true
	@echo "AddressSanitizer output: answer_key/build/sanitizer_answer_key.txt"

sanitize: sanitize-student sanitize-answer-key
	@echo ""
	@echo "✅ AddressSanitizer analysis complete for both solutions"

coverage-student: build
	@echo "Generating coverage for student code..."
	@cd ../_student/build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="--coverage -fprofile-arcs -ftest-coverage" .. >/dev/null
	@cd ../_student/build && $(MAKE) -s
	@cd ../_student/build && ./run_tests >/dev/null 2>&1 || true
	@if command -v gcov >/dev/null 2>&1; then \
		cd ../_student/build && gcov ../src/legacy/*.c ../src/*.c >/dev/null 2>&1 || true; \
		echo "Student coverage files: ../_student/build/*.gcov"; \
	fi

coverage-answer-key:
	@echo "Generating coverage for answer key..."
	@cd answer_key/build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="--coverage -fprofile-arcs -ftest-coverage" .. >/dev/null
	@cd answer_key/build && $(MAKE) -s
	@cd answer_key/build && ./run_tests >/dev/null 2>&1 || true
	@if command -v gcov >/dev/null 2>&1; then \
		cd answer_key/build && gcov ../src/legacy/*.c ../src/*.c >/dev/null 2>&1 || true; \
		echo "Answer key coverage files: answer_key/build/*.gcov"; \
	fi

coverage: coverage-student coverage-answer-key
	@echo ""
	@echo "✅ Coverage analysis complete for both solutions"

clean:
	@rm -rf ../_student/build
	@cd answer_key && $(MAKE) clean >/dev/null 2>&1 || true
	@rm -f comparison_report.md
	@rm -f cppcheck_*.xml cppcheck_*.txt

help:
	@echo "Teacher Makefile - Available targets:"
	@echo ""
	@echo "Testing:"
	@echo "  make test              - Test both solutions and generate comparison report"
	@echo "  make final             - Test student solution with final tests"
	@echo ""
	@echo "Analysis Tools:"
	@echo "  make valgrind          - Run Valgrind on both student and answer key"
	@echo "  make valgrind-student  - Run Valgrind on student code only"
	@echo "  make valgrind-answer-key - Run Valgrind on answer key only"
	@echo ""
	@echo "  make cppcheck          - Run cppcheck on both solutions"
	@echo "  make cppcheck-student  - Run cppcheck on student code only"
	@echo "  make cppcheck-answer-key - Run cppcheck on answer key only"
	@echo ""
	@echo "  make sanitize          - Run AddressSanitizer on both solutions"
	@echo "  make sanitize-student  - Run AddressSanitizer on student code only"
	@echo "  make sanitize-answer-key - Run AddressSanitizer on answer key only"
	@echo ""
	@echo "  make coverage          - Generate coverage for both solutions"
	@echo "  make coverage-student  - Generate coverage for student code only"
	@echo "  make coverage-answer-key - Generate coverage for answer key only"
	@echo ""
	@echo "Other:"
	@echo "  make clean              - Clean all build directories"
	@echo "  make help               - Show this help message"

