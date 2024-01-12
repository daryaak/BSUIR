#include "ProfMember.h"


int ProfMember:: getContributionPerMonth() { return ContributionPerMonth; }
void ProfMember:: setContributionPerMonth(int temp) { this->ContributionPerMonth = temp; }

ProfMember ProfMember:: operator=(ProfMember& obj)
{
	*((Professor*)this) = (Professor&)obj;
	*((MemberOfOrg*)this) = (MemberOfOrg&)obj;
	this->ContributionPerMonth = obj.ContributionPerMonth;
	return *this;
}

bool ProfMember:: operator==(const ProfMember& obj)
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

	if (obj.ContributionPerMonth)
	{
		if (ContributionPerMonth != obj.ContributionPerMonth) return false;
	}


	return true;
}

istream& operator>>(istream& is, ProfMember& obj)
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
	cout << "Введите название организации: ";
	is >> obj.NameOfOrganization;
	cout << "Введите год вступления: ";
	is >> obj.YearOfEnter;
	cout << "Введите автобиографию: ";
	for (int i = 0; i < 3; i++)
	{
		is >> obj.Autobiography[i];
	}
	cout << "Введите ежемесячный взнос: ";
	is >> obj.ContributionPerMonth;
	return is;
}

ostream& operator<<(ostream& out, ProfMember& obj)
{
	
	out << (Man&)obj;
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << setw(15) << obj.Specialization;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.ScienceWork[i] << setw(15) << obj.NameOfOrganization << setw(15) << obj.YearOfEnter << setw(20) << obj.Autobiography[i] << setw(15) << obj.ContributionPerMonth << endl;
			continue;
		}
		out << setw(90) << " " << obj.ScienceWork[i];
		out << setw(49) << " " << obj.Autobiography[i] << endl;
	}
	out.unsetf(ios::left);
	return out;
}

void ProfMember:: HeadOfSheet()
{
	
	cout.setf(ios::left);
	cout << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Год рождения";
	cout << setw(15) << "Должность" << setw(15) << "Специализация" << setw(20) << "Научная работа";
	cout << setw(15) << "Назв.орган." << setw(15) << "Год вступления" << setw(20) << "Автобиография" <<setw(20)<<"Ежемес.вклад" << endl;
	cout.unsetf(ios::left);
}

void ProfMember::menu() {
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
	}break; case 8:
	{
		char ax[20];
		cin >> ax;
		setNameOfOrganization(ax);
	}break;
	case 9:
	{
		int Year;
		cin >> Year;
		setYearOfEnter(Year);
	}break;
	case 10:
	{
		char** ax;
		ax = new char* [3];
		for (int i = 0; i < 3; i++)
		{
			ax[i] = new char[20];
		}
		for (int i = 0; i < 3; i++)
			cin >> ax[i];
		setAutobiography(ax);
	}break;
	case 11:
	{
		int a;
		cin >> a;
		setContributionPerMonth(a);
	}break;
	}
}