#include "vector.h"

template <typename T>
void Vector<T>::new_size_capacity(int new_size)
{
    if(new_size < capacity)
        return;

    while(new_size >= capacity)
        capacity *= resize_cpacity;

    T* copy = new T[capacity];

    for(int i{}; i < size; i++)
        copy[i] = data[i];

    size = new_size;
    delete[] data;
    data = copy;
}

template <typename T>
Vector<T>::Vector(unsigned int sz): Vector()
{
    if(sz >= capacity)
        new_size_capacity(sz);

    size = sz;
    for(int i{}; i < size; i++)
        data[i] = 0;    
}

template <typename T>
Vector<T>::Vector(): capacity{default_cpacity}, size{0}
        { data = new T[capacity]; }

template <typename T>
Vector<T>::Vector(const Vector& right)
{
    if(this == &right)
        return;

    size = right.size;
    capacity = right.capacity;
    
    data = new T[capacity];
    
    for(int i{}; i < size; i++)
        data[i] = right.data[i];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& right)
{
    if(this == &right)
        return *this;
    
    if(size < right.size)
        new_size_capacity(right.size);

    for(int i{}; i < size; i++)
        data[i] = right.data[i];

    return *this;
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] data;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& right) noexcept
{
    data = nullptr;
    data = right.data;
    size = right.size;
    capacity = right.capacity;
    right.data = nullptr;
}

template <typename T>
Vector<T>::Vector(T* ar, unsigned int sz): Vector(sz)
{   
    if(data == ar)
        return;

    for(int i{}; i < sz; i++)
    {   
        data[i] = ar[i];
    }
}

template <typename T>
Vector<T>::Vector(std::unique_ptr<T[]> ar, int sz): data{ar.release()}, size{sz}
{
    new_size_capacity(size);
}

template <typename T>
Vector<T>::Vector(int sz, T value): Vector(sz)
{
    for(int i{}; i < size; i++)
        data[i] = value;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& right) noexcept
{
    if(this == &right)
        return *this;
    data = nullptr;
    data = right.data;
    size = right.size;
    capacity = right.capacity;
    right.data = nullptr;
    return *this;
}

template <typename T>
T* Vector<T>::get_data()
{
    return data;
}

template <typename T>
int Vector<T>::get_size()
{
    return size;
}

template <typename T>
void Vector<T>::push_back(T value)
{
    if(++size >= capacity)
        new_size_capacity(size);

    data[size - 1] = value;
}

template <typename T>
void Vector<T>::remove(int index)
{
    for(int i{index};i < --size; i++)
    {
        data[i] = data[i + 1];
    }
}

template <typename T>
void Vector<T>::emplace(int pos, T value)
{
    for(int i{size - 1}; i < pos; i--)
        data[i] = data[i - 1];

    data[pos] = value;
}

template <typename T>
void Vector<T>::insert(int pos, int n, T value)
{
    for(int i{size - n}; i > pos; i--)
        data[i] = data[i - n];

    for(int i{}; i < n; i++)
        data[pos + i] = value;
}

template <typename T>
typename Vector<T>::Item Vector<T>::operator[](int index)
{
    return Item(this, index);
}

template <typename T>
Vector<T>::Item::Item(Vector<T>* obj, int idx): curr{obj}, index{idx}
    {  }

template <typename T>
Vector<T>::Item::operator int() const
{
    if(index >= curr->size || index < 0)
        throw "Vector index out of range\n";

    return curr->data[index];
}

template <typename T>
int Vector<T>::Item::operator=(int right) const
{
    int old_size = curr->size;
    if(index >= curr->capacity)
        curr->new_size_capacity(index + 1);
    
    for(int i{old_size}; i < index; i++)
    {
        curr->data[i] = T{};
    }

    curr->data[index] = right;
    return right;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> args): Vector(args.size())
{
    std::copy(args.begin(), args.end(), data);
}

template <typename T>
int Vector<T>::get_capacity() const
{
    return capacity;
}

int main(void)
{
    Vector<int> v1{10}, v4{11};
    Vector<int> v2{v1}, v3{}, mv4 = std::move(v4), mv5{20};
    v3 = v2;
    mv5 = std::move(v2);
    std::cout << &mv5;

    int* ar = new int[10];
    for(int i{}; i < 10; i++)
        ar[i] = i * i;
    Vector<int> v6{ar, 10};

    int total = 25;
    // std::unique_ptr<int[]> arr {std::make_unique<int[]>(total)};
    // Vector<int> v7 {std::move(arr), total};

    Vector<int> v8 {25, 10};
    int* ptr = v8.get_data();
    int size = v8.get_size();
    for(int j{}; j < size; j++)
        std::cout << ptr[j] << ' ';

    std::cout << std::endl;

    for(int i{}; i < 10; i++)
        v8.push_back(i * i);

    v8.remove(v8.get_size() - 1);
    v8.emplace(10, 10000);

    int* ptr_out = v8.get_data();
    std::cout << v8.get_size() << std::endl;
    for(int i{}; i < v8.get_size(); i++)
        std::cout << ptr_out[i] << ' ';

    std::cout << std::endl;

    Vector<int> v9 {10, 1};
    v9.insert(4, 3, 10);
    std::cout << "vec v9: ";
    for(int i{}; i < v9.get_size(); i++)
        std::cout << v9.get_data()[i] << ' ';

    std::cout << std::endl << v9.get_size() << std::endl;
    v9[17] = 1000;
    try
    {
        total = v9[20];
    }
    catch(const char* err)
    {
        std::cerr << err;
    }
    std::cout << total << std::endl;
    std::cout << v9[16] << std::endl;

    for(int i{}; i < v9.get_size(); i++)
        std::cout << v9[i] << std::endl;

    Vector<int> v10{1, 2, 3, 4, 5, 32, 543, 564, 654, 12, 76};
    std::cout << "v10 size: " << v10.get_size() << " v10 capacity: " << v10.get_capacity() << std::endl;
    std::cout << "v10 elemets: ";
    for(int i{}; i < v10.get_size(); i++)
        std::cout << v10[i] << ' ';
    
    delete[] ar;
    return 0;
}
