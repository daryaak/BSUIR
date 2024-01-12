#pragma once
#include <iostream>
#include <ostream>
#include <iomanip>
#include <windows.h> 
#include "TextFile.h"
#include "BinFile.h"
#include "FileExeption.h"

template <class T>
struct Node
{
public:
	T Data;
	Node<T>* Prev;
	Node<T>* Next;
};

using namespace std;
template <typename T>
class Queue {

private:
	Node<T>* Head;
	Node<T>* Tail;
	int Size;


public:
	Queue()
	{
		Head = nullptr;
		Tail = nullptr;
		Size = 0;
	}

	Queue(const Queue<T>& obj)
	{
		Head = nullptr;
		Tail = nullptr;
		this->Size = 0;
		Node<T>* Temp = obj.Head;
		while (Temp)
		{
			this->PushTail(Temp->Data);
			Temp = Temp->Next;
		}
	}

	~Queue()
	{
		deleteQueue();
	}

	int size() { return this->Size; }

	void PushTail(T value);                                    //�������� � ����� �������
	void PushHead(T value);                                    //�������� � ����� �������

	void output();                                         //����� �������      

	T DeleteFromHead();                                 //������� �� ������

	T DeleteFromTail();                                 //������� �� ������

	T Delete_(int num);

	T& operator[](int num);

	void deleteQueue();

	/*void textfile_in(string fname);
	void textfile_out(string fname);
	void binfile_in(string fname);
	void binfile_out(string fname);*/
	
	bool QueueEmpty();                                     //�������� �� ������������� ��������	

	Queue<T> Poisk(T obj);                                 //����� �� ����������

	Queue<T>& operator=(Queue<T>& other);             //���������� �����

	void HeadTable();                                      //��������� �������

};
