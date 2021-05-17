/*
Jacobo Soffer Levy
A01028653
Stack linear data structure
implementation.
Modified: 16/05/21
*/
#ifndef STACK_H
#define STACK_H
#include "linked_list.h"

template<class T>
class Stack {
public:
    Stack();
    void push(T data);
    T pop();
    T peek();
    bool isEmpty();
    int size();
private:
    LinkedList<T> stack;
};


template<class T>
Stack<T>::Stack() {}

template<class T>
void Stack<T>::push(T data) {
    stack.pushBack(data);
}

template<class T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    T e = stack[stack.getSize() - 1]->getData();
    stack.deleteAt(stack.getSize() - 1);
    return e;
}

template<class T>
T Stack<T>::peek() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    return stack[stack.getSize() - 1]->getData();
}

template<class T>
bool Stack<T>::isEmpty() {
    return stack.getSize() == 0;
}

template<class T>
int Stack<T>::size() {
    return stack.getSize();
}

#endif