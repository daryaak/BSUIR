#pragma once
#include "Man.h"
#include "MemberOfOrg.h"
#include "Professor.h"
#include "ProfMember.h"
#include "FileExeption.h"
#include "Queue.cpp"
#include <Windows.h>
#include <deque>

using namespace std;

template <typename T>
class myInterface
{
public:
	myInterface() {};
	~myInterface() {};
	static void MenuStart();
	void menu();
	void Menu(Queue<T>& obj, string tfile, string bfile);
	void menudeque();
	void Menufordeque(deque<T>& obj, string tfile, string bfile);
};




