#pragma once
#include "Node.h"

//��������� ����� ��������
template<class T>
class Iterator 
{
public:
	Node<T>* current;                  //��������� �� ������� �������
	Iterator(Node<T>* temp = nullptr); //����������� ��-��������
	~Iterator();                       //����������
	T& operator*();                    //������������
	void operator=(T data);            //��������� ��������� ������������ �������
	bool operator++();                 //���������� ��������� ++
	bool operator--();                 //���������� ��������� --
	bool operator==(Iterator<T>& ob);  //���������� ��������� == ��� ��������� � ����������
	bool operator!=(Iterator<T>& ob);  
};
