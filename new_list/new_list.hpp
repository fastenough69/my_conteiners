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
        
        Node(T val)
        {
            next = nullptr;
            value = val;
        }
    };

    std::shared_ptr<Node> head {nullptr};
    std::weak_ptr<Node> tail;
    size_t size {0};

    void swap(List obj) noexcept
    {
        std::swap(head, obj.head);
        std::swap(tail, obj.tail);
        std::swap(size, obj.size);
    }

    class Prox {
        List* obj;
        size_t index;

        std::shared_ptr<Node> search_node() const
        {
            auto curr = obj->head;
            int i{};
            if(index > obj->size / 2)
            {
                curr = obj->tail.lock();
                i = obj->size - 1;
                for( ; i != index; i++)
                {
                    curr = curr->prev.lock();
                }
            }
            else
            {
                for( ; i < index; i++)
                {
                    curr = curr->next;
                }
            }
            return curr;
        }

    public:
        Prox(List* arg, size_t idx)
        {
            if(arg == nullptr)
                return;

            obj = arg;
            index = idx;
        }

        operator T() const
        {
            if(index >= obj->size)
                throw "Index out of range\n";

            auto curr = search_node();
            return curr->value;
        }

        T operator=(T right)
        {
            if(index >= obj->size)
                throw "Index out of range\n";

            auto curr = search_node();
            curr->value = right;
            return curr->value;
        }
    };

public:
    List()
    {
        head = nullptr;
        tail = head;
        size = 0;
    }

    ~List() = default;

    void push_back(T val)
    {
        auto new_node = std::make_shared<Node>(val);
        if(!head)
        {
            head = new_node;
            tail = head;
        }
        else
        {
            auto last = tail.lock();
            new_node->prev = last;
            last->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void print_list() const
    {
        auto curr = head;
        while(curr != nullptr)
        {
            std::cout << curr->value << ' ';
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    List(const List& right)
    {
        if(this == &right)
            return;

        auto curr_r = right.head;
        while (curr_r != nullptr)
        {
            push_back(curr_r->value);
            curr_r = curr_r->next;
        }
    }

    List(List&& right) noexcept
    {
        if(this == &right)
            return;

        head = right.head;
        tail = right.tail;
        size = right.size;
        right.head = nullptr;
        right.tail = right.head;
        right.size = 0;
    }

    List(std::initializer_list<T> args)
    {
        for(auto i = args.begin(); i != args.end(); i++)
        {
            push_back(*i);
        }
    }

    List(size_t quainity, T val)
    {
        for(int i{}; i < quainity; i++)
        {
            push_back(val);
        }
    }

    List& operator=(const List& right)
    {
        List<T> copy {right};
        swap(copy);
        return *this;
    }

    List& operator=(List&& right) noexcept
    {
        List<T> copy {std::move(right)};
        swap(copy);
        return *this;
    }

    void push_front(T val)
    {
        auto new_node = std::make_shared<Node>(val);
        if(!head)
        {
            head = new_node;
            tail = head;
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        size++;
    }

    Prox operator[](int index)
    {
        return Prox(this, index);
    }

    void pop_back()
    {
        auto p_last = tail.lock();
        tail = p_last->prev.lock();
        auto last = tail.lock();
        last->next = nullptr;
        tail = last;
        size--;
    }

    void pop_front()
    {
        head = head->next;
        auto p_head = head->prev.lock();
        p_head = nullptr;
        head->prev = p_head;
        size--;
    }

    size_t get_size() const
    {
        return size;
    }
};