#ifndef BST_H
#define BST_H


#include <stack>
#include <stdexcept>
#include <iostream>


template<typename K, typename V>
struct node {
    K key;
    V value;
    node* right;
    node* left;

    node(K k, V v) : key(k), value(v), right(nullptr), left(nullptr) {}
};


template<typename K, typename V>
class BST {
private:
    node<K, V>* _root;
    int _size;

    node<K, V>* find(K key) const {
        node<K, V>* temp = _root;
        
        while (temp) {
            if (key == temp->key) break;
            
            if (key > temp->key) temp = temp->right;
            else temp = temp->left;
        }

        return temp;
    }

    void cleanup() {
        if (!_root) return;

        std::stack<node<K,V>*> treeStack;
        treeStack.push(_root);

        while (!treeStack.empty()) {
            node<K, V>* temp = treeStack.top();
            treeStack.pop();

            if (temp->left) treeStack.push(temp->left);
            if (temp->right) treeStack.push(temp->right);

            delete temp;
        }
    }

public:
    BST() : _root(nullptr), _size(0) {}

    ~BST() { cleanup(); }

    BST(const BST<K, V>& other) : _root(nullptr), _size(0){
        // check empty assignment
        if (other.isEmpty()) return;

        node<K, V>* temp = other._root;

        std::stack<node<K, V>*> treeStack;
        treeStack.push(temp);

        while (!treeStack.empty()) {
            temp = treeStack.top();
            treeStack.pop();
            put(temp->key, temp->value);

            if (temp->right) treeStack.push(temp->right);
            if (temp->left) treeStack.push(temp->left);
        }
    }

    BST<K, V>& operator=(const BST<K, V>& other) {
        // check self-assignment
        if (this == &other) return *this;

        clear();

        // check empty assignment
        if (other.isEmpty()) return *this;

        node<K, V>* temp = other._root;

        std::stack<node<K, V>*> treeStack;
        treeStack.push(temp);

        while (!treeStack.empty()) {
            temp = treeStack.top();
            treeStack.pop();
            put(temp->key, temp->value);

            if (temp->right) treeStack.push(temp->right);
            if (temp->left) treeStack.push(temp->left);
        }

        return *this;
    }

    void put(K key, V value) {
        // check first node
        if (!_root) {
            _root = new node<K, V>(key, value);
            _size++;
            return;
        }

        node<K, V>* temp = _root;
        
        while (true) {
            // check duplicate keys
            if (key == temp->key) {
                temp->value = value;
                return;
            }

            if (key > temp->key) {
                if (temp->right) temp = temp->right;
                else {
                    temp->right = new node<K, V>(key, value);
                    _size++;
                    return;
                }
            } else {
                if (temp->left) temp = temp->left;
                else {
                    temp->left = new node<K, V>(key, value);
                    _size++;
                    return;
                }
            }
        }
    }

    V get(K key) const {
        node<K, V>* temp = find(key);

        if (temp) return temp->value;
        else throw std::out_of_range("Key not found");
    }

    bool contains(K key) const {
        node<K, V>* temp = find(key);

        if (temp) return true;
        else return false;
    }

    void remove(K key) {
        node<K, V>* temp1 = _root;
        node<K, V>* tracker = _root;

        while (temp1) {
            if (key == temp1->key) break;
            
            if (key > temp1->key) {
                temp1 = temp1->right;

                if (temp1 && key != temp1->key) tracker = tracker->right;
            }
            else {
                temp1 = temp1->left;

                if (temp1 && key != temp1->key) tracker = tracker->left;
            }
        }

        if (!temp1) throw std::out_of_range("Key not found");

        _size--;

        // in case of no right child
        if (!temp1->right) {
            // in case of root node
            if (temp1 == _root) {
                _root = temp1->left;
                delete temp1;
                return;
            }

            if (tracker->right == temp1) tracker->right = temp1->left;
            else tracker->left = temp1->left;

            delete temp1;
            return;
        }

        // in case of no left child
        if (!temp1->left) {
            // in case of root node
            if (temp1 == _root) {
                _root = temp1->right;
                delete temp1;
                return;
            }

            if (tracker->right == temp1) tracker->right = temp1->right;
            else tracker->left = temp1->right;

            delete temp1;
            return;
        }


        // find the in-order successor
        node<K, V>* temp2 = temp1->right;
        tracker = temp1;

        while (temp2->left) {
            tracker = temp2;
            temp2 = temp2->left;
        }

        if (tracker->right == temp2) tracker->right = temp2->right;
        else tracker->left = temp2->right;

        temp1->key = temp2->key;
        temp1->value = temp2->value;

        delete temp2;
        return;
    }

    int size() const { return _size; }

    bool isEmpty() const { return _size == 0; }

    void clear() {
        cleanup();

        _root = nullptr;
        _size = 0;
    }
};

#endif

