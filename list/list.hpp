#pragma once

#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class List {
    class Node {
        shared_ptr<Node> next{nullptr};
        shared_ptr<Node> prev{nullptr};
        T value;

    public:
        Node();
        Node(T val);
        Node(const Node& right);
        Node(Node&& right) noexcept;
        Node& operator=(const Node& right);
        Node& operator=(Node&& right) noexcept;
        T& get_value() const;
        void linked_node(T val);
        void swap(Node& obj) noexcept;
        ~Node() = default;
    };

    shared_ptr<Node> head{nullptr};
    shared_ptr<Node> tail{nullptr};
    int size = 0;
public:
    List();
};  

