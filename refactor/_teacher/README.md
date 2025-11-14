# Teacher-Only Resources

**⚠️ IMPORTANT: DELETE THIS DIRECTORY BEFORE DISTRIBUTING TO STUDENTS**

This directory contains:
- Comprehensive final tests that are designed to catch bugs (will fail initially)
- Answer keys and evaluation documentation
- Teacher-only notes and checklists

Students should NOT have access to any content in this directory.

## Purpose

The final tests in this directory:
- Test NULL pointer handling
- Test edge cases and boundary conditions
- Test error handling
- Test invalid inputs
- Will reveal bugs that need to be fixed

## Usage

From the `refactor/_teacher/` directory:

### Test and Compare Both Solutions (Recommended)

```bash
cd refactor/_teacher
make test
# or simply
make
```

This will:
1. Test answer key solution with all tests (64 initial + 96 final)
2. Test student solution with all tests (64 initial + 96 final)
3. Generate comparison report: `comparison_report.md`

**Expected:**
- Answer Key: 64/64 initial + 96/96 final = 160/160 ✅
- Student: 64/64 initial + many final failures ❌

### Test Student Only

```bash
cd refactor/_teacher
make final
```

This will:
1. Build the project (uses code from `../_student/`)
2. Run the initial test suite (should pass)
3. Run the final test suite (will show failures)
4. Generate markdown reports in `../_student/build/`

## Before Distributing to Students

1. **Delete this `refactor/_teacher/` directory entirely**
2. Verify that `make final` is not available in the student Makefile
3. Students should only have access to `make test` which runs the initial tests

## Test Results

### Comparison Report (make test)
- `comparison_report.md` - Side-by-side comparison of student vs answer key

### Student Test Results (make final)
- `../_student/build/test_results.md` - Initial test results (should all pass)
- `../_student/build/test_results_final.md` - Final test results (will show failures)

## Analysis Tools

The teacher Makefile also supports analysis tools for both solutions:

```bash
cd refactor/_teacher

# Memory leak detection
make valgrind          # Both solutions
make valgrind-student  # Student only
make valgrind-answer-key # Answer key only

# Static analysis
make cppcheck          # Both solutions
make cppcheck-student  # Student only
make cppcheck-answer-key # Answer key only

# Runtime memory error detection
make sanitize          # Both solutions
make sanitize-student  # Student only
make sanitize-answer-key # Answer key only

# Code coverage
make coverage          # Both solutions
make coverage-student  # Student only
make coverage-answer-key # Answer key only
```

See `COMMANDS.md` for complete command reference.

The final tests are designed to help you evaluate:
- How well students found and fixed bugs
- Test coverage and quality
- Code quality improvements

## Documentation Files

This directory also contains:
- **`ANSWER_KEY.md`** - Complete list of all intentional bugs in the codebase
- **`FOR_TEACHERS_ONLY.md`** - Evaluation guidelines and project structure notes
- **`MaintainerNotes.md`** - Quick reference for known issues and evaluation rubric

These files should never be shared with students.

