#ifndef LEGACY_LIST_H
#define LEGACY_LIST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_node {
    int data;
    struct list_node* next;
} list_node;

typedef struct {
    list_node* head;
    size_t size;
} int_list;

// Create a new empty list
int_list* list_create(void);

// Free all nodes and the list itself
void list_destroy(int_list* list);

// Append value to end of list
void list_append(int_list* list, int value);

// Insert value at index (0-based). If index >= size, append.
void list_insert(int_list* list, size_t index, int value);

// Remove value at index. Returns removed value or 0 if invalid.
int list_remove_at(int_list* list, size_t index);

// Get value at index. Returns 0 if invalid.
int list_get(const int_list* list, size_t index);

// Find first index of value, or -1 if not found
int list_find(const int_list* list, int value);

// Reverse the list in-place
void list_reverse(int_list* list);

// Sort the list in-place (simple bubble sort)
void list_sort(int_list* list);

// Merge two sorted lists into a new sorted list
int_list* list_merge_sorted(const int_list* a, const int_list* b);

#ifdef __cplusplus
}
#endif

#endif

