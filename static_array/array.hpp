#pragma once

#include <iostream>
#include <initializer_list>

template <typename T, int sz=1>
class Array{
private:
    T* data;
    int size = sz;

    class Prox {
        Array<T, sz>* curr;
        int index;

    public:
        Prox(Array<T, sz>* obj, int idx);
        T operator=(T value);
        operator T() const;
    };

public:
    int get_size() const;
    T* get_data() const;
    T& front() const;
    T& back() const;
    void fill(T value);
    Array();
    Array(std::initializer_list<T> args);
    Array(const Array<T, sz>& right);
    Array(Array<T, sz>&& right) noexcept;
    Array<T, sz>& operator=(const Array<T, sz>& right);
    Array<T, sz>& operator=(Array<T, sz>&& right) noexcept;
    Prox operator[](int index);
    ~Array();
};