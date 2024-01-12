#pragma once

#include <iostream>
#include <ostream>
#include <iomanip>
//#include  <conio.h>
//#include <fstream>
#include <windows.h> 
#include "TextFile.h"
#include "BinFile.h"
//#include "FileExeption.h"
#include "Node.h"


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
	void textfile_in(string fname);
	void textfile_out(string fname);
	void binfile_in(string fname);
	void binfile_out(string fname);

	void PushTail(T value);                                    //�������� � ����� �������
	void PushHead(T value);                                    //�������� � ����� �������

	void output();                                         //����� �������      

	T DeleteFromHead();                                 //������� �� ������

	T DeleteFromTail();                                 //������� �� ������

	T Delete_(int num);

	T& operator[](int num);

	void deleteQueue();

	Node<T>* begin();                  //������ �������
	Node<T>* end();                    //����� �������

	bool QueueEmpty();                                     //�������� �� ������������� ��������	

	Queue<T> Poisk(T obj);                                 //����� �� ����������

	Queue<T>& operator=(Queue<T>& other);             //���������� �����

	void HeadTable();                                      //��������� �������

};
