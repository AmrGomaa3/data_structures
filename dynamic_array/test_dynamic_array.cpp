#include "dynamic_array.h"
#include <cassert>
#include <iostream>


int main() {
    DynamicArray<int> arr;
    assert(arr.isEmpty());

    arr.push(5);
    arr.push(2);
    assert(arr.getSize() == 2);
    assert(arr.get(0) == 5);

    arr.set(1, 1);
    assert(arr.get(1) == 1);

    arr.clear();
    assert(arr.isEmpty());

    std::cout << "All tests passed successfully\n";

    return 0;
}
