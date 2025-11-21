#include "deque.h"
#include <cassert>
#include <iostream>


int main() {
    // Test 1: constructor
    Deque<int> d;
    assert(d.isEmpty());
    assert(d.size() == 0);

    std::cout << "Test 1 (constructor) passed successfully\n";

    // Test 2: pushBack() operations
    d.pushBack(1);
    assert(d.peekBack() == 1);
    assert(d.peekFront() == 1);
    assert(d.size() == 1);

    d.pushBack(2);
    assert(d.peekBack() == 2);
    assert(d.peekFront() == 1);
    assert(d.size() == 2);

    d.pushBack(3);
    assert(d.peekBack() == 3);
    assert(d.peekFront() == 1);
    assert(d.size() == 3);

    std::cout << "Test 2 (pushBack() operations) passed successfully\n";

    // Test 3: pushFront() operations
    d.pushFront(4);
    assert(d.peekFront() == 4);
    assert(d.peekBack() == 3);
    assert(d.size() == 4);

    d.pushFront(5);
    assert(d.peekFront() == 5);
    assert(d.peekBack() == 3);
    assert(d.size() == 5);

    std::cout << "Test 3 (pushFront()) passed successfully\n";

    // Test 4: pop operations
    assert(d.popFront() == 5);
    assert(d.popFront() == 4);
    assert(d.size() == 3);

    assert(d.popBack() == 3);
    assert(d.popBack() == 2);
    assert(d.size() == 1);

    std::cout << "Test 4 (pop operations) passed successfully\n";

    // Test 5: clear()
    d.pushFront(1);
    d.pushBack(2);
    assert(d.size() == 3);

    d.clear();
    assert(d.size() == 0);
    assert(d.isEmpty());
    
    std::cout << "Test 5 (clear()) passed successfully\n";

    // Test 6: rebuild after clear
    d.pushBack(1);
    assert(d.peekBack() == 1);
    assert(d.peekFront() == 1);
    assert(d.size() == 1);

    d.pushFront(4);
    assert(d.peekFront() == 4);
    assert(d.peekBack() == 1);
    assert(d.size() == 2);

    assert(d.popFront() == 4);
    assert(d.popBack() == 1);
    assert(d.size() == 0);
    
    std::cout << "Test 6 (rebuild after clear) passed successfully\n";

    std::cout << "All tests passed successfully\n";

    return 0;
}
