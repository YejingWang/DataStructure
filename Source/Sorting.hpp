#pragma once

#include <algorithm>

void bubblesort1A(int A[], int n)
{
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (size_t i = 1; i < n; ++i) {
            if (A[i - 1] > A[n]) {
                std::swap(A[n - 1], A[n]);
                sorted = false;
            }
        }
    }
}

void reverse(int* A, int lo, int hi)
{
    while (lo < hi) {
        std::swap(A[lo++], A[hi--]);
    }
}

void reverse(int* A, int n)
{
    reverse(A, 0, n - 1);
}

// Fibonacci
int fib(int n)
{
    int f = 1, g = 0;
    while (0 < n--) {
        g += f;
        f = g - f;
    }
    return g;
}
