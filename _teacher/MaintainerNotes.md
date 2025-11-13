# Maintainer Notes (not for candidate)

**For detailed bug list, see `ANSWER_KEY.md` in this directory - it contains a comprehensive list of all intentional bugs.**

## Known issues (non-exhaustive - see ANSWER_KEY.md for complete list)

- **metrics.c**
  - `metrics_sum`: off-by-one `i <= n` loop; useless branch; potential UB read at `arr[n]`.
  - `metrics_average`: division by zero on `n==0`.
  - `metrics_argmax`: odd tie-breaker branch; unnecessary equality check branch.
  - `metrics_median`: sorts input (side-effect); odd branch returns average for odd `n`.

- **text.c**
  - `is_ws`: duplicated `\t` branch; treats `\r` as non-whitespace.
  - `text_normalize_whitespace`: starts `in_ws=1` causing drop of initial non-space; trailing trim ok.
  - `text_replace_all`: leak when no more replacements; skips overlaps; arbitrary loop cap.

- **config.c**
  - `parse_bool`: returns 0 on `TRUE/FALSE` parsing despite setting output.
  - keys: inconsistent case handling; unknown keys silently ignored.
  - `strncpy` may leave `host` unterminated.
  - `atoi` without validation; port range unchecked.
  - Long lines truncated silently; no error handling.

## Rubric (100 pts)

- Tests breadth & depth (40)
- Defect discovery & classification (20)
- Refactoring / complexity reduction (25)
- Build quality & docs (10)
- Polish (5)

## Stretch ideas

- Add `-Wall -Wextra -Werror` with CI.
- Fuzz `config_parse_file` with random inputs.
- Replace bubble sort with `qsort` and stable argmax.
- Memory-leak checks (valgrind/asan).
