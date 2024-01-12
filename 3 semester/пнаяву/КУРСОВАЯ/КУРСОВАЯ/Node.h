#pragma once

template <class T>
struct Node
{
public:
    T data;
    Node<T>* previous;
    Node<T>* next;
};
