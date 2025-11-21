# Deque

A double-ended queue implemented using a doubly-linked list, enabling O(1) operations at both front and back.

## Overview

The Deque (Double-Ended Queue) extends queue functionality by allowing efficient insertion and removal from both ends. Unlike a standard queue which only operates on one end, a deque provides true bidirectional access while maintaining constant-time complexity.

This implementation uses a doubly-linked list with explicit head and tail pointers, allowing O(1) `pushFront`, `pushBack`, `popFront`, and `popBack` operations. Like Stack and Queue, it features an optimized copy assignment operator that reuses nodes. For more details, see the `stack` documentation [here](../stack/README.md).

## Features

- **O(1) operations at both ends** - Push/pop from front or back
- **O(1) peek from both ends** - View elements without removal
- **Doubly-linked structure** - Forward and backward traversal support
- **Optimized assignment operator** - Reuses nodes like Stack and Queue
- **Comprehensive testing** - 23 test cases covering all operations and edge cases

## Usage

```cpp
#include "deque.h"

// Create an empty deque
Deque<int> deque;

// Add elements to front and back
deque.pushBack(10);    // [10]
deque.pushBack(20);    // [10, 20]
deque.pushFront(5);    // [5, 10, 20]
deque.pushFront(1);    // [1, 5, 10, 20]

// Peek at both ends
int front = deque.peekFront();  // Returns 1 (doesn't remove)
int back = deque.peekBack();    // Returns 20 (doesn't remove)

// Remove from both ends
int val1 = deque.popFront();    // Returns 1, deque: [5, 10, 20]
int val2 = deque.popBack();     // Returns 20, deque: [5, 10]

// Query state
std::cout << deque.size();      // Number of elements
std::cout << deque.isEmpty();   // Check if empty

// Clear all elements
deque.clear();
```

## Operations

### `void pushFront(T element)`
Adds an element to the front of the deque.
- **Parameters**: `element` - The value to add
- **Complexity**: Θ(1)

### `T popFront()`
Removes and returns the front element.
- **Returns**: The front element
- **Complexity**: Θ(1)
- **Throws**: `std::out_of_range` if deque is empty
- **Note**: Unlinks prev pointer and nulls tail if deque becomes empty

### `const T& peekFront() const`
Returns the front element without removing it.
- **Returns**: Const reference to the front element
- **Complexity**: Θ(1)
- **Throws**: `std::out_of_range` if deque is empty

### `void pushBack(T element)`
Adds an element to the back of the deque.
- **Parameters**: `element` - The value to add
- **Complexity**: Θ(1)

### `T popBack()`
Removes and returns the back element.
- **Returns**: The back element
- **Complexity**: Θ(1)
- **Throws**: `std::out_of_range` if deque is empty
- **Note**: Unlinks next pointer and nulls head if deque becomes empty

### `const T& peekBack() const`
Returns the back element without removing it.
- **Returns**: Const reference to the back element
- **Complexity**: Θ(1)
- **Throws**: `std::out_of_range` if deque is empty

### `void clear()`
Removes all elements from the deque.
- **Complexity**: Θ(n)

### `int size() const`
Returns the number of elements in the deque.
- **Returns**: Element count
- **Complexity**: Θ(1)

### `bool isEmpty() const`
Checks if the deque is empty.
- **Returns**: `true` if empty, `false` otherwise
- **Complexity**: Θ(1)

## Design Decisions

### Doubly-Linked List Structure

The deque uses a doubly-linked list where each node has both `prev` and `next` pointers:

```
Head                    Tail
 ↓                       ↓
[1] ← → [2] ← → [3] ← → [4]
```

**Why doubly-linked?**
- Enables efficient operations at both ends
- `popFront()` and `popBack()` both need to unlink the removed node correctly
- Forward (`next`) pointers for traversing toward back
- Backward (`prev`) pointers for efficient tail manipulation

**Comparison:**
- Singly-linked deque would need O(n) to find the node before tail for `popBack()`
- Array-based deque sacrifices memory efficiency

### Node Constructor Micro-Optimization

The node constructor initializes only `value`, omitting initialization of `prev` and `next` pointers:

```cpp
node(T v) : value(v) {}  // Omits prev(nullptr), next(nullptr)
```

This is safe because pointers are always set before use:
- In `pushFront()`: `newNode->prev = nullptr; newNode->next = head;`
- In `pushBack()`: `newNode->prev = tail; newNode->next = nullptr;`

### Critical Invariants

The deque maintains two key invariants:

**Invariant 1: Empty Deque**
When the deque is empty, both `head` and `tail` must be `nullptr`. This invariant is maintained by:
- Constructor: initializes both to `nullptr`
- `popFront()`: nulls `tail` when last element removed
- `popBack()`: nulls `head` when last element removed
- `clear()`: explicitly nulls both pointers

**Invariant 2: Pointer Chain Integrity**
For all non-empty deques:
- `head->prev` is always `nullptr`
- `tail->next` is always `nullptr`
- For every node: `node->next->prev == node` and `node->prev->next == node`

These invariants are maintained in both `pushFront/Back` and verified throughout the copy operations.

### Optimized Assignment Operator

The copy assignment operator uses the same node-reuse strategy as Stack and Queue:
- Reuses existing nodes by updating values (no allocations)
- Only allocates nodes when source is larger
- Only deallocates nodes when source is smaller

For doubly-linked lists, this requires updating both `prev` and `next` pointers correctly during the append and delete phases, making it more complex than singly-linked versions but still efficient.

## Complexity Analysis

| Operation | Time Complexity | Constants | Notes |
|-----------|----------------|-----------|-------|
| `pushFront()` | Θ(1) | 1 allocation, 4 pointer ops | Updates head and handles first-node case |
| `pushBack()` | Θ(1) | 1 allocation, 4 pointer ops | Updates tail and handles first-node case |
| `popFront()` | Θ(1) | 1 deallocation, 2 pointer ops | Unlinking and tail null check |
| `popBack()` | Θ(1) | 1 deallocation, 2 pointer ops | Unlinking and head null check |
| `peekFront()` | Θ(1) | 1 pointer dereference | No allocations |
| `peekBack()` | Θ(1) | 1 pointer dereference | No allocations |
| `clear()` | Θ(n) | n deallocations, ~n pointer ops | Traverse entire list |
| `size()` | Θ(1) | 1 member access | Variable lookup |
| `isEmpty()` | Θ(1) | 1 comparison | Equality check |
| Copy constructor | Θ(n) | n allocations, ~3n pointer ops | Must create nodes and link both directions |
| Assignment (optimized) | Θ(m) where m = source size | Reuses min(n,m), allocates/deallocates diff | Node reuse minimizes heap ops |

**Key Insight**: Doubly-linked operations have higher constant factors (more pointer assignments) than singly-linked, but maintain the same asymptotic complexity. The optimized assignment operator saves the most in equal-size scenarios where no allocations/deallocations occur.

## Why Deque Over Other Structures

| Use Case | Best Structure | Why |
|----------|----------------|-----|
| Only add/remove from one end | Stack or Queue | Simpler, lower overhead |
| Add/remove from both ends | **Deque** | True O(1) at both ends |
| Random access needed | Dynamic Array | Indexed O(1) access |
| Memory-critical | Deque or Singly-linked Queue | No wasted capacity |
| Cache locality critical | Dynamic Array | Contiguous memory |

## Complexity of Doubly-Linked Lists

Doubly-linked structures have higher constant factors than singly-linked alternatives:
- More pointers to update (prev and next)
- More edge cases to handle (both directions)
- More invariants to maintain (pointer chain integrity)

However, this complexity is justified when true O(1) operations at both ends are required.

---

**Part of the Data Structures Portfolio**  
[Previous: Queue](../queue/README.md) | [View Repository](../) | [Next: Hash Table](../hash_table/README.md)
