#pragma once

#include <iostream>
#include <memory>
#include <initializer_list>


template <typename T>
class Vector {
    enum{
        resize_cpacity=2,
        default_cpacity=8,
    };

    class Item {
        Vector<T>* curr {nullptr};
        int index {-1};
    public:
        Item(Vector<T>* obj, int idx): curr{obj}, index{idx}
            {  }
        operator T() const
        {
            if(index >= curr->size || index < 0)
                throw "Vector index out of range\n";

            return curr->data[index];
        }

        T operator=(T right)
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
    };

    T* data;
    int size{0};
    int capacity;
    
    void new_size_capacity(int new_size)
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
    void swap(Vector& obj) noexcept
    {
        std::swap(data, obj.data);
        std::swap(size, obj.size);
        std::swap(capacity, obj.capacity);
    }

public:
    Vector(unsigned int sz): Vector()
    {
        if(sz >= capacity)
            new_size_capacity(sz);

        size = sz;
        for(int i{}; i < size; i++)
            data[i] = 0;    
    }

    Vector(): capacity{default_cpacity}, size{0}
            { data = new T[capacity]; }

    Vector(const Vector& right)
    {
        if(this == &right)
            return;

        size = right.size;
        capacity = right.capacity;
        
        data = nullptr;
        data = new T[capacity];
        
        for(int i{}; i < size; i++)
            data[i] = right.data[i];
    }

    Vector& operator=(const Vector<T>& right)
    {
        Vector copy{right};
        swap(copy);
        return *this;
    }

    ~Vector()
    {
        delete[] data;
    }

    Vector(Vector<T>&& right) noexcept
    {
        if(this == &right)
            return;

        data = nullptr;
        data = right.data;
        size = right.size;
        capacity = right.capacity;
        right.data = nullptr;
    }

    Vector(T* ar, unsigned int sz): Vector(sz)
    {   
        if(data == ar)
            return;

        for(int i{}; i < sz; i++)
        {   
            data[i] = ar[i];
        }
    }

    Vector(int sz, T value): Vector(sz)
    {
        for(int i{}; i < size; i++)
            data[i] = value;
    }

    Vector& operator=(Vector<T>&& right) noexcept
    {
        Vector copy{std::move(right)};
        swap(copy);
        return *this;
    }

    T* get_data()
    {
        return data;
    }

    int get_size()
    {
        return size;
    }

    void push_back(T value)
    {
        if(++size >= capacity)
            new_size_capacity(size);

        data[size - 1] = value;
    }

    void push_front(T value)
    {
        if(++size >= capacity)
            new_size_capacity(size);

        for(int i = size; i >= 1; i--)
            data[i] = data[i - 1];

        data[0] = value;
    }

    void remove(int index)
    {
        size--;
        for(int i{index}; i < size; i++)
        {
            data[i] = data[i + 1];
        }
    }

    void emplace(int pos, T value)
    {
        for(int i{size - 1}; i < pos; i--)
            data[i] = data[i - 1];

        data[pos] = value;
    }

    void insert(int pos, int n, T value)
    {
        for(int i{size - n}; i > pos; i--)
            data[i] = data[i - n];

        for(int i{}; i < n; i++)
            data[pos + i] = value;
    }

    Item operator[](int index)
    {
        return Item(this, index);
    }

    Vector(std::initializer_list<T> args): Vector(args.size())
    {
        std::copy(args.begin(), args.end(), data);
    }

    int get_capacity() const
    {
        return capacity;
    }
};
