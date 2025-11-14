/**
 * @file text.h
 * @brief Text manipulation and transformation functions
 * 
 * This module provides functions for normalizing whitespace, converting
 * text case, and performing string replacements.
 */

#ifndef LEGACY_TEXT_H
#define LEGACY_TEXT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Normalizes whitespace in a string in-place
 * 
 * Collapses sequences of whitespace characters (space, tab, newline, etc.)
 * into single spaces, and trims leading/trailing whitespace.
 * 
 * @param s String to normalize (can be NULL)
 * @return New length of the string after normalization, or 0 if s is NULL
 * 
 * @note Modifies the string in-place
 * @note Uses isspace() to detect all whitespace types
 * @note Time complexity: O(n)
 * @note Safe to call with NULL pointer (returns 0)
 * 
 * @example
 *   char str[] = "  hello\t\tworld\n\n";
 *   size_t len = text_normalize_whitespace(str);
 *   // str is now "hello world" and len is 11
 */
size_t text_normalize_whitespace(char* s);

/**
 * @brief Creates an uppercased copy of a string
 * 
 * @param s Source string to convert (can be NULL)
 * @return Newly allocated uppercased string, or NULL if s is NULL or allocation fails
 * 
 * @note Caller is responsible for freeing the returned string with free()
 * @note Uses toupper() for case conversion
 * @note Non-ASCII bytes are passed through toupper() but may remain unchanged
 * @note Time complexity: O(n)
 * 
 * @example
 *   char* upper = text_to_upper("Hello World");
 *   // upper is "HELLO WORLD"
 *   free(upper);
 */
char* text_to_upper(const char* s);

/**
 * @brief Replaces all occurrences of a substring in a string
 * 
 * @param s Source string (can be NULL)
 * @param from Substring to find (can be NULL or empty)
 * @param to Replacement string (can be NULL)
 * @return Newly allocated string with replacements, or NULL on error
 * 
 * @note Caller is responsible for freeing the returned string with free()
 * @note If from is NULL or empty, returns a copy of s
 * @note Returns NULL if s is NULL, or if memory allocation fails
 * @note Has a safety limit of 1000 iterations to prevent infinite loops
 * @note Time complexity: O(n*m) where n is string length, m is number of replacements
 * 
 * @example
 *   char* result = text_replace_all("hello world", "world", "universe");
 *   // result is "hello universe"
 *   free(result);
 */
char* text_replace_all(const char* s, const char* from, const char* to);

#ifdef __cplusplus
}
#endif

#endif

