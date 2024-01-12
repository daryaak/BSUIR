#pragma once
#include "Man.h"
#include "MemberOfOrg.h"
#include "Professor.h"
#include "ProfMember.h"
#include "FileExeption.h"
#include "Queue.cpp"
#include "Exeption.h"
#include "InputExeption.h"

using namespace std;
template <class T>
class Algorithm
{
public:
	static void Add(T Elem, Queue<T>& obj);
	static void Delete_Element(int num,Queue<T>& obj, int pick);
	static Queue<T> Search(Iterator<T> begin, Iterator<T> end, T Temp);
	static void update(Queue<T>& q, int tempNum);
	static void SortFromMin(Iterator<T> beg, Iterator<T> end,T temp);
	static void SortFromMax(Iterator<T> beg, Iterator<T> end, T temp);
};

