#pragma once


#include "Man.h"
class Professor :
	virtual public Man
{

protected:
	char Occupation[LEN];
	char Specialization[LEN];
	char ScienceWork[3][LEN];

public:

	Professor() :                                           //����������� �� ���������
		Man()
	{
		this->Occupation[0] = '\0';
		this->Specialization[0] = '\0';
		for (int i = 0; i < 3; i++)
		{
			this->ScienceWork[i][0] = '\0';
		}
	}

	Professor(int yearofbirth, const char* name, const char* middlename, const char* surname, const char* occup, const char* spec, const char** work) :
		Man(yearofbirth, name, middlename, surname)        //����������� � �����������
	{
		strcpy_s(this->Occupation, LEN, occup);
		strcpy_s(this->Specialization, LEN, spec);
		for (int i = 0; i < 3; i++)
		{
			strcpy_s(this->ScienceWork[i], LEN, work[i]);
		}
	}
	~Professor()                                            //����������
	{
	}

	Professor(Professor& obj) :Man(obj)                              //����������� �����������
	{
		strcpy_s(this->Occupation, LEN, obj.Occupation);
		strcpy_s(this->Specialization, LEN, obj.Specialization);
		for (int i = 0; i < 3; i++)
		{
			strcpy_s(this->ScienceWork[i], LEN, obj.ScienceWork[i]);
		}
	}

	char* getOccupation();
	char* getSpecialization();
	char** getScienceWork();

	void setOccupation(char* a);
	void setSpecialization(char* a);
	void setScienceWork(char** a);

	Professor operator=(const Professor& obj);                //���������� =

	friend istream& operator>>(istream& is, Professor& obj);  //���������� �����

	friend ostream& operator<<(ostream& out, const Professor& obj); //���������� ������

	friend ofstream& operator<<(ofstream& out, Professor& obj);
	friend ifstream& operator>>(ifstream& in, Professor& obj);

	friend fstream& operator<<(fstream& in, Professor& obj);
	friend fstream& operator>>(fstream& out, Professor& obj);

	bool operator==(const Professor& obj);
	bool operator<(const Professor& obj);
	bool operator>(const Professor& obj);

	void Find();

	//void menu() override;

	void HeadOfSheet() override;
	void Change();
	void ReplaceField(Professor& obj);
	void Pick();
};

