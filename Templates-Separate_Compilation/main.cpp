#include <iostream>
#include <iomanip>
#include "Elements.h"

using std::cout;
using std::endl;
using std::setw;

int main(int argc, char *argv[])
{
    int natural[5] = { 5,8,2,3,7 };
    double rational[9] = { 52.6, 2.51, 67.89, 381.2, 20.91, 97.195, 123.15, 18.2, 9.8 };
    char str[] = "fire";

    Elements<int> ei(natural, 5);
    Elements<double> ed(rational, 9);
    Elements<char> ec(str, 4);

    cout << setw(10) << "Max" << setw(10) << "Min"
         << setw(10) << "Sum" << setw(10) << "Avg"
         << endl << endl;

    cout << setw(10) << ei.GetMax() << setw(10) << ei.GetMin()
         << setw(10) << ei.GetSum() << setw(10) << ei.GetAvg()
         << endl;

    cout << setw(10) << ed.GetMax() << setw(10) << ed.GetMin()
         << setw(10) << ed.GetSum() << setw(10) << ed.GetAvg()
         << endl;

    cout << setw(10) << ec.GetMax() << setw(10) << ec.GetMin()
         << setw(10) << ec.GetSum() << setw(10) << ec.GetAvg()
         << endl;
}
