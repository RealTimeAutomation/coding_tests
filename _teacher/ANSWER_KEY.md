# Teacher's Answer Key - Known Bugs and Issues

This document lists all intentional bugs and code quality issues in the legacy codebase. Use this to evaluate whether candidates have:
1. Found the bugs through testing
2. Properly categorized them
3. Fixed them correctly
4. Added appropriate regression tests

**DO NOT share this file with candidates** - it's the answer key for evaluation.

---

## Module: metrics.c

### Bug #1: `metrics_sum` - Off-by-one error
**Location:** `metrics_sum()` function, line 7
**Issue:** Loop condition is `i <= n` instead of `i < n`, causing out-of-bounds read at `arr[n]`
**Severity:** High - potential undefined behavior
**Test case to reveal:** Any non-empty array (the bug may not crash but reads invalid memory)

### Bug #2: `metrics_sum` - Dead code branch
**Location:** `metrics_sum()` function, lines 8-11
**Issue:** Useless conditional `if (i < n)` inside loop that always executes the else branch
**Severity:** Low - code quality issue
**Test case to reveal:** Code review / static analysis

### Bug #3: `metrics_average` - Division by zero
**Location:** `metrics_average()` function, line 19
**Issue:** No check for `n == 0` before division, causing undefined behavior
**Severity:** High - crashes on empty array
**Test case to reveal:** Call with `n == 0`

### Bug #4: `metrics_argmax` - Incorrect tie-breaker logic
**Location:** `metrics_argmax()` function, line 31
**Issue:** Tie-breaker compares `i < (size_t)idx` which is backwards - should prefer first occurrence, not last
**Severity:** Medium - incorrect behavior
**Test case to reveal:** Array with duplicate maximum values

### Bug #5: `metrics_median` - Wrong calculation for odd-length arrays
**Location:** `metrics_median()` function, lines 70-72
**Issue:** For odd `n`, returns average instead of the middle element (copy-paste error from average function)
**Severity:** High - completely wrong result
**Test case to reveal:** Array with odd length, e.g., `[1,2,3]` should return 2, not 2 (average)

### Bug #6: `metrics_sort` - Redundant conditionals
**Location:** `metrics_sort()` function, lines 48-54
**Issue:** Nested redundant equality checks that do nothing
**Severity:** Low - code quality
**Test case to reveal:** Code review

---

## Module: text.c

### Bug #7: `is_ws` - Duplicate condition
**Location:** `is_ws()` function, line 11
**Issue:** Checks `c == '\t'` twice (lines 9 and 11) - copy-paste error
**Severity:** Low - code quality
**Test case to reveal:** Code review

### Bug #8: `is_ws` - Incorrect classification of carriage return
**Location:** `is_ws()` function, line 12
**Issue:** Returns 0 for `'\r'` (carriage return), treating it as non-whitespace when it should be whitespace
**Severity:** Medium - incorrect behavior with CRLF line endings
**Test case to reveal:** String containing `'\r'` characters

### Bug #9: `text_normalize_whitespace` - Drops leading non-whitespace
**Location:** `text_normalize_whitespace()` function, line 20
**Issue:** `in_ws` initialized to 1, causing first non-space character to be treated as whitespace and dropped
**Severity:** High - data loss bug
**Test case to reveal:** String starting with non-whitespace character

### Bug #10: `text_replace_all` - Memory leak
**Location:** `text_replace_all()` function, lines 82-83
**Issue:** When `did == 0` (no more replacements), returns `next` (which is NULL) but leaks `cur`
**Severity:** High - memory leak
**Test case to reveal:** Valgrind/AddressSanitizer, or test with replacement that completes

### Bug #11: `text_replace_all` - Skips overlapping matches
**Location:** `text_replace_all()` function, line 87
**Issue:** `start++` increments by 1, which may skip overlapping matches (e.g., replacing "aa" with "b" in "aaa")
**Severity:** Medium - incorrect behavior
**Test case to reveal:** String with overlapping patterns

### Bug #12: `text_replace_all` - Arbitrary loop limit
**Location:** `text_replace_all()` function, line 78
**Issue:** Hard-coded limit of 1000 iterations, no error handling if exceeded
**Severity:** Medium - potential silent failure
**Test case to reveal:** String requiring >1000 replacements

---

## Module: config.c

### Bug #13: `parse_bool` - Returns failure on uppercase TRUE/FALSE
**Location:** `parse_bool()` function, lines 13-14
**Issue:** Returns 0 (failure) for "TRUE" and "FALSE" even though it correctly sets the output value
**Severity:** Medium - inconsistent behavior
**Test case to reveal:** Config file with `enable_tls=TRUE`

### Bug #14: `config_parse_file` - Missing NULL pointer checks
**Location:** `config_parse_file()` function, line 30
**Issue:** No validation that `path` or `out_cfg` are non-NULL
**Severity:** Medium - potential crash
**Test case to reveal:** Call with NULL parameters

### Bug #15: `config_parse_file` - Unsafe strcpy
**Location:** `config_parse_file()` function, line 36
**Issue:** Uses `strcpy()` instead of safer `strncpy()` for default host value
**Severity:** Low - code quality (safe in this case but bad practice)

### Bug #16: `config_parse_file` - Silent truncation of long lines
**Location:** `config_parse_file()` function, line 38
**Issue:** `fgets()` with 256-byte buffer silently truncates lines >255 chars without error
**Severity:** Medium - data loss
**Test case to reveal:** Config file with line >255 characters

### Bug #17: `config_parse_file` - No validation of port value
**Location:** `config_parse_file()` function, line 55
**Issue:** Uses `atoi()` without checking for invalid values or range (e.g., negative, too large)
**Severity:** Medium - accepts invalid data
**Test case to reveal:** Config with `port=abc` or `port=-1` or `port=999999`

### Bug #18: `config_parse_file` - Silent failure on invalid bool
**Location:** `config_parse_file()` function, line 56
**Issue:** Silently ignores invalid boolean values without error
**Severity:** Medium - silent failure
**Test case to reveal:** Config with `enable_tls=maybe`

### Bug #19: `config_parse_file` - Unterminated string risk
**Location:** `config_parse_file()` function, line 61
**Issue:** `strncpy()` may leave `host` unterminated if `val` is exactly 128 chars
**Severity:** High - buffer overflow risk
**Test case to reveal:** Config with `host=` followed by exactly 128 characters

### Bug #20: `config_parse_file` - Inconsistent null termination
**Location:** `config_parse_file()` function, lines 61 vs 64
**Issue:** Line 62 adds null terminator fix, but line 64 (HOST case) doesn't - copy-paste inconsistency
**Severity:** Medium - inconsistent behavior
**Test case to reveal:** Config with `HOST=` (uppercase) with long value

### Bug #21: `config_parse_file` - Copy-paste port handling
**Location:** `config_parse_file()` function, lines 65-68
**Issue:** Multiple copy-paste cases for "Port" and "PORT" with same `atoi()` bug, no validation
**Severity:** Medium - code duplication + bugs
**Test case to reveal:** Config with `Port=` or `PORT=` keys

### Bug #22: `config_parse_file` - Dead/unreachable code
**Location:** `config_parse_file()` function, lines 69-71
**Issue:** Can never reach this branch because "port" is already handled above
**Severity:** Low - dead code
**Test case to reveal:** Code review / static analysis

---

## Module: list.c

### Bug #23-29: Missing NULL pointer checks
**Location:** All functions in `list.c`
**Issue:** No validation that `list` parameter is non-NULL in: `list_destroy`, `list_append`, `list_insert`, `list_remove_at`, `list_get`, `list_find`, `list_reverse`, `list_sort`
**Severity:** High - potential crashes
**Test case to reveal:** Call any function with NULL list pointer

### Bug #30-31: Missing malloc failure checks
**Location:** `list_create()` and `list_append()` functions
**Issue:** No check if `malloc()` returns NULL
**Severity:** High - potential crash
**Test case to reveal:** Simulate out-of-memory condition

### Bug #32-35: Copy-paste traversal patterns
**Location:** Multiple functions
**Issue:** Same "find end of list" or "traverse to index" code duplicated in: `list_append`, `list_insert`, `list_remove_at`, `list_get`
**Severity:** Low - code quality (DRY violation)
**Test case to reveal:** Code review

### Bug #36: `list_insert` - Missing NULL check in loop
**Location:** `list_insert()` function, line ~60
**Issue:** Loop doesn't verify `current` doesn't become NULL during traversal
**Severity:** Medium - potential crash on corrupted list
**Test case to reveal:** Malformed list structure

### Bug #37: `list_remove_at` - Missing NULL check
**Location:** `list_remove_at()` function
**Issue:** Doesn't check if `to_remove` is NULL before dereferencing
**Severity:** Medium - potential crash
**Test case to reveal:** Edge case with index at boundary

### Bug #38: `list_sort` - Complex function should be refactored
**Location:** `list_sort()` function
**Issue:** Large function with nested loops and complex node swapping logic - should extract helper functions
**Severity:** Low - code quality / maintainability
**Test case to reveal:** Code review

### Bug #39: `list_merge_sorted` - Missing NULL checks
**Location:** `list_merge_sorted()` function, line ~120
**Issue:** No validation that `a` or `b` are non-NULL
**Severity:** High - potential crash
**Test case to reveal:** Call with NULL parameters

### Bug #40: `list_merge_sorted` - Missing malloc check
**Location:** `list_merge_sorted()` function
**Issue:** Doesn't check if `list_create()` failed
**Severity:** High - potential crash
**Test case to reveal:** Out-of-memory condition

### Bug #41: `list_merge_sorted` - Copy-paste remainder handling
**Location:** `list_merge_sorted()` function, lines ~140-150
**Issue:** Two identical while loops for handling remaining elements in `a` and `b`
**Severity:** Low - code quality (DRY violation)
**Test case to reveal:** Code review

---

## Module: string_utils.c

### Bug #42-48: Missing NULL pointer checks
**Location:** All functions
**Issue:** No validation of NULL parameters in: `string_split`, `string_join`, `string_remove_chars`, `string_starts_with`, `string_ends_with`, `string_parse_int`, `string_format_int`, `string_remove_duplicates`, `string_count_substring`
**Severity:** High - potential crashes
**Test case to reveal:** Call any function with NULL parameters

### Bug #49: `string_split` - Missing malloc failure checks
**Location:** `string_split()` function, multiple locations
**Issue:** Multiple `malloc()` calls without checking for failure
**Severity:** High - potential crash
**Test case to reveal:** Out-of-memory condition

### Bug #50: `string_split` - Large function should be refactored
**Location:** `string_split()` function
**Issue:** Complex function with many branches - should use helper functions
**Severity:** Low - code quality
**Test case to reveal:** Code review

### Bug #51: `string_join` - Missing malloc failure check
**Location:** `string_join()` function
**Issue:** No check if `malloc()` returns NULL
**Severity:** High - potential crash
**Test case to reveal:** Out-of-memory condition

### Bug #52: `string_join` - Missing NULL check in array
**Location:** `string_join()` function, line ~50
**Issue:** Doesn't check if `strings[i]` is NULL before using it
**Severity:** Medium - potential crash
**Test case to reveal:** Array with NULL element

### Bug #53: `string_remove_chars` - Inefficient algorithm
**Location:** `string_remove_chars()` function
**Issue:** O(n*m) nested loop - should use lookup table for O(n) performance
**Severity:** Low - performance issue
**Test case to reveal:** Performance testing with large inputs

### Bug #54-55: `string_starts_with` / `string_ends_with` - Copy-paste code
**Location:** Both functions
**Issue:** Nearly identical comparison logic - should share common helper
**Severity:** Low - code quality (DRY violation)
**Test case to reveal:** Code review

### Bug #56: `string_parse_int` - No overflow checking
**Location:** `string_parse_int()` function
**Issue:** Doesn't check for integer overflow when building value
**Severity:** High - undefined behavior
**Test case to reveal:** String like "99999999999999999999"

### Bug #57: `string_parse_int` - Doesn't validate entire string
**Location:** `string_parse_int()` function
**Issue:** Stops on first non-digit but doesn't verify rest of string is valid
**Severity:** Medium - accepts partial input like "123abc" as "123"
**Test case to reveal:** String like "123abc" - should fail but returns 123

### Bug #58: `string_format_int` - Missing NULL check
**Location:** `string_format_int()` function, line ~90
**Issue:** Doesn't check if `buffer` is NULL
**Severity:** High - potential crash
**Test case to reveal:** Call with NULL buffer

### Bug #59: `string_format_int` - Buffer overflow risk
**Location:** `string_format_int()` function
**Issue:** Doesn't properly check buffer bounds in all code paths
**Severity:** High - buffer overflow
**Test case to reveal:** Small buffer with large negative number

### Bug #60: `string_format_int` - Should use snprintf
**Location:** `string_format_int()` function
**Issue:** Manual integer-to-string conversion instead of standard `snprintf()`
**Severity:** Low - code quality (reinventing the wheel)
**Test case to reveal:** Code review

### Bug #61: `string_remove_duplicates` - Inefficient algorithm
**Location:** `string_remove_duplicates()` function
**Issue:** O(n²) algorithm checking all previous characters - should use hash/lookup
**Severity:** Low - performance issue
**Test case to reveal:** Performance testing

### Bug #62: `string_count_substring` - Doesn't handle empty substring
**Location:** `string_count_substring()` function, line ~150
**Issue:** Returns 0 for empty substring, but behavior is ambiguous (could be infinite matches)
**Severity:** Medium - edge case handling
**Test case to reveal:** Call with empty substring

### Bug #63: `string_count_substring` - Inefficient nested loops
**Location:** `string_count_substring()` function
**Issue:** O(n*m) algorithm - should use `strstr()` in a loop
**Severity:** Low - performance / code quality
**Test case to reveal:** Code review

### Bug #64: `string_count_substring` - Doesn't skip overlapping matches
**Location:** `string_count_substring()` function
**Issue:** Counts overlapping matches (e.g., "aaa" with "aa" counts 2, not 1)
**Severity:** Low - may be intentional, but should be documented
**Test case to reveal:** String "aaa" with substring "aa"

---

## Module: protocol_apple.c, protocol_banana.c, protocol_carrot.c

**Note:** These three modules are **nearly identical copy-paste duplicates**. All bugs appear in all three.

### Bug #65-67: Missing NULL pointer checks (all three protocols)
**Location:** All `*_parse()` and `*_serialize()` functions
**Issue:** No validation that `buffer`, `out`, `msg`, or `buffer` parameters are non-NULL
**Severity:** High - potential crashes
**Test case to reveal:** Call with NULL parameters

### Bug #68-70: Insufficient buffer size checks (all three protocols)
**Location:** All `*_parse()` functions, line ~10
**Issue:** Only checks `buffer_len < 10` but actual minimum needed is 77 bytes (4+64+8+1)
**Severity:** High - buffer overflow risk
**Test case to reveal:** Buffer with 10-76 bytes

### Bug #71-73: No strtol error checking (all three protocols)
**Location:** All `*_parse()` functions, hex parsing
**Issue:** `strtol()` called without checking for conversion errors
**Severity:** Medium - accepts invalid hex strings
**Test case to reveal:** Buffer with invalid hex like "GGGG" for version

### Bug #74-76: Copy-paste hex parsing (all three protocols)
**Location:** All `*_parse()` functions
**Issue:** Manual character-by-character hex string building - should use helper function
**Severity:** Low - code quality (DRY violation)
**Test case to reveal:** Code review

### Bug #77-79: Invalid active flag handling (all three protocols)
**Location:** All `*_parse()` functions, line ~80
**Issue:** Doesn't return false for invalid active flag values (e.g., '2', 'x')
**Severity:** Medium - accepts invalid data
**Test case to reveal:** Buffer with active='x'

### Bug #80-82: Insufficient buffer size check (all three protocols)
**Location:** All `*_serialize()` functions, line ~95
**Issue:** Only checks `buffer_size < 80` but should be more precise
**Severity:** Medium - may be too conservative

### Bug #83-85: No snprintf return value check (all three protocols)
**Location:** All `*_serialize()` functions
**Issue:** Doesn't properly validate `snprintf()` return value
**Severity:** Medium - potential truncation
**Test case to reveal:** Very large version or temperature values

### Bug #86-88: Inconsistent null termination (all three protocols)
**Location:** All `*_serialize()` functions, device_id handling
**Issue:** Doesn't ensure proper null termination when padding device_id
**Severity:** Medium - potential unterminated string
**Test case to reveal:** Serialize then parse round-trip

### Bug #89-91: Copy-paste formatting (all three protocols)
**Location:** All `*_serialize()` functions
**Issue:** Same formatting logic duplicated - should use helper
**Severity:** Low - code quality

### Bug #92-94: Missing NULL checks in validation (all three protocols)
**Location:** All `*_validate()` functions
**Issue:** No check if `msg` is NULL
**Severity:** High - potential crash
**Test case to reveal:** Call with NULL

### Bug #95-97: Inefficient device_id validation (all three protocols)
**Location:** All `*_validate()` functions
**Issue:** Calls `strlen()` in loop condition, recalculating each iteration
**Severity:** Low - performance issue
**Test case to reveal:** Performance testing

### Bug #98-100: Missing NULL check in checksum (all three protocols)
**Location:** All `*_checksum()` functions
**Issue:** No check if `msg` is NULL
**Severity:** High - potential crash
**Test case to reveal:** Call with NULL

### Bug #101-103: Inefficient string checksum (all three protocols)
**Location:** All `*_checksum()` functions
**Issue:** Calls `strlen()` in loop, recalculating each iteration
**Severity:** Low - performance issue
**Test case to reveal:** Performance testing

### Bug #104: **MAJOR CODE DUPLICATION**
**Location:** All three protocol files
**Issue:** `protocol_apple.c`, `protocol_banana.c`, and `protocol_carrot.c` are **nearly identical** - should share common implementation
**Severity:** Critical - major refactoring opportunity
**Test case to reveal:** Code review - compare the three files

---

## Summary Statistics

- **Total bugs identified:** 104+
- **High severity:** ~35 bugs (crashes, data loss, undefined behavior)
- **Medium severity:** ~25 bugs (incorrect behavior, silent failures)
- **Low severity:** ~44 bugs (code quality, performance, maintainability)

### Categories:
- **NULL pointer issues:** ~25 instances
- **Missing error handling:** ~15 instances
- **Copy-paste code duplication:** ~12 instances
- **Buffer overflow risks:** ~8 instances
- **Memory leaks:** 1 instance
- **Algorithm inefficiencies:** ~5 instances
- **Dead/unreachable code:** 2 instances

### Key Refactoring Opportunities:
1. Extract common protocol code (apple/banana/carrot)
2. Add helper functions for repeated patterns (list traversal, hex parsing)
3. Consolidate validation logic
4. Break down large functions into smaller, testable units
5. Add comprehensive error handling
6. Use safer standard library functions (snprintf, strncpy with proper null termination)

---

## Evaluation Rubric

When reviewing candidate submissions, check:

1. **Test Coverage (40 points)**
   - Did they find the high-severity bugs?
   - Did they test edge cases (NULL, empty, overflow)?
   - Are tests well-organized and readable?

2. **Bug Classification (20 points)**
   - Did they correctly identify bug severity?
   - Did they document the bugs clearly?
   - Did they prioritize fixes appropriately?

3. **Refactoring Quality (25 points)**
   - Did they extract common code (especially protocols)?
   - Did they break down large functions?
   - Did they improve code maintainability?
   - Did they preserve intentional behavior?

4. **Build & Documentation (10 points)**
   - Does it still build and run?
   - Are tests passing?
   - Is documentation clear?

5. **Polish (5 points)**
   - Code style consistency
   - Commit quality
   - Attention to detail

