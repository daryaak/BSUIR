#pragma once

#include "MyQueue.cpp"

template<class T>
class Algoritm {
public:
	void add(Queue<T>& queue);							//������� ����������
	void delete_el(Queue<T>& queue);					//������� ��������
};

template<class T>
void Algoritm<T>::add(Queue<T>& st)
{
	int z;
	system("cls");
	SetColor(3, 0);
	int y = 0;
	cout << "1. �������� � ������ �������" << endl;
	cout << "2. �������� � ����� �������" << endl;
	cout << "3. �������� � n-�� �������0" << endl;
	cout << "4. �����" << endl;
	cin >> y;
	SetColor(7, 0);
	switch (y)
	{
	case 1: {
		T newm;
		cout << "������� �������: " << endl;
		cin >> newm;
		st.pushHead(newm);
	}break;
	case 2: {
		T newm;
		cout << "������� �������: " << endl;
		cin >> newm;
		st.pushTail(newm);
	}break;
	case 3: {
		int p;
		cout << "������� n-�� �������: " << endl;
		cin >> p;
		T newm;
		cout << "������� �������: " << endl;
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
	cout << "1. ������� 1 ������� �������" << endl;
	cout << "2. ������� ��������� �������" << endl;
	cout << "3. ������� n-�� ������� �� �������" << endl;
	cout << "4. ������� ��� �������" << endl;
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
		cout << "������� n-�� �������: " << endl;
		cin >> p;
		st.pop(p);
	}break;
	case 4: {
		st.deleteAll();
	}break;
	}
}
