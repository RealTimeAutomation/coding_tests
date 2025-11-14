#!/bin/bash
# Script to compare student and answer key test results
# Generates a comparison report

STUDENT_INITIAL="$1"
STUDENT_FINAL="$2"
ANSWER_KEY_INITIAL="$3"
ANSWER_KEY_FINAL="$4"
OUTPUT_REPORT="$5"

if [ ! -f "$STUDENT_INITIAL" ] || [ ! -f "$STUDENT_FINAL" ]; then
    echo "Error: Student test result files not found"
    exit 1
fi

if [ ! -f "$ANSWER_KEY_INITIAL" ] || [ ! -f "$ANSWER_KEY_FINAL" ]; then
    echo "Error: Answer key test result files not found"
    exit 1
fi

# Extract test counts from markdown files
extract_summary() {
    local file="$1"
    if [ ! -f "$file" ]; then
        echo "0|0|0|0"
        return
    fi
    # Look for summary section - format: "- **Total**: 64 tests" or "Total Tests:  64"
    local total=$(grep -iE "(\*\*Total\*\*:|Total Tests:)" "$file" | head -1 | grep -oE '[0-9]+' | head -1)
    local passed=$(grep -iE "(\*\*Passed\*\*:|Passed:)" "$file" | head -1 | grep -oE '[0-9]+' | head -1)
    local failed=$(grep -iE "(\*\*Failed\*\*:|Failed:)" "$file" | head -1 | grep -oE '[0-9]+' | head -1)
    local crashed=$(grep -iE "(\*\*Crashed\*\*:|Crashed:)" "$file" | head -1 | grep -oE '[0-9]+' | head -1)
    
    # If summary not found, count from test results
    if [ -z "$total" ] || [ "$total" = "0" ]; then
        # First, try to get total from "Running X tests..." line (should be at start)
        total=$(grep -iE "Running [0-9]+ tests" "$file" | head -1 | grep -oE '[0-9]+' | head -1)
        # Count actual test results from the file
        passed=$(grep -c "✅ PASS\|PASS\]" "$file" 2>/dev/null || echo "0")
        failed=$(grep -c "❌ FAIL\|FAIL\]" "$file" 2>/dev/null || echo "0")
        crashed=$(grep -c "💥 CRASH\|CRASH\]" "$file" 2>/dev/null || echo "0")
        # If we have a total from "Running X tests" but no summary, use that total
        # Otherwise, if no total found, use sum of results (partial run)
        if [ -z "$total" ] || [ "$total" = "0" ]; then
            total=$((passed + failed + crashed))
        fi
    fi
    
    # Default to 0 if not found
    total=${total:-0}
    passed=${passed:-0}
    failed=${failed:-0}
    crashed=${crashed:-0}
    echo "$total|$passed|$failed|$crashed"
}

# Extract individual test results
extract_test_results() {
    local file="$1"
    grep -E "^\| \`.*\` \|" "$file" | sed 's/| `\([^`]*\)` | \([^|]*\) |/\1|\2/' | sed 's/[[:space:]]*//g'
}

STUDENT_INIT_SUM=$(extract_summary "$STUDENT_INITIAL")
STUDENT_FINAL_SUM=$(extract_summary "$STUDENT_FINAL")
ANSWER_INIT_SUM=$(extract_summary "$ANSWER_KEY_INITIAL")
ANSWER_FINAL_SUM=$(extract_summary "$ANSWER_KEY_FINAL")

# Parse summaries
IFS='|' read -r s_init_total s_init_passed s_init_failed s_init_crashed <<< "$STUDENT_INIT_SUM"
IFS='|' read -r s_final_total s_final_passed s_final_failed s_final_crashed <<< "$STUDENT_FINAL_SUM"
IFS='|' read -r a_init_total a_init_passed a_init_failed a_init_crashed <<< "$ANSWER_INIT_SUM"
IFS='|' read -r a_final_total a_final_passed a_final_failed a_final_crashed <<< "$ANSWER_FINAL_SUM"

# Calculate totals
s_total=$((s_init_total + s_final_total))
s_passed=$((s_init_passed + s_final_passed))
s_failed=$((s_init_failed + s_final_failed))
s_crashed=$((s_init_crashed + s_final_crashed))

a_total=$((a_init_total + a_final_total))
a_passed=$((a_init_passed + a_final_passed))
a_failed=$((a_init_failed + a_final_failed))
a_crashed=$((a_init_crashed + a_final_crashed))

# Generate report
cat > "$OUTPUT_REPORT" << EOF
# Test Results Comparison Report

Generated: $(date)

## Summary

| Test Suite | Student | Answer Key | Difference |
|------------|---------|------------|------------|
| **Initial Tests** | $s_init_passed/$s_init_total ✅ | $a_init_passed/$a_init_total ✅ | $((a_init_passed - s_init_passed)) |
| **Final Tests** | $s_final_passed/$s_final_total ✅ | $a_final_passed/$a_final_total ✅ | $((a_final_passed - s_final_passed)) |
| **Total** | **$s_passed/$s_total** | **$a_passed/$a_total** | **$((a_passed - s_passed))** |

## Detailed Breakdown

### Initial Test Suite

**Student Results:**
- Total: $s_init_total
- Passed: $s_init_passed ✅
- Failed: $s_init_failed ❌
- Crashed: $s_init_crashed 💥
- Success Rate: $(if [ "$s_init_total" -gt 0 ]; then awk "BEGIN {printf \"%.1f\", ($s_init_passed*100.0/$s_init_total)}"; else echo "0.0"; fi)%

**Answer Key Results:**
- Total: $a_init_total
- Passed: $a_init_passed ✅
- Failed: $a_init_failed ❌
- Crashed: $a_init_crashed 💥
- Success Rate: $(if [ "$a_init_total" -gt 0 ]; then awk "BEGIN {printf \"%.1f\", ($a_init_passed*100.0/$a_init_total)}"; else echo "0.0"; fi)%

### Final Test Suite

**Student Results:**
- Total: $s_final_total
- Passed: $s_final_passed ✅
- Failed: $s_final_failed ❌
- Crashed: $s_final_crashed 💥
- Success Rate: $(if [ "$s_final_total" -gt 0 ]; then awk "BEGIN {printf \"%.1f\", ($s_final_passed*100.0/$s_final_total)}"; else echo "0.0"; fi)%

**Answer Key Results:**
- Total: $a_final_total
- Passed: $a_final_passed ✅
- Failed: $a_final_failed ❌
- Crashed: $a_final_crashed 💥
- Success Rate: $(if [ "$a_final_total" -gt 0 ]; then awk "BEGIN {printf \"%.1f\", ($a_final_passed*100.0/$a_final_total)}"; else echo "0.0"; fi)%

## Overall Assessment

**Student Progress:**
- Tests Fixed: $((s_final_passed)) / $a_final_total final tests
- Completion: $(if [ "$a_final_total" -gt 0 ]; then awk "BEGIN {printf \"%.1f\", ($s_final_passed*100.0/$a_final_total)}"; else echo "0.0"; fi)% of final tests passing
- Remaining Issues: $((a_final_total - s_final_passed)) tests still failing

**Grade Estimation:**
- Initial Tests: $(if [ "$a_init_total" -gt 0 ]; then awk "BEGIN {printf \"%.0f\", ($s_init_passed*100.0/$a_init_total)}"; else echo "0"; fi)% (Expected: 100%)
- Final Tests: $(if [ "$a_final_total" -gt 0 ]; then awk "BEGIN {printf \"%.0f\", ($s_final_passed*100.0/$a_final_total)}"; else echo "0"; fi)% (Expected: 100%)
- Overall: $(if [ "$a_total" -gt 0 ]; then awk "BEGIN {printf \"%.0f\", ($s_passed*100.0/$a_total)}"; else echo "0"; fi)% (Expected: 100%)

## Notes

- Initial tests are designed to pass with buggy code (intentionally skip bug-revealing scenarios)
- Final tests are designed to catch bugs and will fail until bugs are fixed
- Answer key represents the reference implementation with all bugs fixed
- Student should aim for 100% pass rate on both test suites

EOF

echo "Comparison report generated: $OUTPUT_REPORT"

