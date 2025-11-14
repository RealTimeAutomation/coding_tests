# Quick Start Guide

## Structure Summary

- **`refactor/_student/`**: Buggy code + initial tests (64 tests that pass)
- **`refactor/_teacher/`**: Final tests + can test student code
- **`refactor/_teacher/answer_key/`**: Optimized code + ALL tests + can test student code

## Quick Commands

### Student Builds and Tests
```bash
cd refactor/_student
make test
# Should show: 64/64 passed ✅
```

### Teacher Tests Student Code (Full Test Suites)
```bash
# Option 1: From _teacher directory
cd refactor/_teacher
make final

# Option 2: From answer key (recommended)
cd refactor/_teacher/answer_key
make test-student
# Runs both initial (64) + final (96) tests against student code
```

### Teacher Tests Answer Key (Reference Implementation)
```bash
cd refactor/_teacher/answer_key
make test-all
# Should show: 64/64 initial + 96/96 final = all pass ✅
```

## Directory Paths

From `refactor/_teacher/answer_key/`:
- Student code: `../../_student/`
- Answer key code: `./src/`
- Answer key tests: `./tests/`

## What Each Directory Does

| Directory | Code | Tests | Purpose |
|-----------|------|-------|---------|
| `_student/` | Buggy | Initial only | Student workspace |
| `_teacher/` | Uses student | Final only | Teacher evaluation |
| `_teacher/answer_key/` | Optimized | All (initial + final) | Reference + testing tool |
