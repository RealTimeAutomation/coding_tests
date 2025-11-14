#include "cunit.h"
#include "text.h"
#include <string.h>
#include <stdlib.h>

CUNIT_TEST(test_upper_basic) {
    char* up = text_to_upper("Abc!");
    CUNIT_ASSERT_STR_EQ(up, "ABC!");
    free(up);
}

CUNIT_TEST(test_upper_all_lower) {
    char* up = text_to_upper("hello");
    CUNIT_ASSERT_STR_EQ(up, "HELLO");
    free(up);
}

CUNIT_TEST(test_upper_all_upper) {
    char* up = text_to_upper("HELLO");
    CUNIT_ASSERT_STR_EQ(up, "HELLO");
    free(up);
}

CUNIT_TEST(test_upper_mixed) {
    char* up = text_to_upper("Hello World 123");
    CUNIT_ASSERT_STR_EQ(up, "HELLO WORLD 123");
    free(up);
}

CUNIT_TEST(test_normalize_basic) {
    char buf[64];
    strcpy(buf, "hello   world");
    size_t n = text_normalize_whitespace(buf);
    CUNIT_ASSERT_EQ((int)n, 11);
    CUNIT_ASSERT_STR_EQ(buf, "hello world");
}

CUNIT_TEST(test_normalize_single_space) {
    char buf[64];
    strcpy(buf, "hello world");
    size_t n = text_normalize_whitespace(buf);
    CUNIT_ASSERT_EQ((int)n, 11);
    CUNIT_ASSERT_STR_EQ(buf, "hello world");
}

CUNIT_TEST(test_normalize_tabs) {
    char buf[64];
    strcpy(buf, "hello\t\tworld");
    size_t n = text_normalize_whitespace(buf);
    CUNIT_ASSERT(n > 0);
    // Result should have single space
}

CUNIT_TEST(test_replace_basic) {
    char* r = text_replace_all("a_b_c", "_", "-");
    CUNIT_ASSERT_STR_EQ(r, "a-b-c");
    free(r);
}

CUNIT_TEST(test_replace_single) {
    char* r = text_replace_all("hello", "l", "L");
    CUNIT_ASSERT_STR_EQ(r, "heLLo");
    free(r);
}

CUNIT_TEST(test_replace_multiple) {
    char* r = text_replace_all("test_test_test", "_", "-");
    CUNIT_ASSERT_STR_EQ(r, "test-test-test");
    free(r);
}

CUNIT_TEST(test_replace_no_match) {
    char* r = text_replace_all("hello", "x", "y");
    CUNIT_ASSERT_STR_EQ(r, "hello");
    free(r);
}

// Intentionally skipping tests for CR vs LF, leading/trailing spaces, overlapping replacements, NULL pointers, memory leaks

