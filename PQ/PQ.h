#ifndef PQ_H
#define PQ_H


#include <stdexcept>


static int DEFAULT_CAPACITY {4};


template<typename T>
struct element {
    T a;
    int p;

    element() {}
    element(T activity, int priority) : a(activity), p(priority) {}
};


template<typename T>
class PQ {
private:
    element<T>* heap;
    int _capacity;
    int _index;

    void swap(int index1, int index2) {
        element<T> temp = heap[index1];
        heap[index1] = heap[index2];
        heap[index2] = temp;
    }

    void resize(int newCapacity) {
        element<T>* newHeap = new element<T>[newCapacity];

        for (int i = 0; i < _index; i++) newHeap[i] = heap[i];

        delete[] heap;
        heap = newHeap;
        _capacity = newCapacity;
    }

public:
    PQ() : _capacity(DEFAULT_CAPACITY), _index(0) { heap = new element<T>[_capacity]; }

    ~PQ() { delete[] heap; }

    PQ(const PQ<T>& other) 
        : _capacity(other._capacity), _index(other._index) {
            heap = new element<T>[_capacity];

            for (int i = 0; i < _index; i++) heap[i] = other.heap[i];
        }

    PQ<T>& operator=(const PQ<T>& other) {
        // check self-assignment
        if (this == &other) return *this;

        // destroy the old heap
        delete[] heap;
        _capacity = other._capacity;
        _index = other._index;
        heap = new element<T>[_capacity];

        // check empty assignment
        if (other.isEmpty()) return *this;

        // rebuild the heap;
        for (int i = 0; i < _index; i++) heap[i] = other.heap[i];

        return *this;
    }

    void push(T activity, int priority) {
        if (_index >= _capacity) resize(_capacity * 2);

        heap[_index++] = element<T>(activity, priority);

        int i = _index - 1;
        int parent = (i - 1) / 2;

        while (i > 0 && heap[i].p < heap[parent].p) {
            swap(i, parent);

            i = parent;
            parent = (i - 1) / 2;
        }
    }

    T pop() {
        if (isEmpty()) throw std::out_of_range("PQ is empty");
        
        T returnValue = heap[0].a;

        heap[0] = heap[--_index];
        
        int parent {0};
        int leftChild;
        int rightChild;
        int leastChild;

        while (true) {
            leftChild = (2 * parent) + 1;
            rightChild = (2 * parent) + 2;

            if (leftChild >= _index) break;
            else if (rightChild >= _index) leastChild = leftChild;
            else leastChild = (heap[rightChild].p < heap[leftChild].p)? rightChild : leftChild;

            if (heap[parent].p > heap[leastChild].p) {
                swap(parent, leastChild);
                parent = leastChild;
                continue;
            }

            break;
        }
        
        if (_capacity > 4 && _index < (_capacity / 4)) resize(_capacity / 2);

        return returnValue;
    }

    T peek() const { 
        if (isEmpty()) throw std::out_of_range("PQ is empty");

        return heap[0].a;
    }

    void shrinkToFit() { 
        if (_index < DEFAULT_CAPACITY) resize(DEFAULT_CAPACITY);
        else resize(_index);
    }

    int capacity() { return _capacity; }

    int size() const { return _index; }

    bool isEmpty() const { return _index == 0; }

    void clear() { _index = 0; }
};

#endif

