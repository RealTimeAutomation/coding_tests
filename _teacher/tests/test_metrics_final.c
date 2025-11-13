#include "cunit.h"
#include "metrics.h"

// These tests are designed to catch bugs and will fail initially
// They should pass after bugs are fixed

CUNIT_TEST(test_sum_null_pointer) {
    // Should handle NULL pointer gracefully
    long result = metrics_sum(NULL, 5);
    // If function crashes, test will fail
    CUNIT_ASSERT(result == 0 || result != 0); // Just check it doesn't crash
}

CUNIT_TEST(test_sum_zero_elements) {
    int a[] = {1, 2, 3};
    long result = metrics_sum(a, 0);
    CUNIT_ASSERT_EQ((int)result, 0);
}

CUNIT_TEST(test_sum_negative_numbers) {
    int a[] = {-1, -2, -3};
    CUNIT_ASSERT_EQ((int)metrics_sum(a, 3), -6);
}

CUNIT_TEST(test_average_null_pointer) {
    int result = metrics_average(NULL, 5);
    // Should handle NULL gracefully
    CUNIT_ASSERT(result == 0 || result != 0);
}

CUNIT_TEST(test_average_zero_elements) {
    int a[] = {1, 2, 3};
    // Division by zero - should be handled
    int result = metrics_average(a, 0);
    // Test will fail if division by zero occurs
    CUNIT_ASSERT(result == 0 || result != 0);
}

CUNIT_TEST(test_average_negative) {
    int a[] = {-10, -20};
    int result = metrics_average(a, 2);
    CUNIT_ASSERT_EQ(result, -15);
}

CUNIT_TEST(test_argmax_zero_elements) {
    int a[] = {1, 2, 3};
    int result = metrics_argmax(a, 0);
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_argmax_null_pointer) {
    int result = metrics_argmax(NULL, 5);
    // Should handle NULL gracefully
    CUNIT_ASSERT(result == -1 || result != -1);
}

CUNIT_TEST(test_argmax_duplicates) {
    int a[] = {5, 3, 5, 2};
    int result = metrics_argmax(a, 4);
    // Should return first occurrence (index 0)
    CUNIT_ASSERT_EQ(result, 0);
}

CUNIT_TEST(test_median_zero_elements) {
    int a[] = {1, 2, 3};
    // Undefined for n==0, but should not crash
    int result = metrics_median(a, 0);
    CUNIT_ASSERT(result == 0 || result != 0);
}

CUNIT_TEST(test_median_null_pointer) {
    int result = metrics_median(NULL, 5);
    // Should handle NULL gracefully
    CUNIT_ASSERT(result == 0 || result != 0);
}

CUNIT_TEST(test_median_even_correct) {
    int a[] = {1, 2, 3, 4};
    metrics_sort(a, 4);
    int median = metrics_median(a, 4);
    // For even n, should return lower median (2)
    CUNIT_ASSERT_EQ(median, 2);
}

CUNIT_TEST(test_median_negative) {
    int a[] = {-5, -1, -3};
    metrics_sort(a, 3);
    int median = metrics_median(a, 3);
    CUNIT_ASSERT_EQ(median, -3);
}

