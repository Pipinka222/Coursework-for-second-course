#include <iostream>
#include <Windows.h>
#include "Source.h"

int main() {
    std::cout.precision(4);
    std::cout << std::fixed;
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int M, N;
    std::cout << "Введите количество координат: ";
    std::cin >> M;
    std::cout << "Введите количество функций: ";
    std::cin >> N;

    double* x_values = new double[M];
    double* y_values = new double[M];
    std::cout << "Введите координаты x:\n";
    for (int i = 0; i < M; ++i) {
        std::cin >> x_values[i];
    }
    std::cout << "Введите координаты y:\n";
    for (int i = 0; i < M; ++i) {
        std::cin >> y_values[i];
    }

    Matrix matrixA(N, N);
    Matrix matrixB(N, 1);
    matrixA.fill_array_A(x_values, M);
    matrixB.fill_array_B(x_values, y_values, N, M);

    std::cout << "Матрица А: \n";
    matrixA.print();

    std::cout << "Матрица B: \n";
    matrixB.print();

    Matrix adj_A = matrixA.adjugate();
    Matrix A_obr = adj_A;
    std::cout << "Обратная матрица А: \n";
    A_obr.print();

    Matrix result = A_obr * matrixB;
    std::cout << "Матрица коэффициентов: \n";
    result.print();

    print_values(result, y_values, x_values, M);

    delete[] x_values;
    delete[] y_values;

    return 0;
}
