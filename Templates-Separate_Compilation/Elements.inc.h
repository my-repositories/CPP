template<class T>
Elements<T>::Elements(T *data, int count)
{
    el = data;
    size = count;
}

template<class T>
T Elements<T>::GetMax()
{
    T max = el[0];
    for (int i = 1; i < size; i++)
    {
        if (el[i] > max) max = el[i];
    }
    return max;
}

template<class T>
T Elements<T>::GetMin()
{
    T min = el[0];
    for (int i = 1; i < size; i++)
    {
        if (el[i] < min) min = el[i];
    }
    return min;
}

template<class T>
T Elements<T>::GetSum()
{
    T sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += el[i];
    }
    return sum;
}

template<class T>
T Elements<T>::GetAvg()
{
    return GetSum()/ size;
}
