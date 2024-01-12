#include "Man.h"

char* Man::getName() { return this->Name; };
char* Man::getMiddleName() { return this->MiddleName; };
char* Man::getSurname() { return this->Surname; };
int Man::getYearOfBirth() { return this->YearOfBirth; }

void Man::setName(const char* name) { strcpy_s(this->Name, LEN, name); };
void Man::setMiddleName(const char* middlename) { strcpy_s(this->MiddleName, LEN, middlename); };
void Man::setSurname(const char* surname) { strcpy_s(this->Surname, LEN, surname); };
void Man::setYearOfBirth(int a) { this->YearOfBirth = a; };

Man Man:: operator=(const Man& obj)
{
	strcpy_s(this->Surname, LEN, obj.Surname);
	this->YearOfBirth = obj.YearOfBirth;
	strcpy_s(this->Name, LEN, obj.Name);
	strcpy_s(this->MiddleName, LEN, obj.MiddleName);

	return *this;
}
bool Man::operator==(const Man& obj)
{

	if (strlen(obj.Name))
	{
		if (strncmp(Name, obj.Name, strlen(obj.Name))) return false;
	}

	if (strlen(obj.MiddleName))
	{
		if (strncmp(MiddleName, obj.MiddleName, strlen(obj.MiddleName))) return false;
	}

	if (strlen(obj.Surname))
	{
		if (strncmp(Surname, obj.Surname, strlen(obj.Surname)))return false;
	}

	if (obj.YearOfBirth != 0)
	{
		if (YearOfBirth != obj.YearOfBirth) return false;
	}

	return true;
}

bool Man::operator<(const Man& obj)
{

	if (strlen(obj.Name))
	{
		if (strcmp(Name, obj.Name) > 0) return false;
	}

	if (strlen(obj.MiddleName))
	{
		if (strcmp(MiddleName, obj.MiddleName) > 0) return false;
	}

	if (strlen(obj.Surname))
	{
		if (strcmp(Surname, obj.Surname) > 0)return false;
	}

	if (obj.YearOfBirth != 0)
	{
		if (YearOfBirth > obj.YearOfBirth) return false;
	}

	return true;
}
bool Man::operator>(const Man& obj)
{

	if (strlen(obj.Name))
	{
		if (strcmp(Name, obj.Name) < 0) return false;
	}

	if (strlen(obj.MiddleName))
	{
		if (strcmp(MiddleName, obj.MiddleName) < 0) return false;
	}

	if (strlen(obj.Surname))
	{
		if (strcmp(Surname, obj.Surname) < 0)return false;
	}

	if (obj.YearOfBirth != 0)
	{
		if (YearOfBirth < obj.YearOfBirth) return false;
	}

	return true;
}

fstream& operator<<(fstream& in, Man& ob)
{
	in.write(reinterpret_cast<char*> (&ob.Surname), sizeof(ob.Surname));
	in.write(reinterpret_cast<char*> (&ob.Name), sizeof(ob.Name));
	in.write(reinterpret_cast<char*> (&ob.MiddleName), sizeof(ob.MiddleName));
	in.write(reinterpret_cast<char*> (&ob.YearOfBirth), sizeof(ob.YearOfBirth));
	return in;
}

fstream& operator>>(fstream& out, Man& ob)
{
	out.read(reinterpret_cast<char*> (&ob.Surname), sizeof(ob.Surname));
	out.read(reinterpret_cast<char*> (&ob.Name), sizeof(ob.Name));
	out.read(reinterpret_cast<char*> (&ob.MiddleName), sizeof(ob.MiddleName));
	out.read(reinterpret_cast<char*> (&ob.YearOfBirth), sizeof(ob.YearOfBirth));
	return out;
}



ifstream& operator>>(ifstream& in, Man& ob)
{
	//for(int i=0;i<3;i++) 
	in.ignore(10000, '\n');
	in.getline(ob.Surname, 80, '|');
	in.clear();
	in.getline(ob.Name, 80, '|');
	in.clear();
	in.getline(ob.MiddleName, 80, '|');
	in.clear();
	in >> ob.YearOfBirth;
	return in;

}

istream& operator>>(istream& is, Man& obj)
{
	rewind(stdin);
	std::cout << "�������: ";
	char* tmp = InputRussian();
	strcpy_s(obj.Surname, LEN, tmp);
	rewind(stdin);
	std::cout << "���: ";
	tmp = InputRussian();
	strcpy_s(obj.Name, LEN, tmp);
	rewind(stdin);
	std::cout << "��������: ";
	tmp = InputRussian();
	strcpy_s(obj.MiddleName, LEN, tmp);
	rewind(stdin);
	std::cout << "������� ��� ��������: ";
	obj.YearOfBirth = InputInt(1900, 2022);
	delete tmp;
	return is;
}



ostream& operator<<(ostream& out, const Man& obj)
{
	out.setf(ios::left);
	out << setw(15) << obj.Surname << setw(15) << obj.Name << setw(15) << obj.MiddleName << setw(15) << obj.YearOfBirth;
	out.unsetf(ios::left);
	return out;
}


ofstream& operator<<(ofstream& out, Man& obj)
{
	out.setf(ios::left);
	out << setw(15) << obj.Surname << '|' << setw(15) << obj.Name << '|' << setw(15) << obj.MiddleName << '|' << setw(15) << obj.YearOfBirth << '|';
	out.unsetf(ios::left);
	return out;
}

void Man::HeadOfSheet()
{
	std::cout.setf(ios::left);
	std::cout << setw(15) << "�������" << setw(15) << "���" << setw(15) << "��������" << setw(15) << "��� ��������" << endl;
	std::cout.unsetf(ios::left);
}

void Man::Find()
{
	int check;
	char* tmp;
	do
	{
		std::cout << "�������� �������� ��� ������" << endl << "1.�������" << endl << "2.���" << endl << "3.��������" << endl << "4.��� ��������" << endl << "5.�����" << endl;

		int a;
		a = InputInt(1, 5);
		switch (a)
		{
		case 1:
		{
			rewind(stdin);
			std::cout << "������� �������: ";
			tmp = InputRussian();
			strcpy_s(this->Surname, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 2:
		{
			rewind(stdin);
			std::cout << "������� ���: ";
			tmp = InputRussian();
			strcpy_s(this->Name, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 3:
		{
			rewind(stdin);
			std::cout << "������� ��������: ";
			tmp = InputRussian();
			strcpy_s(this->MiddleName, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 4:
		{
			rewind(stdin);
			std::cout << "������� ��� ��������: ";
			this->YearOfBirth = InputInt(1900, 2022);
			std::cout << endl;
			break;
		}
		case 5:
		{
			return;
		}
		}

		std::cout << "�������� ��������� ��� ������? 1 - ��, 0- ��� : ";

		check = InputInt(0, 1);
		std::cout << endl;

	} while (check == 1);


	return;
}
