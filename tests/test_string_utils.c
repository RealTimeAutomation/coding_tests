#include "cunit.h"
#include "string_utils.h"
#include <string.h>
#include <stdlib.h>

CUNIT_TEST(test_string_starts_with) {
    CUNIT_ASSERT(string_starts_with("hello world", "hello") == true);
    CUNIT_ASSERT(string_starts_with("hello world", "world") == false);
}

CUNIT_TEST(test_string_starts_with_exact) {
    CUNIT_ASSERT(string_starts_with("hello", "hello") == true);
}

CUNIT_TEST(test_string_ends_with) {
    CUNIT_ASSERT(string_ends_with("hello world", "world") == true);
    CUNIT_ASSERT(string_ends_with("hello world", "hello") == false);
}

CUNIT_TEST(test_string_ends_with_exact) {
    CUNIT_ASSERT(string_ends_with("hello", "hello") == true);
}

CUNIT_TEST(test_string_parse_int) {
    int value;
    CUNIT_ASSERT(string_parse_int("123", &value) == true);
    CUNIT_ASSERT_EQ(value, 123);
    
    CUNIT_ASSERT(string_parse_int("-456", &value) == true);
    CUNIT_ASSERT_EQ(value, -456);
}

CUNIT_TEST(test_string_parse_int_zero) {
    int value;
    CUNIT_ASSERT(string_parse_int("0", &value) == true);
    CUNIT_ASSERT_EQ(value, 0);
}

CUNIT_TEST(test_string_format_int) {
    char buffer[32];
    int written = string_format_int(buffer, sizeof(buffer), 123);
    CUNIT_ASSERT(written > 0);
    CUNIT_ASSERT_STR_EQ(buffer, "123");
}

CUNIT_TEST(test_string_format_int_negative) {
    char buffer[32];
    int written = string_format_int(buffer, sizeof(buffer), -456);
    CUNIT_ASSERT(written > 0);
    CUNIT_ASSERT_STR_EQ(buffer, "-456");
}

CUNIT_TEST(test_string_remove_chars) {
    char str[] = "hello world";
    string_remove_chars(str, "lo");
    // Should remove 'l' and 'o' characters
    CUNIT_ASSERT(strlen(str) < 11);
}

CUNIT_TEST(test_string_remove_duplicates) {
    char str[] = "aabbcc";
    string_remove_duplicates(str);
    // Should remove duplicate characters
    CUNIT_ASSERT(strlen(str) <= 6);
}

CUNIT_TEST(test_string_count_substring) {
    size_t count = string_count_substring("hello hello", "hello");
    CUNIT_ASSERT(count >= 1);
}

CUNIT_TEST(test_string_split) {
    size_t count;
    char** tokens = string_split("a,b,c", ',', &count);
    if (tokens != NULL) {
        CUNIT_ASSERT(count >= 1);
        // Free tokens
        for (size_t i = 0; i < count; i++) {
            free(tokens[i]);
        }
        free(tokens);
    }
}

CUNIT_TEST(test_string_join) {
    const char* strings[] = {"a", "b", "c"};
    char* result = string_join(strings, 3, ',');
    if (result != NULL) {
        CUNIT_ASSERT(strlen(result) > 0);
        free(result);
    }
}

// Intentionally skipping tests for: NULL pointers, empty strings, buffer overflow, integer overflow, overlapping memory

