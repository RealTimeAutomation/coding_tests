# Assignment Checklist

Use this checklist to track your progress through each task.

## Task A: Initial Testing & Bug Discovery (2-3 hours)

- [ ] Project builds and existing tests pass
- [ ] Added tests for `metrics.c` module
  - [ ] Happy path tests
  - [ ] Edge cases (n==0, negatives, overflow)
  - [ ] Error conditions
- [ ] Added tests for `text.c` module
  - [ ] Happy path tests
  - [ ] Edge cases (CR/LF, leading/trailing spaces, overlapping replacements)
  - [ ] Error conditions
- [ ] Added tests for `config.c` module
  - [ ] Happy path tests
  - [ ] Edge cases (long lines, invalid values, NULL pointers)
  - [ ] Error conditions
- [ ] Added tests for `list.c` module
  - [ ] Happy path tests
  - [ ] Edge cases (NULL pointers, empty list, out-of-bounds)
  - [ ] Error conditions
- [ ] Added tests for `string_utils.c` module
  - [ ] Happy path tests
  - [ ] Edge cases (NULL pointers, empty strings, buffer overflow)
  - [ ] Error conditions
- [ ] Added tests for protocol modules (apple/banana/carrot)
  - [ ] Happy path tests
  - [ ] Edge cases (NULL pointers, invalid buffers, malformed input)
  - [ ] Error conditions
- [ ] Created `BUGS_FOUND.md` documenting all discovered bugs
- [ ] All tests run and document current behavior (even if buggy)

**Check-in ready:** Submit test files and `BUGS_FOUND.md`

---

## Task B: Fix Critical Bugs (2-3 hours)

- [ ] Prioritized bugs from Task A (High → Medium → Low)
- [ ] Fixed division by zero bug (if found)
  - [ ] Added regression test
  - [ ] All tests pass
- [ ] Fixed NULL pointer dereference bugs (if found)
  - [ ] Added regression tests
  - [ ] All tests pass
- [ ] Fixed memory leak bugs (if found)
  - [ ] Added regression tests
  - [ ] All tests pass
- [ ] Fixed buffer overflow risks (if found)
  - [ ] Added regression tests
  - [ ] All tests pass
- [ ] Fixed data loss bugs (if found)
  - [ ] Added regression tests
  - [ ] All tests pass
- [ ] Updated `BUGS_FOUND.md` with fix status
- [ ] All existing tests still pass
- [ ] All new regression tests pass

**Check-in ready:** Submit fixes and updated `BUGS_FOUND.md`

---

## Task C: Refactoring & Code Quality (3-4 hours)

- [ ] Identified copy-paste patterns
- [ ] Extracted common protocol code (apple/banana/carrot)
  - [ ] Created shared helper functions
  - [ ] All tests pass
- [ ] Extracted other copy-paste patterns
  - [ ] List traversal helpers
  - [ ] String comparison helpers
  - [ ] Other duplicated code
- [ ] Broke down large functions (>50 lines)
  - [ ] Split into smaller, testable units
  - [ ] All tests pass
- [ ] Simplified complex conditionals
  - [ ] Extracted into helper functions
  - [ ] Used lookup tables where appropriate
- [ ] Added NULL pointer checks where appropriate
- [ ] Replaced unsafe functions with safer alternatives
- [ ] Removed dead/unreachable code
- [ ] All tests pass after refactoring

**Check-in ready:** Submit refactored code with all tests passing

---

## Task D: Documentation & Final Review (1-2 hours)

- [ ] Created `DESIGN_NOTES.md` with:
  - [ ] List of bugs found and fixed
  - [ ] Refactoring decisions and rationale
  - [ ] Tradeoffs made
  - [ ] Open risks or future improvements
- [ ] Verified all tests pass
- [ ] Verified code builds cleanly
- [ ] Checked for compiler warnings
- [ ] Code is readable and maintainable
- [ ] Updated `BUGS_FOUND.md` with final status
- [ ] Prepared final submission:
  - [ ] All source code
  - [ ] All test files
  - [ ] `BUGS_FOUND.md`
  - [ ] `DESIGN_NOTES.md`
  - [ ] Time log (optional but helpful)

**Check-in ready:** Final submission

---

## Time Log (Optional)

Track your time to help with evaluation:

- Task A: ___ hours
- Task B: ___ hours
- Task C: ___ hours
- Task D: ___ hours
- **Total:** ___ hours

