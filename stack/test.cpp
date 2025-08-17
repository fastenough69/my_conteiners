#include "stack.hpp"

int main(void)
{
    Stack<int> obj{};
    obj.push(10);
    obj.push(20);
    obj.push(30);
    obj.print_stack();

    std::cout << std::endl;

    obj.pop();
    obj.print_stack();
    std::cout << obj.top() << ' ' << obj.get_size();
    return 0;
}