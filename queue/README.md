# Queue

A FIFO (First-In-First-Out) data structure implemented using a singly-linked list with head and tail pointers.

## Overview

The Queue implementation provides standard queue operations with O(1) enqueue, dequeue, and peek operations. Unlike array-based implementations, it uses a linked list with explicit tail pointer management to avoid the complexity of circular buffers while maintaining constant-time operations.

This implementation features the same optimized copy assignment operator used in the Stack, reusing nodes instead of deallocating and reallocating, and uses the same node constructor micro-optimization. For more details see the `stack` documentation [here](../stack/README.md).

## Features

- **O(1) enqueue and dequeue** operations
- **O(1) peek** at front element
- **Head and tail pointers** for efficient operations at both ends
- **Optimized assignment operator** - Reuses existing nodes (same strategy as Stack)
- **Comprehensive testing** - 19 test cases covering all edge cases

## Usage

```cpp
#include "queue.h"

// Create an empty queue
Queue<int> queue;

// Add elements to the back
queue.enqueue(10);
queue.enqueue(20);
queue.enqueue(30);

// Peek at front element
int front = queue.peek();       // Returns 10 (doesn't remove)

// Remove from front
int value = queue.dequeue();    // Returns 10 (removes from queue)

// Query state
std::cout << queue.size();      // Number of elements
std::cout << queue.isEmpty();   // Check if empty

// Clear all elements
queue.clear();
```

## Operations

### `void enqueue(T element)`
Adds an element to the back of the queue.
- **Parameters**: `element` - The value to add
- **Complexity**: Θ(1)
- **Note**: Automatically sets both head and tail if queue was empty

### `T dequeue()`
Removes and returns the front element.
- **Returns**: The front element
- **Complexity**: Θ(1)
- **Throws**: `std::out_of_range` if queue is empty
- **Note**: Automatically nulls tail pointer when queue becomes empty

### `const T& peek() const`
Returns the front element without removing it.
- **Returns**: Const reference to the front element
- **Complexity**: Θ(1)
- **Throws**: `std::out_of_range` if queue is empty

### `void clear()`
Removes all elements from the queue.
- **Complexity**: Θ(n)

### `int size() const`
Returns the number of elements in the queue.
- **Returns**: Element count
- **Complexity**: Θ(1)

#### `bool isEmpty() const`
Checks if the queue is empty.
- **Returns**: `true` if empty, `false` otherwise
- **Complexity**: Θ(1)

## Design Decisions

### Singly-Linked List with Dual Pointers

The queue uses a singly-linked list with both head and tail pointers.

**Why this design?**
- Head pointer enables O(1) dequeue from front
- Tail pointer enables O(1) enqueue at back
- Simpler than circular buffer (no modular arithmetic needed)
- No wasted capacity like array-based implementations

### Edge Case: Empty Queue Management

When the queue becomes empty after dequeue:

```cpp
if (!head) tail = nullptr;  // Critical: null both pointers
```

Both head and tail must be null when the queue is empty. This is crucial because `enqueue()` checks `if (!head)` to determine if the queue was empty and needs initialization.

### Optimized Assignment Operator

Like the Stack, the Queue uses an optimized copy assignment operator that reuses existing nodes instead of deallocating and reallocating. This achieves significant performance improvements on equal-size or similarly-sized assignments.

See the `stack` documentation [here](../stack/README.md) for detailed analysis of this optimization strategy and benchmark results. The same principle applies: node reuse eliminates unnecessary heap operations.

### Node Constructor Micro-Optimization

The same node constructor micro-optimization from Stack is applied here. `prev` is not always initialized to `nullptr`. However, the `next` pointer is initialized to `nullptr` in the node constructor since `next` always points to nothing during `enqueue()`.

## Comprehensive Testing Strategy

The Queue includes 19 distinct test cases covering:

**Basic Operations (4 tests):**
- Empty queue state
- Multiple enqueue operations
- Dequeue reducing size
- Interleaved enqueue/dequeue

**Rule of Three - Copy Constructor (3 tests):**
- Multiple node copy
- Single node copy
- Empty queue copy

**Rule of Three - Copy Assignment (12 tests):**
- Empty to empty
- Empty to non-empty (single and multiple)
- Non-empty to empty (single and multiple)
- Non-empty to non-empty with same size (single and multiple)
- Non-empty to non-empty with different sizes (4 combinations)
- Self-assignment

This exhaustive test coverage ensures all edge cases work correctly, from the most common operations to the subtlest corner cases.

## Complexity Analysis

| Operation | Time Complexity | Constants | Notes |
|-----------|----------------|-----------|-------|
| `enqueue()` | Θ(1) | 1 allocation, 3 pointer ops | Constant time, O(1) regardless of queue size |
| `dequeue()` | Θ(1) | 1 deallocation, 2 pointer ops | Constant time, checks if queue becomes empty |
| `peek()` | Θ(1) | 1 pointer dereference | No allocations, purest constant time |
| `clear()` | Θ(n) | n deallocations, ~n pointer ops | Must visit every node |
| `size()` | Θ(1) | 1 member access | Direct variable lookup |
| `isEmpty()` | Θ(1) | 1 comparison | Simple equality check |
| Copy constructor | Θ(n) | n allocations, ~2n pointer ops | Must create n new nodes |
| Assignment (optimized) | Θ(m) where m = source size | Reuses min(n,m), allocates/deallocates diff | Node reuse saves allocations on equal size |
| Assignment (naive) | Θ(n+m) | n deallocations, m allocations, ~2m copies | Always does full delete + rebuild |

**Key Insight**: The optimized assignment operator saves Θ(\|n-m\|) allocations/deallocations compared to naive approach, making it especially efficient for equal-size assignments which require zero heap operations.

---

**Part of the Data Structures Portfolio**  
[Previous: Stack](../stack/README.md) | [View Repository](../) | [Next: Deque](../deque/README.md)
