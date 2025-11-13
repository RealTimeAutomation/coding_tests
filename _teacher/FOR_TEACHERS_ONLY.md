# For Teachers/Evaluators Only

This file should **NOT** be shared with students/candidates.

## Answer Key Location

The complete answer key with all bugs documented is in **`ANSWER_KEY.md`** (in this same `_teacher/` directory).

## Project Structure

**Teacher-only files (in `_teacher/` directory):**
- **`ANSWER_KEY.md`** - Complete list of all intentional bugs (104+ bugs documented)
- **`MaintainerNotes.md`** - Brief summary and evaluation rubric
- **`FOR_TEACHERS_ONLY.md`** - This file
- **`tests/`** - Final comprehensive tests (will fail initially)

**Student-facing files (in root directory):**
- **`src/legacy/`** - The buggy code
- **`tests/`** - Basic tests (students should add more)
- **`README.md`** - Student-facing instructions
- **`CHECKLIST.md`** - Progress tracking checklist for students
- **`BUGS_FOUND_TEMPLATE.md`** - Template for students to document bugs

## Quick Start for Evaluation

1. **Delete the `_teacher/` directory** before distributing to students
2. Give students access to the repo (they should NOT see the `_teacher/` directory)
3. Students work through **4 tasks** with check-ins:
   - **Task A (2-3 hours):** Write tests and document bugs → Check-in #1
   - **Task B (2-3 hours):** Fix critical bugs → Check-in #2
   - **Task C (3-4 hours):** Refactor code → Check-in #3
   - **Task D (1-2 hours):** Documentation and final review → Final submission
4. Use `_teacher/ANSWER_KEY.md` to evaluate each check-in:
   - **Check-in #1:** Did they find the bugs? Did they write good tests?
   - **Check-in #2:** Did they fix bugs correctly? Are regression tests good?
   - **Check-in #3:** Did they refactor well? Is code quality improved?
   - **Final:** Is documentation clear? Is everything complete?

## Evaluation by Task

### Task A Check-in (2-3 hours expected)
Evaluate using `_teacher/ANSWER_KEY.md`:
- [ ] Found high-severity bugs (crashes, data loss) - should find ~35
- [ ] Found medium-severity bugs (incorrect behavior) - should find ~25
- [ ] Found code quality issues (copy-paste, large functions) - should find ~44
- [ ] Wrote comprehensive tests (edge cases, NULL, overflow)
- [ ] `BUGS_FOUND.md` is well-documented
- [ ] Tests document current behavior (even if buggy)

### Task B Check-in (2-3 hours expected)
- [ ] Fixed high-severity bugs correctly
- [ ] Added regression tests for each fix
- [ ] All existing tests still pass
- [ ] Updated `BUGS_FOUND.md` with fix status
- [ ] Commits are clear and atomic

### Task C Check-in (3-4 hours expected)
- [ ] Extracted common code (especially the three protocols) - **CRITICAL**
- [ ] Broke down large functions (>50 lines)
- [ ] Simplified complex conditionals
- [ ] Added NULL pointer checks where appropriate
- [ ] Removed dead code
- [ ] All tests pass after refactoring
- [ ] Code quality significantly improved

### Final Submission (1-2 hours expected)
- [ ] `DESIGN_NOTES.md` is comprehensive
- [ ] All tests pass
- [ ] Code builds cleanly
- [ ] Documentation is clear
- [ ] Time log provided (optional but helpful)

## Key Things to Look For

1. **The three protocol modules** (apple, banana, carrot) are copy-paste duplicates - this is the biggest refactoring opportunity
2. **NULL pointer checks** - missing throughout (25+ instances)
3. **Memory leaks** - at least one in `text_replace_all`
4. **Buffer overflows** - several potential issues
5. **Division by zero** - in `metrics_average`
6. **Off-by-one errors** - in `metrics_sum`

## Hiding the Answer Key

Before sharing with students, ensure:
- **Delete the `_teacher/` directory entirely** - this contains all teacher-only files
- The `_teacher/` directory should never be committed to a student-accessible repository
- Consider using a `.gitignore` entry for `_teacher/` if using version control

