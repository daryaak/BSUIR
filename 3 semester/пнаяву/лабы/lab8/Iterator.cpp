#include "Iterator.h"


template<class T>
Iterator<T>::Iterator(Node<T>* temp) {
	current = temp;
}

template<class T>
Iterator<T>::~Iterator() {

}

template<class T>
bool Iterator<T>::operator++() {
	if (current == nullptr) return false;
	current = current->Next;
	return true;
}

template<class T>
bool Iterator<T>::operator--() {
	if (current->Prev != nullptr)
		current = current->Prev;
}

template<class T>
void Iterator<T>::operator=(T data) {
	current->Data = data;

}

template<class T>
T& Iterator<T>::operator*() {
	return current->Data;
}


template<class T>
bool Iterator<T>::operator==(Iterator<T>& ob) {
	return current == ob.current;
}

template<class T>
bool Iterator<T>::operator!=(Iterator<T>& ob) {
	return current != ob.current;
}


