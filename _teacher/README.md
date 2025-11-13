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

From the project root directory:

```bash
cd _teacher
make final
```

This will:
1. Build the project
2. Run the initial test suite (should pass)
3. Run the final test suite (will show failures)
4. Generate markdown reports in `build/`

## Before Distributing to Students

1. **Delete this `_teacher/` directory entirely**
2. Verify that `make final` is not available in the main Makefile
3. Students should only have access to `make test` which runs the initial tests

## Test Results

Results are saved to:
- `build/test_results.md` - Initial test results (should all pass)
- `build/test_results_final.md` - Final test results (will show failures)

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

