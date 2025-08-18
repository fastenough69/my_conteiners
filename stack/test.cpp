#include "stack.hpp"

int main(void)
{
    Stack<int> obj{};
    Stack<int> obj1{};

    obj1.push(1);
    obj = obj1;
    obj.print_stack();

    obj.push(10);
    obj.push(20);
    obj.push(30);

    obj.print_stack();

    obj.pop();
    obj.print_stack();
    std::cout << obj.top() << ' ' << obj.get_size();
    return 0;
}