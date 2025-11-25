#include "PQ.h"
#include <cassert>
#include <string>
#include <iostream>


constexpr int ELEMENTS {1'000'000};


int main() {
    // Test 1: constructor
    PQ<std::string> pq;
    assert(pq.isEmpty());
    assert(pq.size() == 0);

    std::cout << "Test 1 passed\n";

    // Test 2: basic operations
    pq.push("Python", 5);
    pq.push("C", 0);
    pq.push("Java", 2);
    assert(pq.peek() == "C");
    
    std::string temp = pq.pop();

    assert(temp == "C");
    assert(pq.peek() == "Java");
    assert(!pq.isEmpty());
    assert(pq.size() == 2);

    std::cout << "Test 2 passed\n";

    // Test 3: duplicate priorities
    pq.push("C++", 0);
    assert(pq.peek() == "C++");

    pq.push("C", 0);
    assert(pq.peek() == "C++");

    pq.pop();
    assert(pq.peek() == "C");
    assert(pq.size() == 3);

    std::cout << "Test 3 passed\n";

    // Test 4: clear
    assert(pq.capacity() == 4);
    assert(pq.size() == 3);

    pq.push("Ruby", 8);
    assert(pq.size() == 4);
    assert(pq.capacity() == 4);

    pq.push("Rust", 1);
    assert(pq.size() == 5);
    assert(pq.capacity() == 8);

    pq.clear();
    assert(pq.size() == 0);
    assert(pq.capacity() == 8);

    pq.shrinkToFit();
    assert(pq.size() == 0);
    assert(pq.capacity() == 4);

    std::cout << "Test 4 passed\n";

    // Test 5: stress testing (expand/shrink)
    PQ<double> stress_pq1;
    PQ<double> stress_pq2;

    for (int i = ELEMENTS; i > 0; i--) {
        stress_pq1.push(static_cast<double>(i), i);
        stress_pq2.push(static_cast<double>(i), i);
    }

    assert(stress_pq1.size() == ELEMENTS);
    assert(stress_pq2.size() == ELEMENTS);

    stress_pq2.clear();

    assert(stress_pq2.size() == 0);
    assert(stress_pq2.isEmpty());

    for (int i = 0; i < ELEMENTS; i++) stress_pq1.pop();

    assert(stress_pq1.isEmpty());

    std::cout << "Test 5 passed\n";

    // Copy constructor tests
    // Test 6: empty assignment
    PQ<double> pq1;
    assert(pq1.isEmpty());
    assert(pq1.size() == 0);

    PQ<double> pq2(pq1);
    assert(pq2.isEmpty());
    assert(pq2.size() == 0);

    std::cout << "Test 6 passed\n";

    // Test 7: one node
    PQ<double> pq3;
    pq3.push(1.0, 1);

    PQ<double> pq4{pq3};
    assert(pq4.size() == 1);
    assert(pq4.peek() == 1.0);

    std::cout << "Test 7 passed\n";

    // Test 8: multiple nodes
    PQ<double> pq5;
    pq5.push(1.0, 1);
    pq5.push(2.0, 2);
    pq5.push(3.0, 3);

    PQ<double> pq6{pq5};
    assert(pq6.size() == 3);
    assert(pq6.peek() == 1.0);
    
    std::cout << "Test 8 passed\n";

    // Copy assignment operator tests
    // Test 9: empty to empty
    PQ<double> pq7;
    assert(pq7.isEmpty());

    PQ<double> pq8;
    assert(pq8.isEmpty());

    pq8 = pq7;
    assert(pq8.isEmpty());
    assert(pq7.isEmpty());

    std::cout << "Test 9 passed\n";

    // Test 10: empty to non-empty - single node
    PQ<double> pq9;

    PQ<double> pq10;
    pq10.push(1.0, 1);
    
    pq10 = pq9;
    assert(pq10.isEmpty());

    std::cout << "Test 10 passed\n";

    // Test 11: empty to non-empty - multiple nodes
    PQ<double> pq11;

    PQ<double> pq12;
    pq12.push(1.0, 1);
    pq12.push(2.0, 2);
    pq12.push(3.0, 3);

    pq12 = pq11;
    assert(pq12.isEmpty());

    std::cout << "Test 11 passed\n";

    // Test 12: non-empty to empty - single node
    PQ<double> pq13;
    pq13.push(1.0, 1);

    PQ<double> pq14;

    pq14 = pq13;
    assert(pq14.size() == 1);
    assert(pq14.peek() == 1.0);

    std::cout << "Test 12 passed\n";

    // Test 13: non-empty to empty - multiple nodes
    PQ<double> pq15;
    pq15.push(2.0, 2);
    pq15.push(1.0, 1);
    pq15.push(3.0, 3);

    PQ<double> pq16;
    
    pq16 = pq15;
    assert(pq16.size() == 3);
    assert(pq16.peek() == 1.0);

    std::cout << "Test 13 passed\n";

    // Test 14: non-empty to non-empty - same size (1)
    PQ<double> pq17;
    pq17.push(1.0, 1);

    PQ<double> pq18;
    pq18.push(2.0, 2);

    pq18 = pq17;
    assert(pq18.size() == pq17.size());
    assert(pq18.peek() == pq17.peek());

    std::cout << "Test 14 passed\n";

    // Test 15: non-empty to non-empty - same size (2)
    PQ<double> pq19;
    pq19.push(2.0, 2);
    pq19.push(1.0, 1);
    pq19.push(3.0, 3);

    PQ<double> pq20;
    pq20.push(5.0, 5);
    pq20.push(4.0, 4);
    pq20.push(6.0, 6);

    pq20 = pq19;
    assert(pq20.size() == pq19.size());
    assert(pq20.peek() == pq19.peek());
    assert(pq20.pop() == pq19.pop());
    assert(pq20.peek() == pq19.peek());
    
    std::cout << "Test 15 passed\n";

    // Test 16: non-empty to non-empty - different size (1)
    PQ<double> pq21;
    pq21.push(2.0, 2);
    pq21.push(1.0, 1);
    pq21.push(3.0, 3);

    PQ<double> pq22;
    pq22.push(4.0, 4);

    pq22 = pq21;
    assert(pq22.size() == pq21.size());
    assert(pq22.peek() == pq21.peek());
    assert(pq22.pop() == pq21.pop());
    assert(pq22.peek() == pq21.peek());

    std::cout << "Test 16 passed\n";

    // Test 17: non-empty to non-empty - different size (2)
    PQ<double> pq23;
    pq23.push(2.0, 2);
    pq23.push(1.0, 1);
    pq23.push(3.0, 3);

    PQ<double> pq24;
    pq24.push(4.0, 4);
    pq24.push(5.0, 5);

    pq24 = pq23;
    assert(pq24.size() == pq23.size());
    assert(pq24.peek() == pq23.peek());
    assert(pq24.pop() == pq23.pop());
    assert(pq24.peek() == pq23.peek());

    std::cout << "Test 17 passed\n";

    // Test 18: non-empty to non-empty - different size (3)
    PQ<double> pq25;
    pq25.push(1.0, 1);

    PQ<double> pq26;
    pq26.push(5.0, 5);
    pq26.push(4.0, 4);
    pq26.push(6.0, 6);

    pq26 = pq25;
    assert(pq26.size() == pq25.size());
    assert(pq26.peek() == pq25.peek());

    std::cout << "Test 18 passed\n";

    // Test 19: non-empty to non-empty - different size (4)
    PQ<double> pq27;
    pq27.push(1.0, 1);
    pq27.push(2.0, 2);

    PQ<double> pq28;
    pq28.push(5.0, 5);
    pq28.push(4.0, 4);
    pq28.push(6.0, 6);

    pq28 = pq27;
    assert(pq28.size() == pq27.size());
    assert(pq28.peek() == pq27.peek());

    std::cout << "Test 19 passed\n";

    // Test 20: self-assignment - empty
    PQ<double> pq29;

    pq29 = pq29;
    assert(pq29.isEmpty());
    assert(pq29.size() == 0);

    std::cout << "Test 20 passed\n";

    // Test 21: self-assignment - single node
    PQ<double> pq30;
    pq30.push(1.0, 1);

    pq30 = pq30;
    assert(pq30.size() == 1);
    assert(pq30.peek() == 1.0);

    std::cout << "Test 21 passed\n";

    // Test 22: self-assignment - multiple nodes
    PQ<double> pq31;
    pq31.push(2.0, 2);
    pq31.push(1.0, 1);
    pq31.push(3.0, 3);

    pq31 = pq31;
    assert(pq31.size() == 3);
    assert(pq31.peek() == 1.0);
    pq31.pop();
    assert(pq31.peek() == 2.0);

    std::cout << "Test 22 passed\n";

    std::cout << "All tests passed successfully\n";

    return 0;
}

