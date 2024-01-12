#pragma once
#include"Man.h"
#include <string>
#include <windows.h>

class MemberOfOrg : virtual public Man
{
protected:
	char NameOfOrganization[20];
	int YearOfEnter;
	char Autobiography[3][20];
public:

	MemberOfOrg() :                                        //консруктор по умолчанию
		Man()
	{
		this->NameOfOrganization[0] = '\0';
		this->YearOfEnter = 0;
		for (int i = 0; i < 3; i++)
		{
			this->Autobiography[i][0] = '\0';
		}
	}

	MemberOfOrg(int yearofbirth, const char* name, const char* middlename, const char* surname, const char* nameoforg, int yearofenter, const char** autob) :
		Man(yearofbirth, name, middlename, surname)        //конструктор с параметрами
	{
		strcpy_s(this->NameOfOrganization, 20, nameoforg);
		this->YearOfEnter = yearofenter;
		for (int i = 0; i < 3; i++)
		{
			strcpy_s(this->Autobiography[i], 20, autob[i]);
		}
	}
	~MemberOfOrg()                                         //деструктор
	{
	}

	MemberOfOrg(MemberOfOrg& obj)                          //конструктор копирования
	{
		strcpy_s(this->NameOfOrganization, 20, obj.NameOfOrganization);
		this->YearOfEnter=obj.YearOfEnter;
		for (int i = 0; i < 3; i++)
		{
			strcpy_s(this->Autobiography[i], 20, obj.Autobiography[i]);
		}
	}

	char* getNameOfOrganization();
	int getYearOfEnter();
	char** getAutobiography();

	void setNameOfOrganization(char* a);
	void setYearOfEnter(int a);
	void setAutobiography(char** a);

	MemberOfOrg operator=(const MemberOfOrg& obj);               //перегрузка =

	friend istream& operator>>(istream& is, MemberOfOrg& obj);   //перегрузка ввода
	
	friend ostream& operator<<(ostream& out, MemberOfOrg& obj);  //перегрузка вывода

	void HeadOfSheet() override;                                 //шапка таблицы

};
