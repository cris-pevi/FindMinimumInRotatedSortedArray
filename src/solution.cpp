#include "solution.hpp"

int encontrarMin(int arr[], int n) {
    int low = 0, high = n - 1;
    while (low < high) {
        int medio = (low + high) / 2;
        if (arr[medio] > arr[high])
            low = medio + 1;
        else
            high = medio;
    }
    return low;
}

int encontrarMinIngenua(int arr[], int n) {
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}