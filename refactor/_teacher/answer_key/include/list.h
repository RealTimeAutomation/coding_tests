/**
 * @file list.h
 * @brief Singly-linked list data structure for integers
 * 
 * This module provides a complete implementation of a singly-linked list
 * for storing integers, with operations for insertion, deletion, searching,
 * sorting, and merging.
 */

#ifndef LEGACY_LIST_H
#define LEGACY_LIST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Node structure for the linked list
 */
typedef struct list_node {
    int data;                  /**< Integer data stored in the node */
    struct list_node* next;    /**< Pointer to the next node, NULL for last node */
} list_node;

/**
 * @brief Linked list structure
 */
typedef struct {
    list_node* head;   /**< Pointer to the first node, NULL if list is empty */
    size_t size;       /**< Number of elements in the list */
} int_list;

/**
 * @brief Creates a new empty linked list
 * 
 * @return Pointer to newly allocated list, or NULL on allocation failure
 * 
 * @note Caller is responsible for destroying the list with list_destroy()
 * @note Initial size is 0, head is NULL
 * 
 * @example
 *   int_list* list = list_create();
 *   if (list) {
 *       // Use list...
 *       list_destroy(list);
 *   }
 */
int_list* list_create(void);

/**
 * @brief Destroys a linked list and frees all memory
 * 
 * @param list List to destroy (can be NULL)
 * 
 * @note Safe to call with NULL pointer (no-op)
 * @note Frees all nodes and the list structure itself
 * 
 * @example
 *   list_destroy(list);
 *   list = NULL; // Good practice after destroy
 */
void list_destroy(int_list* list);

/**
 * @brief Appends a value to the end of the list
 * 
 * @param list List to append to (can be NULL)
 * @param value Integer value to append
 * 
 * @note Safe to call with NULL pointer (no-op)
 * @note Time complexity: O(n) where n is list size
 * 
 * @example
 *   list_append(list, 42);
 */
void list_append(int_list* list, int value);

/**
 * @brief Inserts a value at a specific index
 * 
 * @param list List to insert into (can be NULL)
 * @param index Position to insert at (0-based)
 * @param value Integer value to insert
 * 
 * @note If index >= size, appends to the end
 * @note Safe to call with NULL pointer (no-op)
 * @note Time complexity: O(n) where n is index
 * 
 * @example
 *   list_insert(list, 0, 10); // Insert at beginning
 *   list_insert(list, 2, 20); // Insert at position 2
 */
void list_insert(int_list* list, size_t index, int value);

/**
 * @brief Removes and returns the value at a specific index
 * 
 * @param list List to remove from (can be NULL)
 * @param index Position to remove from (0-based)
 * @return Removed value, or 0 if list is NULL, empty, or index is invalid
 * 
 * @note Returns 0 if index >= size
 * @note Time complexity: O(n) where n is index
 * 
 * @example
 *   int value = list_remove_at(list, 0); // Remove first element
 */
int list_remove_at(int_list* list, size_t index);

/**
 * @brief Gets the value at a specific index without removing it
 * 
 * @param list List to read from (can be NULL)
 * @param index Position to read from (0-based)
 * @return Value at index, or 0 if list is NULL, empty, or index is invalid
 * 
 * @note Returns 0 if index >= size
 * @note Does not modify the list
 * @note Time complexity: O(n) where n is index
 * 
 * @example
 *   int value = list_get(list, 0); // Get first element
 */
int list_get(const int_list* list, size_t index);

/**
 * @brief Finds the first index of a value in the list
 * 
 * @param list List to search in (can be NULL)
 * @param value Value to search for
 * @return Index of first occurrence (0-based), or -1 if not found
 * 
 * @note Returns -1 if list is NULL or value not found
 * @note Time complexity: O(n) where n is list size
 * 
 * @example
 *   int idx = list_find(list, 42);
 *   if (idx >= 0) {
 *       // Found at index idx
 *   }
 */
int list_find(const int_list* list, int value);

/**
 * @brief Reverses the list in-place
 * 
 * @param list List to reverse (can be NULL)
 * 
 * @note Modifies the list in-place
 * @note Safe to call with NULL pointer or empty list (no-op)
 * @note Time complexity: O(n) where n is list size
 * 
 * @example
 *   list_reverse(list); // List is now reversed
 */
void list_reverse(int_list* list);

/**
 * @brief Sorts the list in-place in ascending order
 * 
 * @param list List to sort (can be NULL)
 * 
 * @note Uses bubble sort algorithm
 * @note Modifies the list in-place
 * @note Safe to call with NULL pointer or empty/single-element list (no-op)
 * @note Time complexity: O(n²) where n is list size
 * 
 * @example
 *   list_sort(list); // List is now sorted
 */
void list_sort(int_list* list);

/**
 * @brief Merges two sorted lists into a new sorted list
 * 
 * @param a First sorted list (can be NULL)
 * @param b Second sorted list (can be NULL)
 * @return New sorted list containing all elements, or NULL on error
 * 
 * @note Both input lists must be sorted (ascending)
 * @note Returns NULL if either list is NULL or allocation fails
 * @note Caller is responsible for destroying the returned list
 * @note Original lists are not modified
 * @note Time complexity: O(n+m) where n and m are sizes of input lists
 * 
 * @example
 *   int_list* merged = list_merge_sorted(list1, list2);
 *   if (merged) {
 *       // Use merged list...
 *       list_destroy(merged);
 *   }
 */
int_list* list_merge_sorted(const int_list* a, const int_list* b);

#ifdef __cplusplus
}
#endif

#endif

