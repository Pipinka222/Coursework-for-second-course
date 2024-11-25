#include "Source.h"

double Math::f(int i, double xi) { //если подгонять под себя, то тут
    switch (i) {
    case 0:
        return sin(xi);
    case 1:
        return cos(xi);
    case 2:
        return 1;
    }
    return 0;
}

void Matrix::fill_array_A(double x_values[], int M) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double sum = 0.00;
            for (int k = 0; k < M; k++) {
                sum += (f(i, x_values[k]) * f(j, x_values[k]));
            }
            data[i][j] = sum;
        }
    }
}

void Matrix::fill_array_B(double x_values[], double y_values[], int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 1; j++) {
            double sum = 0.00;
            for (int k = 0; k < M; k++) {
                sum += y_values[k] * f(i, x_values[k]);
            }
            data[i][j] = sum;
        }
    }
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

double Matrix::get_value(int row, int col) const {
    return data[row][col];
}

double Matrix::det() const {
    return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
        - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
        + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
}

double Matrix::minor_2x2(int row, int col) const {
    int rows[2], cols[2];
    for (int i = 0, ri = 0; i < this->rows; ++i) {
        if (i != row) rows[ri++] = i;
    }
    for (int j = 0, cj = 0; j < this->cols; ++j) {
        if (j != col) cols[cj++] = j;
    }
    return data[rows[0]][cols[0]] * data[rows[1]][cols[1]] -
        data[rows[0]][cols[1]] * data[rows[1]][cols[0]];
}

Matrix Matrix::adjugate() const {
    Matrix adj(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            adj.data[i][j] = pow(-1, i + j) * minor_2x2(i, j) * (1 / det());
        }
    }
    return adj;
}

void Matrix::transpos() { //shitcoding
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < cols; j++) {
            std::swap(data[i][j], data[j][i]);
        }
    }
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(this->rows, other.cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < this->cols; k++) {
                result.data[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

void print_values(const Matrix& result, double y_values[], double x_values[], int M) {
    std::cout << "Аппроксимированные значения:\n";
    double* dev = new double[M];
    double maxDev = -10000;
    double summ = 0.0;
    int index_max = 0;
    for (int i = 0; i < M; ++i) {
        double approximated_value = result.get_value(0, 0) * sin(x_values[i]) + result.get_value(1, 0) * cos(x_values[i]) + result.get_value(2, 0); //и тут
        std::cout << "x = " << x_values[i] << ", y = " << y_values[i] << ", y` = " << approximated_value << ", отклонение =  " << abs(y_values[i] - approximated_value) << "\n";
        dev[i] = abs(y_values[i] - approximated_value);
        summ = summ + (dev[i] * dev[i]);
    }
    std::cout << "\n";
    for (int j = 0; j < M; j++) {
        if (dev[j] > maxDev) {
            maxDev = dev[j];
            index_max = j;
        }
    }
    std::cout << "Наибольшее отклонение равно  " << maxDev << " и наблюдается при х равном  " << x_values[index_max] << "\n\n";
    std::cout << "Критерий аппроксимации равен " << summ << "\n\n";
    delete[] dev;
    dev = nullptr;
}
