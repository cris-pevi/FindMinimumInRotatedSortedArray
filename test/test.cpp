#include <cassert>
#include <iostream>
#include <string>
#include "../src/solution.hpp"

using namespace std;

void ejecutar_test(int arr[], int n, int esperado, const string& nombre) {
    int resultado = encontrarMin(arr, n);
    assert(arr[resultado] == esperado);
    cout << nombre << " pasó" << endl;
}

int main() {
    int arr1[] = {3, 4, 5, 1, 2};
    ejecutar_test(arr1, 5, 1, "Caso normal");

    int arr2[] = {2, 1};
    ejecutar_test(arr2, 2, 1, "Caso pequeño");

    int arr3[] = {1};
    ejecutar_test(arr3, 1, 1, "Caso borde 1");

    int arr4[] = {1, 2, 3, 4, 5};
    ejecutar_test(arr4, 5, 1, "Caso borde 2");

    int arr5[] = {22, 23, 24, 25, 20, 21};
    ejecutar_test(arr5, 6, 20, "Caso propuesto");

    cout << "Todos los test pasaron" << endl;
    return 0;
}