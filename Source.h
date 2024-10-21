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
    Matrix(int row, int col);
    ~Matrix();

    // Çàïîëíåíèå è âûâîä
    void fill_array_A(double x_values[], int M);
    void fill_array_B(double x_values[], double y_values[], int N, int M);
    void print() const;
    double get_value(int row, int col) const;

    // Äåéñòâèÿ íàä ìàòðèöàìè
    double det() const;
    double minor_2x2(int row, int col) const;
    Matrix adjugate() const;
    void transpos();
    Matrix operator*(const Matrix& other) const;
};

void print_values(const Matrix& result, double y_values[], double x_values[], int M);

#endif 

