#pragma once

#include <iostream>
#include <memory>
#include "../vector/vector.hpp"

template <typename T>
class Stack {
    Vector<T> data;
    int size = data.get_size();

public:
    Stack()
    {
        data = Vector<T>();
        size = data.get_size();
    }

    ~Stack() = default;

    void push(T value)
    {
        data.push_front(value);
        size++;
    }

    void print_stack()
    {
        for(int i{}; i < data.get_size(); i++)
        {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }

    void pop()
    {
        data.remove(0);
        size--;
    }

    T top()
    {
        return data[0];
    }

    int get_size() const
    {
        return size;
    }
};