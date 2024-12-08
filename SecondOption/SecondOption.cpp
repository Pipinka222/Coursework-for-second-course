#include <iostream>
#include <Windows.h>
#include "Source_SecondOption.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::cout.precision(4);
    std::cout << std::fixed;

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

    Preparation prep(N, M);
    prep.fill_matrix_A(x_values);
    prep.fill_matrix_B(x_values, y_values);
    prep.print_matrix_A();
    prep.print_matrix_B();

    Solution solver(prep.get_matrix_A(), prep.get_matrix_B(), N);
    solver.solve();
    print_result(x_values, y_values, M, solver.get_result());

    delete[] x_values;
    delete[] y_values;

    return 0;
}
