#include <iostream>
#include <cstdlib>
#include "Matrix.h"
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    system("title C++ Operator overloading");

    Matrix A(3, 3), B(3, 3);

    cout << "Заполните матрицу А:\n";
    cin >> A;

    cout << "Заполните матрицу B:\n";
    cin >> B;

    if (A * B == B * A)
        cout << "Произведения A*B и B*A равны! :)\n\n";
    else
        cout << "Произведения A*B и B*A не равны! :(\n\n";

    cout << "Матрица А: " << A << endl;
    cout << "Матрица B: " << B << endl << endl;

    cout << "Матрица A*B: " << A*B << endl;
    cout << "Матрица B*A: " << B*A << endl << endl;


    // [SUM] TEST
    cout << endl << "[SUM] TEST" << endl;
    Matrix D = A + B;
    cout << "D = (A+B): " << D << endl << endl;

    D += A;
    cout << "Матрица D += A: " << D << endl;

    // [DIFF] TEST
    cout << endl << "[DIFF] TEST" << endl;
    Matrix G = A - B;
    cout << "G = (A-B): " << G << endl << endl;

    G -= A;
    cout << "Матрица G -= A: " << G << endl;


    // [MULT] TEST
    cout << endl << "[MULT] TEST" << endl;
    Matrix C = A * B;
    cout << "Матрица C = A*B: " << C << endl;

    C *= B;
    cout << "Матрица C *= B: " << C << endl;


    int k = 2;
    C *= k;
    cout << "k = " << k << endl;
    cout << "C *= k: " << C << endl;

    k = 5;
    cout << "k = " << k << endl;
    cout << "k * C: " << k * C << endl;

    k = 10;
    cout << "k = " << k << endl;
    cout << "C * k: " << C * k << endl;

    return 0;
}
