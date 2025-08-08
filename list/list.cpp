#include "list.hpp"

template <typename T>
List<T>::Node::Node(T val): next{nullptr}, prev{nullptr}, value{val}
    {   }

template <typename T>
List<T>::List(): head{nullptr}, tail{nullptr}, size{0}
    {   }

template <typename T>
List<T>::List(const List& right)
{
    if(this == &right)
        return;

    head.reset(right.head.get());
    tail.reset(right.tail.get());
    size = right.size;
}

template <typename T>
List<T>::List(List&& right) noexcept
{
    if(&right == this)
        return;

    head = nullptr;
    tail = nullptr;
    head = right.head;
    tail = right.tail;
    size = right.size;
    right.head = nullptr;
    right.tail = nullptr;
}

template <typename T>
void List<T>::swap(List& obj) noexcept
{
    std::swap(head, obj.head);
    std::swap(tail, obj.tail);
    std::swap(size, obj.size);
}

template <typename T>
List<T>& List<T>::operator=(const List& right)
{
    List<T> copy{right};
    swap(copy);
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& right) noexcept
{
    List<T> copy{right};
    swap(copy);
    return *this;
}

template <typename T>
void List<T>::push_back(T val)
{
    auto new_node = make_shared<Node>(val);
    if(!head)
    {
        head = new_node;
        tail = new_node;
        new_node->prev = head;
    }
    else 
    {
        new_node->prev = tail;
        head->next = new_node;
        tail = new_node;
    }
    size++;
}

template <typename T>
List<T>::List(std::initializer_list<T> args)
{
    for(auto i = args.begin(); i != args.end(); i++)
    {
        push_back(*i);
    }
}

int main(void)
{
    List<int> lst{};
    List<int> lst1{1, 2, 3};
    lst.push_back(10);
    lst.push_back(20);
    return 0;
}