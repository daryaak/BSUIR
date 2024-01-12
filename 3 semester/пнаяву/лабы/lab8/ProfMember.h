#pragma once
#include "Professor.h"
#include "MemberOfOrg.h"

class ProfMember : public Professor, public MemberOfOrg
{
protected:
	double ContributionPerMonth;

public:

	ProfMember() :                                //конструктор по умолчанию
		Professor(), MemberOfOrg()
	{
		this->ContributionPerMonth = 0;
	}

	ProfMember(double contrib, int yearofbirth, const char* name, const char* midname, const char* surname, const char* ocup, const char* spec, const char** work, const char* nameoforg, const char** autobio, int yearofenter) :
		Professor(yearofbirth, name, midname, surname, ocup, spec, work), MemberOfOrg(yearofbirth, name, midname, surname, nameoforg, yearofenter, autobio),
		Man(yearofbirth, name, midname, surname)  //конструктор с параметрами
	{
		this->ContributionPerMonth = contrib;
	}

	~ProfMember()                                 //деструктор
	{
	}

	//ProfMember(ProfMember& obj) : Professor(obj), MemberOfOrg(obj), Man(obj)                  //конструктор копирования
	//{
	//	this->ContributionPerMonth = obj.ContributionPerMonth;
	//}

	double getContributionPerMonth();
	void setContributionPerMonth(int temp);

	ProfMember operator=(const ProfMember& obj);                         //перегрузка =

	friend istream& operator>>(istream& is, ProfMember& obj);      //перегрзука ввода

	friend ostream& operator<<(ostream& out, const ProfMember& obj);     //перегрузка вывода

	friend ofstream& operator<<(ofstream& out, ProfMember& obj);
	friend ifstream& operator>>(ifstream& in, ProfMember& obj);

	friend fstream& operator<<(fstream& in, ProfMember& obj);
	friend fstream& operator>>(fstream& out, ProfMember& obj);

	bool operator==(const ProfMember& obj);
	bool operator<(const ProfMember& obj);
	bool operator>(const ProfMember& obj);

	void HeadOfSheet() override;                                   //шапка таблицы

	void Find();
	void Change();
	void ReplaceField(ProfMember& obj);
	void Pick();
	//void menu() override;
};