#include "string_utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>

char** string_split(const char* str, char delimiter, size_t* count) {
    if (str == NULL || count == NULL) {
        if (count) *count = 0;
        return NULL;
    }

    *count = 0;

    size_t len = strlen(str);
    if (len == 0) {
        char** result = (char**)malloc(sizeof(char*));
        if (!result) {
            *count = 0;
            return NULL;
        }
        result[0] = NULL;
        *count = 1;
        return result;
    }

    size_t token_count = 1;
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == delimiter) {
            token_count++;
        }
    }
    
    char** tokens = (char**)malloc((token_count + 1) * sizeof(char*));
    if (!tokens) {
        *count = 0;
        return NULL;
    }

    size_t token_idx = 0;
    size_t start = 0;

    for (size_t i = 0; i <= len; ++i) {
        if (str[i] == delimiter || str[i] == '\0') {
            size_t token_len = i - start;
            tokens[token_idx] = (char*)malloc(token_len + 1);
            if (!tokens[token_idx]) {
                // Free already allocated tokens
                for (size_t j = 0; j < token_idx; ++j) {
                    free(tokens[j]);
                }
                free(tokens);
                *count = 0;
                return NULL;
            }
            memcpy(tokens[token_idx], str + start, token_len);
            tokens[token_idx][token_len] = '\0';
            token_idx++;
            start = i + 1;
        }
    }
    
    tokens[token_count] = NULL;
    *count = token_count;
    return tokens;
}

char* string_join(const char* const* strings, size_t count, char delimiter) {
    if (strings == NULL) {
        return NULL;
    }
    
    if (count == 0) {
        char* result = (char*)malloc(1);
        if (!result) return NULL;
        result[0] = '\0';
        return result;
    }

    size_t total_len = 0;
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return NULL;
        }
        total_len += strlen(strings[i]);
        if (i < count - 1) {
            total_len++;
        }
    }
    
    char* result = (char*)malloc(total_len + 1);
    if (!result) return NULL;

    size_t pos = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t len = strlen(strings[i]);
        memcpy(result + pos, strings[i], len);
        pos += len;
        if (i < count - 1) {
            result[pos] = delimiter;
            pos++;
        }
    }
    result[pos] = '\0';
    return result;
}

void string_remove_chars(char* str, const char* chars) {
    if (str == NULL || chars == NULL) {
        return;
    }
    
    size_t str_len = strlen(str);
    size_t chars_len = strlen(chars);
    
    size_t write_pos = 0;
    for (size_t i = 0; i < str_len; ++i) {
        int should_remove = 0;

        for (size_t j = 0; j < chars_len; ++j) {
            if (str[i] == chars[j]) {
                should_remove = 1;
                break;
            }
        }
        if (!should_remove) {
            str[write_pos] = str[i];
            write_pos++;
        }
    }
    str[write_pos] = '\0';
}

bool string_starts_with(const char* str, const char* prefix) {
    if (str == NULL || prefix == NULL) {
        return false;
    }
    
    size_t prefix_len = strlen(prefix);
    if (prefix_len == 0) {
        return true; // Empty prefix matches any string
    }
    
    // Use strncmp for efficient comparison
    return strncmp(str, prefix, prefix_len) == 0;
}

bool string_ends_with(const char* str, const char* suffix) {
    if (str == NULL || suffix == NULL) {
        return false;
    }
    
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (suffix_len > str_len) {
        return false;
    }
    if (suffix_len == 0) {
        return true; // Empty suffix matches any string
    }

    // Use strncmp for efficient comparison
    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

bool string_parse_int(const char* str, int* out_value) {
    if (str == NULL || out_value == NULL || *str == '\0') {
        return false;
    }
    
    // Check if entire string is valid
    size_t len = strlen(str);
    size_t start = 0;
    int sign = 1;
    
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        sign = 1;
        start = 1;
    }
    
    // Must have at least one digit
    if (start >= len) {
        return false;
    }
    
    // Check all remaining characters are digits
    for (size_t i = start; i < len; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    
    // Use strtol for proper overflow checking
    char* endptr;
    errno = 0;
    long value = strtol(str, &endptr, 10);
    
    // Check for conversion errors
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        return false;
    }
    
    // Check that entire string was consumed
    if (*endptr != '\0') {
        return false;
    }
    
    *out_value = (int)value;
    return true;
}

int string_format_int(char* buffer, size_t buffer_size, int value) {
    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }
    
    // Use snprintf for safe conversion
    int written = snprintf(buffer, buffer_size, "%d", value);
    
    if (written < 0 || (size_t)written >= buffer_size) {
        return -1;
    }
    
    return written;
}

void string_remove_duplicates(char* str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strlen(str);
    size_t write_pos = 0;
    
    for (size_t i = 0; i < len; ++i) {
        int is_duplicate = 0;

        for (size_t j = 0; j < write_pos; ++j) {
            if (str[j] == str[i]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            str[write_pos] = str[i];
            write_pos++;
        }
    }
    str[write_pos] = '\0';
}

size_t string_count_substring(const char* str, const char* substring) {
    if (str == NULL || substring == NULL) {
        return 0;
    }
    
    size_t count = 0;
    size_t str_len = strlen(str);
    size_t sub_len = strlen(substring);

    if (sub_len == 0) {
        return 0; // Empty substring - return 0 (could be infinite, but 0 is safer)
    }

    // Use strstr for efficient searching
    const char* pos = str;
    while ((pos = strstr(pos, substring)) != NULL) {
        count++;
        pos += sub_len; // Skip past the match to avoid overlapping
    }
    
    return count;
}

