#pragma once

#include <iostream>
#include <memory>

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

public:
    List();
    List(const List& right);
    List(List&& right) noexcept;
    List& operator=(const List& right);
    List& operator=(List&& right) noexcept;
    ~List() = default;
    void push_back(T val);
    void push_front(T val);
    void print_list() const;
};