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

bool Professor:: operator==(const Professor& obj)
{
	if (!(*((Man*)this) == (Man&)obj)) return false;
	
	if (strlen(obj.Occupation))
	{
		if (strncmp(Occupation, obj.Occupation,strlen(obj.Occupation))) return false;
	}

	if (strlen(obj.Specialization))
	{
		if (strncmp(Specialization, obj.Specialization,strlen(obj.Specialization))) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.ScienceWork[i]))
		{
			if (strncmp(ScienceWork[i], obj.ScienceWork[i],strlen(obj.ScienceWork[i])))return false;
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
	std::cout << "������� ���������: ";
	rewind(stdin);
	char* tmp = InputRussian();
	strcpy_s(obj.Occupation, LEN, tmp);

	std::cout << "������� �������������: ";
	rewind(stdin);
	tmp = InputRussian();
	strcpy_s(obj.Specialization, LEN, tmp);

	std::cout << "������� ������� ������: ";
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
	//in.clear();
	in.getline(obj.Specialization, 80, '|');
	//in.clear();
	for (int i = 0; i < 3; i++)
	{
		if(i!=0) in.ignore(1000000, '|');
		in.getline(obj.ScienceWork[i], 80, '|');
		//if(i!=2)in.clear();
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
		std::cout << "�������� �������� ��� ������" << endl << "1.�������" << endl << "2.���" << endl << "3.��������" << endl << "4.��� ��������" << endl;
		std::cout << "5.���������" << endl << "6.�������������" << endl << "7.������� ������" << endl << "8. �����" << endl;
		int a;
		a = InputInt(1, 8);
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
			this->YearOfBirth = InputInt(MIN_YEAR, MAX_YEAR);
			std::cout << endl;
			break;
		}
		case 5:
		{
			rewind(stdin);
			std::cout << "������� ���������: ";
			tmp = InputRussian();
			strcpy_s(this->Occupation, LEN, tmp);
			break;

		}
		case 6:
		{
			rewind(stdin);
			std::cout << "������� �������������: ";
			tmp = InputRussian();
			strcpy_s(this->Specialization, LEN, tmp);
			break;

		}
		case 7:
		{
			rewind(stdin);
			std::cout << "������� ������� ������: ";
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

		std::cout << "�������� ��������� ��� ������? 1 - ��, 0 - ���";

		check = InputInt(0, 1);
		std::cout << endl;

	} while (check == 1);

	return;
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
			out << setw(20)<< obj.ScienceWork[i]  << endl;
			continue;
		}
		out << setw(95) << " " << obj.ScienceWork[i] << endl;
	}
	out.unsetf(ios::left);
	return out;
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

void Professor::HeadOfSheet()
{

	std::cout.setf(ios::left);
	std::cout << setw(5) << "�" << setw(15) << "�������" << setw(15) << "���" << setw(15) << "��������" << setw(15) << "��� ��������";
	std::cout << setw(15) << "���������" << setw(15) << "�������������" << setw(20) << "������� ������" << endl;

	std::cout.unsetf(ios::left);
}
