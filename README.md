# Data Structures

A collection of C++ implementations of core data structures focused on low-level control, manual memory management, raw pointer manipulations and performance optimizations. Avoids the use of STL containers. Each module includes:

- a clean implementation
- targeted optimizations
- full complexity analysis
- test suite

Available structures:

1. [Dynamic Array](./dynamic_array/)
2. [Stack](./stack/)
3. [Queue](./queue/)
4. [Deque](./deque/)
5. [Hash Table](./hash_table/)
6. [Binary Search Tree](./BST/)
7. [Priority Queue](./PQ/)

## Overview

This repository showcases core CS fundamentals, demonstrating deep understanding of:
- Manual memory management
- Pointer manipulation
- Algorithmic complexity and trade-off analysis
- Performance measurement and optimization techniques

## Featured: Stack Optimization

The Stack implementation includes a benchmarked optimization that reuses existing nodes during assignment instead of deallocating and reallocating:

**Benchmark Results** (10M elements, 10 iterations):
- Equal-size assignment: **4.5x faster**
- Different-size assignment: **2.0-2.1x faster**
- Overall average: **2.58x faster**

See full benchmark methodology [here](./stack/)

## Testing Philosophy

All structures implement the Rule of Three and include comprehensive tests:
- Basic operations (empty, single element, multiple elements)
- Edge cases (empty assignment, self-assignment, boundary conditions)
- Stress testing (10,000 - 1,000,000 elements where applicable)
- Rule of Three validation (copy constructor, assignment operator, destructor)

---

## License

The project is licensed under the MIT License.
See the [LICENSE](./LICENSE) file for license information.
