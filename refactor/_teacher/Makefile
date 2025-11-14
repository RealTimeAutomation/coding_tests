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

clean:
	@rm -rf ../_student/build
	@cd answer_key && $(MAKE) clean >/dev/null 2>&1 || true
	@rm -f comparison_report.md

