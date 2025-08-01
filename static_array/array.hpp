#pragma once

#include <iostream>
#include <initializer_list>

template <typename T, int sz=1>
class Array{
public:
    int get_size() const;
    T* get_data() const;
    Array();
    Array(std::initializer_list<T> args);
    Array(const Array<T, sz>& right);
    Array(Array<T, sz>&& right) noexcept;
    Array<T, sz>& operator=(const Array<T, sz>& right);
    Array<T, sz>& operator=(Array<T, sz>&& right) noexcept;
    ~Array();

private:
    T* data;
    int size = sz;
};