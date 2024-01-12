#define _CRT_SECURE_NO_WARNINGS
#include"mystring.h"
#include<cstring>
#include<iostream>
using namespace std;


// obj=obj
String& String:: operator=(const String& s)
{
	if (this == &s) return *this;
	delete[] str;
	this->size = s.size;
	str = new char[this->size + 1];
	strcpy_s(str, size + 1, s.str);              //копирование строки
	return *this;
}

//obj=char*
String& String:: operator=(const char* s)
{
	delete[] str;
	this->size = strlen(s);
	str = new char[this->size + 1];
	strcpy_s(str, this->size + 1, s);                
	return*this;
}

//obj+obj
String String:: operator+(const String& s)
{
	String temp;
	temp.size = this->size + s.size;
	temp.str = new char[temp.size + 1];
	strcpy_s(temp.str, this->size + 1, this->str);
	strcat_s(temp.str, temp.size + 1, s.str);           //соединение строк
	return temp;
}

//obj+*char
String String:: operator+(const char* s)
{
	String temp;
	temp.size = this->size + strlen(s);
	temp.str = new char[temp.size + 1];
	strcpy_s(temp.str, this->size + 1, this->str);     //копирование строк
	strcat_s(temp.str, temp.size + 1, s);              //соединение 2-ух строк
	return temp;
}

//obj+char
String String:: operator+(const char s)
{
	String temp;
	temp.size = this->size + 1;
	temp.str = new char[temp.size + 1];
	strcpy_s(temp.str, this->size + 1, this->str);    //копирование строк
	temp.str[this->size] = s;
	temp.str[temp.size] = '\0';
	return temp;
}

//obj+=obj
String String:: operator +=(const String& s)
{
	*this = *this + s;
	return *this;
}

//obj+=char*
String String:: operator +=(const char* s)
{
	*this = *this + s;
	return *this;
}

//obj==obj
bool String:: operator == (const String& s)
{
	if (strcmp(this->str, s.str) == 0)
		return true;
	else
		return false;
}

//obj==char*
bool String:: operator == (const char* s)
{
	if (strcmp(this->str, s) == 0)
		return true;
	else
		return false;
}

//obj!=obj
bool String:: operator != (const String& s)
{
	if (strcmp(this->str, s.str) != 0)
		return true;
	else
		return false;
}

//obj!=char*
bool String:: operator != (const char* s)
{
	if (strcmp(this->str, s) != 0)
		return true;
	else
		return false;
}

//obj(int,int)
String String:: operator()(int beg, int end)
{
	if (end > this->size || beg > this->size)
	{
		cout << "Неверные значения начала и конца" << endl;
		return 0;
	}
	if (beg > end)
	{
		int a;
		a = end;
		end = beg;
		beg = a;
	}
	String temp;
	temp.size = end - beg+1;
	temp.str = new char[temp.size + 1];
	
	strncpy(temp.str, this->str + beg,end - beg+1);           //копирование нужной подстроки в новую строку
	temp.str[temp.size] = '\0';
	return temp;

}

//obj[int]
char& String:: operator[](int pos)
{
	return this->str[pos];
}