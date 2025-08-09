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
    }
    else 
    {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    size++;
}

template <typename T>
void List<T>::push_front(T val)
{
    auto new_node = make_shared<Node>(val);
    if(!head)
    {
        head = new_node;
        tail = new_node;
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
List<T>::List(initializer_list<T> args)
{
    for(auto i = args.begin(); i != args.end(); i++)
    {
        push_back(*i);
    }
}

template <typename T>
int List<T>::get_size() const
{
    return size;
}

template <typename T>
List<T>::Prox::Prox(List* copy, int idx): obj{copy}, index{idx}
    {   }

template <typename T>
typename List<T>::Prox List<T>::operator[](int index)
{
    return Prox(this, index);
}


template <typename T>
List<T>::Prox::operator T() const
{
    if(index < 0 || index > obj->size - 1)
        throw "Index out of range\n";

    auto curr = obj->head;
    for(int i{}; i < index; i++)
        curr = curr->next;

    return curr->value;
}

template <typename T>
T List<T>::Prox::operator=(T right)
{
    if(index < 0 || index > obj->size - 1)
        throw "Index out of range\n";

    auto curr = obj->head;
    for(int i{}; i < index; i++)
        curr = curr->next;

    curr->value = right;
    return curr->value;
}

template <typename T>
void List<T>::pop_back()
{
    tail = tail->prev;
    tail->next = nullptr;
    size--;
}

template <typename T>
void List<T>::pop_front()
{
    head = head->next;
    head->prev = nullptr;
    size--;
}

template <typename T>
void List<T>::print_all() const
{
    auto curr = head;
    while(curr != nullptr)
    {
        cout << curr->value << ' ';
        curr = curr->next;
    }
}

int main(void)
{
    List<int> lst{};
    List<int> lst1{1, 2, 3};
    // lst1.print_all();
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_front(9);
    lst[0] = 5;
    lst.pop_back();
    lst.pop_front();

    for(int i{}; i < lst.get_size(); i++)
        cout << lst[i] << ' ';

    
    return 0;
}