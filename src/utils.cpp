#include "utils.hpp"
#include <algorithm>

vector<int> generarRotado(int n, int rotacion) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = (rotacion + i) % n;
    return arr;
}

int encontrarMinSort(vector<int> arr) {
    sort(arr.begin(), arr.end());
    return arr[0];
}