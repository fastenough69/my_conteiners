#pragma once

#include <iostream>
#include <memory>
#include <initializer_list>

using namespace std;

template <typename T>
class List {
    struct Node {
        shared_ptr<Node> next{nullptr};
        shared_ptr<Node> prev{nullptr};
        T value;
        Node(T val);
    };

    shared_ptr<Node> head{nullptr};
    shared_ptr<Node> tail{nullptr};
    int size = 0;

    class Prox {
        List* obj;
        int index;

    public:
        Prox(List* copy, int idx);
        operator T() const;
        T operator=(T right);
    };

public:
    List();
    List(initializer_list<T> args);
    List(const List<T>& right);
    List(List<T>&& right) noexcept;
    List& operator=(const List<T>& right);
    List& operator=(List<T>&& right) noexcept;
    void swap(List& obj) noexcept;
    int get_size() const;
    void push_back(T val);
    void push_front(T val);
    void print_all() const;
    Prox operator[](int index);
    void pop_back();
    void pop_front();
    ~List() = default;
};  

