#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "../src/solution.hpp"
#include "../src/utils.hpp"

using namespace std;
using namespace chrono;

template<typename Func>
double medir(Func f, int repeticiones) {
    auto t1 = high_resolution_clock::now();
    volatile int r;
    for (int i = 0; i < repeticiones; i++) { r = f(); }
    auto t2 = high_resolution_clock::now();
    return duration<double, milli>(t2 - t1).count() / repeticiones;
}

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

        double msLineal  = medir([&]() { return encontrarMinIngenua(arr.data(), n); }, REP);
        double msSort    = medir([&]() { return encontrarMinSort(arr); }, REP);
        double msBinaria = medir([&]() { return encontrarMin(arr.data(), n); }, REP);

        cout << setw(12) << n
             << setw(18) << msLineal
             << setw(22) << msSort
             << setw(20) << msBinaria << "\n";
    }

    return 0;
}