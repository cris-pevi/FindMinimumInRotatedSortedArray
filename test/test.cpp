#include <cassert>
#include <iostream>
#include "../src/solution.hpp"

using namespace std;

void test_caso_normal() {
    // Arrange
    int arr[] = {3, 4, 5, 1, 2};
    int n = 5;

    // Act
    int resultado = encontrarMin(arr, n);

    // Assert
    assert(arr[resultado] == 1);
    cout << "Caso normal pasó" << endl;
}

void test_pequenio() {
    // Arrange
    int arr[] = {2, 1};
    int n = 2;

    // Act
    int resultado = encontrarMin(arr, n);

    // Assert
    assert(arr[resultado] == 1);
    cout << "Caso pequeño pasó" << endl;
}

void caso_borde_1() {
    // Arrange
    int arr[] = {1};
    int n = 1;

    // Act
    int resultado = encontrarMin(arr, n);

    // Assert
    assert(arr[resultado] == 1);
    cout << "Caso borde 1 pasó" << endl;
}

void caso_borde_2() {
    // Arrange
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;

    // Act
    int resultado = encontrarMin(arr, n);

    // Assert
    assert(arr[resultado] == 1);
    cout << "Caso borde 2 pasó" << endl;
}

void caso_propuesto() {
    // Arrange
    int arr[] = {22, 23, 24, 25, 20, 21};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Act
    int resultado = encontrarMin(arr, n);

    // Assert
    assert(arr[resultado] == 20);
    cout << "Caso propuesto pasó" << endl;
}

int main() {
    test_caso_normal();
    test_pequenio();
    caso_borde_1();
    caso_borde_2();
    caso_propuesto();
    cout << "Todos los test pasaron" << endl;
    return 0;
}