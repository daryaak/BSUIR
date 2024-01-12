#pragma once
#include "Node.h"

//шаблонный класс итератор
template<class T>
class Iterator 
{
public:
	Node<T>* current;                  //указаетль на текущий элемент
	Iterator(Node<T>* temp = nullptr); //конструктор по-умоланию
	~Iterator();                       //деструктор
	T& operator*();                    //разадресация
	void operator=(T data);            //перегрзка оператора присваивания объекта
	bool operator++();                 //перегрузка оператора ++
	bool operator--();                 //перегрузка оператора --
	bool operator==(Iterator<T>& ob);  //перегрузка оператора == для сравнения с итератором
	bool operator!=(Iterator<T>& ob);  
};
