#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include <stdexcept>
#include <functional>
#include <iostream>


static const int DEFAULT_CAPACITY {16};
static const float MIN_LF {0.25f};
static const float MAX_LF {0.75f};


template<typename K, typename V>
struct node {
    K key;
    V value;
    node* next;

    node(K k, V v) : key(k), value(v) {}
};


template<typename K, typename V>
class HashTable {
private:
    node<K, V>** table;
    int capacity;
    int _size;

    std::size_t hash(K key) const {
        std::hash<K> hasher;

        return hasher(key) % capacity;
    }

    void resize(int newCapacity) {
        node<K, V>** newTable = new node<K, V>*[newCapacity]();

        int oldCapacity = capacity;
        capacity = newCapacity;

        node<K, V>* temp;

        for (int i = 0; i < oldCapacity; i++) {
            temp = table[i];

            while (temp) {
                std::size_t index = hash(temp->key);

                // mutate in-place
                table[i] = temp->next;
                temp->next = newTable[index];
                newTable[index] = temp;

                temp = table[i];
            }
        }

        delete[] table;
        table = newTable;
    }

    void cleanup() {
        node<K, V>* temp1;
        node<K, V>* temp2;

        for (int i = 0; i < capacity; i++) {
            temp1 = table[i];

            while (temp1) {
                temp2 = temp1;
                temp1 = temp1->next;
                delete temp2;
            }
        }

        delete[] table;
    }

public:
    HashTable(int c = DEFAULT_CAPACITY) : _size(0) {
        if (c <= 1) throw std::invalid_argument("Starting capacity must be at least 2");

        capacity = c;
        table = new node<K, V>*[capacity]();
    }

    ~HashTable() { cleanup(); }

    HashTable(const HashTable<K, V>& other) 
        : _size(other._size), capacity(other.capacity), table(new node<K, V>*[other.capacity]()) { 
        node<K, V>* temp1;
        node<K, V>* temp2;

        for (int i = 0; i < capacity; i++) {
            if (other.table[i]) {
                // copy first node in the chain
                temp1 = other.table[i];
                node<K, V>* newNode = new node<K, V>(temp1->key, temp1->value);
                newNode->next = nullptr;
                table[i] = newNode;
                temp2 = newNode;
                temp1 = temp1->next;

                // copy rest of nodes
                while (temp1) {
                    temp2->next = new node<K, V>(temp1->key, temp1->value);
                    temp2 = temp2->next;
                    temp1 = temp1->next;
                }
            }
        }
    }

    HashTable<K, V>& operator=(const HashTable<K, V>& other) {
        // check self-assignment
        if (this == &other) return *this;

        cleanup();
        capacity = other.capacity;
        table = new node<K, V>*[capacity]();

        node<K, V>* temp1;
        node<K, V>* temp2;

        for (int i = 0; i < capacity; i++) {
            if (other.table[i]) {
                // copy first node in the chain
                temp1 = other.table[i];
                node<K, V>* newNode = new node<K, V>(temp1->key, temp1->value);
                newNode->next = nullptr;
                table[i] = newNode;
                temp2 = newNode;
                temp1 = temp1->next;

                // copy rest of nodes
                while (temp1) {
                    temp2->next = new node<K, V>(temp1->key, temp1->value);
                    temp2 = temp2->next;
                    temp1 = temp1->next;
                }
            }
        }

        _size = other._size;

        return *this;
    }

    void put(K key, V value) {
        std::size_t index = hash(key);

        if (static_cast<double>(_size) / capacity > MAX_LF) {
            resize(capacity * 2);
            index = hash(key);
        }

        node<K, V>* temp = table[index];

        while (temp) {
            if (temp->key == key) {
                temp->value = value;
                return;
            }

            temp = temp->next;
        }

        node<K, V>* newNode = new node<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        
        _size++;
    }

    V get(K key) const {
        std::size_t index = hash(key);

        node<K, V>* temp = table[index];

        while (temp) {
            if (temp->key == key) return temp->value;

            temp = temp->next;
        }

        throw std::out_of_range("Key not found");
    }

    V getOrDefault(K key, V value) {
        try {
            return get(key);
        } catch (const std::out_of_range&) {
            return value;
        }
    }

    void remove(K key) {
        std::size_t index = hash(key);
        bool removed {false};

        node<K, V>* temp = table[index];

        // in case of first node
        if (temp && temp->key == key) {
            table[index] = temp->next;
            delete temp;
            removed = true;

        } else{
            node<K, V>* trail = temp;
            temp = temp->next;

            while (temp) {
                if (temp->key == key) {
                    trail->next = temp->next;
                    delete temp;
                    removed = true;
                    break;
                }

                temp = temp->next;
                trail = trail->next;
            }
        }

        if (removed) {
            _size--;

            if (capacity > DEFAULT_CAPACITY && static_cast<double>(_size) / capacity < MIN_LF) resize(capacity / 2);

            return;
        }

        throw std::out_of_range("Key not found");
    }

    bool containsKey(K key) const {
        std::size_t index = hash(key);

        node<K, V>* temp = table[index];

        while (temp) {
            if (temp->key == key) return true;

            temp = temp->next;
        }

        return false;
    }

    bool containsValue(V value) const {
        node<K, V>* temp;

        for (int i = 0; i < capacity; i++) {
            temp = table[i];
            
            while (temp) {
                if (temp->value == value) return true;

                temp = temp->next;
            }
        }

        return false;
    }

    int size() const { return _size; }

    bool isEmpty() const { return _size == 0; }

    void clear(int c = DEFAULT_CAPACITY) {
        if (c <= 1) throw std::invalid_argument("Starting capacity must be at least 2");

        cleanup();

        table = new node<K, V>*[c]();
        _size = 0;
        capacity = c;
    }
};

#endif

