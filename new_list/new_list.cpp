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
    size++;
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
    std::cout << std::endl;
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
List<T>::List(std::initializer_list<T> args)
{
    for(auto i = args.begin(); i != args.end(); i++)
    {
        push_back(*i);
    }
}

template <typename T>
List<T>::List(size_t quainity, T val)
{
    for(int i{}; i < quainity; i++)
    {
        push_back(val);
    }
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
    size++;
}

template <typename T>
typename List<T>::Prox List<T>::operator[](int index)
{
    return Prox(this, index);
}

template <typename T>
List<T>::Prox::Prox(List* arg, size_t idx)
{
    if(arg == nullptr)
        return;

    obj = arg;
    index = idx;
}

template <typename T>
std::shared_ptr<typename List<T>::Node> List<T>::Prox::search_node() const
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

template <typename T>
List<T>::Prox::operator T() const
{
    if(index >= obj->size)
        throw "Index out of range\n";

    auto curr = search_node();
    return curr->value;
}

template <typename T>
T List<T>::Prox::operator=(T right)
{
    if(index >= obj->size)
        throw "Index out of range\n";

    auto curr = search_node();
    curr->value = right;
    return curr->value;
}

template <typename T>
void List<T>::pop_back()
{
    auto p_last = tail.lock();
    tail = p_last->prev.lock();
    auto last = tail.lock();
    last->next = nullptr;
    tail = last;
    size--;
}

template <typename T>
void List<T>::pop_front()
{
    head = head->next;
    auto p_head = head->prev.lock();
    p_head = nullptr;
    head->prev = p_head;
    size--;
}

int main(void)
{
    List<int> lst, lst2 = {1, 2, 3, 4}, lst3(5, 2);
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_front(7);
    lst.pop_back();
    lst3.print_list();
    lst2.print_list();
    lst.print_list();
    lst.pop_front();
    try
    {
        lst[1] = 35;
        lst.print_list();
    }
    catch(const char* mes)
    {
        std::cerr << mes;
    }
    return 0;
}