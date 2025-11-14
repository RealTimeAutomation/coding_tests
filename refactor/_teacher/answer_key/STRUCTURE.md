# Project Structure Overview

## Directory Layout

```
refactor/
├── _student/                    # Student workspace
│   ├── src/
│   │   ├── legacy/             # Buggy code (original)
│   │   │   ├── metrics.c
│   │   │   ├── text.c
│   │   │   └── ...
│   │   ├── logger.c
│   │   └── main.c
│   ├── tests/                  # Initial tests only (pass with bad code)
│   │   ├── cunit.c
│   │   ├── test_*.c
│   │   └── (NO test_*_final.c)
│   ├── include/                # Headers
│   ├── CMakeLists.txt          # Builds student code + initial tests
│   └── Makefile                # make test (runs initial tests only)
│
└── _teacher/                    # Teacher resources
    ├── tests/                   # Final tests (catch bugs)
    │   └── test_*_final.c
    ├── CMakeLists.txt           # Builds final tests
    ├── Makefile                 # make final (runs both test suites)
    │
    └── answer_key/              # Reference implementation
        ├── src/
        │   ├── legacy/         # OPTIMIZED code (all bugs fixed)
        │   └── ...
        ├── tests/              # ALL tests (initial + final)
        │   ├── test_*.c       # Initial tests
        │   └── test_*_final.c # Final tests
        ├── include/            # Headers
        ├── CMakeLists.txt      # Builds optimized code + all tests
        ├── Makefile            # Can test answer key OR student code
        └── student_test_config.cmake  # Config to test student code
```

## Key Differences

### `_student/` Directory
- **Purpose**: Student workspace
- **Code**: Original buggy code
- **Tests**: Initial tests only (64 tests) - intentionally skip bug-revealing tests
- **Result**: All tests pass even with bugs

### `_teacher/` Directory
- **Purpose**: Teacher resources
- **Code**: Uses student code (from parent `_student/`)
- **Tests**: Final tests only (96 tests) - catch bugs
- **Result**: Tests fail with buggy code, pass with fixed code

### `_teacher/answer_key/` Directory
- **Purpose**: Reference implementation + testing tool
- **Code**: Optimized/fixed code (all bugs fixed)
- **Tests**: ALL tests (64 initial + 96 final = 160 total)
- **Result**: All tests pass
- **Special Feature**: Can test student code from `../../_student/` with full test suites

## Testing Workflows

### Student Tests Their Code
```bash
cd refactor/_student
make test
# Runs initial tests only (64 tests) - should all pass
```

### Teacher Tests Student Code (Full Suites)
```bash
# Option 1: From _teacher directory
cd refactor/_teacher
make final
# Runs both initial + final tests against student code

# Option 2: From answer_key (recommended)
cd refactor/_teacher/answer_key
make test-student
# Uses answer key's full test suites to test student code
```

### Teacher Tests Answer Key
```bash
cd refactor/_teacher/answer_key
make test-all
# Tests the optimized code - all 160 tests should pass
```

## Path Relationships

From `refactor/_teacher/answer_key/`:
- Student code: `../../_student/`
- Answer key tests: `./tests/`
- Answer key code: `./src/`

## Test Suites

### Initial Tests (64 tests)
- Location: `_student/tests/` and `_teacher/answer_key/tests/`
- Purpose: Basic functionality, intentionally skip edge cases
- Result with buggy code: ✅ All pass
- Result with fixed code: ✅ All pass

### Final Tests (96 tests)
- Location: `_teacher/tests/` and `_teacher/answer_key/tests/`
- Purpose: Catch bugs (NULL pointers, edge cases, etc.)
- Result with buggy code: ❌ Many fail
- Result with fixed code: ✅ All pass

### Combined (160 tests)
- Location: `_teacher/answer_key/tests/` only
- Purpose: Complete test coverage
- Result with buggy code: ❌ Many fail
- Result with fixed code: ✅ All pass

