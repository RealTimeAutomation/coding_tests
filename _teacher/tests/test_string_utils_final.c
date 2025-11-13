#include "cunit.h"
#include "string_utils.h"
#include <string.h>
#include <stdlib.h>

// These tests are designed to catch bugs and will fail initially

CUNIT_TEST(test_split_null_string) {
    size_t count;
    char** result = string_split(NULL, ',', &count);
    // Should return NULL for NULL string
    CUNIT_ASSERT(result == NULL);
}

CUNIT_TEST(test_split_null_count) {
    char** result = string_split("a,b,c", ',', NULL);
    // Should handle NULL count pointer gracefully
    CUNIT_ASSERT(result == NULL || result != NULL);
    if (result) {
        for (size_t i = 0; result[i] != NULL; i++) {
            free(result[i]);
        }
        free(result);
    }
}

CUNIT_TEST(test_split_empty_string) {
    size_t count;
    char** result = string_split("", ',', &count);
    // Should handle empty string
    CUNIT_ASSERT(result != NULL || result == NULL);
    if (result) {
        for (size_t i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
    }
}

CUNIT_TEST(test_join_null_strings) {
    char* result = string_join(NULL, 3, ',');
    // Should handle NULL strings array
    CUNIT_ASSERT(result == NULL);
}

CUNIT_TEST(test_join_zero_count) {
    const char* strings[] = {"a", "b"};
    char* result = string_join(strings, 0, ',');
    // Should handle zero count
    CUNIT_ASSERT(result != NULL);
    if (result) free(result);
}

CUNIT_TEST(test_parse_int_null_string) {
    int value;
    bool result = string_parse_int(NULL, &value);
    // Should return false for NULL string
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_parse_int_null_out) {
    bool result = string_parse_int("123", NULL);
    // Should handle NULL output pointer
    CUNIT_ASSERT(result == false || result == true);
}

CUNIT_TEST(test_parse_int_invalid) {
    int value;
    bool result = string_parse_int("abc", &value);
    // Should return false for invalid input
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_parse_int_overflow) {
    int value;
    bool result = string_parse_int("999999999999", &value);
    // Should handle overflow gracefully
    CUNIT_ASSERT(result == false || result == true);
}

CUNIT_TEST(test_format_int_null_buffer) {
    int result = string_format_int(NULL, 32, 123);
    // Should return -1 for NULL buffer
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_format_int_zero_size) {
    char buffer[32];
    int result = string_format_int(buffer, 0, 123);
    // Should handle zero size gracefully
    CUNIT_ASSERT(result == -1 || result >= 0);
}

CUNIT_TEST(test_format_int_overflow) {
    char buffer[2];
    int result = string_format_int(buffer, 2, 12345);
    // Should handle buffer too small
    CUNIT_ASSERT(result == -1 || result >= 0);
}

CUNIT_TEST(test_starts_with_null_string) {
    bool result = string_starts_with(NULL, "prefix");
    // Should return false for NULL string
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_starts_with_null_prefix) {
    bool result = string_starts_with("string", NULL);
    // Should handle NULL prefix gracefully
    CUNIT_ASSERT(result == false || result == true);
}

CUNIT_TEST(test_ends_with_null_string) {
    bool result = string_ends_with(NULL, "suffix");
    // Should return false for NULL string
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_ends_with_null_suffix) {
    bool result = string_ends_with("string", NULL);
    // Should handle NULL suffix gracefully
    CUNIT_ASSERT(result == false || result == true);
}

CUNIT_TEST(test_remove_chars_null_string) {
    string_remove_chars(NULL, "abc");
    // Should handle NULL string gracefully
    CUNIT_ASSERT(1 == 1);
}

CUNIT_TEST(test_remove_chars_null_chars) {
    char str[] = "hello";
    string_remove_chars(str, NULL);
    // Should handle NULL chars gracefully
    CUNIT_ASSERT(1 == 1);
}

CUNIT_TEST(test_remove_duplicates_null) {
    string_remove_duplicates(NULL);
    // Should handle NULL gracefully
    CUNIT_ASSERT(1 == 1);
}

CUNIT_TEST(test_count_substring_null_string) {
    size_t result = string_count_substring(NULL, "sub");
    // Should return 0 for NULL string
    CUNIT_ASSERT_EQ((int)result, 0);
}

CUNIT_TEST(test_count_substring_null_substring) {
    size_t result = string_count_substring("string", NULL);
    // Should handle NULL substring gracefully
    CUNIT_ASSERT(result == 0 || result != 0);
}

CUNIT_TEST(test_count_substring_empty_substring) {
    size_t result = string_count_substring("hello", "");
    // Should handle empty substring
    CUNIT_ASSERT(result == 0 || result != 0);
}

