#pragma once
#include "Queue.h"
#include "Iterator.cpp"


template <class T>
Node<T>* Queue<T>::begin()
{
	return Head;
}

template <class T>
Node<T>* Queue<T>::end()
{
	if (Tail != nullptr) return Tail->next;
	return Tail;
}

template<class T>
void Queue<T>::pushHead(T obj)
{
	if (Head == nullptr)
	{
		Head = new Node<T>;
		Head->data = obj;
		Head->next = nullptr;
		Head->previous = nullptr;
		Tail = Head;
		Size++;
	}
	else
	{
		auto* n = new Node<T>;
		n->data = obj;
		n->next = Head;
		n->previous = nullptr;
		Head->previous = n;
		Head = n;
		Size++;
	}
}

template <typename T>
bool Queue<T>::isEmpty() {
	if (Size)
		return false;
	return true;
}


template<class T>
void Queue<T>::pushTail(T obj)
{
	if (Head == nullptr) {
		Head = new Node<T>;
		Head->data = obj;
		Head->next = nullptr;
		Head->previous = nullptr;
		Tail = Head;
		Size++;
	}
	else {
		auto* n = new Node<T>;
		n->data = obj;
		n->next = nullptr;
		n->previous = Tail;
		Tail->next = n;
		Tail = n;
		Size++;
	}
}

template<class T>
T Queue<T>::popHead()
{
	if (isEmpty())
	{
		cout << "Очередь пуста" << endl;
		return T();
	}
	T data = Head->data;
	
	if (Head != Tail) {
		Head = Head->next;
		Head->previous = nullptr;
		Node<T>* tmp = Head;
	}
	else 
	{ Head = Tail = nullptr; }
	Size--;
	return data;
}
template<class T>
void Queue<T>::push(T obj, int num)
{
	if (!Head)								//Если очередь пуста
	{
		pushHead(obj);
		return;
	}

	Node<T>* n = new Node<T>;
	n->data = obj;
	Node<T>* cur = Head;
	for (int i = 0; i < num - 1 && i < Size - 1; i++)
		cur = cur->next;
	if (!cur)								//Если введеное число больше имеющегося кол-ва узлов
	{
		pushTail(obj);
		return;
	}

	if (cur == Head)						//Если в очереди только 1 элемент
	{
		n->next = Head;
		Head->previous = n;
		Head = n;
		Size++;
		return;
	}

	n->next = cur;
	n->previous = cur->previous;
	cur->previous->next = n;
	cur->previous = n;
	Size++;
}

template<class T>
T Queue<T>::pop(int num)
{
	if (isEmpty())
	{
		cout << "Очередь пуста" << endl;
		return T();
	}
	if (num-1 == 0) return popHead();
	if (num == Size) return popTail();
	Node<T>* cur = Head;
	for (int i = 0; i < num-1; i++)
		cur = cur->next;
	Node<T>* prev = cur->previous;
	Node<T>* next = cur->next;
	T data = cur->data;
	Size--;
	prev->next = next;
	next->previous = prev;
	delete cur;
	return data;

}

template<class T>
T Queue<T>::popTail()
{

	if (isEmpty())
	{
		cout << "Очередь пуста" << endl;
		return T();
	}
	T data = Tail->data;
	Node<T>* n = Tail;
	if (Tail != Head) {
		Tail = Tail->previous;
		Tail->next = nullptr;
	}
	else { Head = Tail = nullptr; }
	delete n;
	Size--;
	return data;
}

template<class T>
T& Queue<T>::operator[](int num)
{
	Node<T>* cur = Head;
	if (num < 0 || num > Size) return cur->data;
	for (int i = 0; i < num; i++) { cur = cur->next; }
	return cur->data;
}

template <typename T>
void Queue<T>::HeadTable()
{
	T obj;
	obj.HeadOfSheet();
}

template <typename T>
void Queue<T>::output()
{

	if (isEmpty())
	{
		cout << "Очередь пуста" << endl;
		return;
	}
	Node<T>* tmpq = Head;
	int i = 1;
	
	for (tmpq; tmpq != nullptr; tmpq = tmpq->next)
	{
		cout.setf(ios::left);
		cout <<setw(5)<<i++<< tmpq->data << endl;
	}
	cout.setf(ios::left);
}

template <typename T>
void Queue<T>::deleteQueue()
{
	while (this->Head)
	{
		this->popHead();
	}
}
template <typename T>
void Queue<T>::file_out1(string fname)
{
		TextFile<T> fl_txt(fname);
		fl_txt.openWriteFile1();
		Node<T>* tmp = Head;
		T a;
		fl_txt.writeFile(a);
		while (tmp)
		{
			fl_txt.writeFile(tmp->data);
			tmp = tmp->next;
		}
}
template <typename T>
void Queue<T>::file_out2(string fname)
{
	TextFile<T> fl_txt(fname);
	fl_txt.openWriteFile2();
	Node<T>* tmp = Head;
	while (tmp)
	{
		fl_txt.writeFile(tmp->data);
		tmp = tmp->next;
	}
}

template <typename T>
void Queue<T>::file_in(string fname)
{
	TextFile<T> fl_txt(fname);
	fl_txt.openReadFile();
	T temp;
	while (1)
	{
		fl_txt.readFile(temp);
		if (fl_txt.feof()) break;
		pushTail(temp);
	}
}

