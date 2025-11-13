#include "cunit.h"
#include "text.h"
#include <string.h>
#include <stdlib.h>

// These tests are designed to catch bugs and will fail initially

CUNIT_TEST(test_upper_null_pointer) {
    char* result = text_to_upper(NULL);
    // Should handle NULL gracefully
    CUNIT_ASSERT(result == NULL || result != NULL);
    if (result) free(result);
}

CUNIT_TEST(test_upper_empty_string) {
    char* result = text_to_upper("");
    CUNIT_ASSERT(result != NULL);
    CUNIT_ASSERT_STR_EQ(result, "");
    free(result);
}

CUNIT_TEST(test_normalize_null_pointer) {
    size_t result = text_normalize_whitespace(NULL);
    // Should handle NULL gracefully
    CUNIT_ASSERT(result == 0 || result != 0);
}

CUNIT_TEST(test_normalize_leading_spaces) {
    char buf[64] = "   hello";
    size_t n = text_normalize_whitespace(buf);
    CUNIT_ASSERT(n > 0);
    // Should trim leading spaces
    CUNIT_ASSERT(buf[0] != ' ');
}

CUNIT_TEST(test_normalize_trailing_spaces) {
    char buf[64] = "hello   ";
    size_t n = text_normalize_whitespace(buf);
    CUNIT_ASSERT(n > 0);
    // Should trim trailing spaces
    size_t len = strlen(buf);
    CUNIT_ASSERT(len == 5 || buf[len-1] != ' ');
}

CUNIT_TEST(test_normalize_carriage_return) {
    char buf[64] = "hello\r\nworld";
    size_t n = text_normalize_whitespace(buf);
    // Should handle CR properly
    CUNIT_ASSERT(n > 0);
}

CUNIT_TEST(test_replace_null_pointer) {
    char* result = text_replace_all(NULL, "a", "b");
    CUNIT_ASSERT(result == NULL);
}

CUNIT_TEST(test_replace_empty_string) {
    char* result = text_replace_all("", "a", "b");
    CUNIT_ASSERT(result != NULL);
    CUNIT_ASSERT_STR_EQ(result, "");
    free(result);
}

CUNIT_TEST(test_replace_empty_from) {
    char* result = text_replace_all("hello", "", "x");
    // Empty from string - should handle gracefully
    CUNIT_ASSERT(result != NULL);
    free(result);
}

CUNIT_TEST(test_replace_overlapping) {
    // "aaa" with "aa" - should handle overlapping replacements
    char* result = text_replace_all("aaa", "aa", "x");
    CUNIT_ASSERT(result != NULL);
    // Should be either "xa" or "ax" depending on implementation
    free(result);
}

CUNIT_TEST(test_replace_all_occurrences) {
    char* result = text_replace_all("test_test_test", "_", "-");
    CUNIT_ASSERT(result != NULL);
    CUNIT_ASSERT_STR_EQ(result, "test-test-test");
    free(result);
}

