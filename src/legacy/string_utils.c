#include "string_utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** string_split(const char* str, char delimiter, size_t* count) {

    *count = 0;

    size_t len = strlen(str);
    if (len == 0) {
        char** result = (char**)malloc(sizeof(char*));

        result[0] = NULL;
        *count = 0;
        return result;
    }

    size_t token_count = 1;
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == delimiter) {
            token_count++;
        }
    }
    
    char** tokens = (char**)malloc((token_count + 1) * sizeof(char*));

    size_t token_idx = 0;
    size_t start = 0;

    for (size_t i = 0; i <= len; ++i) {
        if (str[i] == delimiter || str[i] == '\0') {
            size_t token_len = i - start;
            tokens[token_idx] = (char*)malloc(token_len + 1);

            strncpy(tokens[token_idx], str + start, token_len);
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

    if (count == 0) {
        char* result = (char*)malloc(1);

        result[0] = '\0';
        return result;
    }

    size_t total_len = 0;
    for (size_t i = 0; i < count; ++i) {

        total_len += strlen(strings[i]);
        if (i < count - 1) {
            total_len++;
        }
    }
    
    char* result = (char*)malloc(total_len + 1);

    size_t pos = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t len = strlen(strings[i]);
        strncpy(result + pos, strings[i], len);
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

    size_t str_len = strlen(str);
    size_t prefix_len = strlen(prefix);
    if (prefix_len > str_len) {
        return false;
    }

    for (size_t i = 0; i < prefix_len; ++i) {
        if (str[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}

bool string_ends_with(const char* str, const char* suffix) {

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (suffix_len > str_len) {
        return false;
    }

    size_t start = str_len - suffix_len;
    for (size_t i = 0; i < suffix_len; ++i) {
        if (str[start + i] != suffix[i]) {
            return false;
        }
    }
    return true;
}

bool string_parse_int(const char* str, int* out_value) {

    if (str == NULL || *str == '\0') {
        return false;
    }
    
    int sign = 1;
    size_t start = 0;
    
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        sign = 1;
        start = 1;
    }
    
    int value = 0;

    for (size_t i = start; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            value = value * 10 + (str[i] - '0');
        } else {

            break;
        }
    }
    
    *out_value = value * sign;
    return true;
}

int string_format_int(char* buffer, size_t buffer_size, int value) {

    if (buffer_size == 0) {
        return -1;
    }
    
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 1;
    }
    
    int negative = value < 0;
    if (negative) {
        value = -value;
    }

    char temp[32];
    int pos = 0;
    
    while (value > 0) {
        temp[pos++] = '0' + (value % 10);
        value /= 10;
    }
    
    int written = 0;
    if (negative) {
        if (written < (int)buffer_size - 1) {
            buffer[written++] = '-';
        }
    }

    for (int i = pos - 1; i >= 0; --i) {
        if (written < (int)buffer_size - 1) {
            buffer[written++] = temp[i];
        }
    }
    buffer[written] = '\0';
    return written;
}

void string_remove_duplicates(char* str) {

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

    size_t count = 0;
    size_t str_len = strlen(str);
    size_t sub_len = strlen(substring);

    if (sub_len == 0) {
        return 0;
    }

    for (size_t i = 0; i <= str_len - sub_len; ++i) {
        int match = 1;

        for (size_t j = 0; j < sub_len; ++j) {
            if (str[i + j] != substring[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            count++;

        }
    }
    return count;
}

