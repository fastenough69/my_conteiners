#include "array.hpp"

template <typename T, int sz>
Array<T, sz>::Array()
{  
    size = sz;
    data = new T[size];
    
    for(int i{}; i < size; i++)
    {
        data[i] = T{};
    }
}

template <typename T, int sz>
Array<T, sz>::Array(std::initializer_list<T> args): Array()
{
    if(args.size() > size)
        return;
    
    std::copy(args.begin(), args.end(), data);
}

template <typename T, int sz>
Array<T, sz>::~Array()
{
    delete[] data;
}

template <typename T, int sz>
Array<T, sz>::Array(const Array<T, sz>& right)
{
    if(&right == this)
        return;
    
    data = new T[right.size];
    size = right.size;

    for(int i{}; i < size; i++)
        data[i] = right.data[i];
}

template <typename T, int sz>
Array<T, sz>::Array(Array<T, sz>&& right) noexcept
{
    data = nullptr;
    data = right.data;
    size = right.size;
    right.data = nullptr;
}

template <typename T, int sz>
Array<T, sz>& Array<T, sz>::operator=(const Array<T, sz>& right)
{
    if(this == &right)
        return *this;
    
    data = nullptr;
    data = new T[right.size];
    size = right.size;

    for(int i{}; i < size; i++)
        data[i] = right.data[i];

    return *this;
}

int main(void)
{
    Array<int, 15> ar {1, 2, 3, 4, 5};
    Array<int, 15> ar1 {ar};
    Array<int, 15> ar2 = ar;
    Array<int, 15> ar3(std::move(ar));
    return 0;
}