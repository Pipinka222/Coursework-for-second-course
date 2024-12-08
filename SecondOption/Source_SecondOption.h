#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <iostream>
#include <cmath>

class Preparation {
private:
    double** A;
    std::vector<double> B;
    int N, M;

public:
    Preparation(int n, int m) : N(n), M(m), B(n) {
        A = new double* [N];
        for (int i = 0; i < N; ++i) {
            A[i] = new double[N];
        }
    }

    ~Preparation() {
        for (int i = 0; i < N; ++i) {
            delete[] A[i];
        }
        delete[] A;
    }

    void fill_matrix_A(double x_values[]);
    void fill_matrix_B(double x_values[], double y_values[]);
    double** get_matrix_A();
    const std::vector<double>& get_matrix_B() const;
    void print_matrix_A();
    void print_matrix_B();

private:
    double basis_function(int i, double x);
};

class Solution {
private:
    double** A;
    std::vector<double> B;
    std::vector<double> result;
    int N;

    double det(double** matrix, int size);
    double minor_ij(double** matrix, int size, int row, int col);
    double** find_adjugate();

public:
    Solution(double** a, const std::vector<double>& b, int n) : A(a), B(b), N(n), result(n, 0.0) {}
    void solve();
    const std::vector<double> get_result() const;
};

void print_result(double* x_values, double* y_values, int M, std::vector<double> result);

#endif
