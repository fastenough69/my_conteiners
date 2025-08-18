#include "queue.hpp"

int main(void)
{
    // Queue<int> obj;
    // Queue<int> obj1;

    // obj1.push(1);

    // obj.push(10);
    // obj.push(20);
    // obj.push(30);
    // Queue<int> obj3 = std::move(obj1);
    // obj.print_test();
    // obj3.print_test();

    priority_queue<int> pq;
    pq.push(5);
    pq.push(3);
    pq.push(7);
    pq.push(22);
    pq.print_test();
    return 0;
}