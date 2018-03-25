#include <iostream>
#include <cstdlib>
#include <ctime>

template<class T>
T** BuildMatrix(size_t, size_t);

template <class T>
void FillMatrix(T&, size_t, size_t);

template <class T>
void MultMatrix(T&, const T&, const T&, size_t, size_t, size_t);

template<class T>
void PrintMatrix(const T&, size_t, size_t);

template<class T>
void RemoveMatrix(T&, size_t);

int main() {
    srand((unsigned)time(NULL));

    // 0. Init
    size_t rows1 = 3, cols1 = 4, rows2 = 4, cols2 = 2;
    int **matrix1 = BuildMatrix<int>(rows1, cols1);
    int **matrix2 = BuildMatrix<int>(rows2, cols2);
    int **matrix3 = BuildMatrix<int>(rows1, cols2);

    // 1. Fill
    FillMatrix(matrix1, rows1, cols1);
    FillMatrix(matrix2, rows2, cols2);
    MultMatrix(matrix3, matrix1, matrix2, rows1, cols1, cols2);
    
    // 2. Print
    std::cout << "matrix1:" << std::endl;
    PrintMatrix(matrix1, rows1, cols1);
    std::cout << std::endl << "matrix2:" << std::endl;
    PrintMatrix(matrix2, rows2, cols2);
    std::cout << std::endl << "matrix3:" << std::endl;
    PrintMatrix(matrix3, rows1, cols2);

    // 3. Free
    RemoveMatrix(matrix1, rows1);
    RemoveMatrix(matrix2, rows2);
    RemoveMatrix(matrix3, rows1);

    return 0;
}

template<class T>
T** BuildMatrix(size_t rows, size_t cols) {
    T **matrix = new T*[rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new T[cols];
    }
    return matrix;
}

template <class T>
void FillMatrix(T& matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 9 + 1;
        }
    }
}

template <class T>
void MultMatrix(T& out, const T& m1, const T& m2, size_t rows1, size_t cols1, size_t cols2) {
    for (size_t i = 0; i < rows1; ++i) {
        for (size_t k = 0; k < cols2; ++k) {
            out[i][k] = 0;
        }
        for (size_t j = 0; j < cols1; ++j) {
            for (size_t k = 0; k < cols2; ++k) {
                out[i][k] += m1[i][j] * m2[j][k];
            }
        }
    }
}

template<class T>
void PrintMatrix(const T& matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

template<class T>
void RemoveMatrix(T& matrix, size_t rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
