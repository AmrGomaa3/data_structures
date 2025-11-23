# Hash Table

A hash table implementation using separate chaining with dynamic resizing. This structure maintains predictable performance through controlled load factors and straightforward bucket-chaining behavior.

## Overview

Provides key–value storage with constant-time average operations. Collisions are handled using linked lists, and the table automatically grows or shrinks based on load factor thresholds to keep chain lengths short.

## Features

- Separate chaining with linked lists  
- Automatic resize:
  - Grow when load factor > 0.75  
  - Shrink when < 0.25  
- Key and value lookup  
- Deep-copy semantics (Rule of Three)  
- Stress-tested with 1,000,000 operations

---

## Usage Example

```cpp
#include "hash_table.h"

HashTable<std::string, int> ht;

ht.put("alice", 25);
ht.put("bob", 30);

int x = ht.get("alice");
bool ok = ht.containsKey("bob");

ht.remove("bob");

ht.clear(32);
```

---

## API Overview

### Constructor
```
HashTable(int capacity = 16)
```
Creates a table with the given capacity (minimum 2).

### put(key, value)
Insert or update an entry. May trigger resize.

### get(key)
Return value or throw if absent.

### getOrDefault(key, default)
Lookup without throwing.

### remove(key)
Delete entry or throw if absent. May trigger shrink.

### containsKey(key)
Key existence check.

### containsValue(value)
Full scan for value equality.

### clear(capacity = 16)
Remove everything and optionally reset capacity.

### size(), isEmpty()
Constant-time state queries.

---

## Design Notes

### Collision Handling
Separate chaining using singly linked lists.

### Hash Function
Uses `std::hash<K>` and maps to buckets via modulo.  
Keys must support hashing + equality.

### Load Factor Policy
- Grow at >0.75  
- Shrink at <0.25  
Maintains bounded chain length and prevents resize oscillation.

### Resize Strategy
Rehash all entries because bucket index depends on current capacity. Uses in-place mutation.
> Note: Order of nodes in the chain is reversed after resize

---

## Correct Complexity

```
Operation         Average Case      Worst Case
---------------------------------------------------------
put/get/remove    O(1 + m)          O(n)
containsKey       O(1 + m)          O(n)
containsValue     O(n)              O(n)
clear             O(n)              O(n)
copy/assign       O(n)              O(n)
resize            O(n)              O(n)
```

- *m* = average chain length  
- With uniform hashing and controlled load factor, m remains constant ⇒ Θ(1) average for key-based operations.

---

## Stress Testing

Includes a 1,000,000‑element test covering:
- Repeated expansions  
- Repeated shrink cycles  
- Mixed insertion/deletion  
- Full-chain traversal correctness

Confirms stable performance and absence of memory faults.

---

**Part of the Data Structures Portfolio**  
[Previous: Deque](../deque/README.md) | [View Repository](../) | [Next: BST](../BST/README.md)
