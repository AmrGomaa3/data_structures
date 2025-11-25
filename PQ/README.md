# Priority Queue

A priority queue implementation using a binary min-heap, providing O(log n) insertion and removal of the highest-priority (lowest value) element.

## Overview

The Priority Queue maintains elements with associated priorities, always allowing efficient access to the element with the highest priority (lowest numerical value). This implementation uses a binary min-heap stored in a dynamic array, where the parent node always has lower priority than its children.

## Features

- **O(log n) insertion and removal** - Heap operations maintain order efficiently
- **O(1) peek** - Constant-time access to highest-priority element
- **Dynamic resizing** - Automatically grows/shrinks based on load
- **Array-based heap** - Better cache locality compared to tree-based implementations
- **Comprehensive testing** - 22 test cases including stress testing with 1 million elements

## Usage

```cpp
#include "PQ.h"

// Create a priority queue
PQ<std::string> tasks;

// Add tasks with priorities (lower number = higher priority)
tasks.push("Critical bug fix", 0);
tasks.push("Write documentation", 5);
tasks.push("Code review", 2);
tasks.push("Team meeting", 3);

// Access highest-priority task
std::string next = tasks.peek();     // Returns "Critical bug fix"

// Remove and process highest-priority task
std::string task = tasks.pop();      // Returns "Critical bug fix"
std::string task2 = tasks.pop();     // Returns "Code review"

// Query state
std::cout << tasks.size();           // Number of elements
std::cout << tasks.isEmpty();        // Check if empty
std::cout << tasks.capacity();       // Current array capacity

// Manual capacity management
tasks.shrinkToFit();                 // Reduce capacity to current size

// Clear all elements
tasks.clear();
```

## Operations

### Constructor
```cpp
PQ()
```
Creates an empty priority queue with default capacity (4).
- **Complexity**: O(1)

### `void push(T activity, int priority)`
Inserts an element with associated priority into the queue.
- **Parameters**: 
  - `activity` - The element to store
  - `priority` - Integer priority (lower = higher priority)
- **Complexity**: O(log n) - May trigger resize
- **Note**: Maintains heap property by bubbling up

### `T pop()`
Removes and returns the highest-priority (lowest value) element.
- **Returns**: The element with lowest priority value
- **Complexity**: O(log n) - May trigger resize
- **Throws**: `std::out_of_range` if queue is empty
- **Note**: Maintains heap property by bubbling down

### `T peek() const`
Returns the highest-priority element without removing it.
- **Returns**: The element with lowest priority value
- **Complexity**: O(1)
- **Throws**: `std::out_of_range` if queue is empty

### `void clear()`
Removes all elements from the queue.
- **Complexity**: O(1)
- **Note**: Does not deallocate array (capacity unchanged)

### `void shrinkToFit()`
Reduces capacity to match current size or minimum capacity.
- **Complexity**: O(n) - Requires copying elements
- **Note**: Useful after many removals to reclaim memory

### `int capacity()`
Returns the current array capacity.
- **Returns**: Total allocated slots
- **Complexity**: O(1)

### `int size() const`
Returns the number of elements in the queue.
- **Returns**: Element count
- **Complexity**: O(1)

### `bool isEmpty() const`
Checks if the queue is empty.
- **Returns**: `true` if no elements, `false` otherwise
- **Complexity**: O(1)

## Design Decisions

### Binary Min-Heap Implementation

The priority queue uses a binary min-heap where:
- Parent priority ≤ both children's priorities
- Smallest priority is always at the root (index 0)
- Stored in array using index arithmetic

**Index relationships:**
- Parent of node at index `i`: `(i - 1) / 2`
- Left child of node `i`: `(2 * i) + 1`
- Right child of node `i`: `(2 * i) + 2`

### Dynamic Resizing Strategy

Like Dynamic Array, the priority queue automatically resizes:

**Growth:**
- Doubles capacity when full
- Triggers on `push()` when `_index >= _capacity`
- Geometric growth ensures amortized O(1) per push

**Shrinking:**
- Halves capacity when 1/4 full
- Triggers on `pop()` when `_index < _capacity / 4`
- Minimum capacity of 4 (prevents thrashing)

**Design choice:**
The 1/4 threshold prevents alternating grow/shrink cycles when elements hover around capacity/2.

### Clear vs ShrinkToFit

The API provides two ways to reduce memory usage:

**`clear()`:**
- Sets size to 0
- O(1) operation
- Keeps allocated capacity
- Fast but doesn't free memory

**`shrinkToFit()`:**
- Reallocates to current size
- O(n) operation (must copy elements)
- Frees excess memory
- Slower but memory-efficient

### Element Structure

Elements are stored as structs containing both activity and priority:

```cpp
template<typename T>
struct element {
    T a;        // Activity (the data)
    int p;      // Priority (lower = higher priority)
};
```

**Design note:** Storing priority with the element avoids separate priority lookups and keeps related data together (cache-friendly).

## Complexity Analysis

| Operation        | Big-O Time |
|------------------|------------|
| `push`           | O(log n)   |
| `pop`            | O(log n)   |
| `peek`           | O(1)       |
| `size`           | O(1)       |
| `isEmpty`        | O(1)       |
| `clear`          | O(n)       |
| Internal resize  | O(n) when triggered |

**Key insight:** Both `push()` and `pop()` are O(log n) for the heap operations, but resizing adds occasional O(n) cost. With geometric growth/shrink, this amortizes to O(log n) per operation.

## Implementation Notes

### Rule of Three

The priority queue correctly implements the Rule of Three:
1. **Destructor** - Deallocates heap array
2. **Copy constructor** - Deep copy of heap and metadata
3. **Copy assignment** - Delete old, allocate new, copy elements

All three tested in `test_PQ.cpp` (22 test cases).

---

**Part of the Data Structures Portfolio**  
[Previous: Binary Search Tree](../BST/README.md) | [View Repository](../)
