l# Command Reference

Quick reference for all build and test commands.

## Student Commands

**Location:** `refactor/_student/`

### Build and Test
```bash
cd refactor/_student
make test
```

This will:
- Build the student's code
- Run initial tests (64 tests)
- Generate `build/test_results.md`

**Expected:** 64/64 tests should pass ✅ (tests intentionally skip bug-revealing scenarios)

### Alternative (CMake directly)
```bash
cd refactor/_student
mkdir -p build && cd build
cmake ..
cmake --build . -j
./run_tests test_results.md
```

### Run Main Program
```bash
cd refactor/_student/build
./main

# With logging
LOG_LEVEL=DEBUG ./main
LOG_LEVEL=INFO ./main
```

---

## Teacher Commands - Test Student Code

### Option 1: From `_teacher/` Directory (Recommended)

**Location:** `refactor/_teacher/`

```bash
cd refactor/_teacher
make test
# or simply
make
```

This will:
- Test answer key solution with all tests (64 initial + 96 final)
- Test student solution with all tests (64 initial + 96 final)
- Generate comparison report: `comparison_report.md`

**Expected:**
- Answer Key: 64/64 initial + 96/96 final = 160/160 ✅
- Student: 64/64 initial + many final failures ❌
- Report shows side-by-side comparison

### Option 2: Legacy - Just Test Student

**Location:** `refactor/_teacher/`

```bash
cd refactor/_teacher
make final
```

This will:
- Build using student code from `../_student/`
- Run initial tests (64 tests)
- Run final tests (96 tests)
- Generate reports in `../_student/build/`

**Expected:**
- Initial: 64/64 passed ✅
- Final: Many failures ❌ (shows bugs)

### Option 2: From Answer Key (Recommended)

**Location:** `refactor/_teacher/answer_key/`

```bash
# Switch to student branch (if using git)
cd refactor/_student
git checkout student_name

# Test from answer key
cd ../_teacher/answer_key
make test-student
```

This will:
- Build student code from `../../_student/`
- Run answer key's initial tests (64 tests)
- Run answer key's final tests (96 tests)
- Generate reports in `build/student_test/`

**Expected:**
- Initial: 64/64 passed ✅
- Final: Varies based on bugs fixed

**Results:**
- `build/student_test/student_test_results.md`
- `build/student_test/student_test_results_final.md`

---

## Teacher Commands - Test Answer Key (Reference)

**Location:** `refactor/_teacher/answer_key/`

### Test All (Initial + Final)
```bash
cd refactor/_teacher/answer_key
make test-all
```

This will:
- Build optimized code
- Run initial tests (64 tests)
- Run final tests (96 tests)

**Expected:** 64/64 initial + 96/96 final = all 160 tests pass ✅

### Test Individual Suites
```bash
cd refactor/_teacher/answer_key

# Initial tests only
make test

# Final tests only
make test-final
```

---

## Summary Table

| Who | Command | Location | Tests | Expected Result |
|-----|---------|----------|-------|-----------------|
| **Student** | `make test` | `refactor/_student/` | 64 initial | All pass ✅ |
| **Teacher** | `make test` or `make` | `refactor/_teacher/` | 64 + 96 (both solutions) | Comparison report |
| **Teacher** | `make final` | `refactor/_teacher/` | 64 + 96 | Initial pass, final fail |
| **Teacher** | `make test-student` | `refactor/_teacher/answer_key/` | 64 + 96 | Initial pass, final varies |
| **Teacher** | `make test-all` | `refactor/_teacher/answer_key/` | 64 + 96 | All pass ✅ |

---

## Quick Reference

```bash
# Student
cd refactor/_student && make test

# Teacher - compare both solutions (recommended)
cd refactor/_teacher && make test

# Teacher - test student only
cd refactor/_teacher && make final

# Teacher - test answer key only
cd refactor/_teacher/answer_key && make test-all
```

