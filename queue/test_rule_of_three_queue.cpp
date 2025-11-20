#include "queue.h"
#include <cassert>
#include <iostream>


int main() {
    // Copy constructor tests
    // Test 1: non-empty - multiple nodes
    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);

    Queue<int> q2(q1);
    assert(q1.peek() == q2.peek());
    assert(q1.size() == q2.size());

    std::cout << "Test 1 passed\n";

    // Test 2: non-empty - single node
    Queue<int> q3;
    q3.enqueue(1);

    Queue<int> q4(q3);
    assert(q3.peek() == q4.peek());
    assert(q3.size() == q4.size());

    std::cout << "Test 2 passed\n";

    // Test 3: empty
    Queue<int> q5;
    Queue<int> q6(q5);
    assert(q5.size() == q6.size());
    assert(q5.isEmpty());
    assert(q6.isEmpty());

    std::cout << "Test 3 passed\n";

    // Copy assignment operator tests
    // Test 4: non-empty to empty - multiple nodes
    Queue<int> q7;
    q7.enqueue(1);
    q7.enqueue(2);
    q7.enqueue(3);

    Queue<int> q8;
    q8 = q7;
    assert(q7.peek() == q8.peek());
    assert(q7.size() == q8.size());

    std::cout << "Test 4 passed\n";

    // Test 5: non-empty to empty - single node
    Queue<int> q9;
    q9.enqueue(1);

    Queue<int> q10;
    q10 = q9;
    assert(q10.peek() == q9.peek());
    assert(q10.size() == q9.size());

    std::cout << "Test 5 passed\n";

    // Test 6: empty to empty
    Queue<int> q11;

    Queue<int> q12;
    q12 = q11;
    assert(q12.size() == q11.size());
    assert(q11.isEmpty());
    assert(q12.isEmpty());

    std::cout << "Test 6 passed\n";

    // Test 7: empty to non-empty - multiple nodes
    Queue<int> q13;

    Queue<int> q14;
    q14.enqueue(1);
    q14.enqueue(2);
    q14.enqueue(3);

    q14 = q13;
    assert(q13.size() == q14.size());
    assert(q13.isEmpty());
    assert(q14.isEmpty());

    std::cout << "Test 7 passed\n";

    // Test 8: empty to non-empty - single node
    Queue<int> q15;

    Queue<int> q16;
    q16.enqueue(1);

    q16 = q15;
    assert(q16.size() == q15.size());
    assert(q16.isEmpty());
    assert(q15.isEmpty());

    std::cout << "Test 8 passed\n";

    // Test 9: non-empty to non-empty - same size - multiple nodes
    Queue<int> q17;
    q17.enqueue(1);
    q17.enqueue(2);
    q17.enqueue(3);

    Queue<int> q18;
    q18.enqueue(4);
    q18.enqueue(5);
    q18.enqueue(6);

    q18 = q17;

    assert(q17.size() == q18.size());
    assert(q17.peek() == q18.peek());

    std::cout << "Test 9 passed\n";

    // Test 10: non-empty to non-empty - same size - single node
    Queue<int> q19;
    q19.enqueue(1);

    Queue<int> q20;
    q19.enqueue(2);

    q20 = q19;

    assert(q19.size() == q20.size());
    assert(q19.peek() == q20.peek());

    std::cout << "Test 10 passed\n";

    // Test 11: non-empty to non-empty - different size (1)
    Queue<int> q21;
    q21.enqueue(1);
    q21.enqueue(2);
    q21.enqueue(3);

    Queue<int> q22;
    q22.enqueue(4);

    q22 = q21;
    assert(q21.peek() == q22.peek());
    assert(q21.size() == q22.size());

    std::cout << "Test 11 passed\n";

    // Test 12: non-empty to non-empty - different size (2)
    Queue<int> q23;
    q23.enqueue(1);
    q23.enqueue(2);
    q23.enqueue(3);

    Queue<int> q24;
    q24.enqueue(4);
    q24.enqueue(5);

    q24 = q23;
    assert(q23.peek() == q24.peek());
    assert(q23.size() == q24.size());

    std::cout << "Test 12 passed\n";

    // Test 13: non-empty to non-empty - different size (3)
    Queue<int> q25;
    q25.enqueue(1);

    Queue<int> q26;
    q26.enqueue(4);
    q26.enqueue(5);
    q26.enqueue(6);

    q26 = q25;
    assert(q25.peek() == q26.peek());
    assert(q25.size() == q26.size());

    std::cout << "Test 13 passed\n";

    // Test 14: non-empty to non-empty - different size (4)
    Queue<int> q27;
    q27.enqueue(1);
    q27.enqueue(2);

    Queue<int> q28;
    q28.enqueue(4);
    q28.enqueue(5);
    q28.enqueue(6);

    q28 = q27;
    assert(q27.peek() == q28.peek());
    assert(q27.size() == q28.size());

    std::cout << "Test 14 passed\n";

    // Test 15: self-assignment
    Queue<int> q29;
    q29.enqueue(1);

    q29 = q29;

    assert(q29.peek() == 1);
    assert(q29.size() == 1);
    assert(!q29.isEmpty());

    std::cout << "Test 15 passed\n";

    std::cout << "All tests passed successfully\n";

    return 0;
}

