class Array
{
private:
    int *mData;
    size_t mSize;
    
public:

    // Default constructor
    Array(size_t size = 1)
    {
        mSize = size;
        mData = new int[mSize];
    }
    
    // Destructor
    ~Array()
    {
        delete[] mData;
    }

    // Copy constructor
    Array(Array &a)
    {
        mSize = a.mSize;
        mData = new int[mSize];
        for(size_t i = 0; i < mSize; i++)
        {
            mData[i] = a.mData[i];
        }
    }
    
    // Assignment operator
    Array& operator= (Array &a)
    {
        // block a=a;
        if(this != &a)
        {
            delete[] mData;
            mSize = a.mSize;
            mData = new int[mySize];
            for(size_t i = 0; i < mySize; i++)
            {
                mData[i] = a.mData[i];
            }
        }
        return *this
    }
};
