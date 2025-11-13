#include "cunit.h"
#include "list.h"
#include <stdlib.h>

CUNIT_TEST(test_list_create_append) {
    int_list* list = list_create();
    CUNIT_ASSERT(list != NULL);
    
    list_append(list, 42);
    CUNIT_ASSERT_EQ((int)list->size, 1);
    CUNIT_ASSERT_EQ(list_get(list, 0), 42);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_append_multiple) {
    int_list* list = list_create();
    list_append(list, 1);
    list_append(list, 2);
    list_append(list, 3);
    
    CUNIT_ASSERT_EQ((int)list->size, 3);
    CUNIT_ASSERT_EQ(list_get(list, 0), 1);
    CUNIT_ASSERT_EQ(list_get(list, 1), 2);
    CUNIT_ASSERT_EQ(list_get(list, 2), 3);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_insert) {
    int_list* list = list_create();
    list_append(list, 1);
    list_append(list, 3);
    list_insert(list, 1, 2);
    
    CUNIT_ASSERT_EQ((int)list->size, 3);
    CUNIT_ASSERT_EQ(list_get(list, 0), 1);
    CUNIT_ASSERT_EQ(list_get(list, 1), 2);
    CUNIT_ASSERT_EQ(list_get(list, 2), 3);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_insert_at_start) {
    int_list* list = list_create();
    list_append(list, 2);
    list_insert(list, 0, 1);
    
    CUNIT_ASSERT_EQ((int)list->size, 2);
    CUNIT_ASSERT_EQ(list_get(list, 0), 1);
    CUNIT_ASSERT_EQ(list_get(list, 1), 2);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_find) {
    int_list* list = list_create();
    list_append(list, 10);
    list_append(list, 20);
    list_append(list, 30);
    
    CUNIT_ASSERT_EQ(list_find(list, 20), 1);
    CUNIT_ASSERT_EQ(list_find(list, 10), 0);
    CUNIT_ASSERT_EQ(list_find(list, 30), 2);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_remove_at) {
    int_list* list = list_create();
    list_append(list, 1);
    list_append(list, 2);
    list_append(list, 3);
    
    int removed = list_remove_at(list, 1);
    CUNIT_ASSERT_EQ(removed, 2);
    CUNIT_ASSERT_EQ((int)list->size, 2);
    CUNIT_ASSERT_EQ(list_get(list, 0), 1);
    CUNIT_ASSERT_EQ(list_get(list, 1), 3);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_reverse) {
    int_list* list = list_create();
    list_append(list, 1);
    list_append(list, 2);
    list_append(list, 3);
    
    list_reverse(list);
    CUNIT_ASSERT_EQ(list_get(list, 0), 3);
    CUNIT_ASSERT_EQ(list_get(list, 1), 2);
    CUNIT_ASSERT_EQ(list_get(list, 2), 1);
    
    list_destroy(list);
}

CUNIT_TEST(test_list_sort) {
    int_list* list = list_create();
    list_append(list, 3);
    list_append(list, 1);
    list_append(list, 4);
    list_append(list, 2);
    
    list_sort(list);
    CUNIT_ASSERT_EQ(list_get(list, 0), 1);
    CUNIT_ASSERT_EQ(list_get(list, 1), 2);
    CUNIT_ASSERT_EQ(list_get(list, 2), 3);
    CUNIT_ASSERT_EQ(list_get(list, 3), 4);
    
    list_destroy(list);
}

// Intentionally skipping tests for: NULL pointers, empty list operations, out-of-bounds access, merge edge cases

