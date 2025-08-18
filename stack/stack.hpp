#pragma once

#include <iostream>
#include <memory>
#include "../vector/vector.hpp"

template <typename T>
class Stack {
    Vector<T> data;
    int size = data.get_size();

    void swap(Stack& obj) noexcept
    {
        std::swap(data, obj.data);
        std::swap(size, obj.size);
    }

public:
    Stack()
    {
        data = Vector<T>();
        size = data.get_size();
    }

    Stack(const Stack& right)
    {
        if(&right == this)
            return;

        data = right.data;
        size = right.size;
    }

    Stack(Stack&& right) noexcept
    {
        if(&right == this)
            return;

        data = std::move(right);
        size = size;
    }

    Stack& operator=(const Stack& right)
    {
        Stack cp{right};
        swap(cp);
        return *this;
    }

    Stack& operator=(Stack&& right) noexcept
    {
        Stack cp{std::move(right)};
        swap(cp);
        return *this;
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