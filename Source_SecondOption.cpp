#include "Source_SecondOption.h"


void Preparation::fill_matrix_A(double x_values[]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < M; ++k) {
                sum += (basis_function(i, x_values[k]) * basis_function(j, x_values[k]));
            }
            A[i][j] = sum;
        }
    }
}

void Preparation::fill_matrix_B(double x_values[], double y_values[]) {
    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        for (int k = 0; k < M; ++k) {
            sum += y_values[k] * basis_function(i, x_values[k]);
        }
        B[i][0] = sum;
    }
}

double Preparation::basis_function(int i, double x) {
    switch (i) {
    case 0: return sin(x);
    case 1: return cos(x);
    case 2: return 1.0;
    default: exit(1);
    }
}

double** Preparation::get_matrix_A() { return A; }
double** Preparation::get_matrix_B() { return B; }

void Preparation::print_matrix_A() {
    std::cout << "\n������� A:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Preparation::print_matrix_B() {
    std::cout << "\n������� B:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << B[i][0] << std::endl;
    }
}

double Solution::det(double** matrix, int size) {
    if (size == 1) {
        return matrix[0][0];
    }
    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double determinant = 0;
    double** subMatrix = new double* [size - 1];
    for (int i = 0; i < size - 1; ++i) {
        subMatrix[i] = new double[size - 1];
    }
    for (int col = 0; col < size; ++col) {
        for (int i = 1; i < size; ++i) {
            int subCol = 0;
            for (int j = 0; j < size; ++j) {
                if (j == col) continue;
                subMatrix[i - 1][subCol++] = matrix[i][j];
            }
        }
        determinant += pow(-1, col) * matrix[0][col] * det(subMatrix, size - 1);
    }
    for (int i = 0; i < size - 1; ++i) {
        delete[] subMatrix[i];
    }
    delete[] subMatrix;
    return determinant;
}

double Solution::minor_ij(double** matrix, int size, int row, int col) {
    double** subMatrix = new double* [size - 1];
    for (int i = 0; i < size - 1; ++i) {
        subMatrix[i] = new double[size - 1];
    }
    int subRow = 0;
    for (int i = 0; i < size; ++i) {
        if (i == row) continue;
        int subCol = 0;
        for (int j = 0; j < size; ++j) {
            if (j == col) continue;
            subMatrix[subRow][subCol++] = matrix[i][j];
        }
        ++subRow;
    }
    double minorValue = det(subMatrix, size - 1);
    for (int i = 0; i < size - 1; ++i) {
        delete[] subMatrix[i];
    }
    delete[] subMatrix;
    return minorValue;
}

double** Solution::find_adjugate() {
    double determinant = det(A, N);
    if (determinant == 0) {
        std::cout << ("������� ���������, �������� �� ����������.");
        return nullptr;
    }
    double** adj = new double* [N];
    for (int i = 0; i < N; ++i) {
        adj[i] = new double[N];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            adj[j][i] = pow(-1, i + j) * minor_ij(A, N, i, j) / determinant;
        }
    }
    return adj;
}

void Solution::solve() {
    double** adj = find_adjugate();
    std::cout << "\n�������� �������:\n";

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << adj[i][j] << " ";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < N; ++i) {
        result[i][0] = 0;
        for (int j = 0; j < N; ++j) {
            result[i][0] += adj[i][j] * B[j][0];
        }
    }
    std::cout << "\n������� (������������ �������������):\n";
    for (int i = 0; i < N; ++i) {
        std::cout << result[i][0] << "\n";
    }
    for (int i = 0; i < N; ++i) {
        delete[] adj[i];
    }
    delete[] adj;
}

double** Solution::get_result() {
    return result;
}

void print_result(double* x_values, double* y_values, int M, double** result) {
    double sum_of_squares = 0.0;
    double maxdif = -100;
    int maxdif_index = 0;

    std::cout << "\n��������� �����������:\n";
    for (int i = 0; i < M; ++i) {
        double predicted_value = sin(x_values[i]) * result[0][0] + cos(x_values[i]) * result[1][0] + 1.0 * result[2][0];
        double difference = y_values[i] - predicted_value;
        sum_of_squares += difference * difference;
        std::cout << "x: " << x_values[i] << " y: " << y_values[i]
            << " �������� �����������������: " << predicted_value << " �������: " << difference << "\n";

        if (abs(difference) > maxdif) {
            maxdif = abs(difference);
            maxdif_index = i;
        }
    }

    std::cout << "\n����� ��������� ����������: " << sum_of_squares << "\n";
    std::cout << "\n������������ ���������� �� �������  " << maxdif_index << "--- dif =" << maxdif;
}