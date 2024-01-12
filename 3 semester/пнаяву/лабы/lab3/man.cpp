#include"Man.h"

char* Man:: getName() { return this->Name; };
char* Man:: getMiddleName() { return this->MiddleName; };
char* Man:: getSurname() { return this->Surname; };
int Man:: getYearOfBirth() { return this->YearOfBirth; }

void Man:: setName(const char* name) { strcpy_s(this->Name, 20, name); };
void Man:: setMiddleName(const char* middlename) { strcpy_s(this->MiddleName, 20, middlename); };
void Man:: setSurname(const char* surname) { strcpy_s(this->Surname, 20, surname); };
void Man:: setYearOfBirth(int a) { this->YearOfBirth = a; };

Man Man:: operator=(const Man& obj)
{
	this->YearOfBirth = obj.YearOfBirth;
	strcpy_s(this->Name, 20, obj.Name);
	strcpy_s(this->MiddleName, 20, obj.MiddleName);
	strcpy_s(this->Surname, 20, obj.Surname);
	return *this;
}
bool Man::operator==(const Man& obj)
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

	return true;
}

istream& operator>>(istream& is, Man& obj)
{
	rewind(stdin);
	cout << "Введите ФИО: ";
	is >> obj.Surname >> obj.MiddleName >> obj.Name;
	cout << "Введите год рождения: ";
	is >> obj.YearOfBirth;
	return is;
}

ostream& operator<<(ostream& out, Man& obj)
{
	out.setf(ios::left);
	out << setw(15) << obj.Surname << setw(15) << obj.Name << setw(15) << obj.MiddleName << setw(15) << obj.YearOfBirth;
	out.unsetf(ios::left);
	return out;
}
void Man:: HeadOfSheet()
{
	cout.setf(ios::left);
	cout << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Год рождения";
	cout.unsetf(ios::left);
}

void Man::menu() {
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
	}
}