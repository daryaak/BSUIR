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
	current = current->next;
	return true;
}

template<class T>
bool Iterator<T>::operator--() {
	if (current->previous != nullptr)
		current = current->previous;
}

template<class T>
void Iterator<T>::operator=(T data) {
	current->data = data;

}

template<class T>
T& Iterator<T>::operator*() {
	return current->data;
}


template<class T>
bool Iterator<T>::operator==(Iterator<T>& ob) {
	return current == ob.current;
}

template<class T>
bool Iterator<T>::operator!=(Iterator<T>& ob) {
	return current != ob.current;
}


