#include "stack.h"
#include <cassert>
#include <iostream>


int main() {
    // Test 1
    Stack<int> s1;
    s1.push(1); s1.push(2); s1.push(3);
    Stack<int> s2;
    s2 = s1;
    assert(s2.getSize() == 3);
    assert(s2.peek() == 3);

    // Test 2
    Stack<int> s3, s4;
    s4 = s3;
    assert(s4.isEmpty());

    // Test3
    Stack<int> s7;
    s7.push(99);
    Stack<int> s8;
    s7 = s8;
    assert(s7.isEmpty());

    std::cout << "Tests completed successfully\n";

    return 0;
}
