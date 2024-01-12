#pragma once

#include "MyQueue.cpp"

template<class T>
class Algoritm {
public:
	void add(Queue<T>& queue);							//Функция добавления
	void delete_el(Queue<T>& queue);					//Функция удаления
};

template<class T>
void Algoritm<T>::add(Queue<T>& st)
{
	int z;
	system("cls");
	SetColor(3, 0);
	int y = 0;
	cout << "1. Добавить в начало очереди" << endl;
	cout << "2. Добавить в конец очереди" << endl;
	cout << "3. Добавить в n-ую позицию0" << endl;
	cout << "4. Выход" << endl;
	cin >> y;
	SetColor(7, 0);
	switch (y)
	{
	case 1: {
		T newm;
		cout << "Введите элемент: " << endl;
		cin >> newm;
		st.pushHead(newm);
	}break;
	case 2: {
		T newm;
		cout << "Введите элемент: " << endl;
		cin >> newm;
		st.pushTail(newm);
	}break;
	case 3: {
		int p;
		cout << "Введите n-ый элемент: " << endl;
		cin >> p;
		T newm;
		cout << "Введите элемент: " << endl;
		cin >> newm;
		st.push(newm, p);
	}break;
	}
}

template<class T>
void Algoritm<T>::delete_el(Queue<T>& st)
{
	system("cls");
	int y = 0;
	SetColor(3, 0);
	cout << "1. Удалить 1 элемент очереди" << endl;
	cout << "2. Удалить последний очереди" << endl;
	cout << "3. Удалить n-ый элемент из очереди" << endl;
	cout << "4. Удалить всю очередь" << endl;
	cin >> y;
	SetColor(7, 0);
	switch (y)
	{
	case 1: {
		st.popHead();
	}break;
	case 2: {
		st.popTail();
	}break;
	case 3: {
		int p;
		cout << "Введите n-ый элемент: " << endl;
		cin >> p;
		st.pop(p);
	}break;
	case 4: {
		st.deleteAll();
	}break;
	}
}
