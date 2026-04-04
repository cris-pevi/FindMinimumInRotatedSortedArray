#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "../src/solution.hpp"

using namespace std;
using namespace chrono;

int encontrarMinSort(vector<int> arr) {
    sort(arr.begin(), arr.end());
    return arr[0];
}

vector<int> generarRotado(int n, int rotacion) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = (rotacion + i) % n;
    return arr;
}

#define MEDIR(codigo, repeticiones) [&]() { \
    auto t1 = high_resolution_clock::now(); \
    volatile int r; \
    for (int i = 0; i < repeticiones; i++) { r = codigo; } \
    auto t2 = high_resolution_clock::now(); \
    return duration<double, milli>(t2 - t1).count() / repeticiones; \
}()

int main() {
    vector<int> tamanios = {1000, 10000, 100000, 1000000};
    int REP = 100;

    cout << fixed << setprecision(4) << left;
    cout << setw(12) << "Tamaño"
         << setw(18) << "Lineal O(n)"
         << setw(22) << "Sort O(nlogn)"
         << setw(20) << "Binaria O(logn)" << "\n";
    cout << string(70, '-') << "\n";

    for (int n : tamanios) {
        vector<int> arr = generarRotado(n, n / 3);

        double msLineal  = MEDIR(encontrarMin(arr.data(), n), REP);
        double msSort    = MEDIR(encontrarMinSort(arr), REP);
        double msBinaria = MEDIR(encontrarMin(arr.data(), n), REP);

        cout << setw(12) << n
             << setw(18) << msLineal
             << setw(22) << msSort
             << setw(20) << msBinaria << "\n";
    }

    return 0;
}