#ifndef COURSEWORK_H
#define COURSEWORK_H


#include <iostream>
#include <cmath>

class Preparation {
private:
    double** A;
    double** B;
    int N, M;

public:
    Preparation(int n, int m) : N(n), M(m) {
        A = new double* [N];
        B = new double* [N];
        for (int i = 0; i < N; ++i) {
            A[i] = new double[N];
            B[i] = new double[1];
        }
    }

    ~Preparation() {
        for (int i = 0; i < N; ++i) {
            delete[] A[i];
            delete[] B[i];
        }
        delete[] A;
        delete[] B;
    }

    void fill_matrix_A(double x_values[]);
    void fill_matrix_B(double x_values[], double y_values[]);
    double basis_function(int i, double x);
    double** get_matrix_A();
    double** get_matrix_B();
    void print_matrix_A();
    void print_matrix_B();
};

class Solution {
private:
    double** A;
    double** B;
    double** result;
    int N;

    double det(double** matrix, int size);
    double minor_ij(double** matrix, int size, int row, int col);
    double** find_adjugate();

public:
    Solution(double** a, double** b, int n) : A(a), B(b), N(n) {
        result = new double* [N];
        for (int i = 0; i < N; ++i) {
            result[i] = new double[1];
        }
    }
    ~Solution() {
        for (int i = 0; i < N; ++i) {
            delete[] result[i];
        }
        delete[] result;
    }

    void solve();
    double** get_result();
};

void print_result(double* x_values, double* y_values, int M, double** result);

#endif 
