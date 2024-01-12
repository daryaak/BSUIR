#pragma once
#include<cstring>
#include <iostream>
#include <ostream>
#include <iomanip>
#include  <conio.h>
#include <windows.h>
#include "Exeption.h"
#include "InputExeption.h"
#include "TextFile.h"
#include "TextFile.cpp"
#include "BinFile.h"
#include "BinFile.cpp"

#define LEN 30

class Man
{
protected:
	char Name[LEN];
	char MiddleName[LEN];
	char Surname[LEN];
	int YearOfBirth;

public:
	Man()                                                                       //конструктор по умолчанию
	{
		this->YearOfBirth = 0;
		this->Name[0] = '\0';
		this->MiddleName[0] = '\0';
		this->Surname[0] = '\0';
	}

	Man(int temp, const char* name, const char* middlename, const char* surname) //конструктор с параметрами
	{
		this->YearOfBirth = temp;
		strcpy_s(this->Name, LEN, name);
		strcpy_s(this->MiddleName, LEN, middlename);
		strcpy_s(this->Surname, LEN, surname);
	}

	//Man(const Man& obj)                                                        //конструктор копирования
	//{
	//	strcpy_s(this->Surname, LEN, obj.Surname);
	//	this->YearOfBirth = obj.YearOfBirth;
	//	strcpy_s(this->Name, LEN, obj.Name);
	//	strcpy_s(this->MiddleName, LEN, obj.MiddleName);
	//}

	char* getName();
	char* getMiddleName();
	char* getSurname();
	int getYearOfBirth();

	void setName(const char* name);
	void setMiddleName(const char* middlename);
	void setSurname(const char* surname);
	void setYearOfBirth(int a);

	Man operator=(const Man& obj);                                               //перегрузка =

	friend istream& operator>>(istream& is, Man& obj);
	friend ostream& operator<<(ostream& out, const Man& obj);

	friend ofstream& operator<<(ofstream& out, Man& obj);
	friend ifstream& operator>>(ifstream& in, Man& obj);

	friend fstream& operator<<(fstream& in, Man& obj);
	friend fstream& operator>>(fstream& out, Man& obj);

	//fstream& bin_in(fstream& in, Man& obj);

	bool operator==(const Man& obj);
	bool operator<(const Man& obj);
	bool operator>(const Man& obj);

	void Find();

	virtual void HeadOfSheet();                                                  //виртуальная функция шапки таблицы
};

