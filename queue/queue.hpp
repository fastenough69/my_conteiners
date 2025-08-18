#pragma once

#include <iostream>
#include <memory>
#include "../new_list/new_list.hpp"
#include "../vector/vector.hpp"

template <typename T>
class Queue {
    List<T> data;
    size_t size = 0;

public:
    Queue()
    {
        data = List<T>();
        size = data.get_size();
    }

    Queue(const Queue& right)
    {
        if(&right == this)
            return;

        data = right.data;
        size = right.size;
    }

    Queue(Queue&& right) noexcept
    {
        if(&right == this)
            return;

        data = std::move(right.data);
        size = right.size;
    }

    Queue& operator=(const Queue& right)
    {
        Queue copy{right};
        swap(copy);
        return *this;
    }

    Queue& operator=(Queue&& right) noexcept
    {
        Queue copy{std::move(right)};
        swap(copy);
        return *this;
    }

    ~Queue() = default;

    void swap(Queue& obj) noexcept
    {
        std::swap(data, obj.data);
        std::swap(size, obj.size);
    }

    void push(T value)
    {
        data.push_back(value);
        size++;
    }

    void pop()
    {
        data.pop_front();
        size--;
    }

    T front() const
    {
        return data[0];
    }

    T back() const
    {
        return data[size - 1];
    }

    bool is_empty() const
    {
        bool res = false;
        if(size)
        {
            res = true;
        }
        return res;
    }

    void print_test()
    {
        data.print_list();
    }
};

template <typename T>
class priority_queue {
private:
    Vector<T> data{};
    size_t size = 0;

    void search_pos_insert(T value)
    {
        int index = 0;
        for( ; index < data.get_size(); index++)
        {
            
        }
    }

public:
    priority_queue()
    {
        data = Vector<T>();
        size = data.get_size();
    }

    void push(T value)
    {
        if(!size)
        {
            data.push_front(value);
        }
        else
        {
            // for(int i{}; i < data.get_size(); i++)
            // {
            //     if(data[i] > value)
            //         continue;
            //     else
            //     {
            //         data.emplace(i, value);
            //         break;
            //     }
            // }
        }
        size++;
    }

    void print_test()
    {
        for(int i{}; i < data.get_size(); i++)
        {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }
};