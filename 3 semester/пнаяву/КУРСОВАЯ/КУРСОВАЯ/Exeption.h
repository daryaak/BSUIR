#pragma once
#include<cstring>
#include <iostream>
#include <ostream>
#include <iomanip>
#include  <conio.h>
#include <windows.h>
using namespace std;
#define Len 80
class Exeption                          //класс исключение
{
protected:
	int Code;                           //код ошибки
	char Type[Len];                     //тип ошибки
public:
	Exeption()                          //конструктор по-умолчанию
	{
		Code = 0;
		Type[0] = '\0';
	}
	Exeption(int a, const char* str)    //конструктор с параметрами
	{
		Code = a;
		strcpy_s(Type, Len, str);
	}
	~Exeption() {}                      //деструктор
	virtual void ShowError()            //функция вывода ошибки
	{
		return;
	}
};

