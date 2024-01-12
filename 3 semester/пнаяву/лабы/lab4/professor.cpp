#include "Professor.h"
#include <string>
#include <windows.h>

char* Professor:: getOccupation() { return this->Occupation; }
char* Professor:: getSpecialization() { return this->Specialization; }
char** Professor::getScienceWork() { return (char**)this->ScienceWork; }

void Professor:: setOccupation(char* a) { strcpy_s((this->Occupation), 20, a); }
void Professor:: setSpecialization(char* a) { strcpy_s((this->Specialization), 20, a); }
void Professor:: setScienceWork(char** a)
{
	for (int i = 0; i < 3; i++)
		strcpy_s(this->ScienceWork[i], 20, a[i]);
}

Professor Professor::operator=(const Professor& obj)
{
	*((Man*)this) = (Man&)obj;
	strcpy_s(this->Occupation, 20, obj.Occupation);
	strcpy_s(this->Specialization, 20, obj.Specialization);
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->ScienceWork[i], 20, obj.ScienceWork[i]);
	}
	return *this;
}

istream& operator>>(istream& is, Professor& obj)
{
	rewind(stdin);
	is >> (Man&)obj;
	cout << "������� ���������: ";
	is >> obj.Occupation;
	cout << "������� �������������: ";
	is >> obj.Specialization;
	cout << "������� ������� ������: ";
	for (int i = 0; i < 3; i++)
	{
		is >> obj.ScienceWork[i];
	}
	return is;
}

ostream& operator<<(ostream& out, Professor& obj)
{
	
	out << (Man&)obj;
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << setw(15) << obj.Specialization;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << obj.ScienceWork[i] << setw(20) << endl;
			continue;
		}
		out << setw(90) << " " << obj.ScienceWork[i]<< endl;
	}
	out.unsetf(ios::left);
	return out;
}

void Professor::HeadOfSheet()
{
	
	cout.setf(ios::left);
	cout << setw(15) << "�������" << setw(15) << "���" << setw(15) << "��������" << setw(15) << "��� ��������";
	cout << setw(15) << "���������" << setw(15) << "�������������" << setw(20) << "������� ������"<<endl;
	cout.unsetf(ios::left);
}
