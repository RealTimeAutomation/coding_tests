# Testing Student Submissions

This guide explains how to test student code from `../../_student/` using the answer key's full test suites.

## Directory Structure

```
refactor/
├── _student/              # Student code (buggy, with initial tests)
│   ├── src/
│   │   ├── legacy/
│   │   │   └── *.c
│   │   ├── logger.c
│   │   └── main.c
│   ├── tests/            # Initial tests only (pass with bad code)
│   └── CMakeLists.txt
└── _teacher/
    └── answer_key/        # Optimized code + all tests
        ├── src/          # Fixed code
        ├── tests/        # All tests (initial + final)
        └── Makefile      # Can test student code
```

## Quick Start

### 1. Test the Answer Key

```bash
cd refactor/_teacher/answer_key
make test-all
```

Should show: 64/64 initial + 96/96 final = all pass ✅

### 2. Test Student Code

```bash
# Switch to student branch (if using git)
cd ../../_student
git checkout student_name

# Test from answer key
cd ../_teacher/answer_key
make test-student
```

This runs:
- **Initial tests** (64) - basic functionality
- **Final tests** (96) - comprehensive bug-catching tests

## What Gets Tested

### Initial Tests (64 tests)
- Basic functionality
- Intentionally skips edge cases that reveal bugs
- Should pass for both answer key and student code

### Final Tests (96 tests)
- NULL pointer checks
- Buffer overflow tests
- Division by zero tests
- Invalid input handling
- Edge cases
- Should pass for answer key, may fail for student code

## Expected Results

### Answer Key
- Initial: 64/64 ✅
- Final: 96/96 ✅

### Student Code
- Initial: 64/64 ✅ (if basic functionality intact)
- Final: Varies (shows bugs that need fixing)

## Git Branch Workflow

If using git branches in `_student/`:

```bash
# List student branches
cd _student
git branch

# Switch to student
git checkout student_john_doe

# Test
cd ../_teacher/answer_key
make test-student
```

The Makefile automatically shows the current branch.

## Test Results

Results are saved to:
- `build/student_test/student_test_results.md`
- `build/student_test/student_test_results_final.md`

Review these to see:
- Which tests passed/failed
- Specific error messages
- Crash reports (if any)
