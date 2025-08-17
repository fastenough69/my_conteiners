#pragma once

#include <iostream>
#include <memory>
#include <initializer_list>

template <typename T>
class List {
    struct Node {
        std::shared_ptr<Node> next {nullptr};
        std::weak_ptr<Node> prev;
        T value {};
        Node(T val);
    };

    std::shared_ptr<Node> head {nullptr};
    std::weak_ptr<Node> tail;
    size_t size {0};

    void swap(List obj) noexcept;

    class Prox {
        List* obj;
        size_t index;

        std::shared_ptr<Node> search_node() const;
    public:
        Prox(List* arg, size_t idx);
        operator T() const;
        T operator=(T right);
    };

public:
    List();
    List(const List& right);
    List(List&& right) noexcept;
    List(std::initializer_list<T> args);
    List(size_t quainity, T val);
    List& operator=(const List& right);
    List& operator=(List&& right) noexcept;
    Prox operator[](int index);
    ~List() = default;
    void push_back(T val);
    void push_front(T val);
    void pop_back();
    void pop_front();
    void print_list() const;
};