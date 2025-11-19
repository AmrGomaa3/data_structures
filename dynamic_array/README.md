# Dynamic Array

A self-resizing array implementation that automatically manages capacity as elements are added or removed.

## Overview

The Dynamic Array provides a dynamic alternative to fixed-size arrays, automatically expanding when full and shrinking when underutilized. It achieves amortized O(1) push and pop operations through geometric resizing.

## Usage

```cpp
#include "dynamic_array.h"

// Create with default capacity (2)
DynamicArray<int> arr;

// Create with specific initial capacity
DynamicArray<int> arr2(100);

// Add elements
arr.push(10);
arr.push(20);
arr.push(30);

// Access by index
int value = arr.get(1);         // Returns 20
arr.set(1, 25);                 // Update index 1 to 25

// Remove last element
int last = arr.pop();           // Returns 30

// Query state
std::cout << arr.getSize();     // Number of elements
std::cout << arr.isEmpty();     // Check if empty

// Clear all elements
arr.clear();
```

## Operations

### `void push(T element)`
Adds an element to the end of the array.
- **Complexity**: Amortized O(1), worst case O(n) when resizing
- **Note**: Automatically doubles capacity if array is full

### `T pop()`
Removes and returns the last element.
- **Returns**: The removed element
- **Complexity**: Amortized O(1), worst case O(n) when shrinking
- **Throws**: `std::invalid_argument` if array is empty
- **Note**: Automatically shrinks capacity when 1/4 full

### `const T& get(int index) const`
Returns the element at the specified index.
- **Parameters**: `index` - Zero-based position
- **Returns**: Const reference to the element
- **Complexity**: O(1)
- **Throws**: `std::out_of_range` if index is invalid

### `void set(int index, T element)`
Updates the value at the specified index.
- **Parameters**: 
  - `index` - Zero-based position
  - `element` - New value to store
- **Complexity**: O(1)
- **Throws**: `std::out_of_range` if index is invalid

### `void clear()`
Removes all elements and resets to default capacity.
- **Complexity**: O(n)
- **Note**: Deallocates current array and allocates new empty default-sized array

### `int getSize() const`
Returns the number of elements currently in the array.
- **Returns**: Element count
- **Complexity**: O(1)

### `bool isEmpty() const`
Checks if the array contains any elements.
- **Returns**: `true` if empty, `false` otherwise
- **Complexity**: O(1)

## Design Decisions

### Growth Strategy: Geometric Doubling

The array uses **geometric growth** by doubling capacity when full, rather than growing by a fixed amount. This ensures amortized O(1) push operations.

### Shrinking Strategy: 1/4 Load Factor Threshold

The array only shrinks when the load factor drops to **25% (1/4 full)**, not 50%. This prevents **thrashing** - the scenario where alternating pushes and pops trigger constant reallocation.

If we shrunk at 50%, alternating operations around the threshold would repeatedly resize.

### Clear Behavior: Deallocation vs. Fast Reset

The `clear()` method **deallocates and reallocates** rather than just resetting the element count. This design choice prioritizes memory efficiency over speed.

**Tradeoff**: Slower `clear()`, but guaranteed memory release. Useful when arrays may sit empty for extended periods.

## Complexity Analysis

| Operation | Average Case | Worst Case | Notes |
|-----------|--------------|------------|-------|
| `push()` | O(1) | O(n) | Amortized O(1) due to doubling strategy |
| `pop()` | O(1) | O(n) | Amortized O(1) due to 1/4 shrink threshold |
| `get()` | O(1) | O(1) | Direct array indexing |
| `set()` | O(1) | O(1) | Direct array indexing |
| `clear()` | O(n) | O(n) | Deallocates entire array |
| `getSize()` | O(1) | O(1) | Member variable access |
| `isEmpty()` | O(1) | O(1) | Member variable comparison |

**Space Complexity**: O(n) where n is the number of elements. Actual memory usage ranges from n to 2n due to geometric growth.

## Implementation Notes

### No Move Semantics
The current implementation uses copy semantics for all operations. Move semantics were intentionally omitted to keep the implementation focused on core dynamic array concepts without the additional complexity of rvalue references and move constructors.

### Minimum Capacity
The array maintains a minimum capacity of 2 elements and will not shrink below this threshold (enforced by `size > 4 && available <= size/4` check in `pop()`).

---

**Part of the Data Structures Portfolio**  
[View Repository](../) | [Next: Stack](../stack/README.md)
