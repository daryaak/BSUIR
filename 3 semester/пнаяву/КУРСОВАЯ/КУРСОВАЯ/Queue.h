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
    Node<T>* Head;                            //голова очереди
    Node<T>* Tail;                            //хвост очереди
    int Size;                                 //размер очереди
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
    int size() { return this->Size; }  //получение размера
    void pushHead(T obj);              //добавить в голову
    void push(T obj, int num);         //добавить в нужную позицию
    bool isEmpty();                    //проверка на заполненность
    void pushTail(T obj);              //добавить в хвост
    T popHead();                       //удалить из головы
    void deleteQueue();
    T pop(int num);                    //удалить из позиции
    T popTail();                       //удалить с хвоста
    T& operator[](int num);            //перегрузка []
    Node<T>* begin();                  //начало очереди
    Node<T>* end();                    //конец очереди
    void output();                     //вывод очереди
    void file_in(string fname);        //чтение из файла
    void file_out1(string fname);      //запись в файл
    void file_out2(string fname);      //дозапись в файл
    void HeadTable();                  //шапка таблицы
};

