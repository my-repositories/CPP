#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
public:
    Matrix(const int rows = 3, const int cols = 3)
        :
        ROWS(rows),
        COLS(cols),
        matrix(rows, std::vector<int>(cols))
    {}

    // cout << M
    friend std::ostream& operator<< (std::ostream &os, const Matrix &M);

    // cin >> M
    friend std::istream& operator>> (std::istream &is, Matrix &M);

    // A == B
    friend bool operator==(const Matrix &A, const Matrix &B);

    // -M is equal to M * (-1)
    inline const Matrix operator-() const
    {
        return *this * -1;
    }

    // A - B
    inline friend Matrix operator- (const Matrix &A, const Matrix &B)
    {
        return A + -B;
    }

    // A -= B
    Matrix& operator-= (const Matrix &B);

    // A + B
    friend Matrix operator+ (const Matrix &A, const Matrix &B);

    // A += B
    Matrix& operator+= (const Matrix &B);

    // A * B
    friend Matrix operator* (const Matrix &A, const Matrix &B);

    // A *= B
    Matrix& operator*= (const Matrix &B);

    // k * M
    friend Matrix operator* (const int k, const Matrix &M);

    // M * k
    inline friend Matrix operator* (const Matrix &M, const int k)
    {
        return k * M;
    }

    // M *= k
    Matrix& operator*= (const int k);

    // setter
    inline std::vector<int>& operator[] (const int row)
    {
        return matrix[row];
    }

    // getter (const)
    inline const std::vector<int>& operator[] (const int row) const
    {
        return matrix[row];
    }

protected:
    const int ROWS;
    const int COLS;
    std::vector< std::vector<int> > matrix;
};

#endif // !MATRIX_H
