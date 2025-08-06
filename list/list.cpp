#include "list.hpp"

template <typename T>
typename List<T>::Node& List<T>::Node::operator=(const Node& right)
{
    if(&right == this)
        return *this;

    Node copy{right};
    swap(copy);
    return *this;
}

template <typename T>
void List<T>::Node::swap(Node& obj) noexcept
{
    std::swap(obj.next, next);
    std::swap(obj.prev, prev);
    std::swap(obj.value, value);
}

template <typename T>
List<T>::List()
{
    // Node nd1{10};
    // Node nd2{};
    // nd1 = nd1;
}

template <typename T>
List<T>::Node::Node(): value{T{}}, next{nullptr}, prev{nullptr}
    {   }

template <typename T>
List<T>::Node::Node(T val): value{val}, next{nullptr}, prev{nullptr}
    {   }

template <typename T>
List<T>::Node::Node(const Node& right): next{right.next}, prev{right.prev}, value{right.value}
    {   }

int main(void)
{
    List<int> ls{};
    return 0;
}