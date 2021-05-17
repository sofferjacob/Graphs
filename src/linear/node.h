#ifndef LL_NODE_H
#define LL_NODE_H

template<class T>
class Node {
public:
    Node(T, Node*, Node*);
    T getData();
    Node* getNext();
    Node* getPrev();
    void setNext(Node*);
    void setPrev(Node*);
    void operator =(T);
private:
    T data;
    Node* prev;
    Node* next;
};

template<class T>
Node<T>::Node(T data, Node* prev, Node* next) :
    data(data),
    next(next),
    prev(prev) {}

template<class T>
T Node<T>::getData() {
    return data;
}

template<class T>
Node<T>* Node<T>::getNext() {
    return next;
}

template<class T>
void Node<T>::setNext(Node* n) {
    next = n;
}

template<class T>
Node<T>* Node<T>::getPrev() {
    return prev;
}

template<class T>
void Node<T>::setPrev(Node* n) {
    prev = n;
}

template<class T>
void Node<T>::operator=(T newData) {
    data = newData;
}

#endif