#pragma once
#include "Queue.h"




template <typename T>
void Queue<T>::HeadTable()
{
	T obj;

	obj.HeadOfSheet();
}

template <class T>
T Queue<T>::DeleteFromHead()
{
	T data;
	if (QueueEmpty())
	{
		cout << "Очередь пуста" << endl;
		return data;
	}
	data = Head->Data;
	if (Head == Tail)
	{
		Head = Tail = nullptr;
	}
	else
	{
		Head = Head->Next;
		Head->Prev = nullptr;
	}
	this->Size--;
	return data;
}

template <class T>
T Queue<T>::DeleteFromTail()
{
	T data;
	if (QueueEmpty())
	{
		cout << "Очередь пуста" << endl;
		return data;
	}
	data = Tail->Data;
	Node<T>* n = Tail;
	if (Tail == Head)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Tail = Tail->Prev;
		Tail->Next = nullptr;
	}
	this->Size--;
	return data;
}


template <class T>
void Queue<T>::PushTail(T obj)
{
	if (Head != nullptr)
	{
		Node<T>* n = new Node<T>;
		n->Data = obj;
		n->Next = nullptr;
		n->Prev = Tail;
		Tail->Next = n;
		Tail = n;
	}
	else
	{
		Head = new Node<T>;
		Head->Data = obj;
		Head->Next = nullptr;
		Head->Prev = nullptr;
		Tail = Head;
	}
	this->Size++;
}

template<class T>
void Queue<T>::PushHead(T obj)
{
	if (Head != nullptr)
	{
		Node<T>* n = new Node<T>;
		n->Data = obj;
		n->Next = Head;
		n->Prev = nullptr;
		Head->Prev = n;
		Head = n;
	}
	else
	{
		Head = new Node<T>;
		Head->Data = obj;
		Head->Next = nullptr;
		Head->Prev = nullptr;
		Tail = Head;
	}
	this->Size++;
}

template <class T>
void Queue<T>::output()
{
	if (QueueEmpty())
	{
		cout << "Очередь пуста" << endl;
		return;
	}
	Node<T>* tmpq = Head;
	int i = 1;

	for (tmpq; tmpq != nullptr; tmpq = tmpq->Next)
	{
		cout.setf(ios::left);
		cout << setw(5) << i++ << tmpq->Data << endl;
	}
	cout.setf(ios::left);
}


template <class T>
T Queue<T>::Delete_(int num)
{
	T data;
	if (QueueEmpty())
	{
		cout << "Очередь пуста" << endl;
		return data;
	}
	if (num - 1 == 0)
	{
		DeleteFromHead();
		
	}
	if (num == Size)
	{
		DeleteFromTail();
		
	}
	Node<T>* cur = Head;
	for (int i = 0; i < num - 1; i++)
		cur = cur->Next;
	Node<T>* prev = cur->Prev;
	Node<T>* next = cur->Next;
	data = cur->Data;
	this->Size--;
	prev->Next = next;
	next->Prev = prev;
	delete cur;
	return data;
}


template <class T>
bool Queue<T>::QueueEmpty()
{
	if (Size)
		return false;
	return true;
}

template<class T>
T& Queue<T>::operator[](int num)
{
	Node<T>* cur = Head;
	if (num < 0 || num > Size) return cur->Data;
	for (int i = 0; i < num; i++) { cur = cur->Next; }
	return cur->Data;
}

template <class T>
void Queue<T>::deleteQueue()
{
	while (this->Head)
	{
		this->DeleteFromHead();
	}
}

template <typename T>
Queue<T> Queue<T>::Poisk(T obj)
{
	Queue<T> rez;
	Node<T>* tmp = Tail;
	while (tmp) {
		if (tmp->Data == obj)
			rez.PushTail(tmp->Data);
		tmp = tmp->Prev;
	}
	return rez;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>& other)
{
	this->deleteQueue();
	Node<T>* tmp = other.Head;
	while (tmp) {
		this->PushTail(tmp->Data);
		tmp = tmp->Prev;
	}
	return *this;
}





























//template <typename T>
//void Queue<T>::textfile_out(string fname)
//{
//	TextFile<T> fl_txt(fname);
//	fl_txt.openWriteFile();
//	Node<T>* tmp = Head;
//	while (tmp)
//	{
//		fl_txt.writeFile(tmp->Data);
//		tmp = tmp->Next;
//	}
//}
//
//template <typename T>
//void Queue<T>::textfile_in(string fname)
//{
//	TextFile<T> fl_txt(fname);
//	fl_txt.openReadFile();
//	T temp;
//	while (1)
//	{
//		fl_txt.readFile(temp);
//		if (fl_txt.feof()) break;
//		PushTail(temp);
//	}
//}
//
//template <typename T>
//void Queue<T>::binfile_out(string fname)
//{
//	BinFile<T> fl_bin(fname);
//	fl_bin.openWriteFile();
//	Node<T>* tmp = Head;
//	while (tmp)
//	{
//		fl_bin.writeFile(tmp->Data);
//		tmp = tmp->Next;
//	}
//}
//
//template <typename T>
//void Queue<T>::binfile_in(string fname)
//{
//	BinFile<T> fl_bin(fname);
//	fl_bin.openReadFile();
//	T temp;
//	while (1)
//	{
//		fl_bin.readFile(temp);
//		if (fl_bin.feof()) break;
//		PushTail(temp);
//	}
//}








