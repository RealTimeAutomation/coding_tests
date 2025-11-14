#ifndef LEGACY_TEXT_H
#define LEGACY_TEXT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// In-place: collapse sequences of space/tab/newline into single space.
// Trims leading/trailing whitespace. Returns new length.
size_t text_normalize_whitespace(char* s);

// Returns newly allocated uppercased copy (caller must free).
// Non-ASCII bytes are left unchanged.
char* text_to_upper(const char* s);

// Replace all occurrences of `from` with `to` in newly allocated string.
// Returns NULL on allocation failure. Caller must free the result.
char* text_replace_all(const char* s, const char* from, const char* to);

#ifdef __cplusplus
}
#endif

#endif

