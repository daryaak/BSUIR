#include "Professor.h"

char* Professor::getOccupation() { return this->Occupation; }
char* Professor::getSpecialization() { return this->Specialization; }
char** Professor::getScienceWork() { return (char**)this->ScienceWork; }

void Professor::setOccupation(char* a) { strcpy_s((this->Occupation), LEN, a); }
void Professor::setSpecialization(char* a) { strcpy_s((this->Specialization), LEN, a); }
void Professor::setScienceWork(char** a)
{
	for (int i = 0; i < 3; i++)
		strcpy_s(this->ScienceWork[i], LEN, a[i]);
}
ostream& operator<<(ostream& out, const Professor& obj)
{

	out << static_cast<const Man&>(obj);
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << setw(15) << obj.Specialization;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.ScienceWork[i] << endl;
			continue;
		}
		out << setw(95) << " " << obj.ScienceWork[i] << endl;
	}
	out.unsetf(ios::left);
	return out;
}
bool Professor:: operator==(const Professor& obj)
{
	if (!(*((Man*)this) == (Man&)obj)) return false;
	if (strlen(obj.Occupation))
	{
		if (strncmp(Occupation, obj.Occupation, strlen(obj.Occupation))) return false;
	}

	if (strlen(obj.Specialization))
	{
		if (strncmp(Specialization, obj.Specialization, strlen(obj.Specialization))) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.ScienceWork[i]))
		{
			if (strncmp(ScienceWork[i], obj.ScienceWork[i], strlen(obj.ScienceWork[i])))return false;
		}
	}
	return true;
}

bool Professor:: operator<(const Professor& obj)
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
	return true;
}
bool Professor:: operator>(const Professor& obj)
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
	return true;
}

Professor Professor::operator=(const Professor& obj)
{
	*((Man*)this) = (Man&)obj;
	strcpy_s(this->Occupation, LEN, obj.Occupation);

	strcpy_s(this->Specialization, LEN, obj.Specialization);
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->ScienceWork[i], LEN, obj.ScienceWork[i]);
	}
	return *this;
}

fstream& operator<<(fstream& in, Professor& ob)
{
	in << dynamic_cast<Man&>(ob);

	in.write(reinterpret_cast<char*> (&ob.Occupation), sizeof(ob.Occupation));
	in.write(reinterpret_cast<char*> (&ob.Specialization), sizeof(ob.Specialization));
	for (int i = 0; i < 3; i++)
	{
		in.write(reinterpret_cast<char*> (&ob.ScienceWork[i]), sizeof(ob.ScienceWork[i]));
	}
	return in;
}

fstream& operator>>(fstream& out, Professor& ob)
{
	out >> dynamic_cast<Man&>(ob);
	out.read(reinterpret_cast<char*> (&ob.Occupation), sizeof(ob.Occupation));
	out.read(reinterpret_cast<char*> (&ob.Specialization), sizeof(ob.Specialization));
	for (int i = 0; i < 3; i++)
	{
		out.read(reinterpret_cast<char*> (&ob.ScienceWork[i]), sizeof(ob.ScienceWork[i]));
	}
	return out;
}

istream& operator>>(istream& is, Professor& obj)
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
	delete tmp;
	return is;
}

ifstream& operator>>(ifstream& in, Professor& obj)
{
	in >> dynamic_cast<Man&>(obj);
	in.ignore(80, '|');
	in.getline(obj.Occupation, 80, '|');
	in.clear();
	in.getline(obj.Specialization, 80, '|');
	in.clear();
	for (int i = 0; i < 3; i++)
	{
		if (i != 0) in.ignore(1000000, '|');
		in.getline(obj.ScienceWork[i], 80, '|');
		if (i != 2)in.clear();
	}
	return in;
}


void Professor::Find()
{
	Professor Temp;
	int check;
	char* tmp;
	do
	{
		std::cout << "Выберите параметр" << endl << "1.Фамилия" << endl << "2.Имя" << endl << "3.Отчество" << endl << "4.Год рождения" << endl;
		std::cout << "5.Должность" << endl << "6.Специализация" << endl << "7.Научные работы" << endl << "8. Выход" << endl;
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
			return;
		}
		}

		std::cout << "Добавить параметры для поиска? 1 - да, 0 - нет";

		check = InputInt(0, 1);
		std::cout << endl;

	} while (check == 1);

	return;
}

ofstream& operator<<(ofstream& out, Professor& obj)
{
	out << dynamic_cast<Man&>(obj);
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << '|' << setw(15) << obj.Specialization << '|';
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.ScienceWork[i] << '|' << endl;
			continue;
		}
		out << setw(95) << " " << '|' << setw(20) << obj.ScienceWork[i] << '|' << endl;
	}
	out.unsetf(ios::left);
	return out;
}




void Professor::ReplaceField(Professor& obj)
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

}

void Professor::HeadOfSheet()
{

	std::cout.setf(ios::left);
	std::cout << setw(5) << "№" << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Год рождения";
	std::cout << setw(15) << "Должность" << setw(15) << "Специализация" << setw(20) << "Научная работа" << endl;

	std::cout.unsetf(ios::left);
}

void Professor::Change()
{
	Professor Temp;
	int check;
	char* tmp;
	do
	{
		std::cout << "Выберите параметр для редактирования" << endl << "1.Фамилия" << endl << "2.Имя" << endl << "3.Отчество" << endl << "4.Год рождения" << endl;
		std::cout << "5.Должность" << endl << "6.Специализация" << endl << "7.Научные работы" << endl << "8. Выход" << endl;
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
			return;
		}
		}

		std::cout << "Добавить параметры для поиска? 1 - да, 0 - нет";

		check = InputInt(0, 1);
		std::cout << endl;

	} while (check == 1);

	return;
}
void Professor::Pick()
{
	Professor tmp;


	std::cout << "Выберите параметр" << endl << "1.Фамилия" << endl << "2.Имя" << endl << "3.Отчество" << endl << "4.Год рождения" << endl;
	std::cout << "5.Должность" << endl << "6.Специализация" << endl << "7.Научные работы" << endl;
	int a;
	a = InputInt(1, 7);
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
	}

	return;
}
