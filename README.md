# Legacy Refactor Project (Assignment)

This repo contains a small legacy C codebase that needs testing, bug fixing, and refactoring. Your task is to find bugs, write tests, and improve the code quality.

---

## Assignment Structure

This assignment is divided into **4 tasks** with estimated time and check-in points. Complete each task before moving to the next.

### Task A: Initial Testing & Bug Discovery (2-3 hours)
**Deliverable:** Comprehensive test suite that reveals bugs

1. **Run existing tests** to understand the codebase
   ```bash
   make test
   # or
   cd build && cmake .. && cmake --build . -j && ./run_tests
   ```

2. **Add comprehensive tests** for each module:
   - Test happy paths
   - Test edge cases (NULL pointers, empty inputs, overflow, boundary conditions)
   - Test error conditions
   - Document any unexpected behavior you discover

3. **Create a bug report** (`BUGS_FOUND.md`) listing:
   - Each bug you discovered
   - How to reproduce it (test case)
   - Severity (High/Medium/Low)
   - Brief description

**Check-in:** Submit your test files and `BUGS_FOUND.md` before proceeding to Task B.

---

### Task B: Fix Critical Bugs (2-3 hours)
**Deliverable:** Fixed critical bugs with regression tests

1. **Prioritize bugs** from Task A:
   - Focus on High severity bugs first (crashes, data loss, undefined behavior)
   - Then Medium severity (incorrect behavior, silent failures)

2. **Fix each bug** one at a time:
   - Make the fix
   - Add a specific regression test for that bug
   - Ensure all existing tests still pass
   - Commit with clear message (e.g., "Fix: division by zero in metrics_average")

3. **Update bug report** marking which bugs are fixed

**Check-in:** Submit your fixes and updated `BUGS_FOUND.md` showing fixed bugs.

---

### Task C: Refactoring & Code Quality (3-4 hours)
**Deliverable:** Refactored code with reduced complexity

1. **Extract common code:**
   - Identify copy-paste patterns (especially the three protocol modules)
   - Create shared helper functions
   - Refactor to eliminate duplication

2. **Break down large functions:**
   - Functions >50 lines should be split into smaller, testable units
   - Extract complex conditionals into helper functions
   - Improve readability

3. **Improve code quality:**
   - Add NULL pointer checks where appropriate
   - Use safer standard library functions
   - Remove dead/unreachable code
   - Simplify complex conditionals

4. **Ensure all tests pass** after each refactoring step

**Check-in:** Submit refactored code with all tests passing.

---

### Task D: Documentation & Final Review (1-2 hours)
**Deliverable:** Complete documentation and final codebase

1. **Write `DESIGN_NOTES.md`** explaining:
   - What bugs you found and fixed
   - What refactoring you did and why
   - Tradeoffs you made
   - Any open risks or future improvements

2. **Final verification:**
   - All tests pass
   - Code builds cleanly
   - No compiler warnings (if possible)
   - Code is readable and maintainable

3. **Final submission:**
   - All source code
   - All test files
   - `BUGS_FOUND.md` (with status of each bug)
   - `DESIGN_NOTES.md`
   - Brief summary of time spent on each task

**Check-in:** Final submission with all deliverables.

---

## Build & Test

### Prerequisites
- **CMake** (3.10 or later)
- **C compiler** (GCC, Clang, or MSVC)
- **Make** (optional, for convenience Makefile)

### Building

**Option A: Using Make (works in WSL/Linux/Git Bash)**
```bash
make test
```

**Option B: Using CMake directly**

*In WSL/Linux/Git Bash:*
```bash
mkdir -p build && cd build
cmake ..
cmake --build . -j
./run_tests
```

### Test Suite

**Tests** (`run_tests`): Comprehensive tests that should **all pass** initially. These test happy paths and basic functionality.

**Using Make:**
```bash
# Run initial tests
make test
```

**Using CMake directly:**
```bash
# Run initial tests (should all pass)
cd build
./run_tests test_results.md
```

Test results are automatically saved as Markdown files:
- `build/test_results.md` - Test results

The test output includes verbose information showing which tests passed, failed, or crashed (segfaulted).

*In PowerShell:*
```powershell
mkdir build; cd build
cmake ..
cmake --build . -j
.\run_tests.exe
```

*In CMD:*
```cmd
mkdir build
cd build
cmake ..
cmake --build . -j
run_tests.exe
```

**Note:** If `cmake` is not in your PATH, you may need to:
- Add CMake to your system PATH, or
- Use the full path to cmake (e.g., `"C:\Program Files\CMake\bin\cmake.exe"`), or
- Use WSL if CMake is installed there

### Running the Main Program

The main program demonstrates all three protocols (apple, banana, carrot) with configurable logging:

```bash
# Build and run
cd build
./main

# Or with logging enabled (set LOG_LEVEL environment variable)
LOG_LEVEL=DEBUG ./main
LOG_LEVEL=INFO ./main
LOG_LEVEL=WARN ./main
LOG_LEVEL=ERROR ./main
LOG_LEVEL=NONE ./main
```

The logging levels are: `NONE`, `ERROR`, `WARN`, `INFO`, `DEBUG` (from least to most verbose).

---

## Testing & Analysis Tools

### Code Coverage

Use **gcov** (GCC) or **llvm-cov** (Clang) to measure test coverage before and after refactoring:

**Before refactoring:**
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="--coverage -fprofile-arcs -ftest-coverage"
cmake --build .
./run_tests
gcov ../src/legacy/*.c
# View coverage reports in .gcov files
```

**After refactoring:**
```bash
# Repeat the same steps and compare coverage
```

### Memory Analysis

Use **Valgrind** (Linux/WSL) or **AddressSanitizer** to detect memory issues:

**Valgrind (Linux/WSL):**
```bash
# Before refactoring
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/run_tests
valgrind --leak-check=full --show-leak-kinds=all ./build/main

# After refactoring - compare results
```

**AddressSanitizer (GCC/Clang):**
```bash
# Build with AddressSanitizer
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-fsanitize=address -g"
cmake --build .
./run_tests
./main
```

### Static Analysis

Use **cppcheck** or compiler warnings for static analysis:

```bash
# Enable all warnings
cd build
cmake .. -DCMAKE_C_FLAGS="-Wall -Wextra -Wpedantic"
cmake --build .
```

These tools help demonstrate improvements in code quality, test coverage, and memory safety between the initial and refactored codebase.

---

## Code Map

- `include/metrics.h` / `src/legacy/metrics.c` — Basic integer metrics operations
- `include/text.h` / `src/legacy/text.c` — Whitespace normalization, uppercase conversion, and string replacement
- `include/config.h` / `src/legacy/config.c` — Minimal configuration file parser
- `include/list.h` / `src/legacy/list.c` — Linked list implementation
- `include/string_utils.h` / `src/legacy/string_utils.c` — String utilities (split, join, parse, format)
- `include/protocol_apple.h` / `src/legacy/protocol_apple.c` — Apple protocol parser/serializer
- `include/protocol_banana.h` / `src/legacy/protocol_banana.c` — Banana protocol parser/serializer
- `include/protocol_carrot.h` / `src/legacy/protocol_carrot.c` — Carrot protocol parser/serializer

- `src/main.c` — Main program demonstrating the three protocols with configurable logging
- `include/logger.h` / `src/logger.c` — Logging system with configurable levels

- `tests/cunit.h` / `tests/cunit.c` — Simple C unit test framework
- `tests/test_*.c` — Baseline tests; you are expected to add many more

---

## Refactor Goals

- Make functions **total** (defined behavior for all inputs) or clearly document preconditions
- Replace deep `if/else` ladders with table-driven logic or helper functions
- Remove dead branches and duplicated conditions
- Use safer APIs (`snprintf`, length-checked loops)
- **Extract common code**: The three protocol modules (apple/banana/carrot) are nearly identical and should share a common implementation
- Break down large functions into smaller, testable helper functions
- Add NULL pointer checks where appropriate
- Keep interfaces stable unless you *intentionally* improve them

---

## Evaluation Criteria

- **Test quality** (40 points): Meaningful coverage, boundary thinking, good naming
- **Bug finding/triaging** (20 points): Prioritization & clear documentation
- **Refactoring clarity** (25 points): Smaller functions, fewer branches, comments where needed
- **Build hygiene** (10 points): Warnings enabled, clean diffs, reproducibility
- **Polish** (5 points): Code style, commit quality, attention to detail

---

## Time Estimate

- **Task A:** 2-3 hours
- **Task B:** 2-3 hours
- **Task C:** 3-4 hours
- **Task D:** 1-2 hours
- **Total:** 8-12 hours

Good luck — have fun cleaning up 🙂
