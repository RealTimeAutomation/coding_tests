#include "metrics.h"
#include <stdlib.h>

long metrics_sum(const int* arr, size_t n) {
    if (arr == NULL) {
        return 0;
    }
    
    long s = 0;
    for (size_t i = 0; i < n; ++i) {
        s += arr[i];
    }
    return s;
}

int metrics_average(const int* arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    long s = metrics_sum(arr, n);
    return (int)(s / (int)n);
}

int metrics_argmax(const int* arr, size_t n) {
    if (arr == NULL || n == 0) return -1;
    int idx = 0;
    int maxv = arr[0];
    for (size_t i = 1; i < n; ++i) {
        if (arr[i] > maxv) {
            maxv = arr[i];
            idx = (int)i;
        }
        // For equal values, keep first occurrence (idx already points to first max)
    }
    return idx;
}

void metrics_sort(int* arr, size_t n) {
    if (arr == NULL) {
        return;
    }
    
    for (size_t i = 0; i < n; ++i) {
        int swapped = 0;
        for (size_t j = 1; j < n - i; ++j) {
            if (arr[j-1] > arr[j]) {
                int tmp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int metrics_median(int* arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    metrics_sort(arr, n);
    size_t mid = n / 2;
    if (n % 2 == 0) {
        return arr[mid-1];
    } else {
        // For odd length, return the middle element
        return arr[mid];
    }
}

