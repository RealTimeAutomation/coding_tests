# Project Structure

## Directory Layout

```
refactor/
├── _student/                    # Student workspace
│   ├── src/
│   │   ├── legacy/             # Buggy code (original)
│   │   ├── logger.c
│   │   └── main.c
│   ├── tests/                  # Initial tests only (pass with bad code)
│   ├── include/                # Headers
│   ├── CMakeLists.txt          # Builds student code + initial tests
│   └── Makefile                # make test (runs initial tests only)
│
└── _teacher/                    # Teacher resources
    ├── tests/                   # Final tests (catch bugs)
    ├── CMakeLists.txt           # Builds final tests (uses student code)
    ├── Makefile                 # make final (runs both test suites)
    │
    └── answer_key/              # Reference implementation
        ├── src/
        │   ├── legacy/         # OPTIMIZED code (all bugs fixed)
        │   └── ...
        ├── tests/              # ALL tests (initial + final)
        ├── include/            # Headers
        ├── CMakeLists.txt      # Builds optimized code + all tests
        ├── Makefile            # Can test answer key OR student code
        └── student_test_config.cmake  # Config to test student code
```

## Key Points

1. **Everything is under `refactor/`** - No folders in root
2. **`_student/`** - Student workspace with buggy code + initial tests
3. **`_teacher/`** - Teacher resources with final tests
4. **`_teacher/answer_key/`** - Reference implementation + testing tool

## Testing Workflows

### Student Tests Their Code
```bash
cd refactor/_student
make test
# Uses: Student's buggy code + initial tests
# Expected: 64/64 passed ✅
```

### Teacher Tests Student Code (Full Suites)
```bash
# Option 1: From _teacher directory
cd refactor/_teacher
make final
# Uses: Student code + both test suites

# Option 2: From answer_key (recommended)
cd refactor/_teacher/answer_key
make test-student
# Uses: Student code from ../../_student/ + answer key's full test suites
```

### Teacher Tests Answer Key
```bash
cd refactor/_teacher/answer_key
make test-all
# Uses: Answer key's optimized code + all tests
# Expected: 64/64 initial + 96/96 final = all pass ✅
```

## Test Suites

| Location | Tests | Purpose |
|----------|-------|---------|
| `_student/tests/` | 64 initial | Pass with bad code |
| `_teacher/tests/` | 96 final | Catch bugs |
| `_teacher/answer_key/tests/` | 160 total (64+96) | Complete coverage |

