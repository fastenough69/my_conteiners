#include "new_list.hpp"

int main(void)
{
    List<int> lst, lst2 = {1, 2, 3, 4}, lst3(5, 2);
    List<int> lst1 = lst2;
    lst1.print_list();
    // lst.push_back(10);
    // lst.push_back(20);
    // lst.push_back(30);
    // lst.push_front(7);
    // lst.pop_back();
    // lst3.print_list();
    // lst2.print_list();
    // lst.print_list();
    // lst.pop_front();
    // try
    // {
    //     lst[1] = 35;
    //     lst.print_list();
    // }
    // catch(const char* mes)
    // {
    //     std::cerr << mes;
    // }
    return 0;
}