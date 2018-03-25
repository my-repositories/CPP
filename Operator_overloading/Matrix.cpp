#include <iostream>
#include <iomanip>
#include "Matrix.h"

// cout << M
std::ostream& operator<< (std::ostream& os, const Matrix &M)
{
    std::cout << std::endl;
    for (int row = 0; row < M.ROWS; row++)
    {
        for (int col = 0; col < M.COLS; col++)
        {
            os << std::setw(5) << M[row][col] << ' ';
        }
        os << std::endl;
    }
    return os;
}

// cin >> M
std::istream& operator>> (std::istream& is, Matrix &M)
{
    for (int row = 0; row < M.ROWS; row++)
    {
        for (int col = 0; col < M.COLS; col++)
        {
            is >> M[row][col];
        }
    }
    return is;
}

// A == B
bool operator == (const Matrix &A, const Matrix &B)
{
    if (A.COLS != B.COLS || A.ROWS != B.ROWS)
    {
        return false;
    }

    for (int row = 0; row < A.ROWS; row++)
    {
        for (int col = 0; col < A.COLS; col++)
        {
            if (A[row][col] != B[row][col])
            {
                return false;
            }
        }
    }
    return true;
}

// A -= B
Matrix& Matrix::operator-= (const Matrix &B)
{
    if (COLS != B.COLS || ROWS != B.ROWS)
    {
        return *this;
    }

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            matrix[row][col] -= B[row][col];
        }
    }

    return *this;
}

// A + B
Matrix operator+ (const Matrix &A, const Matrix &B)
{
    Matrix C(A.ROWS, A.COLS);

    if (A.COLS != B.COLS || A.ROWS != B.ROWS)
    {
        return C;
    }

    for (int row = 0; row < A.ROWS; row++)
    {
        for (int col = 0; col < A.COLS; col++)
        {
            C[row][col] = A[row][col] + B[row][col];
        }
    }

    return C;
}

// A += B
Matrix& Matrix::operator+= (const Matrix &B)
{
    if (COLS != B.COLS || ROWS != B.ROWS)
    {
        return *this;
    }

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            matrix[row][col] += B[row][col];
        }
    }

    return *this;
}

// A * B
Matrix operator* (const Matrix &A, const Matrix &B)
{
    Matrix C(B.ROWS, A.COLS);

    if (A.COLS != B.ROWS)
    {
        return C;
    }

    for (int i = 0; i < A.ROWS; i++)
    {
        for (int j = 0; j < A.COLS; j++)
        {
            for (int k = 0; k < B.COLS; k++)
            {
                C[i][k] += A[i][j] * B[j][k];
            }
        }
    }

    return C;
}

// A *= B
Matrix& Matrix::operator*= (const Matrix &B)
{
    if (COLS != B.ROWS)
    {
        return *this;
    }

    // tmp = copy (A)
    Matrix tmp = *this;

    // clear (A) - fill by zero
    *this *= 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            for (int k = 0; k < B.COLS; k++)
            {
                matrix[i][k] += tmp[i][j] * B[j][k];
            }
        }
    }

    return *this;
}

// k * M
Matrix operator* (const int k, const Matrix &M)
{
    Matrix C(M.ROWS, M.COLS);

    for (int row = 0; row < C.ROWS; row++)
    {
        for (int col = 0; col < C.COLS; col++)
        {
            C[row][col] = M[row][col] * k;
        }
    }

    return C;
}

// M *= k
Matrix& Matrix::operator*= (const int k)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            matrix[row][col] *= k;
        }
    }

    return *this;
}
