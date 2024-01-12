#pragma once
#include "Professor.h"
#include "MemberOfOrg.h"

class ProfMember : public Professor, public MemberOfOrg
{
protected:
	double ContributionPerMonth;

public:

	ProfMember() :                                //����������� �� ���������
		Professor(), MemberOfOrg()
	{
		this->ContributionPerMonth = 0;
	}

	ProfMember(double contrib, int yearofbirth, const char* name, const char* midname, const char* surname, const char* ocup, const char* spec, const char** work, const char* nameoforg, const char** autobio, int yearofenter) :
		Professor(yearofbirth, name, midname, surname, ocup, spec, work), MemberOfOrg(yearofbirth, name, midname, surname, nameoforg, yearofenter, autobio),
		Man(yearofbirth, name, midname, surname)  //����������� � �����������
	{
		this->ContributionPerMonth = contrib;
	}

	~ProfMember()                                 //����������
	{
	}

	//ProfMember(ProfMember& obj) : Professor(obj), MemberOfOrg(obj), Man(obj)                  //����������� �����������
	//{
	//	this->ContributionPerMonth = obj.ContributionPerMonth;
	//}

	double getContributionPerMonth();
	void setContributionPerMonth(int temp);

	ProfMember operator=(const ProfMember& obj);                         //���������� =

	friend istream& operator>>(istream& is, ProfMember& obj);      //���������� �����

	friend ostream& operator<<(ostream& out, const ProfMember& obj);     //���������� ������

	friend ofstream& operator<<(ofstream& out, ProfMember& obj);
	friend ifstream& operator>>(ifstream& in, ProfMember& obj);

	friend fstream& operator<<(fstream& in, ProfMember& obj);
	friend fstream& operator>>(fstream& out, ProfMember& obj);

	bool operator==(const ProfMember& obj);
	bool operator<(const ProfMember& obj);
	bool operator>(const ProfMember& obj);

	void HeadOfSheet() override;                                   //����� �������

	void Find();
	void Change();
	void ReplaceField(ProfMember& obj);
	void Pick();
	//void menu() override;
};