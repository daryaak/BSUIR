#pragma once
#include<cstring>
#include<iostream>
#include<iomanip>
using namespace std;

class Man
{
protected:
	char Name[20];         
	char MiddleName[20];
	char Surname[20];
	int YearOfBirth;

public:
	Man()                                                                       //����������� �� ���������
	{
		this->YearOfBirth = 0;
		this->Name[0] = '\0';
		this->MiddleName[0] = '\0';
		this->Surname[0] = '\0';


	}
	
	Man(int temp, const char* name,const char* middlename,const char* surname) //����������� � �����������
	{
		this->YearOfBirth = temp;
		strcpy_s(this->Name, 20, name);
		strcpy_s(this->MiddleName, 20, middlename);
		strcpy_s(this->Surname, 20, surname);
	}

	virtual ~Man()                                                             //����������� ����������
	{
	}

	Man(const Man& obj)                                                        //����������� �����������
	{
		this->YearOfBirth = obj.YearOfBirth;
		strcpy_s(this->Name, 20, obj.Name);
		strcpy_s(this->MiddleName, 20, obj.MiddleName);
		strcpy_s(this->Surname, 20, obj.Surname);
	}


	char* getName();
	char* getMiddleName();
	char* getSurname();
	int getYearOfBirth();

	void setName(const char* name);
	void setMiddleName(const char* middlename);
	void setSurname(const char* surname);
	void setYearOfBirth(int a);

	Man operator=(const Man& obj);                                               //���������� =

	friend istream& operator>>(istream& is, Man& obj);                           //���������� �����
	

	friend ostream& operator<<(ostream& out, Man& obj);                          //���������� ������
	
	bool operator==(const Man& obj);

	virtual void menu();

	virtual void HeadOfSheet();                                                  //����������� ������� ����� �������
};