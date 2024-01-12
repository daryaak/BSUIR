#pragma once
#include "Man.h"
#include "MemberOfOrg.h"
#include "Professor.h"
#include "ProfMember.h"
#include "FileExeption.h"
#include <Windows.h>
#include "Queue.cpp"
using namespace std;

template <typename T>
class myInterface
{
public:
	myInterface() {};

	~myInterface() {};

	void menu();
	void Menu(Queue<T>& obj, string tfile, string bfile);
};




