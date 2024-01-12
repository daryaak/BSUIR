#pragma once

template <class T>
struct Node
{
public:
    T Data;
    Node<T>* Prev;
    Node<T>* Next;
};
