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
class Algorithm                   //шаблонный класс алгоритма
{
public:
	//метод поиска
	static Queue<T> Search(Iterator<T> begin, Iterator<T> end, T Temp);	
	//метод добавления
	static void Add(T Elem, Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos,vector<int>& Position);
	//метод удаления
	static void Delete_Element(int num,Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position);
	//метод отмены последнего действия
	static void Cancel(Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position);
	//метод сортировки
	static void SortFromMin(Iterator<T> beg, Iterator<T> end);
	static void SortFromMax(Iterator<T> beg, Iterator<T> end);
	//метод изменения полей объекта
	static void update(Queue<T>& q, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position);
	//метод авторизации администратора
	static bool authotization();
	//метод бронирования тура
	static void reserve_tour(Queue<T>& q,string filename,string bfilename);
};


