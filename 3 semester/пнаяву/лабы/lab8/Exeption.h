#pragma once
#include<cstring>
#include <iostream>
#include <ostream>
#include <iomanip>
#include  <conio.h>
#include <windows.h>
using namespace std;
#define Len 80

class Exeption
{
protected:
	int Code;
	char Type[Len];
public:
	Exeption()
	{
		Code = 0;
		Type[0] = '\0';
	}

	Exeption(int a, const char* str)
	{
		Code = a;
		strcpy_s(Type, Len, str);
	}

	~Exeption() {}

	virtual void ShowError()
	{
		return;
	}
};


