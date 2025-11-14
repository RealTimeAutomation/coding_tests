/**
 * @file string_utils.h
 * @brief String manipulation and utility functions
 * 
 * This module provides comprehensive string operations including splitting,
 * joining, parsing, formatting, and various string transformations.
 */

#ifndef LEGACY_STRING_UTILS_H
#define LEGACY_STRING_UTILS_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Splits a string into tokens by delimiter
 * 
 * @param str String to split (can be NULL)
 * @param delimiter Character to split on
 * @param count Pointer to store number of tokens (can be NULL)
 * @return Array of null-terminated strings, NULL-terminated, or NULL on error
 * 
 * @note Caller must free each token string AND the array itself
 * @note Empty string returns array with one NULL element (count = 1)
 * @note Sets *count to 0 and returns NULL if str or count is NULL
 * @note Time complexity: O(n) where n is string length
 * 
 * @example
 *   size_t count;
 *   char** tokens = string_split("a,b,c", ',', &count);
 *   // tokens[0] = "a", tokens[1] = "b", tokens[2] = "c", tokens[3] = NULL
 *   // count = 3
 *   // Free: for (size_t i = 0; i < count; i++) free(tokens[i]); free(tokens);
 */
char** string_split(const char* str, char delimiter, size_t* count);

/**
 * @brief Joins an array of strings with a delimiter
 * 
 * @param strings Array of string pointers (can be NULL)
 * @param count Number of strings in the array
 * @param delimiter Character to insert between strings
 * @return Newly allocated joined string, or NULL on error
 * 
 * @note Caller is responsible for freeing the returned string with free()
 * @note Returns empty string if count is 0
 * @note Returns NULL if strings is NULL or contains NULL elements
 * @note Time complexity: O(n) where n is total length of all strings
 * 
 * @example
 *   const char* arr[] = {"a", "b", "c"};
 *   char* joined = string_join(arr, 3, ',');
 *   // joined is "a,b,c"
 *   free(joined);
 */
char* string_join(const char* const* strings, size_t count, char delimiter);

/**
 * @brief Removes specified characters from a string in-place
 * 
 * @param str String to modify (can be NULL)
 * @param chars String containing characters to remove (can be NULL)
 * 
 * @note Modifies the string in-place
 * @note Safe to call with NULL pointers (no-op)
 * @note Time complexity: O(n*m) where n is str length, m is chars length
 * 
 * @example
 *   char str[] = "hello world";
 *   string_remove_chars(str, "lo");
 *   // str is now "he wrd"
 */
void string_remove_chars(char* str, const char* chars);

/**
 * @brief Checks if a string starts with a prefix
 * 
 * @param str String to check (can be NULL)
 * @param prefix Prefix to look for (can be NULL)
 * @return true if str starts with prefix, false otherwise
 * 
 * @note Returns true if prefix is empty string
 * @note Returns false if str or prefix is NULL
 * @note Uses strncmp() for efficient comparison
 * @note Time complexity: O(min(n, m)) where n is str length, m is prefix length
 * 
 * @example
 *   bool result = string_starts_with("hello world", "hello"); // true
 */
bool string_starts_with(const char* str, const char* prefix);

/**
 * @brief Checks if a string ends with a suffix
 * 
 * @param str String to check (can be NULL)
 * @param suffix Suffix to look for (can be NULL)
 * @return true if str ends with suffix, false otherwise
 * 
 * @note Returns true if suffix is empty string
 * @note Returns false if str or suffix is NULL, or if suffix is longer than str
 * @note Uses strncmp() for efficient comparison
 * @note Time complexity: O(min(n, m)) where n is str length, m is suffix length
 * 
 * @example
 *   bool result = string_ends_with("hello world", "world"); // true
 */
bool string_ends_with(const char* str, const char* suffix);

/**
 * @brief Parses an integer from a string
 * 
 * @param str String to parse (can be NULL)
 * @param out_value Pointer to store parsed integer (can be NULL)
 * @return true if parsing succeeded, false otherwise
 * 
 * @note Supports optional leading '+' or '-' sign
 * @note Returns false if str is NULL, empty, or contains non-digit characters
 * @note Returns false if value is out of INT_MIN..INT_MAX range
 * @note Uses strtol() with proper overflow checking
 * @note Time complexity: O(n) where n is string length
 * 
 * @example
 *   int value;
 *   if (string_parse_int("123", &value)) {
 *       // value is now 123
 *   }
 */
bool string_parse_int(const char* str, int* out_value);

/**
 * @brief Formats an integer to a string buffer
 * 
 * @param buffer Buffer to write to (can be NULL)
 * @param buffer_size Size of the buffer (must be > 0)
 * @param value Integer value to format
 * @return Number of characters written (excluding null terminator), or -1 on error
 * 
 * @note Returns -1 if buffer is NULL or buffer_size is 0
 * @note Returns -1 if buffer is too small (snprintf would truncate)
 * @note Uses snprintf() for safe formatting
 * @note Time complexity: O(log10(value))
 * 
 * @example
 *   char buf[32];
 *   int len = string_format_int(buf, sizeof(buf), 123);
 *   // buf is "123", len is 3
 */
int string_format_int(char* buffer, size_t buffer_size, int value);

/**
 * @brief Removes duplicate characters from a string in-place
 * 
 * Keeps only the first occurrence of each character.
 * 
 * @param str String to modify (can be NULL)
 * 
 * @note Modifies the string in-place
 * @note Preserves order of first occurrences
 * @note Safe to call with NULL pointer (no-op)
 * @note Time complexity: O(n²) where n is string length
 * 
 * @example
 *   char str[] = "hello";
 *   string_remove_duplicates(str);
 *   // str is now "helo"
 */
void string_remove_duplicates(char* str);

/**
 * @brief Counts occurrences of a substring in a string
 * 
 * @param str String to search in (can be NULL)
 * @param substring Substring to find (can be NULL)
 * @return Number of non-overlapping occurrences, or 0 if not found
 * 
 * @note Returns 0 if str or substring is NULL, or if substring is empty
 * @note Uses strstr() for efficient searching
 * @note Counts non-overlapping matches only
 * @note Time complexity: O(n*m) where n is str length, m is substring length
 * 
 * @example
 *   size_t count = string_count_substring("hello hello", "hello"); // 2
 */
size_t string_count_substring(const char* str, const char* substring);

#ifdef __cplusplus
}
#endif

#endif

