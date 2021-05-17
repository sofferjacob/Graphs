/*
Jacobo Soffer Levy
A01028653
Doubly Linked List
implementation.
Used to store the records
Modified: 13/04/21
*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <functional>
#include <stdexcept>
#include <iostream>
#include "node.h"

template<class T>
class Queue;

template<class T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    // Returns the size of the list
    int getSize();
    // Deletes the list's elements and resets it.
    void clear();
    // Adds an element to the begging of the list
    void addFirst(T);
    // Adds an element to the end of the list
    void pushBack(T);
    // Deletes an element at the specified index
    bool deleteAt(int);
    // Updates an element at the specified index
    void updateAt(T, int);
    // Prints the entire list
    void print(int, int);
    // Performs an operation on the node at the specified index
    void opAt(std::function<void(Node<T>*)>, int);
    // Executes a function on every node of the list (or on every node starting from the 'from' parameter)
    void forEach(std::function<void(Node<T>*, int)> f, int from = 0);
    // Retrieves a node from the list. Returns the node at the specified index.
    Node<T>* at(int);
    // same as at
    Node<T>* operator[](int);
private:
    // Pounter to the first node on the list
    Node<T>* head;
    // Pointer to the last node on the list
    Node<T>* tail;
    // Size of the list
    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    head = tail = nullptr;
    size = 0;
}

template<class T>
int LinkedList<T>::getSize() {
    return size;
}

template<class T>
void LinkedList<T>::pushBack(T data) {
    if (head == nullptr) {
        head = new Node<T>(data, nullptr, nullptr);
        tail = head;
        size += 1;
        return;
    }
    Node<T>* node = new Node<T>(data, tail, nullptr);
    tail->setNext(node);
    tail = node;
    size++;
}

template<class T>
void LinkedList<T>::addFirst(T data) {
    if (head == nullptr) {
        head = new Node<T>(data, nullptr, nullptr);
        tail = head;
        size += 1;
        return;
    }
    Node<T>* node = new Node<T>(data, nullptr, head);
    head->setPrev(node);
    head = node;
    size++;
}


template<class T>
void LinkedList<T>::opAt(std::function<void(Node<T>*)> f, int i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (i == 0) {
        f(head);
        return;
    }
    if (i == size - 1) {
        f(tail);
        return;
    }
    Node<T>* result;
    if (i < (size - 1) / 2) {
        result = head;
        for (int j = 0; j < i; j++) {
            result = result->getNext();
        }
    }
    result = tail;
    for (int j = size - 1; j > i; j--) {
        result = result->getPrev();
    }
    f(result);
}

template<class T>
void LinkedList<T>::forEach(std::function<void(Node<T>*, int)> f, int from) {
    if (from >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node<T>* result;
    if (from < (size - 1) / 2) {
        result = head;
        for (int j = from; j < size; j++) {
            f(result, j);
            result = result->getNext();
        }
        return;
    }
    result = tail;
    for (int j = size - 1; j > from - 1; j--) {
        f(result, j);
        result = result->getPrev();
    }
}

template<class T>
Node<T>* LinkedList<T>::at(int i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (i == 0) {
        return head;
    }
    if (i == size - 1) {
        return tail;
    }
    Node<T>* result;
    if (i < (size - 1) / 2) {
        result = head;
        for (int j = 0; j < i; j++) {
            result = result->getNext();
        }
    }
    result = tail;
    for (int j = size - 1; j > i; j--) {
        result = result->getPrev();
    }
    return result;
}

template<class T>
Node<T>* LinkedList<T>::operator[](int i) {
    return at(i);
}

template<class T>
bool LinkedList<T>::deleteAt(int i) {
    if (size == 1 && i == 0) {
        delete head;
        size--;
        clear();
        return true;
    }
    opAt([this, i](Node<T>* e) {
        Node<T>* prev = e->getPrev();
        Node<T>* next = e->getNext();
        if (prev != nullptr) {
            prev->setNext(next);
        }
        else {
            // Change head
            head = next;
            head->setPrev(nullptr);
        }
        if (next != nullptr) {
            next->setPrev(prev);
        }
        else {
            tail = prev;
        }
        size--;
        delete e;
        }, i);
    return true;
}

template<class T>
void LinkedList<T>::print(int from, int to) {
    for (int i = from; i <= to; i++) {
        std::cout << (at(i)->getData()) << std::endl;
    }
}

template<class T>
void LinkedList<T>::clear() {
    // Free the memory
    Node<T>* current = head;
    for (int i = 0; i < size; i++) {
        Node<T>* temp = current;
        current = temp->getNext();
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
LinkedList<T>::~LinkedList() {
    clear();
}

#endif