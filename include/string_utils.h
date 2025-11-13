#ifndef LEGACY_STRING_UTILS_H
#define LEGACY_STRING_UTILS_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Split string by delimiter, return array of strings (caller must free each and array)
// Returns NULL on error. Sets *count to number of tokens.
char** string_split(const char* str, char delimiter, size_t* count);

// Join array of strings with delimiter. Returns newly allocated string.
char* string_join(const char* const* strings, size_t count, char delimiter);

// Remove all occurrences of characters in 'chars' from string (in-place)
void string_remove_chars(char* str, const char* chars);

// Check if string starts with prefix
bool string_starts_with(const char* str, const char* prefix);

// Check if string ends with suffix
bool string_ends_with(const char* str, const char* suffix);

// Parse integer from string, returns true on success
bool string_parse_int(const char* str, int* out_value);

// Format integer to string buffer (returns number of chars written, or -1 on error)
int string_format_int(char* buffer, size_t buffer_size, int value);

// Remove duplicate characters from string (in-place, keeps first occurrence)
void string_remove_duplicates(char* str);

// Count occurrences of substring in string
size_t string_count_substring(const char* str, const char* substring);

#ifdef __cplusplus
}
#endif

#endif

