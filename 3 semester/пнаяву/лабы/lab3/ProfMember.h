#pragma once
#include "Professor.h"
#include "MemberOfOrg.h"

class ProfMember : public Professor, public MemberOfOrg
{
protected:
	int ContributionPerMonth;

public:

	ProfMember() :                                //конструктор по умолчанию
		Professor(), MemberOfOrg()
	{
		this->ContributionPerMonth = 0;
	}

	ProfMember(int contrib,int yearofbirth, const char* name, const char* midname, const char* surname, const char* ocup, const char* spec, const char** work, const char* nameoforg, const char** autobio, int yearofenter) :
		Professor(yearofbirth, name, midname, surname, ocup, spec, work), MemberOfOrg(yearofbirth, name, midname, surname, nameoforg, yearofenter, autobio),
		Man(yearofbirth, name, midname, surname)  //конструктор с параметрами
	{
		this->ContributionPerMonth = contrib;
	}

	~ProfMember()                                 //деструктор
	{
	}

	ProfMember(ProfMember& obj)                   //конструктор копирования
	{
		this->ContributionPerMonth = obj.ContributionPerMonth;
	}

	int getContributionPerMonth();
	void setContributionPerMonth(int temp);

	ProfMember operator=(ProfMember& obj);                         //перегрузка =

	friend istream& operator>>(istream& is, ProfMember& obj);      //перегрзука ввода

	friend ostream& operator<<(ostream& out, ProfMember& obj);     //перегрузка вывода

	bool operator==(const ProfMember& obj);

	void HeadOfSheet() override;                                   //шапка таблицы

	void menu() override;
};