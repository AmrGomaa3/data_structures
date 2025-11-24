# Binary Search Tree

A binary search tree implementation providing O(log n) average-case operations for key-value storage with ordered traversal support.

## Overview

The Binary Search Tree (BST) is a hierarchical data structure where each node has at most two children (left and right). The BST property ensures that for any node, all keys in the left subtree are smaller and all keys in the right subtree are larger.

This implementation is unbalanced, meaning the tree structure depends on insertion order and can degrade to O(n) in worst-case scenarios.

## Features

- **O(log n) average-case** search, insert, and delete
- **O(n) worst-case** when tree becomes skewed
- **Key-value storage** - Associate values with keys
- **Duplicate key handling** - Updates value for existing keys
- **Comprehensive testing** - 22 test cases

## Usage

```cpp
#include "BST.h"

// Create an empty BST
BST<int, std::string> bst;

// Insert key-value pairs
bst.put(50, "fifty");
bst.put(30, "thirty");
bst.put(70, "seventy");
bst.put(20, "twenty");
bst.put(40, "forty");

// Retrieve values
std::string val = bst.get(30);     // Returns "thirty"

// Check for keys
bool exists = bst.contains(40);    // Returns true

// Remove entries
bst.remove(30);

// Query state
std::cout << bst.size();           // Number of entries
std::cout << bst.isEmpty();        // Check if empty

// Clear all entries
bst.clear();
```

## Operations

### Constructor

```cpp
BST()
```
Creates an empty binary search tree.

### `void put(K key, V value)`
Inserts a new key-value pair or updates an existing key.
- **Parameters**: 
  - `key` - The key to insert/update
  - `value` - The value to associate with the key
- **Complexity**: O(log n) average, O(n) worst case
- **Note**: If key already exists, updates the value without changing tree structure

### `V get(K key) const`
Retrieves the value associated with a key.
- **Parameters**: `key` - The key to look up
- **Returns**: The value associated with the key
- **Complexity**: O(log n) average, O(n) worst case
- **Throws**: `std::out_of_range` if key not found

### `bool contains(K key) const`
Checks if a key exists in the tree.
- **Parameters**: `key` - The key to check
- **Returns**: `true` if key exists, `false` otherwise
- **Complexity**: O(log n) average, O(n) worst case

### `void remove(K key)`
Removes a key-value pair from the tree.
- **Parameters**: `key` - The key to remove
- **Complexity**: O(log n) average, O(n) worst case
- **Throws**: `std::out_of_range` if key not found
- **Note**: Uses in-order successor for nodes with two children

### `void clear()`
Removes all entries from the tree.
- **Complexity**: O(n)

### `int size() const`
Returns the number of key-value pairs in the tree.
- **Returns**: Entry count
- **Complexity**: O(1)

### `bool isEmpty() const`
Checks if the tree is empty.
- **Returns**: `true` if no entries, `false` otherwise
- **Complexity**: O(1)

## Complexity Analysis

| Operation | Average Case | Worst Case | Space | Notes |
|-----------|-------------|-----------|-------|-------|
| `put()` | O(log n) | O(n) | O(1) | Balanced vs skewed tree |
| `get()` | O(log n) | O(n) | O(1) | Path length from root |
| `remove()` | O(log n) | O(n) | O(1) | Includes finding node + successor |
| `contains()` | O(log n) | O(n) | O(1) | Same as `get()` |
| `clear()` | O(n) | O(n) | O(n) | Stack holds up to n nodes |

---

**Part of the Data Structures Portfolio**  
[Previous: Hash Table](../hash_table/README.md) | [View Repository](../) | [Next: Priority Queue](../priority_queue/README.md)
