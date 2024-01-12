#include "MemberOfOrg.h"


char* MemberOfOrg::getNameOfOrganization() { return NameOfOrganization; }
int MemberOfOrg::getYearOfEnter() { return YearOfEnter; }
char** MemberOfOrg::getAutobiography() { return (char**)Autobiography; }

void MemberOfOrg::setNameOfOrganization(char* a) { strcpy_s(this->NameOfOrganization, LEN, a); }
void MemberOfOrg::setYearOfEnter(int a) { this->YearOfEnter = a; }
void MemberOfOrg::setAutobiography(char** a)
{
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->Autobiography[i], LEN, a[i]);
	}
}

bool MemberOfOrg:: operator==(const MemberOfOrg& obj)
{
	if (!(*((Man*)this) == (Man&)obj)) return false;
	
	if (strlen(obj.NameOfOrganization))
	{
		if (strncmp(NameOfOrganization, obj.NameOfOrganization,strlen(obj.NameOfOrganization)))return false;
	}

	if (obj.YearOfEnter != 0)
	{
		if (YearOfEnter != obj.YearOfEnter) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.Autobiography[i]))
		{
			if (strncmp(Autobiography[i], obj.Autobiography[i],strlen(obj.Autobiography[i])))return false;
		}
	}

	return true;
}

MemberOfOrg MemberOfOrg:: operator=(const MemberOfOrg& obj)
{
	*((Man*)this) = (Man&)obj;
	this->YearOfEnter = obj.YearOfEnter;
	strcpy_s(this->NameOfOrganization, LEN, obj.NameOfOrganization);
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->Autobiography[i], LEN, obj.Autobiography[i]);
	}
	return *this;
}

fstream& operator<<(fstream& in, MemberOfOrg& ob)
{
	in << dynamic_cast<Man&>(ob);
	in.write(reinterpret_cast<char*> (&ob.NameOfOrganization), sizeof(ob.NameOfOrganization));
	in.write(reinterpret_cast<char*> (&ob.YearOfEnter), sizeof(ob.YearOfEnter));
	for (int i = 0; i < 3; i++)
	{
		in.write(reinterpret_cast<char*> (&ob.Autobiography[i]), sizeof(ob.Autobiography[i]));
	}

	return in;
}

fstream& operator>>(fstream& out, MemberOfOrg& ob)
{
	out >> dynamic_cast<Man&>(ob);
	out.read(reinterpret_cast<char*> (&ob.NameOfOrganization), sizeof(ob.NameOfOrganization));
	out.read(reinterpret_cast<char*> (&ob.YearOfEnter), sizeof(ob.YearOfEnter));
	for (int i = 0; i < 3; i++)
	{
		out.read(reinterpret_cast<char*> (&ob.Autobiography[i]), sizeof(ob.Autobiography[i]));
	}
	return out;
}

istream& operator>>(istream& is, MemberOfOrg& obj)
{
	rewind(stdin);
	is >> dynamic_cast<Man&>(obj);
	std::cout << "Введите название организации: ";
	rewind(stdin);
	char* tmp = InputRussian();
	strcpy_s(obj.NameOfOrganization, LEN, tmp);
	std::cout << "Введите год вступления: ";
	rewind(stdin);
	obj.YearOfEnter = InputInt(MIN_YEAR, MAX_YEAR);
	std::cout << "Введите автобиографию: ";
	for (int i = 0; i < 3; i++)
	{
		rewind(stdin);
		tmp = InputRussian();
		strcpy_s(obj.Autobiography[i], LEN, tmp);
	}
	delete tmp;
	return is;
}
ifstream& operator>>(ifstream& in, MemberOfOrg& obj)
{
	in >> dynamic_cast<Man&>(obj);
	in.ignore(80, '|');
	in.getline(obj.NameOfOrganization, 80, '|');
	//in.clear();
	in >> obj.YearOfEnter;
	in.ignore(80, '|');
	for (int i = 0; i < 3; i++)
	{
		if (i != 0) in.ignore(1000000, '|');
		in.getline(obj.Autobiography[i], 80, '|');
		//if (i != 2)in.clear();
	}
	return in;
}
ostream& operator<<(ostream& out, const MemberOfOrg& obj)
{

	out << static_cast<const Man&>(obj);
	out.setf(ios::left);
	out << setw(20) << obj.NameOfOrganization << setw(20) << obj.YearOfEnter;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.Autobiography[i] << setw(20) << endl;
			continue;
		}
		out << setw(105) << " "  << obj.Autobiography[i] << setw(20) << endl;
	}
	out.unsetf(ios::left);
	return out;
}

ofstream& operator<<(ofstream& out, MemberOfOrg& obj)
{
	out << dynamic_cast<Man&>(obj);
	out.setf(ios::left);
	out << setw(20) << obj.NameOfOrganization << '|' << setw(20) << obj.YearOfEnter << '|';
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.Autobiography[i] << '|' << setw(20) << endl;
			continue;
		}
		out << setw(105) << " "<<"|" << obj.Autobiography[i] << '|' << setw(20) << endl;
	}
	out.unsetf(ios::left);
	return out;
}

void MemberOfOrg::HeadOfSheet()
{

	std::cout.setf(ios::left);
	std::cout << setw(5) << "№" << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Год рождения";
	std::cout << setw(15) << "Назв.орган." << setw(15) << "Год вступления" << setw(15) << "Автобиография" << endl;
	std::cout.unsetf(ios::left);
}

void MemberOfOrg::Find()
{

	int check;
	char* tmp;
	do
	{
		rewind(stdin);
		cout << "Выберите параметр для поиска" << endl << "1.Фамилия" << endl << "2.Имя" << endl << "3.Отчество" << endl << "4.Год рождения" << endl;
		cout << "5.Название организации" << endl << "6.Год вступления" << endl << "7.Автобиография" << endl << "8. Выход" << endl;
		int a;
		a = InputInt(1, 8);
		switch (a)
		{
		case 1:
		{
			rewind(stdin);
			std::cout << "Введите фамилию: ";
			tmp = InputRussian();
			strcpy_s(this->Surname, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 2:
		{
			rewind(stdin);
			std::cout << "Введите имя: ";
			tmp = InputRussian();
			strcpy_s(this->Name, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 3:
		{
			rewind(stdin);
			std::cout << "Введите отчество: ";
			tmp = InputRussian();
			strcpy_s(this->MiddleName, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 4:
		{
			rewind(stdin);
			std::cout << "Введите год рождения: ";
			this->YearOfBirth = InputInt(MIN_YEAR, MAX_YEAR);
			std::cout << endl;
			break;
		}
		case 5:
		{
			rewind(stdin);
			std::cout << "Введите название организации: ";
			tmp = InputRussian();
			strcpy_s(this->NameOfOrganization, LEN, tmp);
			cout << endl;
			break;
		}
		case 6:
		{
			std::cout << "Введите год вступления: ";
			this->YearOfEnter = InputInt(MIN_YEAR, MAX_YEAR);
			cout << endl;
			break;
		}
		case 7:
		{
			std::cout << "Введите автобиографию: ";
			for (int i = 0; i < 3; i++)
			{
				rewind(stdin);
				tmp = InputRussian();
				strcpy_s(this->Autobiography[i], LEN, tmp);
			}
			break;
		}
		case 8:
		{
			return;
		}
		}

		std::cout << "Добавить параметры для поиска? 1 - да, 0 - нет";

		check = InputInt(0, 1);
		std::cout << endl;

	} while (check == 1);

	return;
}

