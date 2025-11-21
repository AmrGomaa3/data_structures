#include "deque.h"
#include <cassert>
#include <iostream>


int main() {
    // Copy constructor tests
    // Test 1: empty assignment
    Deque<int> d1;
    assert(d1.isEmpty());
    assert(d1.size() == 0);

    Deque<int> d2(d1);
    assert(d1.isEmpty());
    assert(d1.size() == 0);

    std::cout << "Test 1 passed\n";

    // Test 2: one node
    Deque<int> d3;
    d3.pushBack(1);

    Deque<int> d4(d3);
    assert(d4.size() == 1);
    assert(d4.peekBack() == 1);

    std::cout << "Test 2 passed\n";

    // Test 3: multiple nodes
    Deque<int> d5;
    d5.pushBack(1);
    d5.pushBack(2);
    d5.pushBack(3);

    Deque<int> d6(d5);
    assert(d6.size() == 3);
    assert(d6.peekBack() == 3);
    assert(d6.peekFront() == 1);
    assert(d6.popFront() == 1);
    assert(d6.popFront() == 2);
    assert(d6.peekFront() == 3);

    std::cout << "Test 3 passed\n";

    // Copy assignment operator tests
    // Test 4: empty to empty
    Deque<int> d7;
    assert(d7.isEmpty());

    Deque<int> d8;
    assert(d8.isEmpty());

    d8 = d7;
    assert(d8.isEmpty());
    assert(d7.isEmpty());

    std::cout << "Test 4 passed\n";

    // Test 5: empty to non-empty - single node
    Deque<int> d9;

    Deque<int> d10;
    d10.pushBack(1);
    
    d10 = d9;
    assert(d10.isEmpty());

    std::cout << "Test 5 passed\n";

    // test 6: empty to non-empty - multiple nodes
    Deque<int> d11;

    Deque<int> d12;
    d12.pushBack(1);
    d12.pushBack(2);
    d12.pushBack(3);

    d12 = d11;
    assert(d12.isEmpty());

    std::cout << "Test 6 passed\n";

    // Test 7: non-empty to empty - single node
    Deque<int> d13;
    d13.pushBack(1);

    Deque<int> d14;

    d14 = d13;
    assert(d14.size() == 1);
    assert(d14.peekBack() == 1);

    std::cout << "Test 7 passed\n";

    // Test 8: non-empty to empty - multiple nodes
    Deque<int> d15;
    d15.pushBack(1);
    d15.pushBack(2);
    d15.pushBack(3);

    Deque<int> d16;
    
    d16 = d15;
    assert(d16.size() == 3);
    assert(d16.peekFront() == 1);
    assert(d16.peekBack() == 3);

    std::cout << "Test 8 passed\n";

    // Test 9: non-empty to non-empty - same size (1)
    Deque<int> d17;
    d17.pushBack(1);

    Deque<int> d18;
    d18.pushBack(2);

    d18 = d17;
    assert(d18.size() == d17.size());
    assert(d18.peekFront() == d17.peekFront());
    assert(d18.popBack() == d17.popBack());
    assert(d17.isEmpty());
    assert(d18.isEmpty());

    std::cout << "Test 9 passed\n";

    // Test 10: non-empty to non-empty - same size (2)
    Deque<int> d19;
    d19.pushBack(1);
    d19.pushBack(2);
    d19.pushBack(3);

    Deque<int> d20;
    d20.pushBack(4);
    d20.pushBack(5);
    d20.pushBack(6);

    d20 = d19;
    assert(d20.size() == d19.size());
    assert(d20.peekFront() == d19.peekFront());
    assert(d20.popBack() == d19.popBack());
    
    std::cout << "Test 10 passed\n";

    // Test 11: non-empty to non-empty - different size (1)
    Deque<int> d21;
    d21.pushBack(1);
    d21.pushBack(2);
    d21.pushBack(3);

    Deque<int> d22;
    d22.pushBack(4);

    d22 = d21;
    assert(d22.size() == d21.size());
    assert(d22.peekFront() == d21.peekFront());
    assert(d22.popBack() == d21.popBack());

    std::cout << "Test 11 passed\n";

    // Test 12: non-empty to non-empty - different size (2)
    Deque<int> d23;
    d23.pushBack(1);
    d23.pushBack(2);
    d23.pushBack(3);

    Deque<int> d24;
    d24.pushBack(4);
    d24.pushBack(5);

    d24 = d23;
    assert(d24.size() == d23.size());
    assert(d24.peekFront() == d23.peekFront());
    assert(d24.popBack() == d23.popBack());

    std::cout << "Test 12 passed\n";

    // Test 13: non-empty to non-empty - different size (3)
    Deque<int> d25;
    d25.pushBack(1);

    Deque<int> d26;
    d26.pushBack(4);
    d26.pushBack(5);
    d26.pushBack(6);

    d26 = d25;
    assert(d26.size() == d25.size());
    assert(d26.peekFront() == d25.peekFront());
    assert(d26.popBack() == d25.popBack());
    assert(d25.isEmpty());
    assert(d26.isEmpty());

    std::cout << "Test 13 passed\n";

    // Test 14: non-empty to non-empty - different size (4)
    Deque<int> d27;
    d27.pushBack(1);
    d27.pushBack(2);

    Deque<int> d28;
    d28.pushBack(4);
    d28.pushBack(5);
    d28.pushBack(6);

    d28 = d27;
    assert(d28.size() == d27.size());
    assert(d28.peekFront() == d27.peekFront());
    assert(d28.popBack() == d27.popBack());

    std::cout << "Test 14 passed\n";

    // Test 15: self-assignment - empty
    Deque<int> d29;

    d29 = d29;
    assert(d29.isEmpty());
    assert(d29.size() == 0);

    std::cout << "Test 15 passed\n";

    // Test 16: self-assignment - single node
    Deque<int> d30;
    d30.pushBack(1);

    d30 = d30;
    assert(d30.size() == 1);
    assert(d30.peekBack() == 1);
    assert(d30.popFront() == 1);
    assert(d30.isEmpty());

    std::cout << "Test 16 passed\n";

    // Test 17: self-assignment - multiple nodes
    Deque<int> d31;
    d31.pushBack(1);
    d31.pushBack(2);
    d31.pushBack(3);

    d31 = d31;
    assert(d31.size() == 3);
    assert(d31.peekBack() == 3);
    assert(d31.popFront() == 1);
    assert(d31.size() == 2);

    std::cout << "Test 17 passed\n";

    std::cout << "All tests passed successfully\n";

    return 0;
}

