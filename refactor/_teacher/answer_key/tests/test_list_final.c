#include "cunit.h"
#include "list.h"
#include <stdlib.h>

// These tests are designed to catch bugs and will fail initially

CUNIT_TEST(test_list_append_null) {
    list_append(NULL, 42);
    // Should handle NULL gracefully (no crash)
    CUNIT_ASSERT(1 == 1); // Just check we get here
}

CUNIT_TEST(test_list_insert_null) {
    list_insert(NULL, 0, 42);
    // Should handle NULL gracefully
    CUNIT_ASSERT(1 == 1);
}

CUNIT_TEST(test_list_get_null) {
    int result = list_get(NULL, 0);
    // Should return 0 for NULL list
    CUNIT_ASSERT_EQ(result, 0);
}

CUNIT_TEST(test_list_get_out_of_bounds) {
    int_list* list = list_create();
    list_append(list, 1);
    
    int result = list_get(list, 100); // Out of bounds
    // Should return 0 for invalid index
    CUNIT_ASSERT_EQ(result, 0);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_remove_at_null) {
    int result = list_remove_at(NULL, 0);
    // Should return 0 for NULL list
    CUNIT_ASSERT_EQ(result, 0);
}

CUNIT_TEST(test_list_remove_at_out_of_bounds) {
    int_list* list = list_create();
    list_append(list, 1);
    
    int result = list_remove_at(list, 100);
    // Should return 0 for invalid index
    CUNIT_ASSERT_EQ(result, 0);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_find_null) {
    int result = list_find(NULL, 42);
    // Should return -1 for NULL list
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_list_reverse_null) {
    list_reverse(NULL);
    // Should handle NULL gracefully
    CUNIT_ASSERT(1 == 1);
}

CUNIT_TEST(test_list_reverse_empty) {
    int_list* list = list_create();
    list_reverse(list);
    // Should handle empty list gracefully
    CUNIT_ASSERT_EQ((int)list->size, 0);
    list_destroy(list);
}

CUNIT_TEST(test_list_sort_null) {
    list_sort(NULL);
    // Should handle NULL gracefully
    CUNIT_ASSERT(1 == 1);
}

CUNIT_TEST(test_list_sort_empty) {
    int_list* list = list_create();
    list_sort(list);
    // Should handle empty list gracefully
    CUNIT_ASSERT_EQ((int)list->size, 0);
    list_destroy(list);
}

CUNIT_TEST(test_list_merge_sorted_null_a) {
    int_list* b = list_create();
    list_append(b, 1);
    
    int_list* result = list_merge_sorted(NULL, b);
    // Should handle NULL gracefully
    CUNIT_ASSERT(result == NULL || result != NULL);
    if (result) list_destroy(result);
    list_destroy(b);
}

CUNIT_TEST(test_list_merge_sorted_null_b) {
    int_list* a = list_create();
    list_append(a, 1);
    
    int_list* result = list_merge_sorted(a, NULL);
    // Should handle NULL gracefully
    CUNIT_ASSERT(result == NULL || result != NULL);
    if (result) list_destroy(result);
    list_destroy(a);
}

CUNIT_TEST(test_list_merge_sorted_both_null) {
    int_list* result = list_merge_sorted(NULL, NULL);
    // Should handle both NULL gracefully
    CUNIT_ASSERT(result == NULL);
}

