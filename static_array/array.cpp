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

template <typename T, int sz>
Array<T, sz>& Array<T, sz>::operator=(Array<T, sz>&& right) noexcept
{
    if(this == &right)
        return *this;
    
    data = nullptr;
    data = right.data;
    size = right.size;
    right.data = nullptr;
    return *this;
}

template <typename T, int sz>
T* Array<T, sz>::get_data() const
{
    if(!data)
        return nullptr;
    
    return data;
}

template <typename T, int sz>
int Array<T, sz>::get_size() const
{
    return size;
}

template <typename T, int sz>
T& Array<T, sz>::front() const
{
    return data[0];
}

template <typename T, int sz>
T& Array<T, sz>::back() const
{
    return data[size - 1];
}

template <typename T, int sz>
void Array<T, sz>::fill(T value)
{
    for(int i{}; i < size; i++)
        data[i] = value;
}

template <typename T, int sz>
Array<T, sz>::Prox::Prox(Array<T, sz>* obj, int idx): curr{obj}, index{idx}
    {   }

template <typename T, int sz>
T Array<T, sz>::Prox::operator=(T value)
{
    if(index < 0 || index > curr->size - 1)
        throw "Index out of range\n";

    curr->data[index] = value;
    return value;
}

template <typename T, int sz>
Array<T, sz>::Prox::operator T() const
{
    if(index < 0 || index > curr->size - 1)
        throw "Index out of range\n";

    return curr->data[index];
}

template <typename T, int sz>
typename Array<T, sz>::Prox Array<T, sz>::operator[](int index) 
{
    return Prox(this, index);
}

int main(void)
{
    Array<int, 15> ar {1, 2, 3, 4, 5};
    Array<int, 15> ar1 {ar};
    Array<int, 15> ar2 = ar;

    Array<int, 15> ar3(std::move(ar2));
    Array<int, 15> ar4 = std::move(ar2);

    std::cout << ar.front() << ' ' << ar.back() << std::endl;

    int size = ar.get_size();
    int* ptr = ar.get_data();
    for(int i{}; i < size; i++)
        std::cout << ptr[i] << ' ';

    std::cout << std::endl;
    // ar.fill(10);
    // for(int i{}; i < size; i++)
    //     std::cout << ptr[i] << ' ';
    ar[14] = 1000;
    for(int i{}; i < size; i++)
        std::cout << ar[i] << ' ';

    return 0;
}