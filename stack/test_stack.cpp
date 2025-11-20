#include "stack.h"
#include <cassert>
#include <iostream>


int main() {
    Stack<int> stack;
    assert(stack.isEmpty());

    stack.push(5);
    stack.push(78);
    stack.push(-58);
    stack.push(21);
    assert(stack.getSize() == 4);
    assert(!stack.isEmpty());

    Stack<int> secondStack(stack);

    assert(stack.peek() == 21);
    assert(secondStack.peek() == 21);

    assert(stack.pop() == 21);
    assert(stack.getSize() == 3);
    assert(secondStack.getSize() == 4);
    assert(secondStack.peek() == 21);

    secondStack = stack;

    assert(stack.peek() == -58);
    assert(secondStack.peek() == -58);
    assert(secondStack.getSize() == 3);

    stack.clear();
    assert(stack.isEmpty());
    assert(!secondStack.isEmpty());
    assert(secondStack.pop() == -58);
    assert(secondStack.peek() == 78);
    assert(secondStack.getSize() == 2);

    std::cout << "All tests passed successfully\n";

    return 0;
}
