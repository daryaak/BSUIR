#include "ProfMember.h"


double ProfMember::getContributionPerMonth() { return ContributionPerMonth; }
void ProfMember::setContributionPerMonth(int temp) { this->ContributionPerMonth = temp; }

ProfMember ProfMember:: operator=(const ProfMember& obj)
{
	*((Professor*)this) = (Professor&)obj;
	*((MemberOfOrg*)this) = (MemberOfOrg&)obj;
	this->ContributionPerMonth = obj.ContributionPerMonth;
	return *this;
}

bool ProfMember:: operator==(const ProfMember& obj)
{
	if ((*((Professor*)this) == (Professor&)obj)) return false;
	if ((*((MemberOfOrg*)this) == (MemberOfOrg&)obj)) return false;

	if (obj.ContributionPerMonth != 0)
	{
		if (ContributionPerMonth != obj.ContributionPerMonth) return false;
	}
	return true;
}
bool ProfMember:: operator<(const ProfMember& obj)
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
	if (strlen(obj.Occupation))
	{
		if (strcmp(Occupation, obj.Occupation) > 0) return false;
	}

	if (strlen(obj.Specialization))
	{
		if (strcmp(Specialization, obj.Specialization) > 0) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.ScienceWork[i]))
		{
			if (strcmp(ScienceWork[i], obj.ScienceWork[i]) > 0)return false;
		}
	}
	if (strlen(obj.NameOfOrganization))
	{
		if (strcmp(NameOfOrganization, obj.NameOfOrganization) > 0)return false;
	}

	if (obj.YearOfEnter != 0)
	{
		if (YearOfEnter > obj.YearOfEnter) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.Autobiography[i]))
		{
			if (strcmp(Autobiography[i], obj.Autobiography[i]) > 0)return false;
		}
	}

	if (obj.ContributionPerMonth != 0)
	{
		if (ContributionPerMonth > obj.ContributionPerMonth) return false;
	}
	return true;
}
bool ProfMember:: operator>(const ProfMember& obj)
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
	if (strlen(obj.NameOfOrganization))
	{
		if (strcmp(NameOfOrganization, obj.NameOfOrganization) < 0)return false;
	}

	if (obj.YearOfEnter != 0)
	{
		if (YearOfEnter < obj.YearOfEnter) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.Autobiography[i]))
		{
			if (strcmp(Autobiography[i], obj.Autobiography[i]) < 0)return false;
		}
	}
	if (strlen(obj.Occupation))
	{
		if (strcmp(Occupation, obj.Occupation) < 0) return false;
	}

	if (strlen(obj.Specialization))
	{
		if (strcmp(Specialization, obj.Specialization) < 0) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.ScienceWork[i]))
		{
			if (strcmp(ScienceWork[i], obj.ScienceWork[i]) < 0)return false;
		}
	}

	if (obj.ContributionPerMonth != 0)
	{
		if (ContributionPerMonth < obj.ContributionPerMonth) return false;
	}
	return true;
}

istream& operator>>(istream& is, ProfMember& obj)
{
	rewind(stdin);
	is >> dynamic_cast<Man&>(obj);
	std::cout << "Введите должность: ";
	rewind(stdin);
	char* tmp = InputRussian();
	strcpy_s(obj.Occupation, LEN, tmp);

	std::cout << "Введите специализацию: ";
	rewind(stdin);
	tmp = InputRussian();
	strcpy_s(obj.Specialization, LEN, tmp);

	std::cout << "Введите научные работы: ";
	for (int i = 0; i < 3; i++)
	{
		rewind(stdin);
		tmp = InputRussian();
		strcpy_s(obj.ScienceWork[i], LEN, tmp);
	}
	std::cout << "Введите название организации: ";
	rewind(stdin);
	tmp = InputRussian();
	strcpy_s(obj.NameOfOrganization, LEN, tmp);
	std::cout << "Введите год вступления: ";
	rewind(stdin);
	obj.YearOfEnter = InputInt(1900, 2022);
	std::cout << "Введите автобиографию: ";
	for (int i = 0; i < 3; i++)
	{
		rewind(stdin);
		tmp = InputRussian();
		strcpy_s(obj.Autobiography[i], LEN, tmp);
	}
	delete tmp;
	cout << "Введите ежемесячный взнос: ";
	rewind(stdin);
	obj.ContributionPerMonth = InputDouble(-1, 10000);
	return is;
}

ifstream& operator>>(ifstream& in, ProfMember& obj)
{
	in >> dynamic_cast<Man&>(obj);
	in.ignore(80, '|');
	in.getline(obj.Occupation, 80, '|');
	in.clear();
	in.getline(obj.Specialization, 80, '|');
	in.clear();
	in.getline(obj.NameOfOrganization, 80, '|');
	in.clear();
	in >> obj.YearOfEnter;
	in >> obj.ContributionPerMonth;
	in.ignore(80, '|');
	for (int i = 0; i < 3; i++)
	{
		if (i != 0) in.ignore(1000000, '|');
		in.getline(obj.ScienceWork[i], 80, '|');
		//if (i != 2)in.clear();
		//if (i != 0) in.ignore(1000000, '|');
		in.getline(obj.Autobiography[i], 80, '|');
		//if (i != 2)in.clear();
	}
	in.unsetf(ios::left);
	return in;
}

fstream& operator<<(fstream& in, ProfMember& ob)
{
	in << dynamic_cast<Man&>(ob);
	in.write(reinterpret_cast<char*> (&ob.Occupation), sizeof(ob.Occupation));
	in.write(reinterpret_cast<char*> (&ob.Specialization), sizeof(ob.Specialization));
	in.write(reinterpret_cast<char*> (&ob.NameOfOrganization), sizeof(ob.NameOfOrganization));
	in.write(reinterpret_cast<char*> (&ob.YearOfEnter), sizeof(ob.YearOfEnter));
	in.write(reinterpret_cast<char*> (&ob.ContributionPerMonth), sizeof(ob.ContributionPerMonth));
	for (int i = 0; i < 3; i++)
	{
		in.write(reinterpret_cast<char*> (&ob.ScienceWork[i]), sizeof(ob.ScienceWork[i]));
		in.write(reinterpret_cast<char*> (&ob.Autobiography[i]), sizeof(ob.Autobiography[i]));
	}
	return in;
}

fstream& operator>>(fstream& out, ProfMember& ob)
{
	out >> dynamic_cast<Man&>(ob);
	out.read(reinterpret_cast<char*> (&ob.Occupation), sizeof(ob.Occupation));
	out.read(reinterpret_cast<char*> (&ob.Specialization), sizeof(ob.Specialization));
	out.read(reinterpret_cast<char*> (&ob.NameOfOrganization), sizeof(ob.NameOfOrganization));
	out.read(reinterpret_cast<char*> (&ob.YearOfEnter), sizeof(ob.YearOfEnter));
	out.read(reinterpret_cast<char*> (&ob.ContributionPerMonth), sizeof(ob.ContributionPerMonth));
	for (int i = 0; i < 3; i++)
	{
		out.read(reinterpret_cast<char*> (&ob.ScienceWork[i]), sizeof(ob.ScienceWork[i]));
		out.read(reinterpret_cast<char*> (&ob.Autobiography[i]), sizeof(ob.Autobiography[i]));
	}
	return out;
}

ostream& operator<<(ostream& out, const ProfMember& obj)
{
	out << static_cast<const Man&>(obj);
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << setw(15) << obj.Specialization;
	out << setw(15) << obj.NameOfOrganization << setw(15) << obj.YearOfEnter << setw(15) << obj.ContributionPerMonth;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.ScienceWork[i] << setw(20) << obj.Autobiography[i] << endl;
		}
		else out << setw(140) << " " << setw(20) << obj.ScienceWork[i] << setw(20) << obj.Autobiography[i] << endl;
	}
	out.unsetf(ios::left);
	return out;
}

ofstream& operator<<(ofstream& out, ProfMember& obj)
{
	out << dynamic_cast<Man&>(obj);
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << '|' << setw(15) << obj.Specialization << '|';
	out << setw(15) << obj.NameOfOrganization << '|' << setw(15) << obj.YearOfEnter << setw(15) << obj.ContributionPerMonth << '|';
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.ScienceWork[i] << '|' << setw(20) << obj.Autobiography[i] << '|' << endl;
		}
		else out << setw(142) << " " << '|' << setw(20) << obj.ScienceWork[i] << '|' << setw(20) << obj.Autobiography[i] << '|' << endl;
	}
	out.unsetf(ios::left);
	return out;
}

void ProfMember::HeadOfSheet()
{
	cout.setf(ios::left);
	cout << setw(5) << "№" << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Год рождения";
	cout << setw(15) << "Должность" << setw(15) << "Специализация";
	cout << setw(15) << "Назв.орган." << setw(15) << "Год вступления" << setw(15) << "Ежемес.вклад" << setw(15) << "Научные работы" << setw(20) << "Автобиография" << endl;
	cout.unsetf(ios::left);
}

void ProfMember::Find()
{
	int check;
	char* tmp;
	do
	{
		rewind(stdin);
		cout << "Выберите параметр" << endl << "1.Фамилия" << endl << "2.Имя" << endl << "3.Отчество" << endl << "4.Год рождения" << endl;
		cout << "5.Должность" << endl << "6.Специализация" << endl << "7.Научные работы" << endl;
		cout << "8.Название организации " << endl << "9.Год вступления" << endl << "10.Автобиография" << endl;
		cout << "11.Ежемесячный взнос " << endl << "12. Выход" << endl;
		int a;
		a = InputInt(1, 12);
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
			this->YearOfBirth = InputInt(1900, 2022);
			std::cout << endl;
			break;
		}
		case 5:
		{
			rewind(stdin);
			std::cout << "Введите должность: ";
			tmp = InputRussian();
			strcpy_s(this->Occupation, LEN, tmp);
			break;

		}
		case 6:
		{
			rewind(stdin);
			std::cout << "Введите специализацию: ";
			tmp = InputRussian();
			strcpy_s(this->Specialization, LEN, tmp);
			break;

		}
		case 7:
		{
			rewind(stdin);
			std::cout << "Введите научные работы: ";
			for (int i = 0; i < 3; i++)
			{
				rewind(stdin);
				tmp = InputRussian();
				strcpy_s(this->ScienceWork[i], LEN, tmp);
			}
			break;
		}
		case 8:
		{
			rewind(stdin);
			std::cout << "Введите название организации: ";
			tmp = InputRussian();
			strcpy_s(this->NameOfOrganization, LEN, tmp);
			cout << endl;
			break;
		}
		case 9:
		{
			std::cout << "Введите год вступления: ";
			this->YearOfEnter = InputInt(1900, 2022);
			cout << endl;
			break;
		}
		case 10:
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
		case 11:
		{
			cout << "Введите ежемесячный взнос:  ";
			this->ContributionPerMonth = InputDouble(-1, 10000);
			cout << endl;
			break;
		}
		case 12:
		{
			return;
		}
		}
		std::cout << "Добавить параметры для поиска? 1 - да, 0 - нет";

		check = InputInt(0, 1);
		std::cout << endl;
	} while (check == 1);
}
void ProfMember::Pick()
{
	
	
	
		rewind(stdin);
		cout << "Выберите параметр" << endl << "1.Фамилия" << endl << "2.Имя" << endl << "3.Отчество" << endl << "4.Год рождения" << endl;
		cout << "5.Должность" << endl << "6.Специализация" << endl << "7.Научные работы" << endl;
		cout << "8.Название организации " << endl << "9.Год вступления" << endl << "10.Автобиография" << endl;
		cout << "11.Ежемесячный взнос " << endl;
		int a;
		a = InputInt(1, 11);
		switch (a)
		{
		case 1:
		{
			strcpy_s(this->Surname, LEN, "a");
			break;
		}
		case 2:
		{
			strcpy_s(this->Name, LEN, "a");
			break;
		}
		case 3:
		{
			strcpy_s(this->MiddleName, LEN, "a");
			break;
		}
		case 4:
		{
			this->YearOfBirth = 1;
			break;
		}
		case 5:
		{
			strcpy_s(this->Occupation, LEN, "a");
			break;

		}
		case 6:
		{
			strcpy_s(this->Specialization, LEN, "a");
			break;
		}
		case 7:
		{

			for (int i = 0; i < 3; i++)
			{
				strcpy_s(this->ScienceWork[i], LEN, "a");
			}
			break;

		}
		case 8:
		{
			strcpy_s(this->NameOfOrganization, LEN, "a");
			break;
		}
		case 9:
		{
			this->YearOfEnter = 1;
			break;
		}
		case 10:
		{
			std::cout << "Введите автобиографию: ";
			for (int i = 0; i < 3; i++)
			{
				strcpy_s(this->Autobiography[i], LEN, "a");
			}
			break;
		}
		case 11:
		{
			this->ContributionPerMonth = 1;
			break;
		}
		}
		return ;
}

void ProfMember::ReplaceField(ProfMember& obj)
{
	if (strlen(this->Surname))
		strcpy_s(this->Surname, LEN, obj.Surname);
	if (strlen(this->Name))
		strcpy_s(this->Name, LEN, obj.Name);
	if (strlen(this->MiddleName))
		strcpy_s(this->MiddleName, LEN, obj.MiddleName);
	if (strlen(this->Specialization))
		strcpy_s(this->Specialization, LEN, obj.Specialization);
	if (this->YearOfBirth != 0)
		this->YearOfBirth = obj.YearOfBirth;
	if (strlen(this->Occupation))
		strcpy_s(this->Occupation, LEN, obj.Occupation);
	for (int i = 0; i < 3; i++)
	{
		if (strlen(this->ScienceWork[i]))
			strcpy_s(this->ScienceWork[i], LEN, obj.ScienceWork[i]);
	}
	if (strlen(this->NameOfOrganization))
		strcpy_s(this->NameOfOrganization, LEN, obj.NameOfOrganization);
	if (this->YearOfEnter != 0)
		this->YearOfEnter = obj.YearOfEnter;
	for (int i = 0; i < 3; i++)
	{
		if (strlen(this->Autobiography[i]))
			strcpy_s(this->Autobiography[i], LEN, obj.Autobiography[i]);
	}
}

void ProfMember::Change()
{
	int check;
	char* tmp;
	do
	{
		rewind(stdin);
		cout << "Выберите параметр для редактирования" << endl << "1.Фамилия" << endl << "2.Имя" << endl << "3.Отчество" << endl << "4.Год рождения" << endl;
		cout << "5.Должность" << endl << "6.Специализация" << endl << "7.Научные работы" << endl;
		cout << "8.Название организации " << endl << "9.Год вступления" << endl << "10.Автобиография" << endl;
		cout << "11.Ежемесячный взнос " << endl << "12. Выход" << endl;
		int a;
		a = InputInt(1, 12);
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
			this->YearOfBirth = InputInt(1900, 2022);
			std::cout << endl;
			break;
		}
		case 5:
		{
			rewind(stdin);
			std::cout << "Введите должность: ";
			tmp = InputRussian();
			strcpy_s(this->Occupation, LEN, tmp);
			break;

		}
		case 6:
		{
			rewind(stdin);
			std::cout << "Введите специализацию: ";
			tmp = InputRussian();
			strcpy_s(this->Specialization, LEN, tmp);
			break;

		}
		case 7:
		{
			rewind(stdin);
			std::cout << "Введите научные работы: ";
			for (int i = 0; i < 3; i++)
			{
				rewind(stdin);
				tmp = InputRussian();
				strcpy_s(this->ScienceWork[i], LEN, tmp);
			}
			break;
		}
		case 8:
		{
			rewind(stdin);
			std::cout << "Введите название организации: ";
			tmp = InputRussian();
			strcpy_s(this->NameOfOrganization, LEN, tmp);
			cout << endl;
			break;
		}
		case 9:
		{
			std::cout << "Введите год вступления: ";
			this->YearOfEnter = InputInt(1900, 2022);
			cout << endl;
			break;
		}
		case 10:
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
		case 11:
		{
			cout << "Введите ежемесячный взнос:  ";
			this->ContributionPerMonth = InputDouble(-1, 10000);
			cout << endl;
			break;
		}
		case 12:
		{
			return;
		}
		}
		std::cout << "Добавить параметры для поиска? 1 - да, 0 - нет";

		check = InputInt(0, 1);
		std::cout << endl;
	} while (check == 1);
}
