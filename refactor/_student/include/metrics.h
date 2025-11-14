#ifndef LEGACY_METRICS_H
#define LEGACY_METRICS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Computes the sum of `n` integers in `arr`.
long metrics_sum(const int* arr, size_t n);

// Computes the average (integer division).
int metrics_average(const int* arr, size_t n);

// Returns the index of the maximum element, or -1 if n==0.
int metrics_argmax(const int* arr, size_t n);

// Sorts in-place ascending (very basic bubble sort).
void metrics_sort(int* arr, size_t n);

// Returns median (for even n, lower median). Undefined for n==0.
int metrics_median(int* arr, size_t n);

#ifdef __cplusplus
}
#endif

#endif
