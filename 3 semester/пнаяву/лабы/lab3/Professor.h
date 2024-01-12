#pragma once
#include"Man.h"

class Professor : virtual public Man
{
protected:
	char Occupation[20];
    char Specialization[20];
	char ScienceWork[3][20];

public:

	Professor() :                                           //конструктор по умолчанию
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
		Man(yearofbirth, name, middlename, surname)        //конструктор с параметрами
	{
		strcpy_s(this->Occupation, 20, occup);
		strcpy_s(this->Specialization, 20, spec);
		for (int i = 0; i < 3; i++)
		{
			strcpy_s(this->ScienceWork[i], 20, work[i]);
		}
	}
	~Professor()                                            //деструктор
	{
	}

	Professor(Professor& obj)                               //конструктор копирования
	{
		strcpy_s(this->Occupation, 20, obj.Occupation);
		strcpy_s(this->Specialization, 20, obj.Specialization);
		for (int i = 0; i < 3; i++)
		{
			strcpy_s(this->ScienceWork[i], 20, obj.ScienceWork[i]);
		}
	}
	
	char* getOccupation();
	char* getSpecialization();
	char** getScienceWork();

	void setOccupation(char* a);
	void setSpecialization(char* a);
	void setScienceWork(char** a);

	Professor operator=(const Professor& obj);                //перегрузка =

	friend istream& operator>>(istream& is, Professor& obj);  //перегрузка ввода
	
	friend ostream& operator<<(ostream& out, Professor& obj); //перегрузка вывода

	bool operator==(const Professor& obj);

	void menu() override;

	void HeadOfSheet() override;                              
};
