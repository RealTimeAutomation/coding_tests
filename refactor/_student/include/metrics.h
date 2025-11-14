/**
 * @file metrics.h
 * @brief Mathematical operations on integer arrays
 * 
 * This module provides functions for computing statistics and performing
 * operations on integer arrays, including sum, average, maximum, sorting,
 * and median calculations.
 */

#ifndef LEGACY_METRICS_H
#define LEGACY_METRICS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Computes the sum of integers in an array
 * 
 * @param arr Pointer to the integer array (can be NULL)
 * @param n Number of elements in the array
 * @return Sum of all elements, or 0 if arr is NULL
 * 
 * @note Time complexity: O(n)
 * @note Safe to call with NULL pointer (returns 0)
 */
long metrics_sum(const int* arr, size_t n);

/**
 * @brief Computes the average of integers in an array
 * 
 * @param arr Pointer to the integer array (can be NULL)
 * @param n Number of elements in the array
 * @return Average as integer (truncated), or 0 if arr is NULL or n is 0
 * 
 * @note Uses integer division (truncates towards zero)
 * @note Returns 0 for empty arrays or NULL pointer
 * @note Time complexity: O(n)
 */
int metrics_average(const int* arr, size_t n);

/**
 * @brief Finds the index of the maximum element in an array
 * 
 * @param arr Pointer to the integer array (can be NULL)
 * @param n Number of elements in the array
 * @return Index of maximum element (0-based), or -1 if arr is NULL or n is 0
 * 
 * @note If multiple elements have the maximum value, returns the first occurrence
 * @note Time complexity: O(n)
 */
int metrics_argmax(const int* arr, size_t n);

/**
 * @brief Sorts an array in-place in ascending order
 * 
 * @param arr Pointer to the integer array to sort (can be NULL)
 * @param n Number of elements in the array
 * 
 * @note Uses bubble sort algorithm with early termination optimization
 * @note Modifies the array in-place
 * @note Time complexity: O(n²) worst case, O(n) best case (already sorted)
 * @note Safe to call with NULL pointer (no-op)
 */
void metrics_sort(int* arr, size_t n);

/**
 * @brief Computes the median value of an array
 * 
 * @param arr Pointer to the integer array (can be NULL)
 * @param n Number of elements in the array
 * @return Median value, or 0 if arr is NULL or n is 0
 * 
 * @note For even-length arrays, returns the lower median (element at index (n/2)-1)
 * @note For odd-length arrays, returns the middle element (element at index n/2)
 * @note The array is sorted in-place as a side effect
 * @note Time complexity: O(n²) due to sorting
 */
int metrics_median(int* arr, size_t n);

#ifdef __cplusplus
}
#endif

#endif

