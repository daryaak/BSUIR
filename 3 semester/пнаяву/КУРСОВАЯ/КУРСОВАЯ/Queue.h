#pragma once
#include <iostream>
#include <ostream>
#include "TextFile.h"
#include <windows.h>
#include "Node.h"
using namespace std;
template <class T>
class Queue {
private:
    Node<T>* Head;                            //������ �������
    Node<T>* Tail;                            //����� �������
    int Size;                                 //������ �������
public:
    Queue()
    {
        Head = nullptr;
        Tail = nullptr;
        Size = 0;
    };

    Queue(const Queue<T>& obj)
    {
        Head = nullptr;
        Tail = nullptr;
        this->Size = 0;
        Node<T>* Temp = obj.Head;
        while (Temp)
        {
            this->pushHead(Temp->data);
            Temp = Temp->next;
        }
    }
    ~Queue()
    {
        while (this->Head)
        { 
            this->popHead();
        }
    }    
    int size() { return this->Size; }  //��������� �������
    void pushHead(T obj);              //�������� � ������
    void push(T obj, int num);         //�������� � ������ �������
    bool isEmpty();                    //�������� �� �������������
    void pushTail(T obj);              //�������� � �����
    T popHead();                       //������� �� ������
    void deleteQueue();
    T pop(int num);                    //������� �� �������
    T popTail();                       //������� � ������
    T& operator[](int num);            //���������� []
    Node<T>* begin();                  //������ �������
    Node<T>* end();                    //����� �������
    void output();                     //����� �������
    void file_in(string fname);        //������ �� �����
    void file_out1(string fname);      //������ � ����
    void file_out2(string fname);      //�������� � ����
    void HeadTable();                  //����� �������
};

