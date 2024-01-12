#pragma once
#include "Man.h"
class MemberOfOrg :
	virtual public Man
{
protected:
	char NameOfOrganization[LEN];
	int YearOfEnter;
	char Autobiography[3][LEN];
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
		strcpy_s(this->NameOfOrganization, LEN, nameoforg);
		this->YearOfEnter = yearofenter;
		for (int i = 0; i < 3; i++)
		{
			strcpy_s(this->Autobiography[i], LEN, autob[i]);
		}
	}
	~MemberOfOrg()                                         //����������
	{
	}

	//MemberOfOrg(MemberOfOrg& obj) : Man(obj)                         //����������� �����������
	//{
	//	strcpy_s(this->NameOfOrganization, LEN, obj.NameOfOrganization);
	//	this->YearOfEnter = obj.YearOfEnter;
	//	for (int i = 0; i < 3; i++)
	//	{
	//		strcpy_s(this->Autobiography[i], LEN, obj.Autobiography[i]);
	//	}
	//}

	char* getNameOfOrganization();
	int getYearOfEnter();
	char** getAutobiography();

	void setNameOfOrganization(char* a);
	void setYearOfEnter(int a);
	void setAutobiography(char** a);

	MemberOfOrg operator=(const MemberOfOrg& obj);               //���������� =

	friend istream& operator>>(istream& is, MemberOfOrg& obj);   //���������� �����

	friend ostream& operator<<(ostream& out, const MemberOfOrg& obj);  //���������� ������

	friend ofstream& operator<<(ofstream& out, MemberOfOrg& obj);
	friend ifstream& operator>>(ifstream& in, MemberOfOrg& obj);

	friend fstream& operator<<(fstream& in, MemberOfOrg& obj);
	friend fstream& operator>>(fstream& out, MemberOfOrg& obj);

	bool operator==(const MemberOfOrg& obj);
	bool operator<(const MemberOfOrg& obj);
	bool operator>(const MemberOfOrg& obj);

	void HeadOfSheet() override;                                 //����� �������

	void Find();
	void Change();
	void ReplaceField(MemberOfOrg& obj);
	void Pick();
};

