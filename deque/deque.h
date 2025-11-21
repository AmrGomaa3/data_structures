#ifndef DEQUE_H
#define DEQUE_H


#include <stdexcept>


template<typename T>
struct node {
    T value;
    node<T>* prev;
    node<T>* next;

    node(T v) : value(v) {}
};


template<typename T>
class Deque {
private:
    node<T>* head;
    node<T>* tail;
    int _size;

    void cleanup() {
        while (head) {
            tail = head;
            head = head->next;
            delete tail;
        }
        // leaves dangling pointers and does not reset _size
    }

public:
    Deque() : head(nullptr), tail(nullptr), _size(0) {}

    ~Deque() { cleanup(); }

    Deque(const Deque<T>& other) : _size(other._size) {
        // check empty assignment
        if (other._size == 0) {
            head = nullptr;
            tail = nullptr;
            return;
        }

        // create the first node
        head = new node<T>(other.head->value);

        // create rest of nodes
        node<T>* temp1 = head;
        node<T>* tracker = head;
        node<T>* temp2 = other.head->next;

        while (temp2) {
            temp1->next = new node<T>(temp2->value);
            temp1 = temp1->next;
            temp1->prev = tracker;
            tracker = tracker->next;
            temp2 = temp2->next;
        }

        tail = temp1;

        tail->next = nullptr;
        head->prev = nullptr;
    }

    Deque<T>& operator=(const Deque<T>& other) {
        // check self-assignment
        if (this == &other) return *this;

        _size = other._size;

        // check empty assignment
        if (other._size == 0) {
            clear();
            return *this;
        }

        // copy first node
        if (head) head->value = other.head->value;
        else head = new node<T>(other.head->value);

        head->next = nullptr;

        // copy rest of nodes
        node<T>* temp1 = head->next;
        node<T>* tracker = head;
        node<T>* temp2 = other.head->next;

        // copy nodes without memory reallocation
        while (temp1 && temp2) {
            temp1->value = temp2->value;
            temp1 = temp1->next;
            temp2 = temp2->next;
            tracker = tracker->next;
        }

        // in case more nodes needed
        if (!temp1 && temp2) {
            temp1 = tracker;

            while (temp2) {
                temp1->next = new node<T>(temp2->value);
                temp1 = temp1->next;
                temp1->prev = tracker;
                tracker = tracker->next;
                temp2 = temp2->next;
            }

        // in case of excess nodes
        } else if (!temp2 && temp1) {
            node<T>* temp3;

            while (temp1) {
                temp3 = temp1;
                temp1 = temp1->next;
                delete temp3;
            }
        }

        tail = tracker;
        tail->next = nullptr;
        head->prev = nullptr;

        return *this;
    }

    void pushFront(T element) {
        node<T>* newNode = new node<T>(element);
        newNode->prev = nullptr;
        newNode->next = head;

        if (head) head->prev = newNode;

        head = newNode;

        // in case of first node
        if (!tail) tail = newNode;
        
        _size++;
    }

    T popFront() {
        if (_size == 0) throw std::out_of_range("Deque is empty");

        T returnValue = head->value;

        node<T>* temp = head;
        head = head->next;
        delete temp;

        // unlink the popped node
        if (head) head->prev = nullptr;

        // in case deque becomes empty
        if (!head) tail = nullptr;

        _size--;

        return returnValue;
    }

    const T& peekFront() const { 
        if (_size == 0) throw std::out_of_range("Deque is empty");

        return head->value;
    }

    void pushBack(T element) {
        node<T>* newNode = new node<T>(element);
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail) tail->next = newNode;

        tail = newNode;

        // in case of first node
        if (!head) head = newNode;

        _size++;
    }

    T popBack() {
        if (_size == 0) throw std::out_of_range("Deque is empty");
        
        T returnValue = tail->value;

        node<T>* temp = tail;
        tail = tail->prev;
        delete temp;

        // unlinke the popped node
        if (tail) tail->next = nullptr;

        // in case deque becomes empty
        if (!tail) head = nullptr;

        _size--;

        return returnValue;
    }

    const T& peekBack() const { 
        if (_size == 0) throw std::out_of_range("Deque is empty");

        return tail->value;
    }

    void clear() {
        cleanup();

        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    int size() { return _size; }

    bool isEmpty() { return _size == 0; }
};

#endif
