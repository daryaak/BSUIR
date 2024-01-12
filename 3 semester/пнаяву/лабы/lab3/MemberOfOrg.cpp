#include "MemberOfOrg.h"

char* MemberOfOrg:: getNameOfOrganization() { return NameOfOrganization; }
int MemberOfOrg:: getYearOfEnter() { return YearOfEnter; }
char** MemberOfOrg:: getAutobiography() { return (char**)Autobiography; }

void MemberOfOrg:: setNameOfOrganization(char* a) { strcpy_s(this->NameOfOrganization, 20, a); }
void MemberOfOrg:: setYearOfEnter(int a) { this->YearOfEnter = a; }
void MemberOfOrg:: setAutobiography( char** a)
{
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->Autobiography[i], 20, a[i]);
	}
}

bool MemberOfOrg:: operator==(const MemberOfOrg& obj)
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

	if (strlen(obj.NameOfOrganization))
	{
		if (strcmp(NameOfOrganization, obj.NameOfOrganization))return false;
	}

	if (obj.YearOfEnter)
	{
		if (YearOfEnter != obj.YearOfEnter) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.Autobiography[i]))
		{
			if (strcmp(Autobiography[i], obj.Autobiography[i]))return false;
		}
	}

	return true;
}

MemberOfOrg MemberOfOrg:: operator=(const MemberOfOrg& obj)
{
	*((Man*)this) = (Man&)obj;
	this->YearOfEnter = obj.YearOfEnter;
	strcpy_s(this->NameOfOrganization, 20, obj.NameOfOrganization);
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->Autobiography[i], 20, obj.Autobiography[i]);
	}
	return *this;
}

istream& operator>>(istream& is, MemberOfOrg& obj)
{
	rewind(stdin);
	is >> (Man&)obj;
	cout << "Введите название организации: ";
	is >> obj.NameOfOrganization;
	cout << "Введите год вступления: ";
	is >> obj.YearOfEnter;
	cout << "Введите автобиографию: ";
	for (int i = 0; i < 3; i++)
	{
		is >> obj.Autobiography[i];
	}
	return is;
}

ostream& operator<<(ostream& out, MemberOfOrg& obj)
{
	
	out << (Man&)obj;
	out.setf(ios::left);
	out << setw(20) << obj.NameOfOrganization << setw(20) << obj.YearOfEnter;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.Autobiography[i] << setw(20) << endl;
			continue;
		}
		out << setw(100) << " " << obj.Autobiography[i] << setw(20) << endl;
	}
	out.unsetf(ios::left);
	return out;
}

void MemberOfOrg:: HeadOfSheet()
{
	
	cout.setf(ios::left);
	cout << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Год рождения";
	cout << setw(15) << "Назв.орган." << setw(15) << "Год вступления" << setw(15) << "Автобиография"<<endl;
	cout.unsetf(ios::left);
}

void MemberOfOrg::menu()
{
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
	case 5:
	{
		char ax[20];
		cin >> ax;
		setNameOfOrganization(ax);
	}break;
	case 6:
	{
		int Year;
		cin >> Year;
		setYearOfEnter(Year);
	}break;
	case 7:
	{
		char** ax;
		ax = new char* [3];
		for (int i = 0; i < 3; i++)
		{
			ax[i] = new char[20];
		}
		for(int i=0;i<3;i++)
		cin >> ax[i];
		setAutobiography(ax);
	}break;
	}
}