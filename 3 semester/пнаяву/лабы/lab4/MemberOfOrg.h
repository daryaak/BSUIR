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

	MemberOfOrg() :                                        //���������� �� ���������
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
		Man(yearofbirth, name, middlename, surname)        //����������� � �����������
	{
		strcpy_s(this->NameOfOrganization, 20, nameoforg);
		this->YearOfEnter = yearofenter;
		for (int i = 0; i < 3; i++)
		{
			strcpy_s(this->Autobiography[i], 20, autob[i]);
		}
	}
	~MemberOfOrg()                                         //����������
	{
	}

	MemberOfOrg(MemberOfOrg& obj)                          //����������� �����������
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

	MemberOfOrg operator=(const MemberOfOrg& obj);               //���������� =

	friend istream& operator>>(istream& is, MemberOfOrg& obj);   //���������� �����
	
	friend ostream& operator<<(ostream& out, MemberOfOrg& obj);  //���������� ������

	void HeadOfSheet() override;                                 //����� �������

};
