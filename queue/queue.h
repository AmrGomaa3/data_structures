#ifndef QUEUE_H
#define QUEUE_H


#include <stdexcept>


template<typename T>
struct node {
    T value;
    node<T>* next;

    node(T v) : value(v), next(nullptr) {}
};


template<typename T>
class Queue {
private:
    node<T>* head;
    node<T>* tail;
    int _size;

    void cleanup() {
        node<T>* temp; // no need to assign it here, contains garbage

        while (head) {
            temp = head; // assigned first before any operations
            head = head->next;
            delete temp;
        }
        // loop will stop when head = nullptr

        tail = nullptr;

        // does not reset _size
    }

public:
    Queue() : head(nullptr), tail(nullptr), _size(0) {}

    ~Queue() { cleanup(); }

    Queue(const Queue<T>& other) {
        _size = other._size;

        // check empty queue
        if (other.isEmpty()) {
            head = nullptr;
            tail = nullptr;
            return;
        }

        // connect the first node
        head = new node<T>(other.head->value);
        tail = head;

        // connect rest of nodes
        node<T>* temp = other.head->next;

        while (temp) {
            tail->next = new node<T>(temp->value);
            tail = tail->next;
            temp = temp->next;
        }
    }

    Queue<T>& operator=(const Queue<T>& other) {
        // check self-assignment
        if (this == &other) return *this;

        _size = other._size;

        // check empty queue
        if (other.isEmpty()) {
            cleanup();
            return *this;
        }

        // connect first node
        if (head) head->value = other.head->value;
        else head = new node<T>(other.head->value);

        // connect rest of nodes
        node<T>* temp = other.head->next;
        tail = head->next;
        node<T>* tracker = head;

        // copying values without reallocating memory
        while (temp && tail) {
            tail->value = temp->value;
            tail = tail->next;
            temp = temp->next;
            tracker = tracker->next;
        }

        // in case same size
        if (!temp && !tail) {
            tail = tracker;

        // in case more nodes need to be added
        } else if (temp && !tail) {
            tail = tracker;

            while (temp) {
                tail->next = new node<T>(temp->value);
                temp = temp->next;
                tail = tail->next;
            }

        // in case some nodes need to be deleted
        } else if (tail && !temp) {
            node<T>* temp2; // no need to assign value

            while (tail) {
                temp2 = tail;
                tail = tail->next;
                delete temp2;
            }

            tail = tracker;
            tail->next = nullptr;
        }

        return *this;
    }

    void enqueue(T element) {
        node<T>* newNode = new node<T>(element);
        _size++;

        // in case of first node
        if (!head) {
            head = newNode;
            tail = head;
            return;
        }

        tail->next = newNode;
        tail = newNode;
    }

    T dequeue() {
        if (_size == 0) throw std::out_of_range("Queue is empty");

        node<T>* temp = head;
        T returnValue = head->value;
        head = head->next;
        delete temp;
        _size--;

        // in case queue becomes empty
        if (!head) tail = nullptr;

        return returnValue;
    }

    void clear() {
        cleanup();
        _size = 0;
    }

    const T& peek() const { 
        if (_size == 0) throw std::out_of_range("Queue is empty");

        return head->value;
    }

    int size() const {return _size; }

    bool isEmpty() const { return _size == 0; }
};


#endif

