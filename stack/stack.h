#ifndef STACK_H
#define STACK_H


#include <stdexcept>


template<typename T>
struct node {
    T value;
    node* next;

    node(T v) : value(v)/*, next(nullptr)*/ {};
};


template<typename T>
class Stack {
private:
    node<T>* data;
    int size;

    void cleanup() {
        node<T>* temp = data;

        // no need for empty stack check since this loop won't run
        while (temp) {
            data = data->next;
            delete temp;
            temp = data;
        }

        // does not reset size
    }

public:
    Stack() : data(nullptr), size(0) {}
    
    ~Stack() { cleanup(); }

    Stack(const Stack<T>& other) : data(nullptr), size(other.size) {
        // check empty stack
        if (other.isEmpty()) return;

        // connect the first node
        node<T>* newNode = new node<T>(other.data->value);
        newNode->next = data;
        data = newNode;

        node<T>* temp1 = data;
        node<T>* temp2 = other.data->next;

        while (temp2) {
            node<T>* newNode = new node<T>(temp2->value);
            temp1->next = newNode;
            newNode->next = nullptr;
            temp1 = newNode;
            temp2 = temp2->next;
        }
    }
  
    Stack<T>& operator=(const Stack<T>& other) {
        // check self assignment
        if (this == &other) return *this;

        // check empty assignment
        if (other.isEmpty()) {
            clear();
            return *this;
        }

        node<T>* temp2 = other.data;

        // set the first node
        if (data) {
            data->value = temp2->value;
        // in case target is empty
        } else {
            data = new node<T>(temp2->value);
            data->next = nullptr;
        }

        node<T>* temp1 = data;
        node<T>* tracker = data;

        // move forward one node (first node has been set already)
        temp1 = temp1->next;
        temp2 = temp2->next;

        // change node values while avoiding reallocation of memory
        while (temp1 && temp2) {
            temp1->value = temp2->value;
            temp1 = temp1->next;
            temp2 = temp2->next;
            tracker = tracker->next;
        }

        // in case we neeed more nodes
        if (!temp1 && temp2) {
            temp1 = tracker;

            while (temp2) {
                node<T>* newNode = new node<T>(temp2->value);
                temp1->next = newNode;
                temp1 = newNode;
                temp2 = temp2->next;
            }

            temp1->next = nullptr;

        // in case we have excess nodes
        } else if (!temp2 && temp1) {
            node<T>* finalNode = tracker; // track the supposed-to-be final node
            tracker = temp1;

            while (temp1) {
                tracker = tracker->next;
                delete temp1;
                temp1 = tracker;
            }

            finalNode->next = nullptr;
        }

        size = other.size;

        return *this;
    }

    /*
    Stack<T>& operator=(const Stack<T>& other) {
        // check self-assignment
        if (this == &other) return *this;

        // reset the stack
        clear();

        // check empty assignment
        if (other.isEmpty()) return *this;

        // connect the first node
        node<T>* temp2 = other.data;
        node<T>* temp1 = new node<T>(temp2->value);
        temp1->next = nullptr;
        
        data = temp1;

        // connect the rest of the nodes
        temp2 = temp2->next;

        while (temp2) {
            node<T>* newNode = new node<T>(temp2->value);
            temp1->next = newNode;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        temp1->next = nullptr;

        return *this;
    }*/

    void push(T element) {
        node<T>* newNode = new node<T>(element);
        newNode->next = data;
        data = newNode;
        size++;
    }

    T pop() {
        if (size == 0) throw std::out_of_range("Stack is empty");

        T value = data->value;
        
        node<T>* temp = data;
        data = data->next;
        delete temp;
        size--;

        return value;
    }

    const T& peek() const {
        if (size == 0) throw std::out_of_range("Stack is empty");
        
        return data->value;
    }

    bool isEmpty() const { return size == 0; }

    int getSize() const { return size; }

    void clear() {
        cleanup();
        size = 0;
    }
};

#endif

