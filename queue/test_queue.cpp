#include "queue.h"
#include <cassert>
#include <iostream>


int main() {
    Queue<int> queue;
    assert(queue.isEmpty());
    assert(queue.size() == 0);

    queue.enqueue(5);
    queue.enqueue(8);
    queue.enqueue(33);
    assert(queue.peek() == 5);
    assert(queue.size() == 3);

    assert(queue.dequeue() == 5);
    assert(queue.dequeue() == 8);
    assert(queue.peek() == 33);
    assert(queue.size() == 1);

    queue.enqueue(58);
    queue.enqueue(23);
    assert(queue.size() == 3);

    queue.clear();
    assert(queue.isEmpty());
    assert(queue.size() == 0);

    std::cout << "All tests passed successfully\n";

    return 0;
}

