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
        Item(Vector<T>* obj, int idx);
        operator int() const;
        int operator=(int right) const;
    };

    T* data;
    int size{0};
    int capacity;
    void new_size_capacity(int new_size);

public:
    Vector();
    Vector(unsigned int sz);
    Vector(const Vector& right);
    Vector(Vector<T>&& right) noexcept;
    Vector(T* ar, unsigned int sz);
    Vector(std::unique_ptr<T[]> ar, int sz);
    Vector(int sz, T value);
    Vector(std::initializer_list<T> args);
    Vector<T>& operator=(const Vector<T>& right);
    Vector<T>& operator=(Vector<T>&& right) noexcept;
    ~Vector();
    T* get_data();
    int get_size();
    int get_capacity() const;
    void push_back(T value);
    void remove(int index);
    void emplace(int pos, T value);
    void insert(int pos, int n, T value);
    Item operator[](int index);
};
