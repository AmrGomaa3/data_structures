#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H


#include <stdexcept>
#include <iostream>


template<typename T>
class DynamicArray {
private:
    T* array;
    int size;
    int available;

    void resize(int newSize) {
        T* newArray = new T[newSize];

        for (int i = 0; i < available; i++) newArray[i] = array[i];

        delete[] array;
        array = newArray;
        size = newSize;
    }

public:
    DynamicArray(int s=2) {
        if (s < 1) throw std::invalid_argument("Invalid size");

        array = new T[s];
        size = s;
        available = 0;
    }

    ~DynamicArray() { delete[] array; }

    DynamicArray(const DynamicArray<T>& other) {
        size = other.size;
        available = other.available;
        array = new T[size];

        for (int i = 0; i < other.available; i++) {
            array[i] = other.array[i];
        }
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        // check self assignment
        if (this == &other) return *this;

        // reinitialize the DynamicArray
        delete[] array;

        size = other.size;
        available = other.available;
        array = new T[size];

        for (int i = 0; i < other.available; i++) {
            array[i] = other.array[i];
        }

        return *this;
    }
    
    int getSize() const { return available; }

    bool isEmpty() const { return available == 0; }

    void push(T element) {
        // expand with double capacity if full
        if (available >= size) resize(size * 2);

        array[available++] = element;
    }
    
    T pop() {
        // check empty array
        if (available == 0) throw std::invalid_argument("Array is empty");

        T value = array[--available];

        // shrink with half capacity when 1/4 full
        // prevent shrinking when size < 4
        if (size > 4 && available <= (size / 4)) resize(size / 2);

        return value;
    }
    
    void set(int index, T element) {
        if (index < 0 || index >= available) throw std::out_of_range("Index out of range");

        array[index] = element;
    }

    const T& get(int index) const {
        if (index < 0 || index >= available) throw std::out_of_range("Index out of range");

        return array[index];
    }
    
    void clear() {
        /*
         * the method is slower since it resets the array
         * speed is traded here for memory efficiency
         */

        size = 2; // reset to default size
        available = 0;
        delete[] array; // free the old memory
        array = new T[size]; // reallocate new memory
    }
};


#endif
