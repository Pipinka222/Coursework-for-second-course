#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>

class Math {
public:
    double f(int i, double xi);
};

class Matrix : public Math {
private:
    double** data;
    int rows, cols;

public:
    Matrix(int row, int col) : rows(row), cols(col) {
        data = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0.0;
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }

    // Заполнение и вывод
    void fill_array_A(double x_values[], int M);
    void fill_array_B(double x_values[], double y_values[], int N, int M);
    void print() const;
    double get_value(int row, int col) const;

    // Действия над матрицами
    double det() const;
    double minor_2x2(int row, int col) const;
    Matrix adjugate() const;
    void transpos();
    Matrix operator*(const Matrix& other) const;
};

void print_values(const Matrix& result, double y_values[], double x_values[], int M);

#endif 

