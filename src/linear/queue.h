/*
Jacobo Soffer Levy
A01028653
Queue linear data structure
implementation.
Modified: 13/04/21
*/
#ifndef QUEUE_H
#define QUEUE_H
#include "linked_list.h"

template<class T>
class Queue {
public:
    Queue();
    void push(T data);
    T poll();
    T peek();
    bool isEmpty();
    int size();
private:
    LinkedList<T> queue;
};


template<class T>
Queue<T>::Queue() {}

template<class T>
void Queue<T>::push(T data) {
    queue.addFirst(data);
}

template<class T>
T Queue<T>::poll() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    T e = queue[queue.getSize() - 1]->getData();
    queue.deleteAt(queue.getSize() - 1);
    return e;
}

template<class T>
T Queue<T>::peek() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    return queue[queue.getSize() - 1]->getData();
}

template<class T>
bool Queue<T>::isEmpty() {
    return queue.getSize() == 0;
}

template<class T>
int Queue<T>::size() {
    return queue.getSize();
}

#endif