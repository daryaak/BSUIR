#pragma once

#include "Queue.cpp"

#include "Exeption.h"
#include "InputExeption.h"
#include "Travel.h"
#include "Turism.h"
#include "Sea.h"
#include "Sanatorium.h"
#include "Relax.h"
#include "Therapy.h"
#include "Voucher.h"
#include "Admin.h"
#include "Reserve.h"
#include "FileExeption.h"
#include <vector>
using namespace std;
template <class T>
class Algorithm                   //��������� ����� ���������
{
public:
	//����� ������
	static Queue<T> Search(Iterator<T> begin, Iterator<T> end, T Temp);	
	//����� ����������
	static void Add(T Elem, Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos,vector<int>& Position);
	//����� ��������
	static void Delete_Element(int num,Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position);
	//����� ������ ���������� ��������
	static void Cancel(Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position);
	//����� ����������
	static void SortFromMin(Iterator<T> beg, Iterator<T> end);
	static void SortFromMax(Iterator<T> beg, Iterator<T> end);
	//����� ��������� ����� �������
	static void update(Queue<T>& q, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position);
	//����� ����������� ��������������
	static bool authotization();
	//����� ������������ ����
	static void reserve_tour(Queue<T>& q,string filename,string bfilename);
};


