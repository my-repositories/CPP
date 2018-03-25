#ifndef ELEMENTS_H
#define ELEMENTS_H

template<class T>
class Elements
{
public:
    Elements(T *data, int count);
    ~Elements() {}

    T GetMax();
    T GetMin();
    T GetSum();
    T GetAvg();

private:
    T *el;
    int size;
};

#include "Elements.inc.h"
#endif // !ELEMENTS_H
