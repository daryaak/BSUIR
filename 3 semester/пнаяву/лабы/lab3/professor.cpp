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

bool Professor:: operator==(const Professor& obj)
{

	if (strlen(obj.Name))
	{
		if (strcmp(Name, obj.Name)) return false;
	}

	if (strlen(obj.MiddleName))
	{
		if (strcmp(MiddleName, obj.Name)) return false;
	}

	if (strlen(obj.Surname))
	{
		if (strcmp(Surname, obj.Surname))return false;
	}

	if (obj.YearOfBirth)
	{
		if (YearOfBirth != obj.YearOfBirth) return false;
	}

	if (strlen(obj.Occupation))
	{
		if (strcmp(Occupation, obj.Occupation)) return false;
	}

	if (strlen(obj.Specialization))
	{
		if (strcmp(Specialization, obj.Specialization)) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.ScienceWork[i]))
		{
			if (strcmp(ScienceWork[i], obj.ScienceWork[i]))return false;
		}
	}
	return true;
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
	cout << "Введите должность: ";
	is >> obj.Occupation;
	cout << "Введите специализацию: ";
	is >> obj.Specialization;
	cout << "Введите научные работы: ";
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
	cout << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Год рождения";
	cout << setw(15) << "Должность" << setw(15) << "Специализация" << setw(20) << "Научная работа"<<endl;
	cout.unsetf(ios::left);
}

void Professor::menu() {
	int t = 0;
	cout << "\nВыберете поле: \n"
		"1.Имя\n2.Отчество\n3.Фамилия\n4.Год рождения\n";
	cin >> t;
	switch (t) {
	case 1: {
		char ax[20];
		cin >> ax;
		setName(ax);
	}break;
	case 2: {
		char ax[20];
		cin >> ax;
		setMiddleName(ax);
	}break;
	case 3: {
		char ax[20];
		cin >> ax;
		setSurname(ax);
	}break;
	case 4: {
		int Year;
		cin >> Year;
		setYearOfBirth(Year);
	}break;
	case 5: {
		char ax[20];
		cin >> ax;
		setSpecialization(ax);
	}break;
	case 6: {
		char ax[20];
		cin >> ax;
		setOccupation(ax);
	}break;
	case 7:
	{
		char** ax;
		ax = new char* [3];
		for (int i = 0; i < 3; i++)
		{
			ax[i] = new char[20];
		}
		for (int i = 0; i < 3; i++)
			cin >> ax[i];
		setScienceWork(ax);
	}break;
	}
}