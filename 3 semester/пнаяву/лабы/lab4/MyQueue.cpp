#include <iostream>
#include <ostream>
#include <iomanip>
#include  <conio.h>
#include <windows.h>
using namespace std;

template <class T>
struct Node {								//���� ��������������� �������
	T data;									//�������������� ����
	Node<T>* previous;						//��������� �� ���������� �������
	Node<T>* next;							//��������� �� ���� �������
};

template <class T>
class Queue {
private:
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	int amount = 0;							//���-�� ����� �������

public:
	Queue() {};								//�����������
	~Queue();								//����������
	int size() { return this->amount; }		//�������, ������������ ���-�� �����
	void pushHead(T obj);					//���������� �������� � ������ �������
	void push(T obj, int num);				//������������ �������� � ������������ �������
	void pushTail(T obj);					//���������� �������� � ����� �������
	T popHead();							//�������� 1 ��������
	T pop(int num);							//�������� ������������� ��������
	T popTail();							//�������� ���������� ��������
	T perem(int num);						//������� ��� ���������� n-��� ��������
	void output1();							//������� ��� ������ ������ �����
	void deleteAll();						//������ ������� �������
	Queue<T> poisk(T buff);					//������� ������
	void returnback(T obj, int num);
};


void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

template<class T>
Queue<T>::~Queue() {
	while (this->head)
		this->popHead();
}

template<class T>
void Queue<T>::pushHead(T obj) {
	if (head == nullptr) {					//���� ������� �����
		head = new Node<T>;
		head->data = obj;
		head->next = nullptr;
		head->previous = nullptr;
		tail = head;
		amount++;
	}
	else {
		auto* node = new Node<T>;
		node->data = obj;
		node->next = head;
		node->previous = nullptr;
		head->previous = node;
		head = node;
		amount++;
	}
}

template<class T>
void Queue<T>::push(T obj, int num)
{
	if (!head)								//���� ������� �����
	{
		pushHead(obj);
		return;
	}

	Node<T>* node = new Node<T>;
	node->data = obj;
	Node<T>* curr = head;
	for (int i = 0; i < num - 1 && i < amount - 1; i++)
		curr = curr->next;
	if (!curr)								//���� �������� ����� ������ ���������� ���-�� �����
	{
		pushTail(obj);
		return;
	}

	if (curr == head)						//���� � ������� ������ 1 �������
	{
		node->next = head;
		head->previous = node;
		head = node;
		amount++;
		return;
	}

	node->next = curr;
	node->previous = curr->previous;
	curr->previous->next = node;
	curr->previous = node;
	amount++;
}

template<class T>
void Queue<T>::pushTail(T obj) {
	if (head == nullptr) {					//���� ������� �����
		head = new Node<T>;
		head->data = obj;
		head->next = nullptr;
		head->previous = nullptr;
		tail = head;
		amount++;
		return;
	}
	auto* node = new Node<T>;
	node->data = obj;
	node->next = nullptr;
	node->previous = tail;
	tail->next = node;
	tail = node;
	amount++;
}

template<class T>
T Queue<T>::popHead() {
	if (!(head)) return T();
	T data = head->data;
	Node<T>* node = head;
	if (head != tail) {
		head = head->next;
		head->previous = nullptr;
		Node<T>* tmp = head;
	}
	else {
		head = tail = nullptr;
	}
	amount--;
	return data;
}

template<class T>
T Queue<T>::pop(int num) {
	if (num == 0)  return popHead();
	if (num == amount - 1) return popTail();
	Node<T>* curr = head;
	for (int i = 0; i < num; i++)
		curr = curr->next;
	Node<T>* prev = curr->previous;
	Node<T>* next = curr->next;
	T data = curr->data;
	amount--;
	prev->next = next;
	next->previous = prev;
	delete curr;
	return data;
}

template<class T>
T Queue<T>::popTail() {
	if (!(head)) return T();
	T data = tail->data;
	Node<T>* node = tail;
	if (tail != head) {
		tail = tail->previous;
		tail->next = nullptr;
	}
	else {
		head = tail = nullptr;
	}
	delete node;
	amount--;
	return data;
}

template<class T>
void Queue<T>::deleteAll() {
	while (this->head) { this->popHead(); }
}

template<class T>
void Queue<T>::output1() {
	int i = 0;
	for (Node<T>* node = head; node != nullptr; node = node->next) {
		cout << node->data << endl;
		i++;
	}
}

template <class T>
Queue<T> Queue<T>::poisk(T buff)
{
	Queue<T> q;
	Node<T>* point = head;
	for (int i = 0; i < amount; ++i, point = point->next)
	{
		if (point->data == buff)
			q.pushTail(point->data);
	}
	return q;
}

template<class T>
T Queue<T>::perem(int num) {
	Node<T>* curr = head;
	for (int i = 0; i < num - 1 && i < amount - 1; i++)
		curr = curr->next;
	return curr->data;
}

template<class T>
void Queue<T>::returnback(T obj, int num) {
	Node<T>* curr = head;
	for (int i = 0; i < num - 1 && i < amount - 1; i++)
		curr = curr->next;
	curr->data = obj;
}











//#include <iostream>
//#include <ostream>
//#include <iomanip>
//#include  <conio.h>
//using namespace std;
//template <class T>
//struct Node
//{
//	T Data;
//	Node<T>* Prev;
//	Node<T>* Next;
//};
//
//template <class T>
//class MyQueue
//{
//private:
//
//	Node<T>* Head;
//	Node<T>* Tail;
//	int Size;
//
//public:
//
//	MyQueue()
//	{
//		Head = Tail = nullptr;
//		Size = 0;
//	}
//
//	//�������� ����������� � ����������� � ����������
//
//	int GetSize();
//
//	void Show();
//
//	void PushHead(T obj);
//
//	T Pop(int pos);
//	T PopHead();
//
//	MyQueue<T> Search(T obj);
//
//	T PopTail();
//
//	void menu();
//};
//
//template <class T>
//int MyQueue<T>:: GetSize()
//{
//	return this->Size;
//}
//
//template <class T>
//void MyQueue<T>::Show()
//{
//	for (Node<T>* node = Head; node != nullptr; node = node->Next)
//	{
//		cout << node->Data << endl;
//	}
//}
//
//template<class T>
//T MyQueue<T>::PopHead() {
//	if (!(Head)) return T();
//	T data = Head->Data;
//	Node<T>* node = Head;
//	if (Head != Tail) {
//		Head = Head->next;
//		Head->Prev = nullptr;
//		Node<T>* tmp = Head;
//	}
//	else {
//		Head = Tail = nullptr;
//	}
//	Size--;
//	return data;
//}
//
//template<class T>
//T MyQueue<T>::PopTail() {
//	if (!(Head)) return T();
//	T data = Tail->Data;
//	Node<T>* node = Tail;
//	if (Tail != Head) {
//		Tail = Tail->Prev;
//		Tail->Next = nullptr;
//	}
//	else {
//		Head = Tail = nullptr;
//	}
//	delete node;
//	Size--;
//	return data;
//}
//template <class T>
//T MyQueue<T>:: Pop(int pos)
//{
//	if (pos == 0) return PopHead();
//	
//	if (pos == Size - 1) return PopTail();
//	Node<T>* curr = Head;
//	for (int i = 0; i < pos; i++)
//		curr = curr->Next;
//	Node<T>* prev = curr->Prev;
//	Node<T>* next = curr->Next;
//	T data = curr->Data;
//	Size--;
//	prev->Next = next;
//	next->Prev = prev;
//	delete curr;
//	return data;
//}
//
////template <class T>
////MyQueue<T> MyQueue<T>::Search(T obj)
////{
////	MyQueue<T> temp;
////	Node<T>* Point = Head;
////	for (int i = 0; i < Size; ++i, Point = Point->Next)
////	{
////		if (Point->Data == obj)
////			temp.PushHead(Point->Data);
////	}
////	return temp;
////}
//
//template <class T>
//void MyQueue<T>::PushHead(T obj)
//{
//	/*Node<T>* newq = new Node<T>;
//	newq->Data = obj;
//	newq->Next = newq->Prev = nullptr;
//	if (Head && Tail) {
//		newq->Next = Tail;
//		newq->Prev = nullptr;
//		Tail->Prev = newq;
//		Tail = newq;
//	}
//	else {
//		Head = Tail = newq;
//		Head->Next = Tail->Next = nullptr;
//		Head->Prev = Tail->Prev = nullptr;
//	}
//	this->Size++;*/
//	if (Head == nullptr)
//	{
//		Head = new Node<T>;
//		Head->data = obj;
//		Head->Next = Head->Prev = nullptr;
//		Tail = Head;
//		size++;
//	}
//	else
//	{
//		auto* A = new Node<T>;
//		A->Data = obj;
//		A->Next = Head;
//		A->Prev = nullptr;
//		Head->Prev = A;
//		Head = A;
//		size++;
//	}
//}
//
//
//template <class T>
//void MyQueue<T>::menu()
//{
//	int a;
//	bool flag = false;
//	do
//	{
//		cout << endl << "�������� ��������: " << endl << "1. ��������" << endl << "2. �������" << endl
//			<< "3. �����������" << endl << "4. �����" << endl << "5. �����" << endl;
//		cin >> a;
//		switch (a)
//		{
//		case 1:
//		{
//			cout << "������� ����������" << endl;
//			T addElem;
//			cin >> addElem;
//			this->PushHead(addElem);
//			break;
//		}
//		case 2:
//		{
//			int b;
//			cout << "������� ����� ���������� �������� ";
//			cin >> b;
//			cout << endl;
//			this->Pop(b);
//			break;
//		}
//		case 3:
//		{
//			cout << "���� �������:" << endl;
//			this->Show();
//			cout << endl;
//			break;
//		}
//		case 4:
//		{
//			/*T find;
//			cout << "������� ���������� ��� ������:" << endl;
//			cin >> find;
//			MyQueue<T> rez;
//			rez= this->Search(find);
//			cout << "���������:" << endl;
//			rez.Show();*/
//			break;
//		}
//		case 5:
//		{
//			flag = true;
//			break;
//		}
//		}
//	} while (!flag);
//}