#include "cunit.h"
#include "metrics.h"

CUNIT_TEST(test_sum_basic) {
    int a[] = {1,2,3,4};
    CUNIT_ASSERT_EQ((int)metrics_sum(a, 4), 10);
}

CUNIT_TEST(test_sum_single) {
    int a[] = {42};
    CUNIT_ASSERT_EQ((int)metrics_sum(a, 1), 42);
}

CUNIT_TEST(test_sum_large) {
    int a[] = {100, 200, 300};
    CUNIT_ASSERT_EQ((int)metrics_sum(a, 3), 600);
}

CUNIT_TEST(test_sum_zeros) {
    int a[] = {0, 0, 0, 0};
    CUNIT_ASSERT_EQ((int)metrics_sum(a, 4), 0);
}

CUNIT_TEST(test_average_basic) {
    int a[] = {2,4,6,8};
    CUNIT_ASSERT_EQ(metrics_average(a, 4), 5);
}

CUNIT_TEST(test_average_single) {
    int a[] = {10};
    CUNIT_ASSERT_EQ(metrics_average(a, 1), 10);
}

CUNIT_TEST(test_average_rounding) {
    int a[] = {1, 2, 3};
    CUNIT_ASSERT_EQ(metrics_average(a, 3), 2); // 6/3 = 2
}

CUNIT_TEST(test_argmax_basic) {
    int a[] = {1,5,3,5};
    CUNIT_ASSERT_EQ(metrics_argmax(a, 4), 1); // first max index expected
}

CUNIT_TEST(test_argmax_first) {
    int a[] = {10, 5, 3};
    CUNIT_ASSERT_EQ(metrics_argmax(a, 3), 0);
}

CUNIT_TEST(test_argmax_last) {
    int a[] = {1, 2, 10};
    CUNIT_ASSERT_EQ(metrics_argmax(a, 3), 2);
}

CUNIT_TEST(test_sort_basic) {
    int a[] = {3, 1, 4, 1, 5};
    metrics_sort(a, 5);
    CUNIT_ASSERT_EQ(a[0], 1);
    CUNIT_ASSERT_EQ(a[1], 1);
    CUNIT_ASSERT_EQ(a[2], 3);
    CUNIT_ASSERT_EQ(a[3], 4);
    CUNIT_ASSERT_EQ(a[4], 5);
}

CUNIT_TEST(test_sort_already_sorted) {
    int a[] = {1, 2, 3, 4};
    metrics_sort(a, 4);
    CUNIT_ASSERT_EQ(a[0], 1);
    CUNIT_ASSERT_EQ(a[3], 4);
}

CUNIT_TEST(test_sort_reverse) {
    int a[] = {4, 3, 2, 1};
    metrics_sort(a, 4);
    CUNIT_ASSERT_EQ(a[0], 1);
    CUNIT_ASSERT_EQ(a[3], 4);
}

CUNIT_TEST(test_median_odd) {
    int a[] = {5, 2, 8, 1, 9};
    metrics_sort(a, 5);
    CUNIT_ASSERT_EQ(metrics_median(a, 5), 5);
}

CUNIT_TEST(test_median_even) {
    int a[] = {4, 2, 8, 1};
    metrics_sort(a, 4);
    int median = metrics_median(a, 4);
    CUNIT_ASSERT(median == 2 || median == 4); // Accept either lower or upper median
}

// NOTE: Intentionally skipping tests for n==0, negative numbers, overflow, NULL pointers

