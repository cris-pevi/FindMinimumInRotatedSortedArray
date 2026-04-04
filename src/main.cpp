#include <iostream>
#include "solution.hpp"
using namespace std;

int main() {
    int arr[] = {12, 13, 14, 15,10, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    int indiceMin = encontrarMin(arr, n);

    cout << "El mínimo es: " << arr[indiceMin] << endl;
    cout << "Rotaciones: " << indiceMin << endl;

    cout << "Arreglo original: [";
    for (int i = 0; i < n; i++) {
        cout << arr[(indiceMin + i) % n];
        if (i + 1 < n) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}