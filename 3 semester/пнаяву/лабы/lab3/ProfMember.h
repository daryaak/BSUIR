#pragma once
#include "Professor.h"
#include "MemberOfOrg.h"

class ProfMember : public Professor, public MemberOfOrg
{
protected:
	int ContributionPerMonth;

public:

	ProfMember() :                                //����������� �� ���������
		Professor(), MemberOfOrg()
	{
		this->ContributionPerMonth = 0;
	}

	ProfMember(int contrib,int yearofbirth, const char* name, const char* midname, const char* surname, const char* ocup, const char* spec, const char** work, const char* nameoforg, const char** autobio, int yearofenter) :
		Professor(yearofbirth, name, midname, surname, ocup, spec, work), MemberOfOrg(yearofbirth, name, midname, surname, nameoforg, yearofenter, autobio),
		Man(yearofbirth, name, midname, surname)  //����������� � �����������
	{
		this->ContributionPerMonth = contrib;
	}

	~ProfMember()                                 //����������
	{
	}

	ProfMember(ProfMember& obj)                   //����������� �����������
	{
		this->ContributionPerMonth = obj.ContributionPerMonth;
	}

	int getContributionPerMonth();
	void setContributionPerMonth(int temp);

	ProfMember operator=(ProfMember& obj);                         //���������� =

	friend istream& operator>>(istream& is, ProfMember& obj);      //���������� �����

	friend ostream& operator<<(ostream& out, ProfMember& obj);     //���������� ������

	bool operator==(const ProfMember& obj);

	void HeadOfSheet() override;                                   //����� �������

	void menu() override;
};