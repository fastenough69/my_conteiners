#include "new_list.hpp"

template <typename T>
List<T>::Node::Node(T val)
{
    next = nullptr;
    value = val;
}

template <typename T>
List<T>::List()
{
    head = nullptr;
    tail = head;
    size = 0;
}

template <typename T>
void List<T>::push_back(T val)
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
}

template <typename T>
void List<T>::print_list() const
{
    auto curr = head;
    while(curr != nullptr)
    {
        std::cout << curr->value << ' ';
        curr = curr->next;
    }
}

template <typename T>
List<T>::List(const List& right)
{
    if(this == &right)
        return;

    head.reset(right.head.get());
    tail = right.tail;
    size = right.size;
}

template <typename T>
List<T>::List(List&& right) noexcept
{
    if(this == &right)
        return;

    head = right.head;
    tail = right.tail;
    size = right.size;
}

template <typename T>
void List<T>::swap(List obj) noexcept
{
    std::swap(head, obj.head);
    std::swap(tail, obj.tail);
    std::swap(size, obj.size);
}

template <typename T>
typename List<T>::List& List<T>::operator=(const List& right)
{
    List<T> copy {right};
    swap(copy);
    return *this;
}

template <typename T>
typename List<T>::List& List<T>::operator=(List&& right) noexcept
{
    List<T> copy {std::move(right)};
    swap(copy);
    return *this;
}

template <typename T>
void List<T>::push_front(T val)
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
}

int main(void)
{
    List<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_front(7);
    lst.print_list();
    return 0;
}